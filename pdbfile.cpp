#include "pdbfile.hh"

static bool IsFileExist(std::string &pdb)
{
    std::ifstream infile(pdb);
    return infile.good();
}

/*TODO think about flags: 
 *              1) Realtive path or absolute
 *              2) Is file should be backuped
 */

static std::ifstream OpenFile(std::string& pdb, std::ifstream& ifs)
{
    ifs.open(pdb, std::ios::in);
    if (!ifs.is_open()) {
        throw std::string("Can't open file");
    }
    return ifs;
}

void ParsePDBStream(std::ifstream &ifs)
{

}

void ParsePDBFile(std::string pdb)
{
    AtomGroup result;
    std::ifstream ifs;
    OpenFile(pdb, ifs);
    result = ParsePDBStream(ifs);

    ifs.close();
}
