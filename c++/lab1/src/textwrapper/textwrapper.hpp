#include "../mystring/mystring.hpp"

class TextWrapper {
private:
    MyString text;      
    int line_width;      

    void print_border(char edge) const;                      
    void print_line(const char* start, int length, bool first_line, bool last_line) const;

public:
    TextWrapper(const MyString& input, int width);
    ~TextWrapper();

    void print_wrapped() const;
};