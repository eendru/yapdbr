#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <list>
#include <map>
#include <utility>

typedef struct
{
    double x;
    double y;
    double z;
} coordinates;

coordinates operator + (const coordinates& coordinates1, const coordinates& coordinates2);
coordinates operator - (const coordinates& coordinates1, const coordinates& coordinates2);
coordinates operator * (const coordinates& coordinates1, double lambda);
coordinates operator / (const coordinates& coordinates1, double lambda);
bool operator == (const coordinates & coordinates1, const coordinates & coordinates2);
double scalar_product(const coordinates& coordinates1, const coordinates& coordinates2);
coordinates cross_product(const coordinates& coordinates1, const coordinates& coordinates2);
double euclid_distance(const coordinates& coordinates1, const coordinates& coordinates2);
double norm(const coordinates &c);

typedef coordinates coordinates_t;


typedef std::list<std::pair<coordinates_t, int >> atoms_list_t;

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

   /*
    * std::map<int, std::string>& data - it's data from pdbreader->load()
    */
    YAPDBR(std::map<int, std::string>& data);

   /*
    * Build data with given format in std::list of std::tuples
    */
    atoms_list_t asList(std::string format = "ALL");

   /*
    * Set only CA atoms im data map
    */
    void set_coords(const std::vector<coordinates_t>& al);

    void info_by_pdbid(std::string &result, size_t id);

    std::map<int, std::string> data() { return data_;}

private:
    /*
     * Parse line of pdb file with coordinates to double-coordinates
     */
    coordinates_t to_coordinates(std::string &line);
    int atom_serial_number(std::string &line);

    std::map<size_t, size_t> carbon_id_to_pdbid_map_;
    std::map<int, std::string> data_;
};

