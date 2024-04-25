#include <lib/17bit.h>
#include <gtest/gtest.h>
#include <sstream>


TEST(CubicArrayTestSuite, Zero) {
  Bit17Array arr = Bit17Array::make_array(2, 2, 2);
  arr[0][0][0] = 131071;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  check[1][1][1] = 131071;
  ASSERT_EQ(arr[0][0][0], check[1][1][1]);
}


TEST(CubicArrayTestSuite, Last) {
  Bit17Array arr = Bit17Array::make_array(2, 2, 2);
  arr[1][1][1] = 131071;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  check[1][1][1] = 131071;;
  ASSERT_EQ(arr[1][1][1], check[1][1][1]);
}

TEST(CubicArrayTestSuite, Plus) {
  Bit17Array arr = Bit17Array::make_array(2, 2, 2);
  arr[1][1][1] = 1;
  Bit17Array arr2 = Bit17Array::make_array(2, 2, 2);
  arr2[1][1][1] = 2;
  Bit17Array arr3 = Bit17Array::make_array(2, 2, 2);
  arr3=arr2+arr;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  check[1][1][1] = 3;
  ASSERT_EQ(arr3[1][1][1], check[1][1][1]);
}

TEST(CubicArrayTestSuite, Minus) {
  Bit17Array arr = Bit17Array::make_array(2, 2, 2);
  arr[1][1][1] = 1;
  Bit17Array arr2 = Bit17Array::make_array(2, 2, 2);
  arr2[1][1][1] = 2;
  Bit17Array arr3 = Bit17Array::make_array(2, 2, 2);
  arr3=arr2-arr;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  check[1][1][1] = 1;
  ASSERT_EQ(arr3[1][1][1], check[1][1][1]);
}

TEST(CubicArrayTestSuite, Permut) {
  Bit17Array arr = Bit17Array::make_array(2, 2, 2);
  arr[1][1][1] = 1;
  Bit17Array arr2 = Bit17Array::make_array(2, 2, 2);
  arr2=arr*5;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  check[1][1][1] = 5;
  ASSERT_EQ(arr2[1][1][1], check[1][1][1]);
}

TEST(CubicArrayTestSuite, DifficultDunc) {
  Bit17Array arr1 = Bit17Array::make_array(2, 2, 2);
  arr1[1][1][1] = 1;
  Bit17Array arr2 = Bit17Array::make_array(2, 2, 2);
  Bit17Array arr3 = Bit17Array::make_array(2, 2, 2);
  arr2=arr1*5;
  arr3=arr2+arr1;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  check[1][1][1] = 6;
  ASSERT_EQ(arr3[1][1][1], check[1][1][1]);
}

TEST(CubicArrayTestSuite, DifferentSizes) {
  Bit17Array arr1 = Bit17Array::make_array(2, 2, 2);
  arr1[1][1][1] = 1;
  Bit17Array arr2 = Bit17Array::make_array(2, 2, 2);
  Bit17Array arr3 = Bit17Array::make_array(2, 2, 2);
  arr2=arr1*5;
  arr3=arr2+arr1;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  check[1][1][1] = 6;
  ASSERT_EQ(arr3[1][1][1], check[1][1][1]);
}

TEST(CubicArrayTestSuite,ArrDivision) {
  Bit17Array arr = Bit17Array::make_array(2, 2, 2);
  Bit17Array arr1 = Bit17Array::make_array(2, 2, 2);
  Bit17Array arr2 = Bit17Array::make_array(2, 2, 2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){
      for(int k = 0; k < 2; k++){
        arr[i][j][k] = 6;
      }
    }
  }
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){
      for(int k = 0; k < 2; k++){
        arr1[i][j][k] = 2;
      }
    }
  }
  arr2 = arr/arr1;
  Bit17Array check = Bit17Array::make_array(2, 2, 2);
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){
      for(int k = 0; k < 2; k++){
        check[i][j][k] = 3;
      }
    }
  }
  ASSERT_EQ(arr2,check);
}
