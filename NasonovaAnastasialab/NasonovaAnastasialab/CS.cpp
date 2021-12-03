#include "pch.h"
#include "CS.h"
#include <ostream>
#include "proverka.h"
#include <string>

using namespace std;
int CS::MaxID = 1;

CS::CS()
{
	id = MaxID++;
	name = "";
	numA = 0;
	numW = 0;
}

void CS::redact()
{
    cout << "Enter how many workshops are working now: " << endl;
    numW = GetCorrectNumber(0, numA);
}

istream& operator >> (istream& in, CS& c)
{
    cout << "Name of the Compressor Station ";
    cin.ignore(10000, '\n');
    getline(in, c.name);
    cout << "Number of workshops from 0 to 20 ";
    c.numA = GetCorrectNumber(0, 20);

    cout << "Number of workshops in olperation ";
    c.numW = GetCorrectNumber(0, c.numA);
    return in;
}

std::ofstream& operator<<(std::ofstream& fout, const CS& c)
{
    if (fout.is_open())
    {
        fout << c.id << endl
            << c.name << endl
            << c.numA << endl
            << c.numW << endl;
    }
    return fout;
}

std::ifstream& operator>>(std::ifstream& fin, CS& c)
{
   if (fin.is_open())
   {
       fin >> c.id;
       fin >> ws;
       getline(fin, c.name);
       fin >> c.numA;
       fin >> c.numW;
   }
   return fin;
}

ostream& operator << (ostream& out, const CS& c)
{
    cout << "CS ID number: " << c.id << "\tName of the Compressor Station: " << c.name << "\tNumber of workshops: " << c.numA << "\tNumber of workshops in olperation: " << c.numW << endl;
    return out;
}