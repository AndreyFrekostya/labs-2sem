#pragma once

class Point{
private:
    double x;
    double y;
public:
    Point();
    Point(double x, double y);
    ~Point();

    double get_x() const;
    double get_y() const;

    void set_x(double x);
    void set_y(double y);

    void print() const;
};