#include <stdio.h>

int main() {
    char str1[100], str2[100], copyStr[100], catStr[200];
    int len1 = 0, len2 = 0, i, flag;

    printf("Enter first string: ");
    scanf("%99s", str1); 
    printf("Enter second string: ");
    scanf("%99s", str2);

    char *p = str1;
    while (*p != '\0') { len1++; p++; }
    
    p = str2;
    while (*p != '\0') { len2++; p++; }

    printf("Length of String 1: %d\n", len1);
    printf("Length of String 2: %d\n", len2);

    i = 0;
    flag = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            flag = (str1[i] > str2[i]) ? 1 : -1;
            break;
        }
        i++;
    }
    
    if (flag == 0) printf("Strings are Equal.\n");
    else if (flag > 0) printf("String 1 is Greater.\n");
    else printf("String 2 is Greater.\n");

    i = 0;
    while (str1[i] != '\0') {
        copyStr[i] = str1[i];
        i++;
    }
    copyStr[i] = '\0';
    printf("Copy of String 1: %s\n", copyStr);

    i = 0;
    int j = 0;
    while (str1[i] != '\0') {
        catStr[j] = str1[i];
        i++; j++;
    }
    i = 0;
    while (str2[i] != '\0') {
        catStr[j] = str2[i];
        i++; j++;
    }
    catStr[j] = '\0';
    printf("Concatenation: %s\n", catStr);

    return 0;
}
