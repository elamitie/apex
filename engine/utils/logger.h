#pragma once
#include <string>

enum LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR
};

class Logger {
public:
    // TODO: This should be able to grab the classname of the caller
    inline static void Log(const std::string& msg, LogLevel level = INFO) {
        std::string str;
        switch (level) {
        case INFO:
            str = "[APEX::CONSOLE] - INFO:     ";
            break;
        case DEBUG:
            str = "[APEX::CONSOLE] - DEBUG:    ";
            break;
        case WARNING:
            str = "[APEX::CONSOLE] - WARNING:  ";
            break;
        case ERROR:
            str = "[APEX::CONSOLE] - ERROR:    ";
            break;
        default:
            break;
        }

        str += msg;
        printf("%s\n", str.c_str());
    }

private:
    Logger() {};
    ~Logger() {}
};