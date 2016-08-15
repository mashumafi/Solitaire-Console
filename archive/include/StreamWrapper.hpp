#pragma once

#include <iostream>

template<class T>
class StreamWrapper
{
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
protected:
  T m_data;
  std::iostream* m_stream;
  template<class U> void save(const U& var) const
  {
    m_stream->seekg(m_pos + (&var - &m_data));
    m_stream->write(static_cast<const char*>(var), sizeof(U));
  }
  virtual void saved(void)
  {
  }
private:
  long m_pos;
};
