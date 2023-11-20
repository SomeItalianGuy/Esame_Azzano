#include "rnghelper.hpp"

#include <iostream>
// Singleton
std::shared_ptr<RNGHelper> RNGHelper::ptr_;

std::shared_ptr<RNGHelper> RNGHelper::instance(const std::string& seed) {
  if (!ptr_) {
    ptr_ = std::shared_ptr<RNGHelper>(new RNGHelper(seed));
  }
  return ptr_;
}

// Class methods
int RNGHelper::StringToInt(const std::string& str) {
  int ans{};
  for (long unsigned int i = 0; i < str.length(); ++i) {
    ans += str[i];
  }
  return ans;
}

std::string RNGHelper::GetSeed() { return seed_; }

int RNGHelper::GetRandomInt(int min, int max) {
  std::uniform_int_distribution distr(min, max);
  return distr(eng);
}

double RNGHelper::GetRandomDouble(double min, double max) {
  std::uniform_real_distribution distr(min, max);
  return distr(eng);
}

bool RNGHelper::probability(double chance) {
  std::uniform_real_distribution distr_(0.0, 1.0);
  if (distr_(eng) <= chance) {
    return true;
  } else {
    return false;
  }
}
