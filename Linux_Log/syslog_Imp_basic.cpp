#include <syslog.h>   // Core syslog functions
#include <iostream>
#include <string>

int main() {
    // 1. Initialize Syslog
    // "SyslogDemo" - The name that will appear in the log file (the 'ident')
    // LOG_PID      - Includes the Process ID in each entry
    // LOG_USER     - The 'facility' (standard user-level messages)
    openlog("SyslogDemo", LOG_PID, LOG_USER);

    std::cout << "Sending messages to system logs..." << std::endl;

    // 2. Log an Informational message
    syslog(LOG_INFO, "The application has started successfully.");

    // 3. Log a Warning message
    int current_load = 85;
    syslog(LOG_WARNING, "System resources reaching threshold: %d%%", current_load);

    // 4. Log an Error message using %m
    // %m is a special syslog specifier that automatically 
    // prints the error string associated with the current 'errno'
    FILE *file = fopen("non_existent_file.txt", "r");
    if (!file) {
        syslog(LOG_ERR, "Failed to open configuration file: %m");
    }

    // 5. Close the connection
    syslog(LOG_NOTICE, "The application is shutting down.");
    closelog();

    std::cout << "Check /var/log/syslog or /var/log/messages to see the output." << std::endl;

    return 0;
}
