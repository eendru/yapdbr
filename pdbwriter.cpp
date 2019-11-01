#include "pdbwriter.hh"

#include <iostream>
#include <fstream>
#include "pdbreader.hh"

PDBWriter::PDBWriter(const std::string &prefix) : prefix_(prefix)
{}

void PDBWriter::write(const std::string &original, std::map<int, std::string> &data)
{
    std::ifstream is1;
    is1.open(original, std::ios::in);
    if (!is1.is_open()) {
        throw std::string("Can't open file '") + original.c_str() + std::string("'");
    }


    std::ofstream is_wr;
    std::string filename_to_write(prefix_ + original);
    is_wr.open(filename_to_write, std::fstream::out);

    std::string line;
    PDB_LINE_E type;

    while (std::getline(is1, line)) {
        std::string str_type = line_type(line);
        auto it = line_names.find(str_type);

        if (it == line_names.end()) {
            type = UNKNOWN;
        } else {
            type = it->second;
        }

        if (type == PDB_LINE_E::ATOM) {
            int key = std::atoi(line.substr(6, 10).c_str());
            is_wr.write(data[key].c_str(), data[key].size());
        }
        else {
            is_wr.write(line.c_str(), line.size());
        }
    }

    is1.close();
    is_wr.close();
}
