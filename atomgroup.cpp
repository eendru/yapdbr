#pragma once
#include "atomgroup.hh"


AtomGroup::AtomGroup()
{
}

std::string AtomGroup::Title()
{
    std::string title = "Atom group " + title_;
    return title;
}
