#include "array.h"
using namespace ArrayUInt17_t;

Position Array::GetPosition() const {
    uint32_t temp =
        17 * ((size_x_ * size_y_ * coord_.z) + (size_x_ * coord_.y) + coord_.x);
    Position result = {temp / kBitSize, kBitSize - temp % kBitSize};
    return result;
}

Array::Array(uint32_t size_x, uint32_t size_y, uint32_t size_z)
    : size_x_(size_x), size_y_(size_y), size_z_(size_z) {
    uint32_t temp = size_x * size_y * size_z * kIntSize;
    if (temp % kBitSize != 0)
        size = temp / kBitSize + 1;
    else
        size = temp / kBitSize;

    data_ = new int8_t[size]();
}

Array::Array(const Array& other)
    : size(other.size),
      size_x_(other.size_x_),
      size_y_(other.size_y_),
      size_z_(other.size_z_) {
    data_ = new int8_t[size]();
    for (uint32_t i = 0; i < size; ++i) {
        data_[i] = other.data_[i];
    }
};

Array& Array::operator=(const Array& other) {
    size = other.size;
    data_ = new int8_t[size]();
    for (uint32_t i = 0; i < size; ++i) {
        data_[i] = other.data_[i];
    }
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    size_z_ = other.size_z_;
    coord_ = {-1, -1, -1};
    return *this;
};

Array& Array::operator[](uint32_t idx) {
    if (coord_.x == -1)
        coord_.x = idx;
    else if (coord_.y == -1)
        coord_.y = idx;
    else if (coord_.z == -1)
        coord_.z = idx;
    return *this;
}

uint32_t Array::Get() {
    if (coord_.x != -1 && coord_.y != -1 && coord_.z != -1) {
        uint32_t result = 0;
        Position pos = GetPosition();
        result |= (data_[pos.index] & (kMaxByte >> (kBitSize - pos.offset)));
        result <<= kBitSize;
        result |= data_[pos.index + 1] & kCastMask;
        result <<= kIntSize - pos.offset - kBitSize;
        result |= (data_[pos.index + 2] & kCastMask) >>
                  (kBitSize - kIntSize + pos.offset + kBitSize);
        coord_.x = -1;
        coord_.y = -1;
        coord_.z = -1;
        return result;
    } else {
        std::cerr << "Error: coord not set" << '\n';
        exit(1);
    }
}

Array& Array::ClearPosition(Position pos) {
    data_[pos.index] &= kMaxByte << pos.offset;
    data_[pos.index + 1] = 0;
    data_[pos.index + 2] &= kMaxByte >> (kIntSize - pos.offset - kBitSize);
    return *this;
}

Array& Array::operator=(int32_t value) {
    if (coord_.x != -1 && coord_.y != -1 && coord_.z != -1) {
        Position pos = GetPosition();
        ClearPosition(pos);
        value = value <= 0x1ffff ? value : 0x1ffff;
        value <<= kBitSize - kIntSize + pos.offset + kBitSize;
        data_[pos.index + 2] |= value & kCastMask;
        data_[pos.index + 1] |= (value >> kBitSize) & kCastMask;
        data_[pos.index] |= (value >> (2 * kBitSize)) & kCastMask;
        coord_.x = -1;
        coord_.y = -1;
        coord_.z = -1;
        return *this;
    } else {
        std::cerr << "Error: coord not set" << '\n';
        exit(1);
    }
}

Array Array::operator*(const uint32_t value) {
    Array result(size_x_, size_y_, size_z_);
    for (int32_t x = 0; x < size_x_; ++x) {
        for (int32_t y = 0; y < size_y_; ++y) {
            for (int32_t z = 0; z < size_z_; ++z) {
                coord_ = {x, y, z};
                uint32_t temp = Get();
                result[x][y][z];
                result = (temp * value) <= 0x1ffff ? (temp * value) : 0x1ffff;
            }
        }
    }
    return result;
}

Array Array::operator+(Array& other) {
    Array result(size_x_, size_y_, size_z_);
    for (int32_t x = 0; x < size_x_; ++x) {
        for (int32_t y = 0; y < size_y_; ++y) {
            for (int32_t z = 0; z < size_z_; ++z) {
                coord_ = {x, y, z};
                uint32_t temp = Get();
                result[x][y][z] = (temp + other[x][y][z].Get()) <= 0x1ffff
                                      ? (temp + other[x][y][z].Get())
                                      : 0x1ffff;
            }
        }
    }
    return result;
}

Array Array::operator*(Array& other) {
    Array result(size_x_, size_y_, size_z_);
    for (int32_t x = 0; x < size_x_; ++x) {
        for (int32_t y = 0; y < size_y_; ++y) {
            for (int32_t z = 0; z < size_z_; ++z) {
                coord_ = {x, y, z};
                uint32_t temp = Get();
                result[x][y][z] = (temp * other[x][y][z].Get()) <= 0x1ffff
                                      ? (temp * other[x][y][z].Get())
                                      : 0x1ffff;
            }
        }
    }
    return result;
}

void Array::PrintArray() {
    std::cout << "----------v" << std::endl;
    for (int32_t z = 0; z < size_z_; ++z) {
        std::cout << "(z = " << z << ")" << std::endl;
        for (int32_t x = 0; x < size_x_; ++x) {
            for (int32_t y = 0; y < size_y_; ++y) {
                coord_ = {x, y, z};
                std::cout << Get() << " ";
            }
            std::cout << '\n';
        }
        if (z == size_z_ - 1)
            std::cout << "----------^\n" << std::endl;
        else
            std::cout << '\n';
    }
}

std::ostream& operator<<(std::ostream& stream, ArrayUInt17_t::Array& arr) {
    stream << arr.Get();
    return stream;
}

std::istream& operator>>(std::istream& stream, ArrayUInt17_t::Array& arr) {
    int temp;
    stream >> temp;
    arr = temp;
    return stream;
}