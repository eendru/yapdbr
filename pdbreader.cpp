#include "pdbreader.hh"
#include <cstring>
#include <map>

enum PDB_LINE_E {
    HEADER, OBSLTE, TITLE, CAVEAT, COMPND, SOURCE, KEYWDS, EXPDTA, AUTHOR, REMARK,
    DBREF, SEQADV, SEQRES, MODRES,
    HET, HETNAM, HETSYN, FORMUL,
    HELIX, SHEET, TURN,
    SSBOND, LINK, HYDBND, SLTBRG, CISPEP,
    SITE,
    CRYST1, ORIGXn, SCALEn, MTRIXn, TVECT,
    MODEL, ATOM, SIGATM, ANISOU, SIGUIIJ, TER, HETATM, ENDMDL,
    CONNECT,
    MASTER, END,
    UNKNOWN
};

static const std::map<std::string, PDB_LINE_E> line_names = {
    {"HEADER", HEADER}, {"OBSLTE", OBSLTE}, {"TITLE", TITLE}, {"CAVEAT", CAVEAT},
    {"COMPND", COMPND}, {"SOURCE", SOURCE}, {"KEYWDS", KEYWDS}, {"EXPDTA", EXPDTA},
    {"AUTHOR", AUTHOR}, {"REMARK", REMARK},

    {"DBREF", DBREF}, {"SEQADV", SEQADV}, {"SEQRES", SEQRES}, {"MODRES", MODRES},

    {"HET", HET}, {"HETNAM", HETNAM}, {"HETSYN", HETSYN}, {"FORMUL", FORMUL},

    {"HELIX", HELIX}, {"SHEET", SHEET}, {"TURN", TURN},
    {"SSBOND", SSBOND}, {"LINK", LINK}, {"HYDBND", HYDBND}, {"SLTBRG", SLTBRG}, {"CISPEP", CISPEP},

    {"SITE", SITE},

    {"CRYST1", CRYST1}, {"ORIGXn", ORIGXn}, {"SCALEn", SCALEn}, {"MTRIXn", MTRIXn},
    {"TVECT", TVECT},

    {"MODEL", MODEL}, {"ATOM", ATOM}, {"SIGATM", SIGATM}, {"ANISOU", ANISOU}, {"SIGUIIJ", SIGUIIJ},
    {"TER", TER}, {"HETATM", HETATM}, {"ENDMDL", ENDMDL},

    {"CONNECT", CONNECT},
    {"MASTER", MASTER}, {"END", END},

    {"UNKNOWN", UNKNOWN},
};

static std::string
getStringTypeOfLine(std::string &line) {
    std::string result;
    for (auto c : line){
        if (c == ' ')
            break;
        else
            result.push_back(c);
    }

    return result;
}

PDBReader::PDBReader(std::string &file)
{
    file_ = file;
}

PDBReader::~PDBReader()
{

}
void PDBReader::open() {
    is_.open(file_, std::ios::in);
    if (!is_.is_open()) {
        throw std::string("Can't open file");
    }
}

void PDBReader::close() {
    is_.close();
}

std::map<int, std::string>& PDBReader::Data() {
    return data_;
}

void PDBReader::parse() {
    std::string line;
    PDB_LINE_E type;

    while (std::getline(is_, line)) {
        std::string strType = getStringTypeOfLine(line);
        type = line_names.at(strType);

        switch(type) {
        case (HEADER):
            break;

        case (HET):
            break;

        case (MODEL):
            break;

        case (ATOM): {
	    int key = std::atoi(line.substr(6, 10).c_str());
	    data_[key] = line.substr(11, line.length());
            break;
	}

        case (HETATM):
            break;

        case (UNKNOWN):
	        std::cerr << "Something bad with your pdb";
	        return;
        default:
            break;
        }
    }
}

void PDBReader::parsePDB() {
    try {
        open();
    } catch (std::string &s) {
            std::cerr << s << " ";
            return;
    }
    parse();
    close();
}
