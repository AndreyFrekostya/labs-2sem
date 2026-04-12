#include "bool_array.hpp"

BoolArray::Reference::Reference(BoolArray* arr, int idx)
    : array(arr), index(idx) {}

BoolArray::Reference& BoolArray::Reference::operator=(bool value) {
    array->setBit(index, value);
    return *this;
}

BoolArray::Reference& BoolArray::Reference::operator=(const Reference& other) {
    return *this = (bool)other;
}

BoolArray::Reference::operator bool() const {
    return array->getBit(index);
}


// ------------------------------------

int BoolArray::bytesForBits(int bits) {
    return (bits + 7) / 8;
}

void BoolArray::setBit(int index, bool value) {
    int byte = index / 8;
    int bit  = index % 8;
    if (value)
        data[byte] |= (1 << bit);
    else
        data[byte] &= ~(1 << bit);
}

bool BoolArray::getBit(int index) const {
    int byte = index / 8;
    int bit  = index % 8;
    return (data[byte] >> bit) & 1;
}

BoolArray::BoolArray(int n, bool value)
    : size(n), bytes(bytesForBits(n)) {
    data = new unsigned char[bytes];

    for (int i = 0; i < bytes; ++i)
        data[i] = value ? 0xFF : 0x00;

    if (value && n % 8 != 0) {
        unsigned char mask = (1 << (n % 8)) - 1;
        data[bytes - 1] &= mask;
    }
}

BoolArray::BoolArray(const BoolArray& other)
    : size(other.size), bytes(other.bytes) {
    data = (bytes > 0) ? new unsigned char[bytes] : 0;
    for (int i = 0; i < bytes; ++i)
        data[i] = other.data[i];
}

BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        bytes = other.bytes;
        data = (bytes > 0) ? new unsigned char[bytes] : 0;
        for (int i = 0; i < bytes; ++i)
            data[i] = other.data[i];
    }
    return *this;
}

BoolArray::~BoolArray() {
    delete[] data;
}

BoolArray::Reference BoolArray::operator[](int index) {
    return Reference(this, index);
}

bool BoolArray::operator[](int index) const {
    return getBit(index);
}

int BoolArray::get_size() const {
    return size;
}

void BoolArray::resize(int newSize, bool value) {
    int newBytes = bytesForBits(newSize);
    unsigned char* newData = (newBytes > 0) ? new unsigned char[newBytes] : 0;

    for (int i = 0; i < newBytes; ++i)
        newData[i] = value ? 0xFF : 0x00;

    int minBits = (newSize < size) ? newSize : size;
    for (int i = 0; i < minBits; ++i) {
        if (getBit(i))
            newData[i / 8] |= (1 << (i % 8));
        else
            newData[i / 8] &= ~(1 << (i % 8));
    }

    delete[] data;
    data = newData;
    size = newSize;
    bytes = newBytes;

    if (value && newSize % 8 != 0) {
        unsigned char mask = (1 << (newSize % 8)) - 1;
        data[bytes - 1] &= mask;
    }
}