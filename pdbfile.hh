#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "atomgroup.hh"

/*
 * This function extends(calls) ParsePDBStream()
 * @arg pdb filename of pdb file
 * @return object of atomgroup class 
 * */
void ParsePDBLine(std::string pdb);
void ParsePDBStream(std::ifstream ifs);

