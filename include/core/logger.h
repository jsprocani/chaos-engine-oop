#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#ifndef NAMESPACE
#define NAMESPACE "CORE"
#endif

#ifndef MODULE_NAME
#define MODULE_NAME "UNKNOWN"
#endif

#define CORE_INFO(...) Core_Log(LOG_INFO, NAMESPACE, MODULE_NAME, __VA_ARGS__)
#define CORE_OK(...) Core_Log(LOG_OK, NAMESPACE, MODULE_NAME, __VA_ARGS__)
#define CORE_WARN(...) Core_Log(LOG_WARN, NAMESPACE, MODULE_NAME, __VA_ARGS__)
#define CORE_ERROR(...) Core_Log(LOG_ERROR, NAMESPACE, MODULE_NAME, __VA_ARGS__)

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"

typedef enum {
    LOG_INFO,
    LOG_OK,
    LOG_WARN,
    LOG_ERROR,
    LOG_NONE
} LogLevel;

#ifdef __cplusplus
extern "C" {
#endif

void Core_OpenLogs(LogLevel threshold);
void Core_Log(LogLevel level, const char *ns, const char *module, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif //CORE_LOGGER_H