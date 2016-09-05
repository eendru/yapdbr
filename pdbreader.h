#ifndef PDBREADER_H
#define PDBREADER_H


class PDBReader
{
private:
    std::string file_;
public:
    PDBReader(std::string &file = "");
    ~PDBReader();
    void opeParseClose();
};

#endif // PDBREADER_H
