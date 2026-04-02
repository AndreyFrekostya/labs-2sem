#include <iostream>
#include "rect.hpp"
using namespace std;

Rect::Rect() {
    cout << "Конструктор по умолчанию " << this << endl;
    // left=0;
    // top=0;
    // right=0;
    // bottom=0;

    x=0;
    y=0;
    width=0;
    height=0;
    
}
Rect::Rect(int l, int t, int r, int b) {
    cout << "Конструктор " << this << endl;
    // left=l;
    // top=t;
    // right=r;
    // bottom=b;  

    x = l;
    y = b;
    width  = r - l;
    height = t - b;
}

Rect::Rect(const Rect& other) {
    cout << "Конструктор копирования " << this << endl;
    // left=other.left;
    // top=other.top;
    // right=other.right;
    // bottom=other.bottom;  

    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
}

int Rect::get_left() const { return x; }
int Rect::get_right() const { return x + width; }
int Rect::get_bottom() const { return y; }
int Rect::get_top() const { return y + height; }

void Rect::set_all(int l, int t, int r, int b) {
    // left = l;
    // right = r;
    // top = t;
    // bottom = b;

    x = l;
    y = b;
    width  = r - l;
    height = t - b;
}

void Rect::inflate(int amount) {
    // left -= amount;
    // right += amount;
    // top -= amount;
    // bottom += amount;

    x -= amount;
    width += 2*amount;
    y -= amount;
    height += 2*amount;
}

void Rect::inflate(int dw, int dh) {
    // left -= dw;
    // right += dw;
    // top -= dh;
    // bottom += dh;

    x -= dw;
    width += 2*dw;
    y -= dh;
    height += 2*dh;
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    // left -= d_left;
    // right += d_right;
    // top -= d_top;
    // bottom += d_bottom;

    x -= d_left;
    width += d_left + d_right;
    y -= d_bottom;
    height += d_bottom + d_top;
}

void Rect::move(int dx, int dy) {
    // left += dx;
    // right += dx;
    // top += dy;
    // bottom += dy;

    x += dx;
    y += dy;
}

Rect::~Rect() {
    cout << "Деструктор " << this << endl;
}

int Rect::get_width() const { return width; }
int Rect::get_height() const { return height; }
int Rect::get_square() const { return width * height; }

void Rect::set_width(int w) { width = w; }
void Rect::set_height(int h) { height = h; }

Rect bounding_rect(Rect r1, Rect r2) {
    int left = min(r1.get_left(), r2.get_left());
    int right = max(r1.get_right(), r2.get_right());
    int bottom = min(r1.get_bottom(), r2.get_bottom());
    int top = max(r1.get_top(), r2.get_top());

    return Rect(left, top, right, bottom);
}

void print_rect(const Rect &r) {
    cout << "Прямоугольник: "
         << r.get_left() << ", " << r.get_right() << ", "
         << r.get_top() << ", " << r.get_bottom() << endl;
}