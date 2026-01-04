#include "math_operations.h"

// Add two integers
int add(int a, int b) {
    return a + b;
}

// Subtract two integers
int subtract(int a, int b) {
    return a - b;
}

// Multiply two integers
int multiply(int a, int b) {
    return a * b;
}

// Divide two integers
float divide(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    }
    return 0.0;
}
