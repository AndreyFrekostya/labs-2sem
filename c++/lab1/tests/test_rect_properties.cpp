#include <cassert>
#include <iostream>
#include "../src/rect/rect.hpp"

int main() {
    Rect r(2, 7, 5, 3);

    assert(r.get_width() == 3);   
    assert(r.get_height() == 4); 
    assert(r.get_square() == 12); 

    r.set_width(6);
    r.set_height(5);
    assert(r.get_width() == 6);
    assert(r.get_height() == 5);

    std::cout << "Все property тесты rect пройдены\n";
    return 0;
}
