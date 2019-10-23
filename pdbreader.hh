#ifndef PDBREADER_H
#define PDBREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>

class PDBReader {
public:
    PDBReader() = default;
    ~PDBReader() = default;

    void load(const std::string &filename);

    std::map<int, std::string>& data();

private:
    std::string file_;
    std::ifstream is_;
    std::map<int, std::string> data_;

    void open(const std::string &filename);
    void close();
    void parse();
};

#endif // PDBREADER_H
