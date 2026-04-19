#include "base_file.hpp"
#include <iostream>
#include <cstdio>

using namespace std;

// ----------- BaseFile -----------

BaseFile::BaseFile(): file(nullptr){
    cout << "BaseFile конструктор по умолчанию" << endl;
}

BaseFile::BaseFile(const char* path, const char* mode): file(nullptr) {
    file = fopen(path, mode);
    cout << "BaseFile конструктор с параметрами (path, mode)" << endl;
}

BaseFile::BaseFile(FILE* _file): file(_file) {
    cout << "BaseFile конструктор с параметрами (file)" << endl;
}

BaseFile::~BaseFile(){
    if (file) {
        fclose(file);
        file = nullptr;
    }
    cout << "BaseFile деструктор" << endl;
}

BaseFile::BaseFile(BaseFile&& other): file(other.file) {
    other.file = nullptr;
}

BaseFile& BaseFile::operator=(BaseFile&& other) {
    if (this != &other) {
        if (file) {
            fclose(file);
        }
        file = other.file;
        other.file = nullptr;
    }
    return *this;
}


bool BaseFile::is_open() const {
    return file != nullptr;
}

bool BaseFile::can_read() const {
    if (!file) {
        return false;
    }
    
    int ch = fgetc(file);
    
    if (ch == EOF) {
        return false;
    }

    ungetc(ch, file);
    return true;
}

bool BaseFile::can_write() const {
    return file != nullptr;
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!file) {
        return 0;
    }

    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!file) {
        return 0;
    }

    return fread(buf, 1, max_bytes, file);
}

long BaseFile::tell() const {
    if (!file) {
        return -1;
    }

    return ftell(file);
}

bool BaseFile::seek(long offset) {
    if (!file) {
        return false;
    }

    return fseek(file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}

// ----------- Base32File -----------

Base32File::Base32File(const char* path, const char* mode, const char* table)
    : BaseFile(path, mode),
      encode_table(table),
      write_bits_buffer(0),
      write_bits_count(0),
      read_bits_buffer(0),
      read_bits_count(0) {
    cout << "Base32File конструктор по умолчанию" << endl;
}

Base32File::Base32File(FILE* _file, const char* table)
    : BaseFile(_file),
      encode_table(table),
      write_bits_buffer(0),
      write_bits_count(0),
      read_bits_buffer(0),
      read_bits_count(0) {
    cout << "Base32File конструктор с параметрами (file, table)" << endl;
}

Base32File::~Base32File() {
    flush();
    cout << "Base32File деструктор" << endl;
}

int Base32File::encoded32_size(int raw_size) const {
    return (raw_size * 8 + 4) / 5;
}

int Base32File::decoded32_size(int encoded_size) const {
    return (encoded_size * 5) / 8;
}

int Base32File::encode32(const unsigned char* raw_data, int raw_size, unsigned char* dst) const {
    if (!raw_data || !dst || raw_size < 0) return 1;

    int encoded_size = encoded32_size(raw_size);
    int total_bits = raw_size * 8;
    int bit_pos = 0;

    for (int i = 0; i < encoded_size; i++) {
        int value = 0;
        for (int j = 0; j < 5; j++) {
            int current_bit_pos = bit_pos + j;
            int bit = 0;
            if (current_bit_pos < total_bits) {
                int byte_index = current_bit_pos / 8;
                int bit_in_byte = 7 - (current_bit_pos % 8);
                bit = (raw_data[byte_index] >> bit_in_byte) & 1;
            }
            value = (value << 1) | bit;
        }
        dst[i] = encode_table[value];
        bit_pos += 5;
    }
    return 0;
}

int Base32File::decode32(const unsigned char* encoded_data, int encoded_size, unsigned char* dst) const {
    if (!encoded_data || !dst || encoded_size < 0) {
        return 1;
    }

    unsigned int bits = 0;
    int bits_counter = 0;
    int dst_index = 0;

    for (int i = 0; i < encoded_size; ++i) {
        int index = decode_char(encoded_data[i]);
        if (index == -1) {
            return 2;
        }

        bits = (bits << 5) | index;
        bits_counter += 5;

        while (bits_counter >= 8) {
            dst[dst_index++] = (bits >> (bits_counter - 8)) & 0xFF;
            bits_counter -= 8;
        }
    }

    return 0;
}

size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!is_open() || !buf || n_bytes == 0) {
        return 0;
    }

    const unsigned char* data = static_cast<const unsigned char*>(buf);
    size_t written_raw_bytes = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        write_bits_buffer = (write_bits_buffer << 8) | data[i];
        write_bits_count += 8;

        while (write_bits_count >= 5) {
            int index = (write_bits_buffer >> (write_bits_count - 5)) & 0x1F;
            unsigned char out = encode_table[index];

            if (write_raw(&out, 1) != 1) {
                return written_raw_bytes;
            }

            write_bits_count -= 5;
            if (write_bits_count == 0) {
                write_bits_buffer = 0;
            } else {
                write_bits_buffer &= (1u << write_bits_count) - 1;
            }
        }

        written_raw_bytes++;
    }

    return written_raw_bytes;
}

size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!is_open() || !buf || max_bytes == 0) {
        return 0;
    }

    unsigned char* out = static_cast<unsigned char*>(buf);
    size_t produced = 0;

    while (produced < max_bytes) {
        while (read_bits_count < 8) {
            unsigned char ch;
            if (read_raw(&ch, 1) != 1) {
                return produced;
            }

            int value = decode_char(ch);
            if (value == -1) {
                return produced;
            }

            read_bits_buffer = (read_bits_buffer << 5) | value;
            read_bits_count += 5;
        }

        out[produced++] = (read_bits_buffer >> (read_bits_count - 8)) & 0xFF;

        read_bits_count -= 8;
        if (read_bits_count == 0) {
            read_bits_buffer = 0;
        } else {
            read_bits_buffer &= (1u << read_bits_count) - 1;
        }
    }

    return produced;
}

int Base32File::decode_char(unsigned char ch) const {
    for (int i = 0; i < 32; ++i) {
        if (encode_table[i] == ch) {
            return i;
        }
    }
    return -1;
}

void Base32File::flush() {
    if (!is_open() || write_bits_count == 0) {
        return;
    }

    unsigned char out = encode_table[(write_bits_buffer << (5 - write_bits_count)) & 0x1F]; //0x1F - маска на последние 5 битов
    

    write_raw(&out, 1);

    write_bits_buffer = 0;
    write_bits_count = 0;
}

bool Base32File::seek(long offset) {
    flush();

    read_bits_buffer = 0;
    read_bits_count = 0;

    return BaseFile::seek(offset);
}

// ----------- RleFile -----------

RleFile::RleFile(const char* path, const char* mode)
    : BaseFile(path, mode),
      pending_byte(0),
      pending_count(0),
      read_byte(0),
      read_count_left(0) {
    cout << "RleFile конструктор по умолчанию" << endl;
}
RleFile::RleFile(FILE* _file)
    : BaseFile(_file),
      pending_byte(0),
      pending_count(0),
      read_byte(0),
      read_count_left(0) {
    cout << "RleFile конструктор с параметром file" << endl;
}

RleFile::~RleFile() {
    flush();
    cout << "RleFile деструктор" << endl;
}

size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!is_open() || !buf || n_bytes == 0) {
        return 0;
    }

    const unsigned char* data = static_cast<const unsigned char*>(buf);
    size_t accepted = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        unsigned char current = data[i];

        if (pending_count == 0) {
            pending_byte = current;
            pending_count = 1;
        } else if (current == pending_byte && pending_count < 255) {
            pending_count++;
        } else {
            flush();
            pending_byte = current;
            pending_count = 1;
        }

        accepted++;
    }

    return accepted;
}

size_t RleFile::read(void* buf, size_t max_bytes) {
    if (!is_open() || !buf || max_bytes == 0) {
        return 0;
    }

    unsigned char* out = static_cast<unsigned char*>(buf);
    size_t produced = 0;

    while (produced < max_bytes) {
        if (read_count_left == 0) {
            unsigned char pair[2];
            size_t got = read_raw(pair, 2);

            if (got < 2) {
                return produced;
            }

            read_count_left = pair[0];
            read_byte = pair[1];

            if (read_count_left == 0) {
                return produced;
            }
        }

        out[produced++] = read_byte;
        read_count_left--;
    }

    return produced;
}

bool RleFile::seek(long offset) {
    flush();

    read_byte = 0;
    read_count_left = 0;

    return BaseFile::seek(offset);
}

void RleFile::flush() {
    if (!is_open() || pending_count == 0) {
        return;
    }

    unsigned char pair[2];
    pair[0] = pending_count;
    pair[1] = pending_byte;

    write_raw(pair, 2);

    pending_byte = 0;
    pending_count = 0;
}

// ----------- write_int -----------

void write_int(IFile &file, int n) {
    if (n <= 0) {
        file.write("Не могу записать число меньшее либо равное нулю!", 1);
        return;
    }

    char digits[20]; 
    int pos = 0;

    int temp = n;
    while (temp > 0) {
        digits[pos++] = '0' + (temp % 10);
        temp /= 10;
    }

    for (int i = pos - 1; i >= 0; i--) {
        file.write(&digits[i], 1);
    }
}

// ----------- Base32File2 -----------

Base32File2::Base32File2(IFile* _file, const char* table)
    : file(_file),
      encode_table(table),
      write_bits_buffer(0),
      write_bits_count(0),
      read_bits_buffer(0),
      read_bits_count(0) {
    cout << "Base32File2 конструктор с параметром file" << endl;
}

Base32File2::~Base32File2() {
    flush();
    delete file;
    cout << "Base32File2 деструктор" << endl;
}

bool Base32File2::can_read() const {  
    return file && file->can_read();
}

bool Base32File2::can_write() const {
    return file && file->can_write();
}

int Base32File2::decode_char(unsigned char ch) const {
    for (int i = 0; i < 32; ++i) {
        if (encode_table[i] == ch) {
            return i;
        }
    }
    return -1;
}

size_t Base32File2::write(const void* buf, size_t n_bytes) {
    if (!file || !buf || n_bytes == 0 || !file->can_write()) {
        return 0;
    }

    const unsigned char* data = static_cast<const unsigned char*>(buf);
    size_t accepted = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        write_bits_buffer = (write_bits_buffer << 8) | data[i];
        write_bits_count += 8;

        while (write_bits_count >= 5) {
            int index = (write_bits_buffer >> (write_bits_count - 5)) & 0x1F;
            unsigned char out = encode_table[index];

            if (file->write(&out, 1) != 1) {
                return accepted;
            }

            write_bits_count -= 5;
            if (write_bits_count == 0) {
                write_bits_buffer = 0;
            } else {
                write_bits_buffer &= (1u << write_bits_count) - 1;
            }
        }

        accepted++;
    }

    return accepted;
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    if (!file || !buf || max_bytes == 0 || !file->can_read()) {
        return 0;
    }

    unsigned char* out = static_cast<unsigned char*>(buf);
    size_t produced = 0;

    while (produced < max_bytes) {
        while (read_bits_count < 8) {
            unsigned char ch;
            if (file->read(&ch, 1) != 1) {
                return produced;
            }

            int value = decode_char(ch);
            if (value == -1) {
                return produced;
            }

            read_bits_buffer = (read_bits_buffer << 5) | value;
            read_bits_count += 5;
        }

        out[produced++] = (read_bits_buffer >> (read_bits_count - 8)) & 0xFF;

        read_bits_count -= 8;
        if (read_bits_count == 0) {
            read_bits_buffer = 0;
        } else {
            read_bits_buffer &= (1u << read_bits_count) - 1;
        }
    }

    return produced;
}

void Base32File2::flush() {
    if (!file || write_bits_count == 0) {
        return;
    }

    unsigned char out = encode_table[(write_bits_buffer << (5 - write_bits_count)) & 0x1F];

    file->write(&out, 1);

    write_bits_buffer = 0;
    write_bits_count = 0;
}

// ----------- RleFile2 -----------

RleFile2::RleFile2(IFile* _file)
    : file(_file),
      pending_byte(0),
      pending_count(0),
      read_byte(0),
      read_count_left(0) {
    cout << "RleFile2 конструктор с параметром file" << endl;
}

RleFile2::~RleFile2() {
    flush();
    delete file;
    cout << "RleFile2 деструктор" << endl;
}

bool RleFile2::can_read() const {  
    return file && file->can_read();
}

bool RleFile2::can_write() const {
    return file && file->can_write();
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    if (!file || !buf || n_bytes == 0 || !file->can_write()) {
        return 0;
    }

    const unsigned char* data = static_cast<const unsigned char*>(buf);
    size_t accepted = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        unsigned char current = data[i];

        if (pending_count == 0) {
            pending_byte = current;
            pending_count = 1;
        } else if (current == pending_byte && pending_count < 255) {
            pending_count++;
        } else {
            flush();
            pending_byte = current;
            pending_count = 1;
        }

        accepted++;
    }

    return accepted;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    if (!file || !buf || max_bytes == 0 || !file->can_read()) {
        return 0;
    }

    unsigned char* out = static_cast<unsigned char*>(buf);
    size_t produced = 0;

    while (produced < max_bytes) {
        if (read_count_left == 0) {
            unsigned char pair[2];
            size_t got = file->read(pair, 2);

            if (got < 2) {
                return produced;
            }

            read_count_left = pair[0];
            read_byte = pair[1];

            if (read_count_left == 0) {
                return produced;
            }
        }

        out[produced++] = read_byte;
        read_count_left--;
    }

    return produced;
}

void RleFile2::flush() {
    if (!file || pending_count == 0) {
        return;
    }

    unsigned char pair[2];
    pair[0] = pending_count;
    pair[1] = pending_byte;

    file->write(pair, 2);

    pending_byte = 0;
    pending_count = 0;
}