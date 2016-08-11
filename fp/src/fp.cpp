#include <fp.hpp>

#include <vector>
#include <algorithm>
#include <iostream>

#include <boost/phoenix/stl/algorithm.hpp>

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
    bind(arg2, arg1),
    bind(arg2, arg1)
  ]
  .else_
  [
    bind(arg2, "err")
  ];
  isodd(add(1, 2), print);
  isodd(add(1, 3), print);

  boost::phoenix::function<is_odd_impl> is_odd;
  std::cout << std::count_if(v.begin(), v.end(), is_odd(arg1)) << std::endl;
  std::cout << std::endl;
  
  int array[] = {1, 2, 3};
  int output[3];
  copy(arg1, arg2)(array, output);
  std::for_each(output, output+3, print);

  return 0;
}
