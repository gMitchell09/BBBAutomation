#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

#include <signal.h>

bool looping = 1;

static void user_signal(int signo) {
    printf("Caught signal: %d\n", signo);
}

static void kill_app(int signo) {
    printf("Killing app with signal: %d\n", signo);
    looping = 0;
}

int main()
{
    signal(SIGUSR1, user_signal);
    signal(SIGUSR2, user_signal);
    signal(SIGKILL, kill_app);
    signal(SIGABRT, kill_app);
    signal(SIGQUIT, kill_app);
    signal(SIGTERM, kill_app);
    signal(SIGSTOP, kill_app);
    signal(SIGTSTP, kill_app);

    while (looping);
    printf("Exiting\n\n");
    return 0;
}
