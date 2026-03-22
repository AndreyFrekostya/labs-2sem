#pragma once
#include <iostream>
#include "../point/point.hpp"
using namespace std;

class Circle{
private:
    Point center;
    double radius;
public:
    Circle();
    Circle(double x, double y, double radius);
    Circle(const Point& c, double radius);

    ~Circle();

    const Point& get_center() const;
    
    double get_radius() const;
    double get_area() const;

    void set_center(const Point& c);
    void set_radius(double r);

    void print() const;
};

ostream& operator<<(ostream& os, const Circle& c);
istream& operator>>(istream& is, Circle& c);