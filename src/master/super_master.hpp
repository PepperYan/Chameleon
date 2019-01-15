/*
 * Copyright  ：SIAT 异构智能计算体系结构与系统研究中心
 * Author     ：Lele Li lilelr@163.com
 * Date       ：19-1-15
 * Description：super_master
 */

#ifndef CHAMELEON_SUPER_MASTER_HPP
#define CHAMELEON_SUPER_MASTER_HPP
// C++ 11 dependencies
#include <vector>
#include <set>

# google
#include <glog/logging.h>
#include <gflags/gflags.h>

// stout dependencies
#include <stout/gtest.hpp>
#include <stout/json.hpp>
#include <stout/jsonify.hpp>
#include <stout/protobuf.hpp>

// libprocess dependencies
#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>
#include <process/delay.hpp>

// chameleon headers
#include <configuration_glog.hpp>

using std::string;
using std::set;
using std::vector;

using os::Process;
using os::ProcessTree;

using process::UPID;
using process::PID;
using process::Future;
using process::Promise;

namespace chameleon {

    class SuperMaster :public ProtobufProcess<SuperMaster>{

    };

}


#endif //CHAMELEON_SUPER_MASTER_HPP