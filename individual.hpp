#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#define DEFAULT_FOOD -1

enum class Behavior { Passive, Aggressive, Adaptable };

class Individual {
 private:
  double food_;
  Behavior behavior_;

 public:
  Individual(Behavior new_behavior);
  Individual();
  double GetFood() const;
  Behavior GetBehavior() const;
  void SetFood(double new_food);
};

#endif