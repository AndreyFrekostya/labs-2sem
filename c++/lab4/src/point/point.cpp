#include <iostream>
#include "point.hpp"
using namespace std;

Point::Point(): x(0), y(0) {};

Point::Point(double _x, double _y): x(_x), y(_y) {};

Point::~Point() = default;

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

double Point::get_x() const { return x; }
double Point::get_y() const { return y; }

void Point::set_x(double val) { x = val; }
void Point::set_y(double val) { y = val; }

void Point::print() const {
    cout << "Точка (x=" << x << ", y=" << y << ")";
};