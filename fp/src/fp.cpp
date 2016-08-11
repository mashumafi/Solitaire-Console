#include <fp.hpp>

#include <boost/phoenix/phoenix.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

fp::~fp()
{
}

int fp::main()
{
  std::vector<int> v{1, 2, 3, 4, 5};
  
  using namespace boost::phoenix;
  using namespace boost::phoenix::placeholders;

  auto add = arg1 + arg2;
  auto print = std::cout << arg1 << std::endl;
  auto isodd = if_(arg1 > 2 && arg1 % 2 == 1)
    [
      bind(arg2, arg1)
    ];
  isodd(add(1, 2), print);
  std::cout << _1 << std::endl;
  return 0;
}
