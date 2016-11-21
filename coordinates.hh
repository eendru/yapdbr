#pragma once

struct Coordinates {
    double x_;
    double y_;
    double z_;
    
    Coordinates(double x = -1.0, double y = -1.0, double z = -1.0);
    void Set(double x, double y, double z);
};
