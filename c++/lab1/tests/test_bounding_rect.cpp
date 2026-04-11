#include <cassert>
#include <iostream>
#include "../src/rect/rect.hpp"

int main() {
    Rect r1(1, 5, 4, 2);
    Rect r2(2, 6, 5, 3);

    Rect r3 = bounding_rect(r1, r2);

    assert(r3.get_left() == 1);
    assert(r3.get_right() == 5);
    assert(r3.get_bottom() == 2);
    assert(r3.get_top() == 6);

    std::cout << "Все bounding тесты rect пройдены\n";
    return 0;
}
