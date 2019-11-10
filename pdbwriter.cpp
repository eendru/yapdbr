#include "pdbwriter.hh"

#include <iostream>
#include <fstream>
#include "pdbreader.hh"

PDBWriter::PDBWriter(const std::string &out_filename) : out_filename_(out_filename)
{}

void PDBWriter::write(const std::string &orig_filename, const std::map<int, std::string> &data)
{
    std::ifstream is1;
    is1.open(orig_filename, std::ios::in);
    if (!is1.is_open()) {
        throw std::string("Can't open file '") + orig_filename.c_str() + std::string("'");
    }


    std::ofstream is_wr;
    std::string filename_to_write(out_filename_);
    is_wr.open(out_filename_, std::fstream::out);
    if (!is_wr.is_open()) {
        is1.close();
        throw std::string("Can't open file '") + out_filename_.c_str() + std::string("'");
    }

    std::cout << "Writing data to '" << out_filename_<< "'" << std::endl;

    std::string line;
    PDB_LINE_E type;

    while (std::getline(is1, line)) {
        std::string str_type = line_type(line);
        const auto &it = line_names.find(str_type);

        if (it == line_names.end()) {
            type = UNKNOWN;
        } else {
            type = it->second;
        }

        if (type == PDB_LINE_E::ATOM) {
            int key = std::atoi(line.substr(6, 10).c_str());
            is_wr.write(data.at(key).c_str(), data.at(key).size());
            is_wr << "\n";
        }
        else {
            is_wr.write(line.c_str(), line.size());
            is_wr << "\n";
        }
    }

    is1.close();
    is_wr.close();
}
