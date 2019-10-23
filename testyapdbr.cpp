#include "yapdbr.hh"

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>

std::map<int, std::string> data;
void initMap() {
    data[0] = "ATOM      1  N   MET A   0      23.612   8.367  -9.458  1.00 26.59           N  ";
    data[1] = "ATOM      2  CA  MET A   0      23.871   9.800  -9.365  1.00 25.47           C  ";
    data[2] = "ATOM      3  C   MET A   0      25.258  10.146  -9.871  1.00 23.93           C  ";
    data[3] = "ATOM      4  O   MET A   0      26.193   9.343  -9.767  1.00 24.76           O  ";
    data[4] = "ATOM      5  CB  MET A   0      23.749  10.277  -7.931  1.00 26.67           C  ";
    data[5] = "ATOM      8  CE  MET A   0      24.625  11.379  -5.216  1.00 25.33           C  " ;
    data[6] = "ATOM      9  N   VAL A   1      25.410  11.314 -10.492  1.00 21.05           N  " ;
    data[7] = "ATOM     10  CA  VAL A   1      26.714  11.686 -11.004  1.00 17.92           C  " ;
    data[8] = "ATOM     11  C   VAL A   1      26.993  13.165 -10.812  1.00 15.00           C  " ;
    data[9] = "ATOM     12  O   VAL A   1      26.274  14.013 -11.332  1.00 15.16           O  " ;
    data[10] = "ATOM     13  CB  VAL A   1      26.807  11.327 -12.493  1.00 18.63           C  " ;
    data[11] = "ATOM     15  CG2 VAL A   1      26.413   9.872 -12.704  1.00 19.36           C  " ;
    data[12] = "ATOM     16  N   LEU A   2      28.106  13.504 -10.166  1.00 11.18           N  " ;
    data[13] = "ATOM     17  CA  LEU A   2      28.441  14.899  -9.950  1.00  9.10           C  " ;
    data[14] = "ATOM     18  C   LEU A   2      29.165  15.513 -11.144  1.00  8.17           C  " ;
    data[15] = "ATOM     19  O   LEU A   2      29.774  14.817 -11.960  1.00  8.04           O  " ;
    data[16] = "ATOM     20  CB  LEU A   2      29.360  15.038  -8.744  1.00  7.88           C  " ;
}

atoms_list_t All_Coords;
void initAllAtomsList() {
    All_Coords.clear();
    All_Coords.push_back(std::make_pair(std::make_tuple(23.612, 8.367,  -9.458), 1));   // N
    All_Coords.push_back(std::make_pair(std::make_tuple(23.871, 9.800,  -9.365), 2));   // CA
    All_Coords.push_back(std::make_pair(std::make_tuple(25.258, 10.146, -9.871), 3));   // C
    All_Coords.push_back(std::make_pair(std::make_tuple(26.193, 9.343,  -9.767), 4));   // O
    All_Coords.push_back(std::make_pair(std::make_tuple(23.749, 10.277, -7.931), 5));   // CB
    All_Coords.push_back(std::make_pair(std::make_tuple(24.625, 11.379, -5.216), 6));   // CE
    All_Coords.push_back(std::make_pair(std::make_tuple(25.410, 11.314, -10.492), 7));  // N
    All_Coords.push_back(std::make_pair(std::make_tuple(26.714, 11.686, -11.004), 8));  // CA
    All_Coords.push_back(std::make_pair(std::make_tuple(26.993, 13.165, -10.812), 9));  // C
    All_Coords.push_back(std::make_pair(std::make_tuple(26.274, 14.013, -11.332), 10));  // O
    All_Coords.push_back(std::make_pair(std::make_tuple(26.807, 11.327, -12.493), 11));  // CB
    All_Coords.push_back(std::make_pair(std::make_tuple(26.413, 9.872,  -12.704), 12));  // CG2
    All_Coords.push_back(std::make_pair(std::make_tuple(28.106, 13.504, -10.166), 13));  // N
    All_Coords.push_back(std::make_pair(std::make_tuple(28.441, 14.899, -9.950), 14));   // CA
    All_Coords.push_back(std::make_pair(std::make_tuple(29.165, 15.513, -11.144), 15));  // C
    All_Coords.push_back(std::make_pair(std::make_tuple(29.774, 14.817, -11.960), 16));  // O
    All_Coords.push_back(std::make_pair(std::make_tuple(29.360, 15.038, -8.744), 17));   // CB
}

atoms_list_t CA_Coords;
void initCA_AtomsList() {
    CA_Coords.clear();
    CA_Coords.push_back(std::make_pair(std::make_tuple(23.871, 9.800,  -9.365), 2));   // CA
    CA_Coords.push_back(std::make_pair(std::make_tuple(26.714, 11.686, -11.004), 8));  // CA
    CA_Coords.push_back(std::make_pair(std::make_tuple(28.441, 14.899, -9.950), 14));   // CA
}

atoms_list_t CB_Coords;
void initCB_AtomsList() {
    CB_Coords.clear();
    CB_Coords.push_back(std::make_pair(std::make_tuple(23.749, 10.277, -7.931), 5));   // CB
    CB_Coords.push_back(std::make_pair(std::make_tuple(26.807, 11.327, -12.493), 11));  // CB
    CB_Coords.push_back(std::make_pair(std::make_tuple(29.360, 15.038, -8.744), 17));   // CB
}

double eps = 0.001;

bool compareAtomsLists(atoms_list_t &fromYAPDBR, atoms_list_t &realCoords) {

    // size shoul be equal
    if (fromYAPDBR.size() != realCoords.size()) {
        std::cout << "Size not equal " << fromYAPDBR.size() << " and "
                  << realCoords.size() << "\n";
        exit(-1);
    }

    bool result = true;
    atoms_list_t::iterator itc = fromYAPDBR.begin(), ite = fromYAPDBR.end();
    atoms_list_t::iterator itl = realCoords.begin(), ile = realCoords.end();

    for (; itc != ite; ++itc, ++itl) {
        if (fabs(std::get<0>((*itc).first) - std::get<0>((*itl).first)) > eps) {
            std::cout << "Fail at: " << std::get<0>((*itc).first) << " and " << std::get<0>((*itl).first);
            result = false;
        }

        if (fabs(std::get<1>((*itc).first) - std::get<1>((*itl).first)) > eps) {
            std::cout << "Fail at: " << std::get<1>((*itc).first) << " and " << std::get<1>((*itl).first);
            result = false;
        }


        if (fabs(std::get<2>((*itc).first) - std::get<2>((*itl).first)) > eps) {
            std::cout << "Fail at: " << std::get<2>((*itc).first) << " and " << std::get<2>((*itl).first);
            result = false;
        }

    }

   return true;
}

bool test()
{
    YAPDBR r(data);
    atoms_list_t all, ca, cb;

    all = r.asList("ALL");

    ca = r.asList("CA");

    cb = r.asList("CB");

    std::cout << "Check all atoms: \n";
    atoms_list_t::iterator itc = All_Coords.begin(), ite = All_Coords.end();
    bool bAll = compareAtomsLists(all, All_Coords);
    if (bAll)
        std::cout << "            Passed\n";

    std::cout << "Check CA atoms: \n";
    bool bCA = compareAtomsLists(ca, CA_Coords);
    if (bCA)
        std::cout << "            Passed\n";

    std::cout << "Check CB atoms: \n";
    bool bCB = compareAtomsLists(cb, CB_Coords);
    if (bCB)
        std::cout << "            Passed\n";


    return bAll && bCA && bCB;
}

int main () {
    initMap();
    initAllAtomsList();
    initCA_AtomsList();
    initCB_AtomsList();

    if (test())
        exit(0);
    else
        exit(1);  // if exit(0) test wil be passed
                  // if exit(1) test will be failed
}

