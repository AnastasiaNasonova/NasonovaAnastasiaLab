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
    int pin, pout;
    Pipe(); 
    static void setMaxID(const int id) { MaxID = id; }
    static int getMaxID() { return MaxID; }
    int getId() { return id; }

    int getDiameter() { return d; }
    float getLenght() { return l; }
    bool getRepair() const { return r; }

    void redact();
    void link(int in, int out);
    void ClearLink();

    friend std::ostream& operator <<(std::ostream& out, const Pipe& p);
    friend std::istream& operator >>(std::istream& in, Pipe& p);

    friend std::ofstream& operator <<(std::ofstream& fout, const Pipe& p);
    friend std::ifstream& operator >>(std::ifstream& fin, Pipe& p);
};

