#include "engine/logger.hpp"

void engine::log_system::init(const LogLevel threshold, const bool to_console) {
    if (to_console) {
        Core_OpenLogs(threshold);
    }
}
