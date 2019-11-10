#ifndef PDBREADER_H
#define PDBREADER_H

#include <string>
#include <iostream>
#include <fstream>
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

const std::map<std::string, PDB_LINE_E> line_names = {
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

std::string line_type(const std::string &line);

/* Just open pdb file, read all content, put only atoms lines to std::map and close file */
class PDBReader {
public:
    PDBReader() = default;
    ~PDBReader() = default;

   /*
    * Load pdb file with given filename.
    */
    void load(const std::string &filename);

   /*
    * Get std map with key - atom id (int type) in pdb file
    * and value - string(line from pdb file)
    */
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
