/*
 * Copyright  ：SIAT 异构智能计算体系结构与系统研究中心
 * Author     ：Lele Li lilelr@163.com
 * Date       ：19-1-15
 * Description：super_master
 */

#include <super_master_related.pb.h>
#include "super_master.hpp"
#include "master.hpp"

namespace chameleon {
    void SuperMaster::initialize() {
        // Verify that the version of the library that we linked against is
        // compatible with the version of the headers we compiled against.
        GOOGLE_PROTOBUF_VERIFY_VERSION;

        install<MasterRegisteredMessage>(&SuperMaster::registered_master);
        install<OwnedSlavesMessage>(&SuperMaster::terminating_master);
        //kill_master related
        install("KILL",&SuperMaster::owned_masters_message);
        //kill_master end
        install("MAKUN2",&SuperMaster::recevied_slave_infos);

        // change from one level to two levels
        cluster_levels = 2;
        m_masters_size = 2;
//        if(cluster_levels)
        m_uuid = UUID::random().toString();
        m_first_to_second_master = "master@172.20.110.141:6060";
        SuperMasterControlMessage *super_master_control_message = new SuperMasterControlMessage();
        super_master_control_message->set_super_master_id(m_first_to_second_master);
        super_master_control_message->set_super_master_uuid(m_uuid);
        super_master_control_message->set_passive(false);

        UPID t_master(m_first_to_second_master);
        send(t_master, *super_master_control_message);
        LOG(INFO) << " sends a super_master_constrol_message to a master: " << m_first_to_second_master;
//        delete super_master_control_message;

        route(  //change from two level to one levels
                "/kill_master",
                "kill the super_master of two levels",
                [this](Request request){
                    JSON::Object result = JSON::Object();
                    LOG(INFO) << "MAKUN KILL MASTER";
                    string new_master_ip = select_master();
                    result.values["new_master_ip"] = new_master_ip;
                    OK ok_response(stringify(result));
//                    ok_response.headers.insert({"Access-Control-Allow-Origin", "*"});
                    return ok_response;
                });


    }

    void SuperMaster::registered_master(const UPID &from, const MasterRegisteredMessage &master_registered_message) {
        LOG(INFO) << "accept a mater_registered_message from " << from;
        Future<bool> distinctive = true;
        distinctive = distinctive.then(defer(self(), &Self::is_repeated_registered, from));
        distinctive.onAny(defer(self(), &Self::record_master, lambda::_1, from, master_registered_message));

    }

    Future<bool> SuperMaster::is_repeated_registered(const UPID &upid) {
        if (std::find(m_masters.begin(), m_masters.end(), upid) != m_masters.end()) {
            LOG(INFO) << " master " << upid << " registered repeatedly!";

            return false;
        }
        return true;
    }

    void SuperMaster::record_master(const Future<bool> &future, const UPID &from,
                                    const MasterRegisteredMessage &master_registered_message) {
        CHECK(!future.isDiscarded());
        AcceptRegisteredMessage *accept_registered = new AcceptRegisteredMessage();
        accept_registered->set_master_id(stringify(from.address.ip));

        if (!future.isReady()) {
            accept_registered->set_status(AcceptRegisteredMessage_Status_FAILURE);
            send(from, *accept_registered);
            delete accept_registered;
            LOG(ERROR) << "Failed to record master for this super master due to "
                       << (future.isFailed() ? future.failure() : "future discarded");

            return;
        }
        if (!future.get()) {
            accept_registered->set_status(AcceptRegisteredMessage_Status_FAILURE);
            send(from, *accept_registered);
            delete accept_registered;
            LOG(INFO) << " master registered repeatedly!";
            return;
        }

        m_masters.push_back(from);
        LOG(INFO) << "record a registered master " << from <<" Now the size of masters is "<<m_masters.size();
        accept_registered->set_status(AcceptRegisteredMessage_Status_SUCCESS);
        send(from, *accept_registered);
        delete accept_registered;
        return;
    }

    void SuperMaster::terminating_master(const UPID &from, const OwnedSlavesMessage &message) {
        LOG(INFO) << " get an OwnedSlavesMessage from " << from;
        LOG(INFO) << "MAKUN slaveInfo size: " << message.slave_infos().size();

        std::copy(message.slave_infos().begin(), message.slave_infos().end(), std::back_inserter(m_admin_slaves));
        LOG(INFO) << "MAKUN admin slave size: " << m_admin_slaves.size();
        for (SlaveInfo &slaveInfo: m_admin_slaves) {
            LOG(INFO) << "MAKUN slaveInfo has " << slaveInfo.hardware_resources().cpu_collection().cpu_infos_size() << "CPU";
        }
        TerminatingMasterMessage *terminating_master = new TerminatingMasterMessage();
        terminating_master->set_master_id(stringify(from.address.ip));
        LOG(INFO) << "MAKUN: " << from;
        send(from, *terminating_master);
        delete terminating_master;
        LOG(INFO) << " send a TerminatingMasterMessage to master " << from
                  << " since the super master has receive the owned slaves of that master";

        // delete the terminating_master from m_masters
        auto iter = std::find(m_masters.begin(), m_masters.end(), from);
        if (iter != m_masters.end()) {
            m_masters.erase(iter);
        }

        // create new masters
        process::delay(Seconds(1), self(), &Self::create_masters);

    }

    void SuperMaster::classify_masters() {

        CHECK(m_masters.size() == 0);
        m_classification_slaves.clear();
        m_classification_masters.clear();

        // first algorithm, classification by the number of ips
        int32_t count = 1;
        int32_t cluster_size = m_admin_slaves.size() / m_masters_size;

        int32_t current_cluster_number = 0;

        string master_ip;
        for (auto iter = m_admin_slaves.begin(); iter != m_admin_slaves.end(); iter++) {
            SlaveInfo &current_slave = *iter;
            string current_ip = current_slave.hardware_resources().slave_id();
//            int32_t cpus = current_slave.hardware_resources().cpu_collection().cpu_infos_size();

            if(count > cluster_size){
                count = 1;
            }
            if (count == 1) {
                current_cluster_number++;
                if(current_cluster_number>m_masters_size){
                    SlavesInfoControlledByMaster a_slave;
                    a_slave.set_ip(current_ip);
                    a_slave.set_port("6061");
                    m_classification_slaves[master_ip].push_back(a_slave);
                    break;
                }
                master_ip = current_ip;
                m_classification_masters.push_back(master_ip);
                m_classification_slaves.insert({master_ip, vector<SlavesInfoControlledByMaster>()});
            }

            SlavesInfoControlledByMaster a_slave;
            a_slave.set_ip(current_ip);
            a_slave.set_port("6061");
            m_classification_slaves[master_ip].push_back(a_slave);
            count++;

        }

        for(auto iter = m_classification_masters.begin();iter!=m_classification_masters.end();iter++){
            vector<SlavesInfoControlledByMaster> slaves_of_master = m_classification_slaves[*iter];
            std::cout<<slaves_of_master.size()<<std::endl;
//            LOG(INFO) << slaves_of_master.size();
            for(SlavesInfoControlledByMaster s:slaves_of_master){
                std::cout<<s.ip()<<std::endl;
//                LOG(INFO) << s.ip();
            }
        }
    }

    bool SuperMaster::launch_masters() {
//        Try<Subprocess> s = subprocess(
//                "/home/lemaker/open-source/Chameleon/build/src/master/master --port=6060",
//                Subprocess::FD(STDIN_FILENO),
//                Subprocess::FD(STDOUT_FILENO),
//                Subprocess::FD(STDERR_FILENO));

        for(const string& master_ip:m_classification_masters){
            string ssh_command = "ssh "+master_ip+" /home/lemaker/open-source/Chameleon/build/src/master/master --port=6060";
            Try<Subprocess> s = subprocess(
                    ssh_command,
                    Subprocess::FD(STDIN_FILENO),
                    Subprocess::FD(STDOUT_FILENO),
                    Subprocess::FD(STDERR_FILENO));

            if (s.isError()) {
                LOG(ERROR) << " cannot launch master "<<master_ip;
                return false;
            }
        }
        LOG(INFO)<<" launched "<<m_classification_masters.size() << " masters successfully.";
        return true;
//        Try<Subprocess> s = subprocess(
//                "ssh 172.20.110.53 /home/lemaker/open-source/Chameleon/build/src/master/master --port=6060",
//                Subprocess::FD(STDIN_FILENO),
//                Subprocess::FD(STDOUT_FILENO),
//                Subprocess::FD(STDERR_FILENO));



    }

    void SuperMaster::create_masters(){
        classify_masters();
        bool launch_success = launch_masters();
        if(launch_success){
            LOG(INFO)<<" launched all new masters successfully!";
            process::delay(Seconds(3), self(), &Self::send_super_master_control_message);
        }else{
            LOG(INFO) << "launching masters failed!";
        }
    }

    void SuperMaster::send_super_master_control_message(){
        for(const string& master_ip: m_classification_masters){
            SuperMasterControlMessage *super_master_control_message = new SuperMasterControlMessage();
            super_master_control_message->set_super_master_id(master_ip);

            super_master_control_message->set_passive(true);
            for(const SlavesInfoControlledByMaster& slave_info: m_classification_slaves[master_ip]){
                SlavesInfoControlledByMaster* new_slave = super_master_control_message->add_my_slaves();
                new_slave->CopyFrom(slave_info);
            }
            string master_upid = "master@"+master_ip+":6060";
            UPID t_master(master_upid);
            send(t_master, *super_master_control_message);
            LOG(INFO) << " sends a super_master_control_message to a master: " << master_upid;
            delete super_master_control_message;
        }
    }

    //kill_master related
    void SuperMaster::owned_masters_message(const UPID& kill_master, const string& name){
        LOG(INFO) << "MAKUN RECIEVED KILL MESSAGE";
        //OwnedSlavesMessage *owned_slaves = new OwnedSlavesMessage();
        m_owned_slaves_message = new OwnedSlavesMessage();

        SlaveInfo *t_slave = m_owned_slaves_message->add_slave_infos();
        m_owned_slaves_message->set_quantity(m_owned_slaves_message->slave_infos_size());
        send(kill_master, *m_owned_slaves_message);
        //delete m_owned_slaves_message;
        LOG(INFO) << " send owned slaves of " << self() << " to kill_master " << kill_master;
    }
    //kill_master end

    const string SuperMaster::select_master(){
        string master_ip;
        int num_slaves = 0;
        for(auto iter = m_classification_masters.begin();iter!=m_classification_masters.end();iter++){
            vector<SlavesInfoControlledByMaster> slaves_of_master = m_classification_slaves[*iter];
            if(num_slaves<slaves_of_master.size()) {
                num_slaves = slaves_of_master.size();
                master_ip = *iter;
            }
        }
        LOG(INFO) << "MAKUN select master ip: " << master_ip;
        send_terminating_master(master_ip);
        return master_ip;
    }
    void SuperMaster::send_terminating_master(string master_ip) {
        //master_ip = "master@"+master_ip+":6060";
//        UPID master_upid(master_ip);
        TerminatingMasterMessage *terminating_master = new TerminatingMasterMessage();
        terminating_master->set_master_id(master_ip);
        for (auto iter = m_classification_masters.begin(); iter != m_classification_masters.end(); iter++) {
            if (*iter != master_ip) {
                *iter = "master@"+*iter+":6060";
                send(*iter, *terminating_master);
            } else {
                UPID master_upid("master@"+master_ip+":6060");
                send(master_upid,"MAKUN");
            }
        }
        LOG(INFO) << self() << " is terminating due to change levels to one";
        delete(terminating_master);
    }
    void SuperMaster::recevied_slave_infos(const UPID& from, const string& message){
        LOG(INFO) << "MAKUN received message from new master";
        terminate(self());
//        process::wait(self());
    }


}
using namespace chameleon;


int main(int argc, char **argv) {
    chameleon::set_storage_paths_of_glog("super_master");// provides the program name
    chameleon::set_flags_of_glog();

    os::setenv("LIBPROCESS_PORT", "7000");
    process::initialize("super_master");

    SuperMaster super_master;
    PID<SuperMaster> cur_super_master = process::spawn(super_master);

    LOG(INFO) << "Running super_master on " << process::address().ip << ":" << process::address().port;

    const PID<SuperMaster> super_master_pid = super_master.self();
    LOG(INFO) << super_master_pid;

//    bool res = super_master.launch_masters();
//    if (res) {
//        std::cout << " successfully launched master";
//    }
    process::wait(super_master.self());


    return 0;
}
