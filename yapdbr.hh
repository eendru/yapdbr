#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <list>
#include <map>

typedef std::tuple<double, double, double> coordinates_t;
typedef std::list<coordinates_t> atomsList;
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
     * Get data with given format in std::list of std::tuples
     */
    void asList(std::string format = "ALL");

    /*
     * Get list builded with asList() function
     */
    void getList(atomsList &result);

    /*
     * Is asList() function finished correctly
     */
    bool isFinished();

    /*
     * @return std::map with key = id in list, value = id of record in ATOM-started lines
     */
    void getCarbonIdToInfoMap(std::map<size_t, std::string> &result);

    /*
     * Get info from pdb file by atom-record number
     * Each string in pdb file which started with ATOM indexed
     */
    void getInfoStringAboutAtomById(std::string& info, size_t id);
private:
    /*
     * Parse line of pdb file with coordinates to double-coordinates
     */
    coordinates_t toCoordinates(std::string &line);


    std::map<size_t, size_t> carbonIdToPDBId_;
    std::map<int, std::string> data_;
    atomsList result_;
    bool finished_;
};

