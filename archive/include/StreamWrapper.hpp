#pragma once

#include <iostream>

template<class T>
class StreamWrapper
{
private:
  std::iostream* m_stream;
  long m_pos;
protected:
  template<class U> void save(const U& var) const
  {
    m_stream->seekg(m_pos + (&var - &m_data));
    m_stream->write(static_cast<const char*>(var), sizeof(U));
  }
  T m_data;
public:
  StreamWrapper(std::iostream* ios) : m_stream(ios), m_pos(ios->tellg()) {}
  virtual ~StreamWrapper() {}
  void save(void) const
  {
    m_stream->seekg(m_pos);
    m_stream->write(reinterpret_cast<const char*>(&m_data), sizeof(T));
  }
  virtual void load(void)
  {
    m_stream->seekp(m_pos);
    m_stream->read(reinterpret_cast<char*>(&m_data), sizeof(T)); 
  }
};
