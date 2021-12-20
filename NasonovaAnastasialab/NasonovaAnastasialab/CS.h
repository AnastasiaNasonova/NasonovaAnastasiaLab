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
    bool connection;
public: 
    
    CS();
    static void setMaxID(const int id) { MaxID = id; }
    static int getMaxID() { return MaxID; }
    int getID() { return id; }

    std::string getName() { return name; }
    int getNumA() { return numA; }
    int getNumW() { return numW; }
    void redact();
    void link();
    void ClearLink();

    friend std::ostream& operator <<(std::ostream& out, const CS& c);
    friend std::istream& operator >>(std::istream& in, CS& c);
    
    friend std::ofstream& operator <<(std::ofstream& fout, const CS& c);
    friend std::ifstream& operator >>(std::ifstream& fin, CS& c);
};

