#ifndef RNGHELPER_HPP
#define RNGHELPER_HPP
#include <memory>
#include <random>
#include <string>

class RNGHelper {
 private:
  //  Singleton
  std::default_random_engine eng;
  RNGHelper(const std::string& seed) : eng(StringToInt(seed)), seed_(seed) {}
  static std::shared_ptr<RNGHelper> ptr_;
  // Variables
  const std::string seed_;

 public:
  static std::shared_ptr<RNGHelper> instance(const std::string& seed);
  static int StringToInt(const std::string& str);
  std::string GetSeed();
  int GetRandomInt(int min, int max);
  double GetRandomDouble(double min, double max);
  bool probability(double chance);
};

#endif