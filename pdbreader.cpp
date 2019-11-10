#include "pdbreader.hh"
#include <cstring>
#include <map>

PDBReader::PDBReader(const std::string &in_filename) : in_filename_(in_filename)
{}

std::string line_type(const std::string &line) {
    std::string result;
    for (const auto &c : line){
        if (c == ' ')
            break;
        else
            result.push_back(c);
    }

    return result;
}

void PDBReader::open() {
    is_.open(in_filename_, std::ios::in);
    if (!is_.is_open()) {
        throw std::string("Can't open file '") + in_filename_.c_str() + std::string("'");
    }
}

void PDBReader::close() {
    is_.close();
}

std::map<int, std::string>& PDBReader::data() {
    return data_;
}

void PDBReader::parse() {
    std::string line;
    PDB_LINE_E type;
    std::string zeroEntryString = "This is test string for data_[0]";
    data_.insert(std::make_pair(0, zeroEntryString));
    long unsigned int i = 0;

    while (std::getline(is_, line)) {
        std::string str_type = line_type(line);
        auto it = line_names.find(str_type);
        if (it == line_names.end()) {
            type = UNKNOWN;
        } else {
            type = it->second;
        }

        switch(type) {

        case (ATOM): {
            int key = std::atoi(line.substr(6, 10).c_str());
            data_.insert(std::make_pair(key, line));
            break;
        }

        case (UNKNOWN):
            i++;
            break;

        case (HEADER):
        case (HET):
        case (MODEL):
        case (HETATM):
        default:
            break;
        }
    }
    std::cerr << "Number of UNKNOWN lines " << i << "\n";
}

void PDBReader::load() {
    try {
        open();
    } catch (std::string &s) {
        std::cerr << s << " ";
        close();
        throw s;
    }
    parse();
    close();
}
