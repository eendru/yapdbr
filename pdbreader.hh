#ifndef PDBREADER_H
#define PDBREADER_H

#include <string>
#include <iostream>
#include <fstream>

class PDBReader {
public:
    PDBReader(std::string &file);
    ~PDBReader();
    void parsePDB();

private:
    std::string file_;
    std::ifstream is_;

    void open();
    void close();
    void parse();
};

#endif // PDBREADER_H
