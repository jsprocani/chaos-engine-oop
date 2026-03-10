#define MODULE_NAME "LOGGER"
#include "core/logger.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

static struct {
    LogLevel threshold;
    bool use_colors;
} s_log_state = { LOG_INFO, false };

void Core_OpenLogs(const LogLevel threshold) {
    s_log_state.threshold = threshold;
    s_log_state.use_colors = true;
}

void Core_Log(const LogLevel level, const char *ns, const char *module, const char *fmt, ...) {
    if (level < s_log_state.threshold) return;
    const time_t now = time(NULL);
    const struct tm *t = localtime(&now);
    char timebuf[9];
    strftime(timebuf, sizeof(timebuf), "%H:%M:%S", t);
    const char *color = "";
    const char *tag = "[INFO]";
    switch (level) {
        case LOG_INFO: color = s_log_state.use_colors ? COLOR_CYAN : ""; tag = "[INFO]"; break;
        case LOG_OK: color = s_log_state.use_colors ? COLOR_GREEN : ""; tag = "[ OK ]"; break;
        case LOG_WARN: color = s_log_state.use_colors ? COLOR_YELLOW : ""; tag = "[WARN]"; break;
        case LOG_ERROR:color = s_log_state.use_colors ? COLOR_RED : ""; tag = "[ERR!]"; break;
        default: break;
    }
    char msg_buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_buf, sizeof(msg_buf), fmt, args);
    va_end(args);
    const char *reset = s_log_state.use_colors ? COLOR_RESET : "";
    fprintf(stdout, "%s[%s] %s %6s::%-6s : %s%s\n", color, timebuf, tag, ns, module, msg_buf, reset);
}