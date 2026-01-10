#include <stdio.h>
#include <math.h>

int main() {
    int choice;
    double l, w, side, r, a, b, c, s, area, perimeter, base, height, b1, b2, h, s1, s2, adj;

    printf("=== Shape Calculator ===\n");
    printf("1. Rectangle\n");
    printf("2. Square\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");
    printf("5. Parallelogram\n");
    printf("6. Trapezoid\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) == 1) {
        switch (choice) {
            case 1:
                printf("Enter Length and Width: ");
                scanf("%lf %lf", &l, &w);
                if (l > 0 && w > 0) {
                    printf("Area: %.2lf\n", l * w);
                    printf("Perimeter: %.2lf\n", 2 * (l + w));
                } else printf("Invalid dimensions!\n");
                break;

            case 2:
                printf("Enter Side Length: ");
                scanf("%lf", &side);
                if (side > 0) {
                    printf("Area: %.2lf\n", side * side);
                    printf("Perimeter: %.2lf\n", 4 * side);
                } else printf("Invalid dimensions!\n");
                break;

            case 3:
                printf("Enter Radius: ");
                scanf("%lf", &r);
                if (r > 0) {
                    printf("Area: %.2lf\n", M_PI * r * r);
                    printf("Circumference: %.2lf\n", 2 * M_PI * r);
                } else printf("Invalid dimensions!\n");
                break;

            case 4:
                printf("Enter three sides: ");
                scanf("%lf %lf %lf", &a, &b, &c);
                if (a > 0 && b > 0 && c > 0 && (a+b>c) && (a+c>b) && (b+c>a)) {
                    s = (a + b + c) / 2;
                    area = sqrt(s * (s - a) * (s - b) * (s - c));
                    printf("Area: %.2lf\n", area);
                    printf("Perimeter: %.2lf\n", a + b + c);
                } else printf("Invalid triangle!\n");
                break;

            case 5:
                printf("Enter Base and Height: ");
                scanf("%lf %lf", &base, &height);
                printf("Enter adjacent side length for perimeter: ");
                scanf("%lf", &adj);
                if (base > 0 && height > 0 && adj > 0) {
                    printf("Area: %.2lf\n", base * height);
                    printf("Perimeter: %.2lf\n", 2 * (base + adj));
                } else printf("Invalid dimensions!\n");
                break;

            case 6:
                printf("Enter lengths of parallel sides (a and b) and height: ");
                scanf("%lf %lf %lf", &b1, &b2, &h);
                printf("Enter lengths of non-parallel sides (c and d): ");
                scanf("%lf %lf", &s1, &s2);
                
                if (b1 > 0 && b2 > 0 && h > 0 && s1 > 0 && s2 > 0) {
                    printf("Area: %.2lf\n", 0.5 * (b1 + b2) * h);
                    printf("Perimeter: %.2lf\n", b1 + b2 + s1 + s2);
                } else printf("Invalid dimensions!\n");
                break;

            default: 
                printf("Invalid choice!\n");
        }
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}
