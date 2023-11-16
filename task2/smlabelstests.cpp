#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "smartlabels.h"
#include <iostream>
#include <vector>
#include <random>

class tst
{
private:
    int64_t num;

public:
    tst() = delete;
    tst(const tst &pt) = delete;
    tst(tst &&pt) = delete;

    tst &operator=(const tst &pt) = delete;
    tst &operator=(tst &&pt) = delete;
};

TEST_CASE("uniqueptr")
{
    uniqueptr<int64_t> pt(new int64_t(7));
    uniqueptr<int64_t> ptn(new int64_t(33));
    REQUIRE(*pt == 7);

    *pt += 9;
    REQUIRE(*pt == 16);

    REQUIRE(*pt + *ptn == 49);

    uniqueptr<std::vector<int64_t>> ptv(new std::vector<int64_t>(3));
    ptv->clear();
    ptv->push_back(16);
    ptv->push_back(23);
    ptv->push_back(81);
    REQUIRE((*ptv)[2] == 81);
    REQUIRE(ptv->size() == 3);

    ptv->push_back(10);
    REQUIRE((*ptv)[3] == 10);
    ptv->resize(4);
    REQUIRE(ptv->size() == 4);
    REQUIRE((*ptv).size() == 4);
};

TEST_CASE("sharedptr")
{
    sharedptr<int64_t> pt(new int64_t(16));
    sharedptr<int64_t> ptn(new int64_t(10));

    *pt += 17;
    REQUIRE(*pt == 33);
    REQUIRE(*pt + *ptn == 43);
    pt = ptn;
    REQUIRE(*pt + *ptn == 20);

    sharedptr<int64_t> *ptc = new sharedptr<int64_t>(pt);
    REQUIRE(*(*ptc) == 10);
}
