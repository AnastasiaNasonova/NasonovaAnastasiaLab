#include "pch.h"
#include "Pipe.h"
#include <ostream>
#include "proverka.h"

using namespace std;
int Pipe::MaxID = 1;

Pipe::Pipe()
{
	id = MaxID++;
	d = 0;
	l = 0;
	r = 0;
}


ostream& operator << (std::ostream& out, const Pipe& p)
{
    out << "Pipe ID number: " << p.id << "\tDiameter: " << p.d << " mm " << "\tLenght: " << p.l << " km" << "\tPipe under repair: " << p.r << endl;
    return out;
}

istream& operator >> (istream& in, Pipe& p)
{
    cout << "Enter the diameter from 500 to 1428: ";
    p.d = GetCorrectNumber(500, 1428);

    cout << "Enter the lenght from 10 to 1000 ";
    p.l = GetCorrectNumber(10.0, 1000.0);

    p.r = 0;
    return in;
}
