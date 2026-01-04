#include "geometry_utils.h"

// Calculate area of a rectangle
int rectangle_area(int length, int width) {
    return length * width;
}

// Calculate perimeter of a rectangle
int rectangle_perimeter(int length, int width) {
    return 2 * (length + width);
}

// Calculate area of a square
int square_area(int side) {
    return side * side;
}

// Calculate approximate area of a triangle (integer division)
int triangle_area_approx(int base, int height) {
    // Uses integer arithmetic, so precision is lost
    return (base * height) / 2;
}
