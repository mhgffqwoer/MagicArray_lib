#pragma once
#include <iostream>

namespace ArrayUInt17_t {
static const uint32_t kBitSize = 8;
static const uint8_t kMaxByte = 0xFF;
static const uint32_t kCastMask = 0x000000FF;
static const uint32_t kIntSize = 17;

struct Coord {
    int32_t x;
    int32_t y;
    int32_t z;
};

struct Position {
    uint32_t index;
    uint32_t offset;
};

struct test {
    int8_t* data_;

    uint32_t size_x_;
    uint32_t size_y_;
    uint32_t size_z_;

    uint32_t size;

    Coord coord_ = {-1, -1, -1};
};

class Array {
   private:
    int8_t* data_;

    uint32_t size_x_;
    uint32_t size_y_;
    uint32_t size_z_;

    uint32_t size;

    Coord coord_ = {-1, -1, -1};

    Position GetPosition() const;

    Array& ClearPosition(Position pos);

   public:
    Array(uint32_t size_x, uint32_t size_y, uint32_t size_z);

    ~Array() { delete[] data_; };

    Array(const Array& other);

    Array& operator=(const Array& other);

    Array& operator[](uint32_t idx);

    uint32_t Get();

    Array& operator=(int32_t value);

    Array operator*(const uint32_t value);

    Array operator+(Array& other);

    Array operator*(Array& other);

    void PrintArray();
};

}  // namespace ArrayUInt17_t

std::ostream& operator<<(std::ostream& stream, ArrayUInt17_t::Array& arr);

std::istream& operator>>(std::istream& stream, ArrayUInt17_t::Array& arr);