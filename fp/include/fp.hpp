#pragma once

#include <Main.hpp>

#include <boost/phoenix/phoenix.hpp>

struct is_odd_impl
{

    template <typename T>
    bool operator()(T t) const { return t % 2 == 1; }
};

class fp : public Main
{
public:
  virtual int main() override;
  virtual ~fp();
};
