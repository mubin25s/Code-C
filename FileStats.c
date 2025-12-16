#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char filename[100];
    char ch;
    int characters = 0, words = 0, lines = 0, inWord = 0;

    printf("Enter filename to read: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("\nUnable to open file '%s'.\n", filename);
        printf("Create dummy content in '%s'? (y/n): ", filename);
        char ans;
        scanf(" %c", &ans);
        if (ans == 'y' || ans == 'Y') {
             fp = fopen(filename, "w");
             if(fp) {
                 fprintf(fp, "Hello World\nThis is a test file.\nProgramming in C is fun.");
                 fclose(fp);
                 printf("File created. Re-opening for reading...\n");
                 fp = fopen(filename, "r");
             }
        }
    }

    if (fp == NULL) {
         printf("Could not access file. Exiting.\n");
         return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        characters++;

        if (ch == '\n' || ch == '\0')
            lines++;

        if (isspace(ch)) {
            inWord = 0;
        } else if (inWord == 0) {
            inWord = 1;
            words++;
        }
    }

    if (characters > 0 && ch != '\n') { 
        lines++; 
    }

    printf("\n");
    printf("Total Characters: %d\n", characters);
    printf("Total Words     : %d\n", words);
    printf("Total Lines     : %d\n", lines);

    fclose(fp);
    return 0;
}
