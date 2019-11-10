#ifndef PDBWRITER_H
#define PDBWRITER_H

#include <string>
#include <map>

class PDBWriter {
  public:
    PDBWriter() = default;
    ~PDBWriter() = default;

    explicit PDBWriter(const std::string &prefix = "new_");
    void write(const std::string &original, const std::map<int, std::string> &data);

  private:
    std::string prefix_;
};

#endif // PDBWRITER_H
