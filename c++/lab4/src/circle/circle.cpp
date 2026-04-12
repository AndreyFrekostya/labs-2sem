#include <iostream>
#include "circle.hpp"
#include <cmath>
using namespace std;

Circle::Circle(): center(Point()), radius(0) {};

Circle::Circle(double x, double y, double r): center(Point(x, y)), radius(r) {};

Circle::Circle(const Point& c, double r) : center(c), radius(r) {}

Circle::~Circle() = default;

bool Circle::operator==(const Circle& other) const {
    return center == other.center && radius == other.radius;
}

const Point& Circle::get_center() const { return center; }

double Circle::get_radius() const { return radius; }

double Circle::get_area() const {
    return M_PI * radius * radius;
}

void Circle::set_center(const Point& c) { center = c; }

void Circle::set_radius(double r) { radius = r; }

void Circle::print() const {
    cout << "Circle. Center: ";
    center.print();
    cout << ", Radius=" << radius << endl;
}

ostream& operator<<(ostream& os, const Circle& circle) {
    const Point& center=circle.get_center();
    os << center.get_x() << " " << center.get_y() << " " << circle.get_radius();
    return os;
}

istream& operator>>(istream& is, Circle& c) {
    double x, y, r;
    is >> x >> y >> r;
    c.set_center(Point(x, y));
    c.set_radius(r);
    return is;
}