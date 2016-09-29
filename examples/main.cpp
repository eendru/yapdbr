#include <cstdlib>
#include <iostream>

#include "yapdbr.hh"
#include "pdbreader.hh"


void printList(atomsList &l) {
    atomsList::iterator it1 = l.begin(), it2 = l.end();
    for (; it1 != it2; ++it1) {
        std::cout << std::get<0>(*it1) << " " << std::get<1>(*it1) << " " << std::get<2>(*it1) << "<-\n";
    }
}

int main() {
    std::string file = std::string("1ABS.pdb");
    PDBReader pr(file);
    pr.parsePDB();
    std::map<int, std::string> data = pr.getData();

    YAPDBR y(data);
    y.asList("ALL");
    atomsList l = y.asList("CA");
    printList(l);

    return 0;
}
