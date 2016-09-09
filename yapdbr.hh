#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <list>

struct coordinates {
    long x;
    long y;
    long z;
};

class YAPDBR {
public:
	YAPDBR();
	std::list<std::tuple<double, double, double> > asList();
private:
};
