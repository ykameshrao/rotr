#include <iostream>
#include <grpcpp/grpcpp.h>
#include <sstream>
#include <thread>

#include "src/common/Logger.h"
#include "src/common/Container.h"
#include "src/RotrApp.h"

using namespace std;
using namespace rotr;
using namespace rotr::common;

int main(int argc, char* argv[]) {
    Container::I().logger = make_shared<Logger>("/tmp/rotr-svc-logs/rotr.log");
    auto logger = Container::I().logger;

    logger->info("\n\n            __ _                   _   _                           _        \n"
                 "           / _| |                 | | | |                         | |       \n"
                 " _ __ __ _| |_| |_    ___  _ __   | |_| |__   ___   _ __ ___   ___| | _____ \n"
                 "| '__/ _` |  _| __|  / _ \\| '_ \\  | __| '_ \\ / _ \\ | '__/ _ \\ / __| |/ / __|\n"
                 "| | | (_| | | | |_  | (_) | | | | | |_| | | |  __/ | | | (_) | (__|   <\\__ \\\n"
                 "|_|  \\__,_|_|  \\__|  \\___/|_| |_|  \\__|_| |_|\\___| |_|  \\___/ \\___|_|\\_\\___/\n"
                 "                                                                            \n"
                 "                                                                            ");

    // Command Line Params: --node-id rotr.1 --config-path <path-to-config>/server.yaml
    unique_ptr<RotrApp> rotrApp = make_unique<RotrApp>(argc, argv);
    rotrApp->startApp();
    rotrApp->joinAllThreadsAndWait();

    return 0;
}
