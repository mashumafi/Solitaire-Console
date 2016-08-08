#include <random>

class Random : public std::random_device
{
public:
  int nextInt();
  int nextInt(int);
  int nextInt(int, int);
  double nextDouble();
  double nextDouble(double);
  double nextDouble(double, double);
};
