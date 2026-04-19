#include "../src/base-file/base_file.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    const char* filename = "public/test_base32.txt";
    const int size = 50 * 1024;
    const int part = 256;

    char* data1 = new char[size];
    char* data2 = new char[size];

    std::srand((unsigned)std::time(0));

    for (int i = 0; i < size; i++) {
        data1[i] = 'A' + std::rand() % 26;
    }

    {
        Base32File file(filename, "wb");
        int pos = 0;

        while (pos < size) {
            int count = part;
            if (size - pos < part) {
                count = size - pos;
            }

            int written = file.write(data1 + pos, count);
            if (written == 0) {
                std::cout << "Ошибка записи\n";
                break;
            }

            pos += written;
        }

        std::cout << "Записано: " << pos << " байт\n";
    }

    {
        Base32File file(filename, "rb");
        int pos = 0;

        while (pos < size) {
            int count = part;
            if (size - pos < part) {
                count = size - pos;
            }

            int readed = file.read(data2 + pos, count);
            if (readed == 0) {
                break;
            }

            pos += readed;
        }

        std::cout << "Прочитано: " << pos << " байт\n";
    }

    bool ok = true;
    for (int i = 0; i < size; i++) {
        if (data1[i] != data2[i]) {
            ok = false;
            std::cout << "Ошибка в байте " << i << "\n";
            break;
        }
    }

    if (ok) {
        std::cout << "Тест Base32File пройден\n";
    } else {
        std::cout << "Тест Base32File не пройден\n";
    }

    delete[] data1;
    delete[] data2;

    return 0;
}