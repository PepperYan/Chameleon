/*
 * Copyright  ：SIAT 异构智能计算体系结构与系统研究中心
 * Author     ：Lele Li lilelr@163.com
 * Date       ：19-1-15
 * Description：super_master
 */

#include <super_master_related.pb.h>
#include "super_master.hpp"
namespace chameleon {
    void SuperMaster::initialize(){
        // Verify that the version of the library that we linked against is
        // compatible with the version of the headers we compiled against.
        GOOGLE_PROTOBUF_VERIFY_VERSION;

        install<MasterRegisteredMessage>(&SuperMaster::registered_master);
        install<OwnedSlavesMessage>(&SuperMaster::terminating_master);

        // change from one level to two levels
        cluster_levels = 2;
        m_uuid = UUID::random().toString();
        m_first_to_second_master = "master@172.20.110.228:6060";
        SuperMasterControlMessage* super_master_control_message = new SuperMasterControlMessage();
        super_master_control_message->set_super_master_id(m_first_to_second_master);
        super_master_control_message->set_super_master_uuid(m_uuid);
        super_master_control_message->set_passive(false);

        UPID t_master(m_first_to_second_master);
        send(t_master,*super_master_control_message);
        LOG(INFO)<<" sends a super_master_constrol_message to a master: "<< m_first_to_second_master;
        delete super_master_control_message;

    }

    void SuperMaster::registered_master(const UPID &from, const MasterRegisteredMessage &master_registered_message){
        LOG(INFO)<<"accept a mater_registered_message from "<<from;
        Future<bool> distinctive = true;
        distinctive = distinctive.then(defer(self(),&Self::is_repeated_registered,from));
        distinctive.onAny(defer(self(),&Self::record_master,lambda::_1,from,master_registered_message));

    }

    Future<bool> SuperMaster::is_repeated_registered(const UPID& upid){
        if(std::find(m_masters.begin(),m_masters.end(),upid)!=m_masters.end()){
            LOG(INFO)<<" master "<<upid<<" registered repeatedly!";

            return false;
        }
        return true;
    }

    void SuperMaster::record_master(const Future<bool>& future,const UPID &from,const MasterRegisteredMessage &master_registered_message){
        CHECK(!future.isDiscarded());
        AcceptRegisteredMessage* accept_registered = new AcceptRegisteredMessage();
        accept_registered->set_master_id(stringify(from.address.ip));

        if(!future.isReady()){
            accept_registered->set_status(AcceptRegisteredMessage_Status_FAILURE);
            send(from, *accept_registered);
            delete  accept_registered;
            LOG(ERROR)<<"Failed to record master for this super master due to "<<(future.isFailed() ? future.failure() : "future discarded");

            return;
        }
        if(!future.get()){
            accept_registered->set_status(AcceptRegisteredMessage_Status_FAILURE);
            send(from, *accept_registered);
            delete  accept_registered;
            LOG(INFO)<<" master registered repeatedly!";
            return;
        }

        m_masters.push_back(from);
        LOG(INFO)<<"record a registered master "<<from;
        accept_registered->set_status(AcceptRegisteredMessage_Status_SUCCESS);
        send(from, *accept_registered);
        delete  accept_registered;
        return;
    }

    void SuperMaster::terminating_master(const UPID& from,const OwnedSlavesMessage& message){
        LOG(INFO)<<" get an OwnedSlavesMessage from "<< from;
        LOG(INFO)<<message.slave_infos().size();

        std::copy(message.slave_infos().begin(),message.slave_infos().end(),std::back_inserter(m_admin_slaves));
        LOG(INFO)<<m_admin_slaves.size();
        for(SlaveInfo& slaveInfo: m_admin_slaves){
            LOG(INFO)<<slaveInfo.hardware_resources().cpu_collection().cpu_infos_size();
        }
        TerminatingMasterMessage* terminating_master = new TerminatingMasterMessage();
        terminating_master->set_master_id(stringify(from.address.ip));
        send(from,*terminating_master);
        delete terminating_master;
        LOG(INFO)<<" send a TerminatingMasterMessage to master "<<from<<" since the super master has receive the owned slaves of that master";
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
            process::wait(super_master.self());


    return 0;
}
