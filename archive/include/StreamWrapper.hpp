#pragma once

#include <fstream>
#include <iostream>

template<class T>
class StreamWrapper
{
public:
  StreamWrapper(std::fstream* ios) : m_stream(ios), m_pos(ios->tellg())
  {
  }
  virtual ~StreamWrapper(void)
  {
  }
  void save(void) const
  {
    long temp = m_stream->tellp();
    m_stream->seekp(m_pos, std::ios::beg);
    m_stream->write(reinterpret_cast<const char*>(&m_data), sizeof(T));
    m_stream->seekp(temp, std::ios::beg);
  }
  virtual void load(void)
  {
    long temp = m_stream->tellp();
    m_stream->seekg(m_pos, std::ios::beg);
    m_stream->read(reinterpret_cast<char*>(&m_data), sizeof(T)); 
    m_stream->seekp(temp, std::ios::beg);
  }
  long pos(void) const
  {
    return m_pos;
  }
protected:
  T m_data;
  std::fstream* m_stream;
  template<class U> void save(const U* var) const
  {
    long temp = m_stream->tellp();
    m_stream->seekp(m_pos + (reinterpret_cast<const char*>(var) - reinterpret_cast<const char*>(&m_data)), std::ios::beg);
    m_stream->write(reinterpret_cast<const char*>(var), sizeof(U));
    m_stream->seekp(temp, std::ios::beg);
  }
  virtual void saved(void)
  {
  }
private:
  long m_pos;
};
