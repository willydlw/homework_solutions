#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MOVE_HOME()   fputs("\x1b[H",     stdout)
#define CLEAR_LINE()  fputs("\x1b[K",     stdout)
#define RESET_COLOR() fputs("\x1b[0m",    stdout)
#define SET_RED()     fputs("\x1b[1;31m", stdout)

#define ARRAY_SIZE 15
#define MAX_BAR_HEIGHT 10 // The tallest a bar can physically be on screen

#define UPPER_VAL 20 
#define LOWER_VAL 1

void draw_vertical_bars(int arr[], int size, int active1, int active2) {
    MOVE_HOME(); // Jump to top-left to overwrite smoothly without flickering
    
    printf("=== Bubble Sort Visualizer (Vertical Buffer Overwrite) ===\n\n");
    
    // 1. Outer Loop: Scan line-by-line from the TOP down to the floor
    for (int row = MAX_BAR_HEIGHT; row > 0; row--) {
        
        // Indent the graph slightly from the left edge for clean margins
        printf("  "); 

        // 2. Inner Loop: Check every single array element for this specific row height
        for (int col = 0; col < size; col++) {
            
            // Highlight the active elements being compared/swapped
            int highlight = (col == active1 || col == active2);
            if (highlight) SET_RED();

            // Draw a block if the array value reaches or exceeds this altitude
            if (arr[col] >= row) {
                // We add a trailing space ("■ ") so the vertical bars look wider 
                // and don't clump together like a solid wall of text.
                fputs("■ ", stdout); 
            } else {
                fputs("  ", stdout); // Two spaces to match the width of "■ "
            }

            if (highlight) RESET_COLOR();
        }

        CLEAR_LINE(); // Wipe out any lingering artifacts on the far right edge
        fputs("\n", stdout);
    }

    // 3. Optional: Draw a floor baseline and text indicators below the bars
    printf("  ");
    for (int col = 0; col < size; col++) fputs("——", stdout);
    CLEAR_LINE(); fputs("\n", stdout);

    printf("  ");
    for (int col = 0; col < size; col++) printf("%02d", arr[col]);
    CLEAR_LINE(); fputs("\n", stdout);
    
    fflush(stdout); // Force the entire grid to snap onto the screen at once
}


void generate_random(int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        arr[i] = rand() % UPPER_VAL + LOWER_VAL;
    }
}


int main(void){

    int arr[10];
    size_t n = 10;
    generate_random(arr, n);
    draw_vertical_bars(arr, n, 1, 8);
    return 0;
}