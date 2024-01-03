#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graphic.hpp"
#include "individual.hpp"
#include "logical.hpp"
#include "population.hpp"
#include "rnghelper.hpp"
#include "simulation.hpp"

#ifdef MY_ROOT
#include "roothelper.hpp"
#endif

TEST_CASE("Testing namespace Logical") {
  SUBCASE("Testing InitializeVectorAndIndex") {
    const int nSamples = 15;
    std::vector<int> v, id;
    v.push_back(1);
    CHECK_THROWS(Logic::InitializeVectorAndIndex(v, id, nSamples));
    v.clear();
    id.push_back(1);
    CHECK_THROWS(Logic::InitializeVectorAndIndex(v, id, nSamples));
    id.clear();
    CHECK_NOTHROW(Logic::InitializeVectorAndIndex(v, id, nSamples));
    CHECK(v.size() == nSamples);
    CHECK(id.size() == nSamples);
    for (int i = 0; i < nSamples - 1; i++) {
      CHECK(id[i] == i);
    }
  }
}

TEST_CASE("Testing Population") {
  SUBCASE("Testing Place") {
    const int index_first = 1;
    const int index_second = 2;
    Place p;
    CHECK(!p.isFull());
    CHECK(!p.isHalfFull());
    p.Add_Index(index_first);
    CHECK(!p.isFull());
    CHECK(p.isHalfFull());
    CHECK(p.firstIndex_ == index_first);
    p.Add_Index(index_second);
    CHECK(p.isFull());
    CHECK(!p.isHalfFull());
    CHECK(p.firstIndex_ == index_first);
    CHECK(p.secondIndex_ == index_second);
    CHECK_THROWS(p.Add_Index(3));
  }
  SUBCASE("Testing GenerationData") {
    GenerationData g;
    CHECK(g.GetTotalPopulation() == 0);
    CHECK(g.GetPassivePercentage() == 0);
    CHECK(g.GetAggressivePercentage() == 0);
    CHECK(g.GetAdaptablePercentage() == 0);
  }
  SUBCASE("Testing Population") {
    const double rR = 3.6, perc = 1.4;
    const int sP = 1;
    CHECK_THROWS(Population::Population_instance(rR, 0, perc));
    std::shared_ptr<Population> p =
        Population::Population_instance(rR, sP, perc);
    std::vector<int> id_List;
    id_List.push_back(1);
    CHECK_THROWS(p->Get_IdList(id_List));
    CHECK_THROWS(p->Get_IndividualFood(9));  // 9 just means non existent
    CHECK_THROWS(p->Calculate_currentPercentage());
    p = Population::Population_instance(rR, sP, -1);
    CHECK_THROWS(p->Calculate_currentPercentage());
  }
}

#ifdef MY_ROOT
TEST_CASE("Testing RootHelper") {
  RootHelper root("", "", 700, 500);

  SUBCASE("Testing Divide") {
    CHECK_THROWS_MESSAGE(root.DivideCanvas(-1, 1),
                         "Cannot divide the Canvas in 0 or less lines");

    CHECK_THROWS_MESSAGE(root.DivideCanvas(1, -1),
                         "Cannot divide the Canvas in 0 or less columns");

    CHECK_THROWS_MESSAGE(root.DivideCanvas(-1, -1),
                         "Cannot divide the Canvas in 0 or less lines");

    CHECK_THROWS_MESSAGE(root.DivideCanvas(0, 1),
                         "Cannot divide the Canvas in 0 or less lines");

    CHECK_THROWS_MESSAGE(root.DivideCanvas(1, 0),
                         "Cannot divide the Canvas in 0 or less columns");

    CHECK_THROWS_MESSAGE(root.DivideCanvas(0, 0),
                         "Cannot divide the Canvas in 0 or less lines");
    CHECK_NOTHROW(root.DivideCanvas(1, 1));
  }
  SUBCASE("Testing Draw") {
    root.DivideCanvas(2, 1);
    CHECK_THROWS(root.Draw(5, "", "", "", "", kBlue));
    CHECK_NOTHROW(root.Draw(1, "", "", "", "", kBlue));
    CHECK_NOTHROW(root.Draw(2, "", "", "", "", kBlue));
  }
}
#endif