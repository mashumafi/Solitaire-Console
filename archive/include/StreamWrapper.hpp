#pragma once

#include <istream>

template<class T>
class StreamWrapper
{
  T data;
  long pos;
public:
  StreamWrapper(std::istream& is);
  virtual ~StreamWrapper();
};
