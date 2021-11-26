#pragma once
#include <iostream>
#include <fstream>

class Pipe
{
    static int MaxID;
    int id;
    int d;
    float l;
    bool r;
public:
    Pipe(); 
    static void setMaxID(const int id) { MaxID = id; }
    static int getMaxID() { return MaxID; }
    int getId() { return id; }

    int getDiameter() { return d; }
    float getLenght() { return l; }
    bool getRepair() { return r; }

    friend std::ostream& operator <<(std::ostream& out, const Pipe& p);
    friend std::istream& operator >>(std::istream& in, Pipe& p);
};

