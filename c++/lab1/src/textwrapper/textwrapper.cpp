#include <iostream>
#include <string>
#include "../mystring/mystring.hpp"
#include "textwrapper.hpp"

using namespace std;

void TextWrapper::print_border(char edge) const {
    cout << " " << string(line_width + 2, edge) << " \n";
}

void TextWrapper::print_line(const char* start, int length, bool first_line, bool last_line) const {
    if (first_line) cout << "/ ";
    else cout << "\\ ";

    int i = 0;
    for (; i < length; i++) cout << start[i];

    for (; i < line_width; i++) cout << " ";

    if (last_line) cout << " /" << endl;
    else cout << " \\" << endl;
}


TextWrapper::TextWrapper(const MyString& input, int width) {
    text = input;
    line_width = width;
}

TextWrapper::~TextWrapper(){
    cout << "Деструктор TextWrapper" << endl;
}

void TextWrapper::print_wrapped() const {
    int text_len = text.get_size();  
    int line_start = 0;
    int last_space = -1;

    print_border('-');

    while (line_start < text_len) {
        int line_end = line_start;
        int current_length = 0;

        // ищем конец строки или ближайший пробел
        while (line_end < text_len && current_length < line_width) {
            if (text.get(line_end) == ' ') last_space = line_end;
            line_end++;
            current_length++;
        }

        // перенос по пробелу, если строка достигла лимита
        if (current_length == line_width && last_space > line_start) {
            line_end = last_space;
        }

        // печатаем текущую строку
        char* buffer = new char[line_end - line_start + 1];
        for (int i = line_start; i < line_end; i++) buffer[i - line_start] = text.get(i);
        buffer[line_end - line_start] = '\0';

        bool first_line = (line_start == 0);
        bool last_line = (line_end >= text_len);
        print_line(buffer, line_end - line_start, first_line, last_line);

        delete[] buffer;

        line_start = line_end;
        if (line_start < text_len && text.get(line_start) == ' ') line_start++;
        last_space = -1;
    }

    print_border('-');

    cout << "   \\\n";
    cout << "    \\\n";
    cout << "      /\\_/\\  (\n";
    cout << "     ( o_o ) _)\n";
    cout << "       \\\"/  (\n";
    cout << "     ( | | )\n";
    cout << "    (__d b__)\n";
}