#pragma once

#include <StreamWrapper.hpp>

#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/endian/buffers.hpp>

const std::string ISO_FORMAT = "YYYYMMDDTHHMMSS";

struct Meta
{
  boost::endian::big_uint8_buf_at name[256];
  boost::endian::big_uint8_buf_at created[16];
  boost::endian::big_uint8_buf_at changed[16];
};

template<class T> class MetaStream : public StreamWrapper<T>
{
private:
  void created(void);
  void changed(void);
protected:
  template<class U> void save(const U& var) const
  {
    StreamWrapper<T>::save(var);
  }
public:
  MetaStream(std::iostream*);
  virtual ~MetaStream();
  boost::posix_time::ptime created(void) const;
  boost::posix_time::ptime changed(void) const;
  std::string name() const;
  void name(const std::string&);
  virtual void load(void) override;
  void create(const std::string& name);
};
