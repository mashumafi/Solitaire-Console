#pragma once

#include <Meta.hpp>

class FileStream : public MetaStream
{
public:
  FileStream(HeaderStream* header, DirectoryStream* parent = nullptr);
  virtual ~FileStream(void);
  long length(void) const;
private:
};

inline FileStream::FileStream(HeaderStream* header, DirectoryStream* parent)
                 : MetaStream(header, parent)
{
#ifndef NDEBUG
  std::cout << "File m_pos: " << pos() << std::endl;
#endif
}

inline FileStream::~FileStream(void)
{
}
