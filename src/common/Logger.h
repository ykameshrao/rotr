//
// Created by Kamesh Rao Yeduvakula on 31/3/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#ifndef ROTR_LOGGER_H
#define ROTR_LOGGER_H

#include <iostream>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

using namespace std;

class Logger {
    unique_ptr<spdlog::logger> _logger;

public:
    Logger(string fileNameWithPath) {
        auto file = make_shared<spdlog::sinks::basic_file_sink_mt>(fileNameWithPath, true);
        file->set_level(spdlog::level::debug);
        file->set_pattern("[%l] [%H:%M:%S %z] [%n] [pid %P] [thread %t] %v");

        auto console = make_shared<spdlog::sinks::stdout_sink_mt>();
        console->set_level(spdlog::level::debug);
        console->set_pattern("[%l] [%H:%M:%S %z] [%n] [pid %P] [thread %t] %v");

        _logger = make_unique<spdlog::logger>("app_main_logger", spdlog::sinks_init_list{file, console});
    }

    ~Logger() {
        _logger.release();
    }

    template<typename T>
    void info(const T& message) {
        _logger->info(message);
    }

    template<typename T>
    void error(const T& message) {
        _logger->error(message);
    }

    template<typename T>
    void debug(const T& message) {
        _logger->debug(message);
    }

    template<typename T>
    void critical(const T& message) {
        _logger->critical(message);
    }

    template<typename T>
    void warn(const T& message) {
        _logger->warn(message);
    }

    template <typename Arg1, typename... Args>
    void info(const char* fmt, const Arg1 &arg1, const Args&... args) {
        _logger->info(fmt, arg1, args...);
    }

    template <typename Arg1, typename... Args>
    void error(const char* fmt, const Arg1 &arg1, const Args&... args) {
        _logger->error(fmt, arg1, args...);
    }

    template <typename Arg1, typename... Args>
    void debug(const char* fmt, const Arg1 &arg1, const Args&... args) {
        _logger->debug(fmt, arg1, args...);
    }

    template <typename Arg1, typename... Args>
    void critical(const char* fmt, const Arg1 &arg1, const Args&... args) {
        _logger->critical(fmt, arg1, args...);
    }

    template <typename Arg1, typename... Args>
    void warn(const char* fmt, const Arg1 &arg1, const Args&... args) {
        _logger->warn(fmt, arg1, args...);
    }
};

#endif //COMMON_LOGGER_H
