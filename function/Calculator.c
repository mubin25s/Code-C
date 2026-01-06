#include <stdio.h>

// Function declarations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main() {
    char op;
    double first, second;
    
    printf("Enter an operator (+, -, *, /): ");
    scanf("%c", &op);
    
    printf("Enter two operands: ");
    scanf("%lf %lf", &first, &second);

    switch (op) {
        case '+':
            printf("%.1lf + %.1lf = %.1lf", first, second, add(first, second));
            break;
        case '-':
            printf("%.1lf - %.1lf = %.1lf", first, second, subtract(first, second));
            break;
        case '*':
            printf("%.1lf * %.1lf = %.1lf", first, second, multiply(first, second));
            break;
        case '/':
            if (second != 0.0)
                printf("%.1lf / %.1lf = %.1lf", first, second, divide(first, second));
            else
                printf("Error! Division by zero.");
            break;
        default:
            printf("Error! operator is not correct");
    }

    return 0;
}

// Function definitions
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }
