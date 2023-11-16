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
