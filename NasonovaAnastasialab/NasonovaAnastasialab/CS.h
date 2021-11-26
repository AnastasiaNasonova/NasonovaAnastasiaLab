#pragma once
#include <string>
#include <iostream>
#include <fstream>

class CS
{
    static int MaxID;
    int id;
    std::string name;
    int numW, numA;
public: 
    
    CS();
    static void setMaxID(const int id) { MaxID = id; }
    static int getMaxID() { return MaxID; }
    int getID() { return id; }

    std::string getName() const { return name; }
    int getNumA() const { return numA; }
    int getNumW() const { return numW; }

    friend std::ostream& operator <<(std::ostream& out, const CS& c);
    friend std::istream& operator >>(std::istream& in, CS& c);
    
    friend std::ofstream& operator <<(std::ofstream& fout, const CS& c);
    friend std::ifstream& operator >>(std::ifstream& fin, CS& c);
};

