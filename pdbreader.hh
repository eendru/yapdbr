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
    bool isParsingDone();

    std::map<int, std::string>& getData();

private:
    std::string file_;
    std::ifstream is_;
    std::map<int, std::string> data_;
    bool done_;

    void open();
    void close();
    void parse();
};

#endif // PDBREADER_H
