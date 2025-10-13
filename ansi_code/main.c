#include "terminalColors.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("%s", BRED);
    clear_screen();
    sleep(1);
    printf("%sHello%s\n", FYELLOW, RESET);
    sleep(1);
    clear_screen();
    return 0;
}