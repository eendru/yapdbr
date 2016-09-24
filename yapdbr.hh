#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <list>
#include <map>

typedef std::tuple<double, double, double> coordinates_t;
typedef std::list<coordinates_t> atomsList;
typedef std::vector<coordinates_t> atomsVector;

enum ATOM_TYPE_E{
    CA,
    CB,
    N,
    C,
    O,
    ALL,   // for all type of atoms
    UNKN,  // UNKNOWN
};
typedef ATOM_TYPE_E atom_type_t;
typedef std::map<std::string, atom_type_t> string_atom_type_map_t;

static const string_atom_type_map_t type_atom_map = {
    {"CA", CA},
    {"CB", CB},
    {"N", N},
    {"C", C},
    {"O", O},
    {"ALL", ALL},
    {"UNKN", UNKN},
};

atom_type_t getAtomType(std::string &line);


class YAPDBR {
public:
	YAPDBR(std::map<int, std::string>& data);
	atomsList asList(std::string format = "ALL");
    atomsVector asVector(std::string format = "ALL");
private:
    coordinates_t toCoordinates(std::string &line);

    std::map<int, std::string> data_;
};

