//
// Created by ykameshrao on 03/11/20.
//

#ifndef ROTR_ROTRAPP_H
#define ROTR_ROTRAPP_H

#include <grpcpp/grpcpp.h>
#include <sstream>
#include <thread>

#include "common/Logger.h"
#include "Configuration.h"
#include "ElectionServiceImpl.h"

using namespace std;

namespace rotr {
    class RotrApp {
    private:
        unique_ptr<Configuration> _configuration;
        unique_ptr<thread> _electionServiceThread;
        unique_ptr<thread> _replicationServiceThread;
        unique_ptr<thread> _rotrServiceThread;

        void startElectionServiceThread();
        void startReplicationServiceThread();
        void startRotrServiceThread();
    public:
        RotrApp(int argc, char* argv[]);
        RotrApp(const RotrApp &) = delete;
        RotrApp &operator=(const RotrApp &) = delete;
        RotrApp(RotrApp &&) = delete;
        RotrApp &operator=(RotrApp &&) = delete;

        void startApp();
        void joinAllThreadsAndWait();
    };
}

#endif //ROTR_ROTRAPP_H
