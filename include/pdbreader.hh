#ifndef PDBREADER_H
#define PDBREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>

class PDBReader {
public:
    PDBReader(std::string &file);
    ~PDBReader();
    void parsePDB();

    std::map<int, std::string>& getData();

private:
    std::string file_;
    std::ifstream is_;
    std::map<int, std::string> data_;

    void open();
    void close();
    void parse();
};

#endif // PDBREADER_H
