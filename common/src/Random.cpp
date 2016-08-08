#include <Random.hpp>

int Random::nextInt()
{
  return nextInt(max());
}

int Random::nextInt(int max)
{
  return nextInt(min(), max);
} 

int Random::nextInt(int min, int max)
{
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(*this);
}

double Random::nextDouble()
{
  return nextDouble(1.0);
}

double Random::nextDouble(double max)
{
  return nextDouble(0, max);
}

double Random::nextDouble(double min, double max)
{
  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(*this);
}
