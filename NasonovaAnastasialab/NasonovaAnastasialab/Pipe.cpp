#include "pch.h"
#include "Pipe.h"
#include <ostream>
#include "proverka.h"

using namespace std;
int Pipe::MaxID = 0;

Pipe::Pipe()
{
	id = ++MaxID;
	d = 0;
	l = 0;
	r = 0;
}

void Pipe::redact()
{
    r = !r;
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

std::ofstream& operator << (std::ofstream& fout, const Pipe& p)
{
    if (fout.is_open())
    {
        fout << p.id << endl
            << p.d << endl
            << p.l << endl
            << p.r << endl;
    }
    return fout;
}

std::ifstream& operator>>(std::ifstream& fin, Pipe& p)
{
    if (fin.is_open())
    {
        fin >> p.id;
        fin >> p.d;
        fin >> p.l;
        fin >> p.r;
    }
    return fin;
}
