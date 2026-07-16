#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Screen Buffer Controls
#define ENTER_ALT_SCREEN() fputs("\x1b[?1049h", stdout)
#define EXIT_ALT_SCREEN()  fputs("\x1b[?1049l", stdout)

// Cursor Controls
#define HIDE_CURSOR()      fputs("\x1b[?25l",  stdout)
#define SHOW_CURSOR()      fputs("\x1b[?25h",  stdout)
#define MOVE_HOME()        fputs("\x1b[H",     stdout)

// 1. Clean exit handler via atexit
void normal_cleanup(void) {
    SHOW_CURSOR();
    EXIT_ALT_SCREEN(); // Wipes our app window and brings back bash history
    fflush(stdout);
}

// 2. Route standard interruptions to exit()
void handle_normal_signals(int sig) {
    (void)sig;
    exit(0);
}

// 3. Emergency crash handler
void handle_crash_signals(int sig) {
    SHOW_CURSOR();
    EXIT_ALT_SCREEN(); // Ensure terminal isn't stuck in alt mode on crash
    fflush(stdout);
    
    signal(sig, SIG_DFL);
    raise(sig);
}

int main(void) {
    // Register terminal rescue configurations
    atexit(normal_cleanup);
    signal(SIGINT,  handle_normal_signals);
    signal(SIGTERM, handle_normal_signals);
    signal(SIGSEGV, handle_crash_signals);
    signal(SIGBUS,  handle_crash_signals);

    // Initialize our private fullscreen app state
    ENTER_ALT_SCREEN();
    HIDE_CURSOR();
    MOVE_HOME();
    fflush(stdout);

    // App Logic Window
    printf("--- Welcome to My Fullscreen Application ---\n");
    printf("Notice that your previous terminal history is gone!\n");
    printf("Sleeping for 4 seconds before self-destructing...\n");
    fflush(stdout);
    
    sleep(4);

    return 0; // exit() executes, calling normal_cleanup
}
