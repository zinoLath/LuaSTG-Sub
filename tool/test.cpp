﻿#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/sinks/wincolor_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

int main(int argc, char** argv) {
    auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(L"main.log", true);
    auto logger = std::make_shared<spdlog::logger>("global logger", sink);
    logger->set_level(spdlog::level::trace);
    logger->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%L] [%n]%$ %v");
    logger->flush_on(spdlog::level::info);
    
    spdlog::set_default_logger(logger);
    
    spdlog::trace(u8"你");
    spdlog::debug(u8"好吗");
    spdlog::info(u8"我");
    spdlog::warn(u8"很好");
    spdlog::error(u8"他");
    spdlog::critical(u8"更好");
    spdlog::info(u8"Hello spdlog!");
    
    spdlog::get("global logger")->warn(u8"危险");
    
    spdlog::drop_all();
    spdlog::shutdown();
    
    return 0;
}
