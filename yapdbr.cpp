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
    finished_ = false;
}

atom_type_t getAtomType(std::string &line) {
    std::string s_type = line.substr(12, 4);
    std::string s_type_trimmed = trim(s_type);
    string_atom_type_map_t::const_iterator it = type_atom_map.find(s_type_trimmed);

    if (it == type_atom_map.end())
        return UNKN;
    else
        return it->second;
}

void YAPDBR::getInfoStringAboutAtomById(std::string& info, size_t id) {
    try {
        info = data_.at(id);
    } catch (std::out_of_range &e) {
        std::cerr << "Index " << id << " out of range at map\n";
    }
}

static double stringToDouble(std::string s) {
    double result;
    std::stringstream ss;

    ss << s;
    ss >> result;
    return result;
}

coordinates_t YAPDBR::toCoordinates(std::string &line) { 
/* 31 - 38        Real(8.3)       x             Orthogonal coordinates for X in
 *                                              Angstroms.
 * 39 - 46        Real(8.3)       y             Orthogonal coordinates for Y in
 *                                              Angstroms.
 * 47 - 54        Real(8.3)       z             Orthogonal coordinates for Z in
 *                                              Angstroms.
 */
    double x = 0.0, y = 0.0, z = 0.0;
    x = stringToDouble(line.substr(30, 8));
    y = stringToDouble(line.substr(38, 8));
    z = stringToDouble(line.substr(46, 8));

    return std::make_tuple(x, y, z);
}

atomsList YAPDBR::asList(std::string format) {
    string_atom_type_map_t::const_iterator it = type_atom_map.find(format);
    
    if (it == type_atom_map.end())
        throw std::string("Format can't be interpreted");
    
    atomsList result;
    std::map<int, std::string>::iterator itb = data_.begin(), ite = data_.end();

    size_t i = 0;
    if (format == "ALL") {
        for (itb = data_.begin(); itb != ite; ++itb) {
            carbonIdToPDBId_[i] = i;
            coordinates_t tmp = toCoordinates(itb->second);
            result.push_back(tmp);
            i++;
        }
    } else {
        size_t j = 0;
        for (itb = data_.begin(); itb != ite; ++itb) {
            atom_type_t type;
            
            type = getAtomType(itb->second);
            if (type == UNKN) {
                // TODO error.log or something ?
                std::cerr << "[Warning] Unknow type at line " << itb->second << "\n";
                continue;
            }
           
            if (type == it->second) {
                carbonIdToPDBId_[j] = i;
                coordinates_t tmp = toCoordinates(itb->second);
                result.push_back(tmp);
                j++;
            }
            i++;
        }
    }

    finished_ = true;
    return result;
}

bool YAPDBR::isFinished() {
    return finished_;
}

// TODO don't usr asList()
atomsVector YAPDBR::asVector(std::string format) {
    atomsList t = asList(format);
    atomsVector result;
    std::copy(t.begin(), t.end(), back_inserter(result));

    return result;
}
