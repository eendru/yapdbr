#pragma once
#include "coordinates.hh"
#include <array>

/*
 * All data in this class is stored in arrays
 *
 * Get-methods
 * Set-methods 
 * */
class AtomGroup {
    uint32_t n_atoms_;
    std::string title_;
    std::array<coordinates> coords_;

    // TODO chain arg
    // investigate this
 
public:
    std::string Title();
};
