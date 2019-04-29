//
// Created by Kamesh Rao Yeduvakula on 31/3/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#ifndef ROTR_LOGGER_H
#define ROTR_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/async_logger.h>

class Logger {
    std::shared_ptr<spdlog::logger> _console;
    std::shared_ptr<spdlog::logger> _file;

public:
    Logger(std::string fileNameWithPath) {
        spdlog::flush_on(spdlog::level::debug);
        spdlog::set_pattern("[%l] [%H:%M:%S %z] [%n] [pid %P] [thread %t] %v");
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_async_mode(4096);
        _file = spdlog::rotating_logger_mt("async_file_logger", fileNameWithPath, 4096, 4096);
        _console = spdlog::stdout_color_mt("console");
    }

    ~Logger() {
        spdlog::drop_all();
    }

    template<typename T>
    void info(const T& message) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->info(message); });
    }

    template<typename T>
    void error(const T& message) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->error(message); });
    }

    template<typename T>
    void debug(const T& message) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->debug(message); });
    }

    template<typename T>
    void critical(const T& message) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->critical(message); });
    }

    template<typename T>
    void warn(const T& message) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->warn(message); });
    }

    template <typename Arg1, typename... Args>
    void info(const char* fmt, const Arg1 &arg1, const Args&... args) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->info(fmt, arg1, args...); });
    }

    template <typename Arg1, typename... Args>
    void error(const char* fmt, const Arg1 &arg1, const Args&... args) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->error(fmt, arg1, args...); });
    }

    template <typename Arg1, typename... Args>
    void debug(const char* fmt, const Arg1 &arg1, const Args&... args) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->debug(fmt, arg1, args...); });
    }

    template <typename Arg1, typename... Args>
    void critical(const char* fmt, const Arg1 &arg1, const Args&... args) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->critical(fmt, arg1, args...); });
    }

    template <typename Arg1, typename... Args>
    void warn(const char* fmt, const Arg1 &arg1, const Args&... args) {
        spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->warn(fmt, arg1, args...); });
    }
};

#endif //MYCRAFT_LOGGER_H
