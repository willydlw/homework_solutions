#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <locale.h> 

#define MAX_VAL 10 
#define MIN_VAL 1

#define SHOW_CURSOR() fputs("\x1b[?25h", stdout)

// 1. Standard cleanup function for atexit
void normal_cleanup(void) {
    SHOW_CURSOR();
    fflush(stdout);
}

// 2. Normal signals just pass through to exit(), triggering atexit
void handle_normal_signals(int sig) {
    (void)sig; 
    exit(0); 
}

// 3. Crash signals force immediate cursor recovery before dying
void handle_crash_signals(int sig) {
    SHOW_CURSOR();
    fflush(stdout);
    
    // Reset to default and re-raise so the OS handles the crash correctly
    signal(sig, SIG_DFL);
    raise(sig);
}


void clear_screen() {
    // \033[H  - Moves cursor to home (top-left)
    // \033[2J - Clears visible screen
    // \033[3J - Wipes the scrollback history buffer
    printf("\033[H\033[2J\033[3J");
    fflush(stdout); // Force immediate rendering
}

void generate_random(int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        arr[i] = rand() % MAX_VAL + MIN_VAL;
    }
}

void draw_bars(int *arr, size_t n) {
    printf("\033[H"); // Reset cursor to top-left without wiping text
    
    for (size_t i = 0; i < n; i++) {
        // Draw a horizontal bar proportional to the value
        for (int j = 0; j < arr[i]; j++) {
            // Unicode full block character U+2588
            // UTF-8 0xE2 0x96 0x88
            //printf("█"); 
            printf("\xE2\x96\x88"); // Prints exactly: █
        }
        // Clear any leftover characters to the right of the bar
        printf("\033[K\n"); 
    }
    fflush(stdout);
}


int main(void) {
    // Register the automatic cleanup net
    atexit(normal_cleanup);

    // Route standard exit requests to exit()
    signal(SIGINT,  handle_normal_signals); // Ctrl+C
    signal(SIGTERM, handle_normal_signals); // Termination request
    
    // Route fatal memory crashes to the emergency handler
    signal(SIGSEGV, handle_crash_signals);  // Segfault
    signal(SIGBUS,  handle_crash_signals);  // Bus error

    // Enables the terminal's native UTF-8 support
    setlocale(LC_ALL, ""); 

    // Main logic loop goes here...
    int arr[10];
    size_t n = sizeof(arr) / sizeof(arr[0]);
    generate_random(arr, n);

    clear_screen();
    draw_bars(arr, n);
    sleep(3);
    clear_screen();


    return 0; // Automatically calls normal_cleanup() via atexit
}
