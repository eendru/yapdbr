#ifndef PDBWRITER_H
#define PDBWRITER_H

#include <string>
#include <map>

class PDBWriter {
  public:
    PDBWriter() = default;
    ~PDBWriter() = default;

    explicit PDBWriter(const std::string &out_filename);
    void write(const std::string &orig_filename, const std::map<int, std::string> &data);

  private:
    std::string out_filename_;
};

#endif // PDBWRITER_H
