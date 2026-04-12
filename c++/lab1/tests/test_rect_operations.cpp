#include <iostream>
#include <cassert>
#include "../src/rect/rect.hpp"

int main() {
    Rect r(1, 5, 4, 2);  

    assert(r.get_left() == 1);
    assert(r.get_bottom() == 2);
    assert(r.get_right() == 4);
    assert(r.get_top() == 5);

    r.move(2, 3);
    assert(r.get_left() == 3);
    assert(r.get_bottom() == 5);
    assert(r.get_right() == 6);
    assert(r.get_top() == 8);

    r.inflate(1);
    assert(r.get_left() == 2);
    assert(r.get_bottom() == 4);
    assert(r.get_right() == 7);
    assert(r.get_top() == 9);

    r.inflate(1, 2);
    assert(r.get_left() == 1);
    assert(r.get_bottom() == 2);
    assert(r.get_right() == 8);
    assert(r.get_top() == 11);

    r.inflate(0, 1, 2, 3);
    assert(r.get_left() == 1);
    assert(r.get_bottom() == -1);
    assert(r.get_top() == 13);
    assert(r.get_right() == 9);

    std::cout << "Все operations тесты Rect пройдены\n";
    return 0;
}