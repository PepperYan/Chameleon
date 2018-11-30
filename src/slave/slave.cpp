/*
 * Copyright  ：SIAT 异构智能计算体系结构与系统研究中心
 * Author     ：Lele Li lilelr@163.com
 * Date       ：18-11-26
 * Description：slave codes
 */

#include "slave.hpp"
using namespace chameleon;

int main(){
    os::setenv("LIBPROCESS_PORT", stringify(5051));
    process::initialize("slave");

    Slave slave;
    PID<Slave> cur_slave = process::spawn(slave);
    cout << "Running slave on " << process::address().ip << ":" << process::address().port << endl;
    cout << "PID" << endl;

    const PID<Slave> slave_pid = slave.self();
    cout << slave_pid << endl;
    process::wait(slave.self());
    return 0;
}