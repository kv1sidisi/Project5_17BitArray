#include "17bit.h"

Result Bit17Array::Index2::Index3::operator[](size_t z) {
  if (z < z_size) {
    res.main_part += z;
    res.shift += z;
    res.add_part += res.shift / 16;
    res.shift = res.shift - (res.shift / 16 * 16);
  } else {
    std::cerr << "fatal error";
    exit(-1);
  }
  return res;
}
Bit17Array::Index2::Index3 Bit17Array::Index2::operator[](size_t y) {
  if (y < y_size) {
    res.main_part += y * z_size;
    res.shift += y * z_size;
  } else {
    std::cerr << "fatal error";
    exit(-1);
  }
  return Index3(res, z_size);
}

Bit17Array Bit17Array::operator-(const Bit17Array& other) {
  Bit17Array result = make_array(x_size, y_size, z_size);
  for (int i = 0; i < x_size * y_size * z_size; i++) {
    result.main_arr[i] = main_arr[i] - other.main_arr[i];
  }
  for (int i = 0; i < x_size * y_size * z_size / 16 + 1; i++) {
    for (int j = 15; j >= 0; j--) {
      result.add_arr[i] |= (add_arr[i] >> j) - (other.add_arr[i] >> j);
    }
  }
  return result;
}
Bit17Array Bit17Array::operator+(const Bit17Array& other) {
  Bit17Array result = make_array(x_size, y_size, z_size);
  uint32_t summ;
  for (int i = 0; i < x_size * y_size * z_size / 16 + 1; i++) {
    for (int j = 0; j < 16; j++) {
      result.add_arr[i] |= (other.add_arr[i] << j) + (add_arr[i] << j);
    }
  }
  for (int i = 0; i < (x_size * y_size * z_size); i++) {
    summ = other.main_arr[i] + main_arr[i];
    if ((result.add_arr[i / 16] >> (16 - (i % 16 == 0) - (i - i / 16 * 16)))) {
      summ += 65535;
    }
    if (summ > 65535) {
      summ -= 65535;
      result.add_arr[i / 16] |= 1 << (i - (i / 16 * 16));
    }
    result.main_arr[i] = summ;
  }
  return result;
}
std::ostream& operator<<(std::ostream& os, const Result& res) {
  uint32_t number = 0;
  number |= *res.main_part;
  number |= ((*res.add_part >> res.shift) & 1) << 16;
  os << number;
  return os;
}
Result& Result::operator=(uint32_t number) {
  *add_part = 0;
  *add_part |= (((number >> 16) & 1)) << shift;
  *main_part = number & 0xFFFF;
  return *this;
}

std::istream& operator>>(std::istream& is, const Result& result) {
  uint32_t number;
  is >> number;
  Result& res = const_cast<Result&>(result);
  res = number;
  return is;
}
bool Result::operator==(const Result& rhs) const {
  if (*main_part != *rhs.main_part or (*add_part >> shift) != (*rhs.add_part >> rhs.shift)) {
    return false;
  }
  return true;
}
bool Result::operator!=(const Result& rhs) const {
  return *this == rhs;
}
Bit17Array::Index2 Bit17Array::operator[](size_t x) {
  if (x < x_size) {
    res.shift = 0;
    res.main_part = main_arr;
    res.add_part = add_arr;
    res.main_part += x * y_size * z_size;
    res.shift += x * y_size * z_size;
    return Index2(res, y_size, z_size);
  } else {
    std::cerr << "fatal error";
    exit(-1);
  }
}
void Bit17Array::operator=(const Bit17Array& other) {
  for (int i = 0; i < x_size * y_size * z_size; i++) {
    this->main_arr[i] = other.main_arr[i];
  }
  for (int i = 0; i < x_size * y_size * z_size / 16 + 1; i++) {
    this->add_arr[i] |= other.add_arr[i];
  }
}

Bit17Array Bit17Array::operator*(uint16_t number) {
  Bit17Array result = make_array(x_size, y_size, z_size);
  uint32_t mult;
  for (int i = 0; i < x_size * y_size * z_size; i++) {
    mult = main_arr[i] * number;
    if (mult > 65535) {
      mult -= 65536;
      result.add_arr[i / 16] |= 1 << (i - (i / 16 * 16));
    }
    result.main_arr[i] = mult;
  }
  return result;
}

bool Bit17Array::operator==(const Bit17Array& rhs) const {
  for (int i = 0; i < x_size * y_size * z_size; i++) {
    if (main_arr[i] != rhs.main_arr[i]) {
      return false;
    }
  }
  for (int i = 0; i < x_size * y_size * z_size / 16 + 1; i++) {
    if (add_arr[i] != rhs.add_arr[i]) {
      return false;
    }
  }
  return true;
}
bool Bit17Array::operator!=(const Bit17Array& rhs) const {
  return *this == rhs;
}

Bit17Array Bit17Array::operator/(const Bit17Array& other) {
  Bit17Array result = make_array(x_size, y_size, z_size);
  uint32_t number1 = 0;
  uint32_t number2 = 0;
  uint32_t ans;
  for (int i = 0; i < x_size * y_size * z_size; i++) {
    number1 |= main_arr[i];
    number1 |= (add_arr[i / 16] >> (i - (i / 16 * 16))) & 1;
    number2 |= (((other.add_arr[i / 16] >> (16 - (i % 16 == 0) - (i - i / 16 * 16))) << 16) + other.main_arr[i]);
    ans = number1 / number2;
    result.main_arr[i] |= ans & 0xFFFF;
    result.add_arr[i / 16] |= ((ans >> 16) & 1) << (16 - (i % 16 == 0) - (i - i / 16 * 16));
  }
  return result;
}


