#include <stdio.h>
#include <syslog.h>

int main()
{

    openlog("MyProgram", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "Hello 1 from syslog\n");
    printf("Print\n");
    syslog(LOG_INFO, "Hello 2 from syslog\n");
    closelog();

    return 0;
}