#ifndef ENGINE_LOGGER_HPP
#define ENGINE_LOGGER_HPP

#include "core/logger.h"
#include <filesystem>

namespace engine {
    struct log_system {
        static void init(LogLevel threshold, bool to_console);
    };
    class logger {
        std::string ns;
        std::string module;
    public:
        explicit logger(std::string module_name, std::string namespace_name = "ENGINE")
            : ns(std::move(namespace_name)), module(std::move(module_name)) {}
        template <typename... Args>
        void info(const char* fmt, Args... args) const {
            Core_Log(LOG_INFO, ns.c_str(), module.c_str(), fmt, args...);
        }
        template <typename... Args>
        void ok(const char* fmt, Args... args) const {
            Core_Log(LOG_OK, ns.c_str(), module.c_str(), fmt, args...);
        }
        template <typename... Args>
        void warn(const char* fmt, Args... args) const {
            Core_Log(LOG_WARN, ns.c_str(), module.c_str(), fmt, args...);
        }
        template <typename... Args>
        void error(const char* fmt, Args... args) const {
            Core_Log(LOG_ERROR, ns.c_str(), module.c_str(), fmt, args...);
        }
    };
}

#endif //ENGINE_LOGGER_HPP