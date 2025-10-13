#pragma once 

#include <stdio.h>

/* ANSI Escape Codes for Colors and Styles

    Standard way to add color and styling to text output 
    in terminal applications.

    Codes are sequences of characters that 
        - begin with escape character (\x1b or \033)
        - followed by a square bracket, a numerical sequence, and a letter, usually 'm'.
        - [ is control sequence introducer (CSI)

    ASCII escape code \x1b, octal \033, \u001b in Unicode
*/


// Text Styles
#define RESET          "\x1b[0m"        // resets all attributes (returns to default)
#define BOLD           "\x1b[1m" 
#define UNDERLINED     "\x1b[4m" 
#define BLINKING       "\x1b[5m"        // (may not be supported by all terminals)
#define INVERSE        "\x1b[7m"        // swaps foreground and background colors 

// Foreground Text Colors 
#define FBLACK         "\x1b[30m" 
#define FRED           "\x1b[31m" 
#define FGREEN         "\x1b[32m" 
#define FYELLOW        "\x1b[33m" 
#define FBLUE          "\x1b[34m" 
#define FMAGENTA       "\x1b[35m" 
#define FCYAN          "\x1b[36m" 
#define FWHITE         "\x1b[37m" 

// Background Colors 
#define BBLACK         "\x1b[40m" 
#define BRED           "\x1b[41m" 
#define BGREEN         "\x1b[42m" 
#define BYELLOW        "\x1b[43m" 
#define BBLUE          "\x1b[44m" 
#define BMAGENTA       "\x1b[45m" 
#define BCYAN          "\x1b[46m" 
#define BWHITE         "\x1b[47m" 


// 256 Color Mode 
// Replace the <n> with a number from 0 to 255
#define FCOLOR_MODE_256   "\x1b[38;5<n>m"
#define BCOLOR_MODE_256   "\x1b[38;5<n>m"

// True Color (24-bit RGB)
// Replace the <r> <g> <b> with values from 0 to 255
#define FCOLOR_MODE_RGB   "\x1b[38;2;<r>;<g>;<b>m"
#define BCOLOR_MODE_RGB   "\x1b[48;2;<r>;<g>;<b>m"


/* Clear Screen 
   \x1b[2J           2J Erase in Display Command 
   \x1b[H            H moves cursor to home position
*/

#define clear_screen()  puts("\x1b[2J\x1b[H")


/*  Cursor Movement 

    \x1b[<L>;<C>H  move to position 
    \x1b[<N>A       move cursor up N lines
    \x1b[<N>B       move cursor down N lines
    \x1b[<N>C       move cursor forward(right) N colums
    \x1b[<N>D       move cursor backward(left) N columns
*/

#define move_cursor(x, y)       printf("\x1b[%d;%dH", (y), (x))
#define move_cursor_up(n)       printf("\x1b[%dA", (n))
#define move_cursor_down(n)     printf("\x1b[%dB", (n))
#define move_cursor_right(n)    printf("\x1b[%dC", (n))
#define move_cursor_left(n)     printf("\x1b[%dD", (n))

// move cursor to the beginning of the next line, n lines down
#define move_cursor_start_next_line_down(n) printf("\x1b[%dE", (n))

// move cursor to the beginning of the previous line, n lines up
#define move_cursor_start_prev_line_down(n) printf("\x1b[%dF", (n))

// move cursor to colum N in the current line 
#define move_cursor_right_same_line(n) printf("\x1b[%dG", (n))