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

ostream& operator << (ostream& out, const CS& c)
{
    cout << "CS ID number: " << c.id << "\tName of the Compressor Station: " << c.name << "\tNumber of workshops: " << c.numA << "\tNumber of workshops in olperation: " << c.numW << endl;
    return out;
}