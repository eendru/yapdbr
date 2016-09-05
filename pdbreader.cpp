#include "pdbreader.h"
#include <fstream>


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
    UNKNOW
};

static const std::map<std::srting, PDB_LINE_E> line_names = {
    {"HEADER", HEADER}, {"OBSLTE", OBSLTE}, {TITLE, "TITLE"}, {"CAVEAT", CAVEAT},
    {"COMPND", COMPND}, {"SOURCE", SOURCE}, {KEYWDS, "KEYWDS"}, {EXPDTA, "EXPDTA"},
    {"AUTHOR", AUTHOR}, {"REMARK", REMARK},

    {"DBREF", DBREF}, {"SEQADV", SEQADV}, {"SEQRES", SEQRES}, {"MODRES", MODRES},

    {"HET", HET}, {HETNAM, "HETNAM"}, {"HETSYN", HETSYN}, {"FORMUL", FORMUL},

    {"HELIX", HELIX}, {"SHEET", SHEET}, {"TURN", TURN},
    {"SSBOND", SSBOND}, {"LINK", LINK}, {"HYDBND", HYDBND}, {"SLTBRG", SLTBRG}, {"CISPEP", CISPEP},

    {"SITE", SITE},

    {"CRYST1", CRYST1}, {"ORIGXn", ORIGXn}, {"SCALEn", SCALEn}, {"MTRIXn", MTRIXn},
    {"TVECT", TVECT},

    {"MODEL", MODEL}, {"ATOM", ATOM}, {"SIGATM", SIGATM}, {"ANISOU", ANISOU}, {"SIGUIIJ", SIGUIIJ},
    {"TER", TER}, {"HETATM", HETATM}, {"ENDMDL", ENDMDL},

    {"CONNECT", CONNECT},
    {"MASTER", MASTER}, {"END", END},
};

static PDB_LINE_E
getTypeOfLine(std::string &line) {
    for (auto& kv : line_names) {
        if (!std::strncmp(line, kv.first, kv.first.length())) {
            return kv.second;
        }
    }
    return UNKNOW;
}

PDBReader::PDBReader(std::string &file)
{
    file_ = file;
}

PDBReader::~PDBReader()
{

}
void PDBReader::openParseClose() {
    std::ifstream sfile;
    sfile.open(file, ios::in);

    if (!s.open())
        throw "Can't open file";

    std::string line;
    PDB_LINE_E type;

    while (std::getline(sfile, line)) {
        type = getTypeOfLine(line);
        switch(type) {
        case (HEADER):
            break;

        case (HET):
            break;

        case (MODEL):
            break;

        case (ATOM):
            break;

        case (HETATM):
            break;

        default:
            break;
        }
    }

    sfile.close();
}
