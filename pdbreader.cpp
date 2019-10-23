#include "pdbreader.hh"
#include <cstring>
#include <map>

enum PDB_LINE_E {
    HEADER, OBSLTE, TITLE, CAVEAT, COMPND, SOURCE, KEYWDS, EXPDTA, AUTHOR, REVDAT, SPRSDE, JRNL, REMARK,
    DBREF, SEQADV, SEQRES, MODRES,
    HET, HETNAM, HETSYN, FORMUL,
    HELIX, SHEET, TURN,
    SSBOND, LINK, HYDBND, SLTBRG, CISPEP,
    SITE,
    CRYST1, ORIGX1, ORIGX2, ORIGX3, SCALE1, SCALE2, SCALE3, MTRIX1, MTRIX2, MTRIX3, TVECT,
    MODEL, ATOM, SIGATM, ANISOU, SIGUIIJ, TER, HETATM, ENDMDL,
    CONNECT,
    MASTER, END,
    UNKNOWN
};

static const std::map<std::string, PDB_LINE_E> line_names = {
    {"HEADER", HEADER}, {"OBSLTE", OBSLTE}, {"TITLE", TITLE}, {"CAVEAT", CAVEAT},
    {"COMPND", COMPND}, {"SOURCE", SOURCE}, {"KEYWDS", KEYWDS}, {"EXPDTA", EXPDTA},
    {"AUTHOR", AUTHOR}, {"REMARK", REMARK}, {"REVDAT", REVDAT}, {"SPRSDE", SPRSDE},
    {"JRNL", JRNL},

    {"DBREF", DBREF}, {"SEQADV", SEQADV}, {"SEQRES", SEQRES}, {"MODRES", MODRES},

    {"HET", HET}, {"HETNAM", HETNAM}, {"HETSYN", HETSYN}, {"FORMUL", FORMUL},

    {"HELIX", HELIX}, {"SHEET", SHEET}, {"TURN", TURN},
    {"SSBOND", SSBOND}, {"LINK", LINK}, {"HYDBND", HYDBND}, {"SLTBRG", SLTBRG}, {"CISPEP", CISPEP},

    {"SITE", SITE},

    {"CRYST1", CRYST1}, {"ORIGX1", ORIGX1},  {"ORIGX2", ORIGX2},  {"ORIGX3", ORIGX3},
    {"SCALE1", SCALE1}, {"SCALE2", SCALE2}, {"SCALE3", SCALE3},
    {"MTRIX1", MTRIX2}, {"MTRIX2", MTRIX2}, {"MTRIX3", MTRIX3},

    {"TVECT", TVECT},

    {"MODEL", MODEL}, {"ATOM", ATOM}, {"SIGATM", SIGATM}, {"ANISOU", ANISOU}, {"SIGUIIJ", SIGUIIJ},
    {"TER", TER}, {"HETATM", HETATM}, {"ENDMDL", ENDMDL},

    {"CONECT", CONNECT},
    {"MASTER", MASTER}, {"END", END},

    {"UNKNOWN", UNKNOWN},
};

static std::string line_type(const std::string &line) {
    std::string result;
    for (const auto &c : line){
        if (c == ' ')
            break;
        else
            result.push_back(c);
    }

    return result;
}

void PDBReader::open(const std::string &filename) {
    file_ = filename;
    is_.open(file_, std::ios::in);
    if (!is_.is_open()) {
        throw std::string("Can't open file '") + file_.c_str() + std::string("'");
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

void PDBReader::load(const std::string &filename) {
    try {
        open(filename);
    } catch (std::string &s) {
        std::cerr << s << " ";
        close();
        throw s;
    }
    parse();
    close();
}
