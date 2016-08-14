#pragma once

#include <iostream>

template<class T>
class StreamWrapper
{
private:
  long m_pos;
  std::iostream* m_stream;
protected:
  template<class U> void save(const U& var) const
  {
    m_stream->seekg(m_pos + (&var - &m_data));
    m_stream->write(static_cast<const char*>(var), sizeof(U));
  }
  T m_data;
public:
  StreamWrapper(std::iostream*);
  virtual ~StreamWrapper();
  void save(void) const;
  virtual void load(void);
};
