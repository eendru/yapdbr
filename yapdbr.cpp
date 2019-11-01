#include "yapdbr.hh"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// TODO should be tested
// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
    std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

YAPDBR::YAPDBR(std::map<int, std::string> &data) {
    data_ = data;
}

atom_type_t get_atom_type(std::string &line) {
    std::string s_type = line.substr(12, 4);
    std::string s_type_trimmed = trim(s_type);
    string_atom_type_map_t::const_iterator it = type_atom_map.find(s_type_trimmed);

    if (it == type_atom_map.end()) {
        return UNKN;
    } else {
        return it->second;
    }
}

coordinates_t YAPDBR::to_coordinates(std::string &line) {
/* 31 - 38        Real(8.3)       x             Orthogonal coordinates for X in
 *                                              Angstroms.
 * 39 - 46        Real(8.3)       y             Orthogonal coordinates for Y in
 *                                              Angstroms.
 * 47 - 54        Real(8.3)       z             Orthogonal coordinates for Z in
 *                                              Angstroms.
 */
    double x = std::stod(line.substr(30, 8));
    double y = std::stod(line.substr(38, 8));
    double z = std::stod(line.substr(46, 8));

    return std::make_tuple(x, y, z);
}

std::string pdb_string_from_coordinates(coordinates_t c, const std::string &original_line)
{
    std::string result(original_line);

    std::string x = std::to_string(std::get<0>(c));
    x.resize(8, 0);
    result.assign(x, 30, 8);

    x = std::to_string(std::get<0>(c));
    x.resize(8, 0);
    result.assign(x, 38, 8);

    x = std::to_string(std::get<0>(c));
    x.resize(8, 0);
    result.assign(x, 46, 8);

    return result;
}

int YAPDBR::atom_serial_number(std::string &line) {
/*     7 - 11        Integer         serial        Atom serial number. */
    return std::stoi(line.substr(6, 10)); // TODO 10 ? maybe 6?
}

void YAPDBR::info_by_pdbid(std::string &result, size_t id) {
    result = data_.at(id);
}

atoms_list_t YAPDBR::asList(std::string format) {
    string_atom_type_map_t::const_iterator format_type = type_atom_map.find(format);

    if (format_type == type_atom_map.end()) {
        throw "Format can't be interpreted";
    }

    atoms_list_t result;
    std::map<int, std::string>::iterator itb = data_.begin(), ite = data_.end();

    size_t i = 0;
    if (format == "ALL") {
        for (itb = data_.begin(); itb != ite; ++itb) {
            carbon_id_to_pdbid_map_[i] = i + 1;
            coordinates_t tmp = to_coordinates(itb->second);
            int x = atom_serial_number(itb->second);
            result.push_back(std::make_pair(tmp, x));
            i++;
        }
    } else {
        size_t j = 0;
        i = 1;
        for (itb = data_.begin(); itb != ite; ++itb) {
            if (get_atom_type(itb->second) == format_type->second) {
                carbon_id_to_pdbid_map_[j] = i;
                result.push_back(std::make_pair(to_coordinates(itb->second), atom_serial_number(itb->second)));
                j++;
            }
            i++;
        }
    }

    return result;
}

void YAPDBR::set_coords(atoms_list_t &al)
{
    std::map<int, std::string>::iterator itm_b = data_.begin(), itm_e = data_.end();
    atoms_list_t::iterator itl_b = al.begin(), itl_e = al.end();

    size_t i = 0;
    // Iterate over data map
    // Check line type
    //
    for (itm_b = data_.begin(); itm_b != itm_e; ++itm_b) {
        if (get_atom_type(itm_b->second) == ATOM_TYPE_E::CA) {
            if (itl_b != itl_e) {
                itm_b->second = pdb_string_from_coordinates(itl_b->first, itm_b->second);
                itl_b ++;
            }
        }
    }
}
