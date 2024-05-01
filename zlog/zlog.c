#include <stdio.h>
#include <zlog.h>
#include <syslog.h>

zlog_category_t *c;

void constructor() __attribute__((constructor));

void constructor() {
    int rc;

    rc = zlog_init("/workspaces/debian/config/zlog.conf");

    if (rc) {
        printf("Failed to initialize zlog\n");
    }

    c = zlog_get_category("logger");
    if (!c) {
    printf("get cat fail\n");
    zlog_fini();
    }

    zlog_info(c, "zlog initialized");
}

void destructor() __attribute__((destructor));

void destructor() {
    zlog_info(c, "finishing zlog");
    zlog_fini();
}


void syslog(int priority, const char *format, ...)
{
    if (priority == LOG_INFO){
        zlog_info(c, format);
    }
    else if (priority == LOG_ERR){
        zlog_error(c, format);
    }
    else if (priority == LOG_DEBUG){
        zlog_debug(c, format);
    }
    else if (priority == LOG_WARNING){
        zlog_warn(c, format);
    }
    else if (priority == LOG_CRIT){
        zlog_fatal(c, format);
    }
    else if (priority == LOG_NOTICE){
        zlog_notice(c, format);
    }
    else {
        zlog_info(c, format);
    }

}