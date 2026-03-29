#include <iostream>
#include <syslog.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

void make_me_a_daemon() {
    pid_t pid;

    // 1. Fork the parent process
    pid = fork();

    // If fork fails
    if (pid < 0) exit(EXIT_FAILURE);

    // If we are the parent, terminate so the child continues
    if (pid > 0) exit(EXIT_SUCCESS);

    // 2. Become the session leader (detach from terminal)
    if (setsid() < 0) exit(EXIT_FAILURE);

    // 3. Fork a second time (optional but recommended for stability)
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    // 4. Set new file permissions
    umask(0);

    // 5. Change to the root directory
    if ((chdir("/")) < 0) exit(EXIT_FAILURE);

    // 6. Close standard file descriptors (stdin, stdout, stderr)
    // A daemon has no screen to print to!
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // 7. Open the log connection
    openlog("MyDaemonService", LOG_PID, LOG_DAEMON);
}

int main() {
    make_me_a_daemon();

    syslog(LOG_NOTICE, "Daemon started successfully.");

    // The "Heartbeat" Loop
    while (true) {
        syslog(LOG_INFO, "Daemon is alive and working...");
        sleep(10); // Wait 10 seconds
    }

    closelog();
    return 0;
}
