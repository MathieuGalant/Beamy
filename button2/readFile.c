#include <stdlib.h>
#include <stdio.h>


void readFile()
{
    int c;
    FILE *file;
    file = fopen("media/command.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
}
}
