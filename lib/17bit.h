#pragma once
#include <iostream>

class Result {
  friend class Bit17Array;
  friend std::ostream& operator<<(std::ostream& os, const Result& res);
  friend std::istream& operator>>(std::istream& is,const Result& result);
 public:
  bool operator==(const Result& rhs) const;
  bool operator!=(const Result& rhs) const;
  Result& operator=(uint32_t number);
 private:
  uint16_t* main_part{0};
  uint16_t* add_part{0};
  uint16_t shift = 0;
  size_t x_size;
  size_t y_size;
  size_t z_size;
};

std::ostream& operator<<(std::ostream& os, const Result& res);
std::istream& operator>>(std::istream& is, const Result& result);

class Bit17Array {
 public:

  bool operator==(const Bit17Array& rhs) const;
  bool operator!=(const Bit17Array& rhs) const;

  Bit17Array(size_t x, size_t y, size_t z) : x_size(x), y_size(y), z_size(z) {
    main_arr = new uint16_t[x_size * y_size * z_size]{0};
    add_arr = new uint16_t[x_size * y_size * z_size / 16 + 1]{0};
    res.x_size = x;
    res.y_size = y;
    res.z_size = z;
  }
  ~Bit17Array() {
    delete[] main_arr;
    delete[] add_arr;
  }
  Bit17Array(const Bit17Array& other)
      : x_size(other.x_size), y_size(other.y_size), z_size(other.z_size)
  {
    main_arr = new uint16_t[x_size * y_size * z_size];
    for (size_t i = 0; i < x_size * y_size * z_size; ++i)
    {
      main_arr[i] = other.main_arr[i];
    }
    size_t add_arr_size = x_size * y_size * z_size / 16 + 1;
    add_arr = new uint16_t[add_arr_size];
    for (size_t i = 0; i < add_arr_size; ++i)
    {
      add_arr[i] = other.add_arr[i];
    }
  }

  static Bit17Array make_array(const size_t x, const size_t y, const size_t z) {
    return Bit17Array(x, y, z);
  }
  class Index2 {
   public:
    Index2(Result res, size_t y_size, size_t z_size) : res(res), y_size(y_size), z_size(z_size) {}
    class Index3 {
     public:
      Index3(Result res, size_t z_size) : res(res), z_size(z_size) {}
      Result operator[](size_t z);
     private:
      size_t z_size;
      Result res;
    };
    Index3 operator[](size_t y);
   private:
    size_t y_size, z_size;
    Result res;
  };
  Bit17Array operator*(uint16_t number);
  Bit17Array operator+(const Bit17Array& other);
  Bit17Array operator-(const Bit17Array& other);
  Bit17Array operator/(const Bit17Array& other);
  void operator=(const Bit17Array& other);
  Index2 operator[](size_t x);

 private:
  size_t x_size, y_size, z_size;
  uint16_t* main_arr = 0;
  uint16_t* add_arr = 0;
  Result res;
};

