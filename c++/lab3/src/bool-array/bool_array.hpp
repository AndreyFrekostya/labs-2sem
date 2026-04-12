#pragma once

class BoolArray {
private:
    unsigned char* data; 
    int size;            
    int bytes;           

    int bytesForBits(int bits);
    void setBit(int index, bool value);
    bool getBit(int index) const;

public:
    class Reference {
        BoolArray* array;
        int index;
    public:
        Reference(BoolArray* arr, int idx);

        Reference& operator=(bool value);
        Reference& operator=(const Reference& other);
        operator bool() const;
    };

    BoolArray(int n = 0, bool value = false);
    BoolArray(const BoolArray& other);
    BoolArray& operator=(const BoolArray& other);
    ~BoolArray();

    Reference operator[](int index);       
    bool operator[](int index) const;      

    int get_size() const;
    void resize(int newSize, bool value = false);
};
