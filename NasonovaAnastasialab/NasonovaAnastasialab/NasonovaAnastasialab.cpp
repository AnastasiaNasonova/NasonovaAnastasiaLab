// NasonovaAnastasialab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"


using namespace std;

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((cin >> x).fail() || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter number (" << min << "-" << max << ") again:";
    }
    return x;

}


string GetString()
{
    while (1)
    {
        cin >> ws;
        string str;
        getline(cin, str);

        return str;
    }
}

void PrintPipe(const unordered_map <int, Pipe>& Pipes)
{
    for (auto& p: Pipes)
        cout << p.second;
}

void PrintCS(const unordered_map <int, CS>& CSs)
{
    for (auto& c : CSs)
        cout << c.second;
}

//void RedactPipe(Pipe& p)
//{
//        if (p.d > 0) {
//        cout << "Enter the state of the pipe (1 - under repair; 0 - not under repair)";
//        p.r = GetCorrectNumber(0, 1);
//
//        }
//    else cout << "No pipe data available"; //данных о трубе нет
//}

//void RedactCS(CS& c) {
//
//    if (c.id > 0) {
//        cout << "How many workshops are in operation? ";
//        c.numW = GetCorrectNumber(0, c.numA);
//    }
//    else cout << "No CS data available";
//}


//void Savep(ofstream& fout, const Pipe& p)
//{
//    if (p.l != 0 && p.d != 0)
//    {
//        fout << p.id << endl << p.l << endl << p.d << endl << p.r << endl;
//    }
//     
//}

//void Savec(ofstream& fout, const CS& c)
//{
//    if (c.numA != 0)
//    {
//        fout << c.id << endl << c.name << endl << c.numA << endl << c.numW << endl;
//    }
//}

//Pipe Loadp(ifstream& fin)
//{
//    Pipe p;
//            fin >> p.id;
//            fin >> p.l;
//            fin >> p.d;
//            fin >> p.r;
//
//           return p;
//     
//}

//CS Loadc(ifstream& fin)
//{
//    CS c;
//        fin >> c.id;
//        fin.ignore(256, '\n');
//        getline(fin, c.name);
//        fin >> c.numA;
//        fin >> c.numW;
//    
//    return c;
//}

//istream& operator >> (istream& in, Pipe& p)
//{
//    cout << "Enter the diameter from 500 to 1428: ";
//    p.d = GetCorrectNumber(500, 1428);
//
//    cout << "Enter the lenght from 10 to 1000 ";
//    p.l = GetCorrectNumber(10.0, 1000.0);
//
//    p.r = 0;
//    return in;
//}

//ostream& operator << (ostream& out, const Pipe& p)
//{
//
//    if (p.d > 0)
//    {
//        out << "Pipe ID number: " << p.id << "\tDiameter: " << p.d << " mm " << "\tLenght: " << p.l << " km" << "\tPipe under repair: " << p.r << endl;
//    }
//   // else cout << "No data pipe.";
//    return out;
//}

//istream& operator >> (istream& in, CS& c)
//{
//        cout << "Name of the Compressor Station ";
//    cin >> ws;
//    getline(cin, c.name);
//    cout << "Number of workshops from 0 to 20 ";
//    c.numA = GetCorrectNumber(0, 20);
//
//    cout << "Number of workshops in olperation ";
//    c.numW = GetCorrectNumber(0, c.numA);
//    return in;
//}

ostream& operator << (ostream& out, const CS& c)
{

    if (c.numA > 0) {
        
        cout << "CS ID number: " << c.id << "\tName of the Compressor Station: " << c.name << "\tNumber of workshops: " << c.numA << "\tNumber of workshops in olperation: " << c.numW << endl;
    }
    else cout << "No data CS." << endl;
    return out;
}

Pipe& SelectPipe(unordered_map<int, Pipe>& Pipes)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, Pipes.size());
    return Pipes[index - 1];
}

CS& SelectCS(unordered_map<int, CS>& CSs)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, CSs.size());
    return CSs[index - 1];
}

template<typename T>
using Filterp = bool(*)(const Pipe& p, T param);

//bool CheckPipeByRepair(const Pipe& p, int param)
//{
//    return p.r == param;
//}

template<typename T>
unordered_map <int, Pipe> FindPipebyFilter(const unordered_map<int, Pipe>& Pipes, Filterp<T> f, T param)
{
    unordered_map <int, Pipe> res;
    int i = 0;
    for (auto& p : Pipes)
    {
        if (f(p, param))
            res.insert({ i, p });
        i++;
    }
    return res;
}


template<typename T>
using Filterc = bool(*)(const CS& c,T param);

//bool CheckbyName(const CS& c, string param)
//{
//    return c.name == param;
//}
//
//bool CheckbyWorkingCex(const CS& c, int param)
//{
//    return c.numW >= param;
//}

template<typename T>
vector <int> FindCSbyFilter(const vector<CS>& CSs, Filterc<T> f, T param)
{
    vector <int> res;
    int i = 0;
    for (auto& c : CSs)
    {
        if (f(c, param))
            res.push_back(i);
        i++;

    }
    return res;
}



int main()
{
    
    unordered_map <int, Pipe> Pipes;
    //unordered_map <int, Pipe>::iterator iter_pipe;

    unordered_map <int, CS> CSs = {};
    //unordered_map <int, CS>::iterator iter_cs;
  

   for(;;)
    {
        cout << "\n 1. Add a pipe"
            << "\n 2. Add Compressor Station"
            << "\n 3. Viewing all objects"
            << "\n 4. Redact Pipe"
            << "\n 5. Redact CS"
            << "\n 6. Save"
            << "\n 7. Load"
            << "\n 8. Find Compressor Ststion by Name"
            << "\n 0. Exit\n";

        switch (GetCorrectNumber(0,9))
        {       
        case 1:
        {
            Pipe p;
            cin >> p;
            Pipes.insert({p.getId(), p});
            break;
        }
        case 2:
        {
            CS c;
            cin >> c;
            CSs.insert({c.getId(), c});
            break;
        }
        case 3:
        {    
            if (Pipes.size() != 0)
            {
                cout << "Pipes: " << endl;
                PrintPipe(Pipes);
            }
            
            if (CSs.size() != 0)
            {
                cout << "Compession Station: " << endl;
                PrintCS(CSs);
            }       
            break;
        }
        case 4:
        {
           // RedactPipe(SelectPipe(Pipes);
            break;
        }
        case 5:
        {
            //RedactCS(SelectCS(CSs));
            break;
        }
        case 6:
        {
            /*ofstream fout;
            fout.open("save.txt", ios::out);
            if (fout.good()) 
            {
                fout << Pipes.size() << endl;
                for (Pipe p: Pipes)
                    Savep(fout, p);

                fout << CSs.size() << endl;
                for (CS c : CSs)
                    Savec(fout, c);
                fout.close();
            }
           cout << "Saved." << endl;
            break;*/
        }
        case 7:
        {
            /*ifstream fin;
            fin.open("save.txt", ios::in);
            if (fin.is_open())
            {
                int count1;
                fin >> count1;
                while (count1--)
                Pipes.push_back(Loadp(fin));

                int count2;
                fin >> count2;
                while (count2--)
                CSs.push_back(Loadc(fin));

                 fin.close();
              
            }*/
           
            break;
        }
        case 8:
        {
            //string name;
            //cout << "Enter name Compressor Station ";
            //cin >> name;
            //for (int i : FindCSbyFilter<string>(CSs, CheckbyName, name))
            //{
            //    CSs.erase(CSs.begin()+i);
            //    //cout << CSs[i];
            //}

            /*int numW;
            cout << "Enter working cex ";
            cin >> numW;

            for (int i : FindCSbyFilter(CSs, CheckbyWorkingCex, numW))
                cout << CSs[i];*/
            break;
        }
        case 9:
        {
           /* int r;
            cout << "Enter pipe rapair";
            cin >> r;

            for (int i : FindPipebyFilter(Pipes, CheckPipeByRepair, r))

                cout << Pipes[i];
            */
            //DeleteCS(it_cs, CSs);
            break;
        }
        case 0:
        {
           return 0;
        }
        default:
          
            break;
        }
    }


}