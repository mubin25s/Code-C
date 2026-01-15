<<<<<<< HEAD
#include <stdio.h>

int main() {
    double n1, n2, n3;

    printf("Enter three base numbers: ");
    scanf("%lf %lf %lf", &n1, &n2, &n3);

    if (n1 >= n2 && n1 >= n3)
        printf("%.2f is the largest number.", n1);
    else if (n2 >= n1 && n2 >= n3)
        printf("%.2f is the largest number.", n2);
    else
        printf("%.2f is the largest number.", n3);

    return 0;
}
=======
#include <stdio.h>

int main() {
    double n1, n2, n3;

    printf("Enter three base numbers: ");
    scanf("%lf %lf %lf", &n1, &n2, &n3);

    if (n1 >= n2 && n1 >= n3)
        printf("%.2f is the largest number.", n1);
    else if (n2 >= n1 && n2 >= n3)
        printf("%.2f is the largest number.", n2);
    else
        printf("%.2f is the largest number.", n3);

    return 0;
}
>>>>>>> d7eb2636aed7dfa5b0b36ab38f4c73756a198456
