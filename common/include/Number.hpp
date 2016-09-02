#pragma once

#include <math.h>
#include <iostream>

template<class T>
class Number
{
public:
  T value;
public:
  Number() : Number<T>::Number(0) {}
  Number(T) { this->value = value; }
  //Number<T> operator =(const T& t) { return Number<T>(t); }
  Number<T> operator ++(int) { return this->value + 1; }
  Number<T> operator --(int) { return this->value - 1; }
  Number<T> sqrt() { return ::sqrt(this->value); }
  Number<T> cbrt() { return ::cbrt(this->value); }
  template<class U> Number<T> operator +(const Number<U>& b)
  {
    return this->value + b.value;
  }
  template<class U> Number<T> operator -(const Number<U>& b)
  {
    return this->value - b.value;
  }
  template<class U> Number<T> operator *(const Number<U>& b)
  {
    return this->value / b.value;
  }
  template<class U> Number<T> operator /(const Number<U>& b)
  {
    return this->value / b.value;
  }
  template<class U> bool operator <(const Number<U>& b)
  {
    return this->value < b.value;
  }
  template<class U>  bool operator >(const Number<U>& b)
  {
    return this->value > b.value;
  }
  template<class U> bool operator <=(const Number<U>& b)
  {
    return this->value <= b.value;
  }
  template<class U> bool operator >=(const Number<U>& b)
  {
    return this->value >= b.value;
  }
  template<class U> bool operator ==(const Number<U>& b)
  {
    return this->value == b.value;
  }
  template<class U> bool operator !=(const Number<U>& b)
  {
    return this->value != b.value;
  }
  template<class U> Number<T> operator ^(const Number<U>& b)
  {
    return pow(this->value, b.value);
  }
};

template<class T> std::ostream& operator<<(std::ostream& out, const Number<T>& n)
{
   return out << n.value;
}

#define Byte Number<char>
#define Short Number<short>
#define Integer Number<int>
#define Long Number<long>
#define Float Number<float>
#define Double Number<double>
#define Character Number<char>
