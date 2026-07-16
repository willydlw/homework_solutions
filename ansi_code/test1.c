#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// ANSI Control Macros

/** Anatomy of Hide/Show Cursor Commands
 *  Escape Character \x1b signals the terminal that a control sequence is starting.
 *      Notes: 
 *        1) The backslash character '\' in C indicates the start of an escape sequence 
 *        2) ASCII ESC character is x1b (hexadecimal) or 033 (octal) or 27 decimal
 *  Control Sequence Introducer (CSI) [
 *      Combined with the escape character (ESC [), this tells the terminal to look for a multi-character command sequence.
 * 
 *  Private Mode Flag ? indicates a non-standard, vendor specific extension
 *      Tells the terminal to interpret as a mode settings toggle
 * 
 *  Parameter ID 25 
 *      The specific ID assigned to the text cursor visibility state.
 *  
 *  Reset Mode Low - lowercase 'L' turns off the specified feature. 
 *  Set Mode High - 'h' turns on the specified feature.
 */

#define HIDE_CURSOR() fputs("\x1b[?25l", stdout)
#define SHOW_CURSOR() fputs("\x1b[?25h", stdout)
#define CLEAR_SCREEN() fputs("\x1b[2J", stdout)
#define MOVE_HOME() fputs("\x1b[H", stdout)

// Restores terminal state before the application exits
void cleanup(void) {
    SHOW_CURSOR();
    fflush(stdout);
}

// Handles user interruptions (like Ctrl+C) to prevent leaving the cursor hidden
void handle_signal(int sig) {
    (void)sig; // Avoid unused parameter warning
    exit(0);   // Triggers the atexit cleanup function
}

int main(void) {
    // 1. Register cleanup triggers
    atexit(cleanup);
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // 2. Setup the screen
    CLEAR_SCREEN();
    MOVE_HOME();
    HIDE_CURSOR();
    fflush(stdout);

    // 3. Simple animation loop
    for (int i = 0; i < 5; i++) {
        MOVE_HOME();
        printf("Running animation frame: %d\n", i);
        printf("Notice that the blinking cursor is invisible.\n");
        fflush(stdout);
        sleep(1);
    }

    return 0; // Exiting automatically calls cleanup() via atexit
}
