template<int f>
struct fib
{
  operator int() const
  {
    return fib<f-1>() + fib<f-2>();
  }
};

template<>
struct fib<0>
{
  operator int() const
  {
    return 0;
  }
};

template<>
struct fib<1>
{
  operator int() const
  {
    return 1;
  }
};