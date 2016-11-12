#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <list>
#include <map>
#include <utility>

typedef std::tuple<double, double, double> coordinates_t;
typedef std::list<std::pair<coordinates_t, int >> atomsList;
typedef std::vector<coordinates_t> atomsVector;

// This enum is used as format for what we need.
// Think about logic expression on this enum
// For example CA || CB
// See ProDy python package

enum ATOM_TYPE_E{
    CA,
    CB,
    N,
    C,
    O,
    CE,
    CG2,
    ALL,   // for all type of atoms
    UNKN,  // UNKNOWN
};
typedef ATOM_TYPE_E atom_type_t;
typedef std::map<std::string, atom_type_t> string_atom_type_map_t;

const string_atom_type_map_t type_atom_map = {
    {"CA", CA},
    {"CB", CB},
    {"CE", CE},
    {"CG2", CG2},
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

    /*
     * Build data with given format in std::list of std::tuples
     */
    void asList(std::string format = "ALL");

    /*
     * Get list builded with asList() function
     */
    void getList(atomsList &result);

    /*
     * If asList() function finished correctly
     */
    bool isFinished();

    void getInfoLineByPDBId(std::string &result, size_t id);

private:
    /*
     * Parse line of pdb file with coordinates to double-coordinates
     */
    coordinates_t toCoordinates(std::string &line);
    int getPDBId(std::string &line);

    std::map<size_t, size_t> carbonIdToPDBId_;
    std::map<int, std::string> data_;
    atomsList result_;
    bool finished_;
};

