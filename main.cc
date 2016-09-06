#include "pdbreader.hh"

int main() {
    std::string file = std::string("1ABS.pdb");
    PDBReader pr(file);
    pr.parsePDB();

    return 0;
}
