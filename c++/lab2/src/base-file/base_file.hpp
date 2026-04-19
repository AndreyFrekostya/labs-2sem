#include <cstdio>

#pragma once

class IFile {
public:
    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;

    virtual size_t read(void* buf, size_t max_bytes) = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;

    virtual ~IFile() = default;
};

class BaseFile: public IFile {
protected:
    FILE* file;
public:
    BaseFile();
    BaseFile(const char* path, const char* mode);
    BaseFile(FILE* _file);

    virtual ~BaseFile();

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;

    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);

    long tell() const;
    virtual bool seek(long offset);

    virtual size_t write(const void* buf, size_t n_bytes);
    virtual size_t read(void* buf, size_t max_bytes);

};

class Base32File: public BaseFile {
private:
    const char* encode_table;

    unsigned int write_bits_buffer;
    int write_bits_count;

    unsigned int read_bits_buffer;
    int read_bits_count;

    int encoded32_size(int raw_size) const;
    int decoded32_size(int encoded_size) const;
    int encode32(const unsigned char* raw_data, int raw_size, unsigned char* dst) const;
    int decode32(const unsigned char* encoded_data, int encoded_size, unsigned char* dst) const;

    int decode_char(unsigned char ch) const;
    void flush();
public:
    Base32File(const char* path, const char* mode, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    Base32File(FILE* _file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    ~Base32File();

    bool seek(long offset);

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

class RleFile: public BaseFile {
private:
    unsigned char pending_byte;
    unsigned char pending_count;

    unsigned char read_byte;
    unsigned char read_count_left;

    void flush();
public:
    RleFile(const char* path, const char* mode);
    RleFile(FILE* _file);

    ~RleFile();

    bool seek(long offset);

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

void write_int(IFile &file, int n);

class Base32File2: public IFile {
private:
    IFile* file;
    const char* encode_table;

    unsigned int write_bits_buffer;
    int write_bits_count;

    unsigned int read_bits_buffer;
    int read_bits_count;

    int decode_char(unsigned char ch) const;
    void flush();

public:
    Base32File2(IFile* _file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    ~Base32File2();

    bool can_read() const;
    bool can_write() const;

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};;

class RleFile2: public IFile {
private:
    IFile* file;

    unsigned char pending_byte;
    unsigned char pending_count;

    unsigned char read_byte;
    unsigned char read_count_left;

    void flush();

public:
    RleFile2(IFile* _file);
    ~RleFile2();

    bool can_read() const;
    bool can_write() const;

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};
