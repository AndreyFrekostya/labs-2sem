#include <cassert>
#include <iostream>
#include "../src/rect/rect.hpp"  

int main() {
    Rect r1;
    r1.set_all(0, 0, 0, 0); 
    assert(r1.get_left() == 0);
    assert(r1.get_right() == 0);
    assert(r1.get_top() == 0);
    assert(r1.get_bottom() == 0);

    Rect r2(1, 2, 5, 6);
    assert(r2.get_left() == 1);
    assert(r2.get_top() == 2);
    assert(r2.get_right() == 5);
    assert(r2.get_bottom() == 6);

    r2.set_all(10, 30, 20, 40);
    assert(r2.get_left() == 10);
    assert(r2.get_top() == 30);
    assert(r2.get_right() == 20);
    assert(r2.get_bottom() == 40);

    std::cout << "Все basic тесты rect пройдены\n";

    return 0;
}