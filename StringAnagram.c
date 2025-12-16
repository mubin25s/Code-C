#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str1[100], str2[100];
    char temp;
    int i, j;
    int n1, n2;
    int isAnagram = 1;

    printf("Enter first string: ");
    scanf("%99s", str1);
    printf("Enter second string: ");
    scanf("%99s", str2);

    for(n1 = 0; str1[n1] != '\0'; ++n1);
    for(n2 = 0; str2[n2] != '\0'; ++n2);

    if (n1 != n2) {
        isAnagram = 0;
    } else {
        for(i = 0; i < n1; i++) str1[i] = tolower(str1[i]);
        for(i = 0; i < n2; i++) str2[i] = tolower(str2[i]);

        for (i = 0; i < n1-1; i++) {
            for (j = i+1; j < n1; j++) {
                if (str1[i] > str1[j]) {
                    temp = str1[i];
                    str1[i] = str1[j];
                    str1[j] = temp;
                }
            }
        }

        for (i = 0; i < n2-1; i++) {
            for (j = i+1; j < n2; j++) {
                if (str2[i] > str2[j]) {
                    temp = str2[i];
                    str2[i] = str2[j];
                    str2[j] = temp;
                }
            }
        }

        for (i = 0; i < n1; i++) {
            if (str1[i] != str2[i]) {
                isAnagram = 0;
                break;
            }
        }
    }

    if (isAnagram) {
        printf("The strings are anagrams.\n");
    } else {
        printf("The strings are NOT anagrams.\n");
    }

    return 0;
}
