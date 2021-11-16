// NasonovaAnastasialab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// NasonovaLR.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
struct Pipe
{
    int id;
    int d;
    float l;
    bool r;
};

struct CS
{
    int id;
    string name;
    int numW, numA;
};

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

/*Pipe AddPipe()
{
    Pipe p = {};
    p.id = 1;
    cout << "Enter the diameter from 500 to 1428: ";
    p.d = GetCorrectNumber(500, 1428);

    cout << "Enter the lenght from 10 to 1000 ";
    p.l = GetCorrectNumber(10.0, 1000.0);

    p.r = 0;

    return p;
}

CS AddCS()
{
    CS c = {};
    c.id = 1;
    cout << "Name of the Compressor Station ";
    cin >> ws;
    getline(cin, c.name);
    cout << "Number of workshops from 0 to 20 ";
    c.numA = GetCorrectNumber(0, 20);

    cout << "Number of workshops in olperation ";
    c.numW = GetCorrectNumber (0, c.numA);
    //while (c.numW > c.numA) {
        //cout << "The number of workstation must not exceed the number of all station " << endl << "Enter another number ";
        //c.numW = GetCorrectNumber(0, INT_MAX);
   // };
    return c;
}*/

/*void AddPipeVector(Pipe& p, int& p_id, std::unordered_map<int, Pipe>& Pipes) {
    p = AddPipe();
    p_id++;
    p.id = p_id;
    Pipes.insert({ p_id, p });
}

void AddCSVector(CS& c, int& c_id, std::unordered_map<int, CS>& CSs) {
    c = AddCS();
    c_id++;
    c.id = c_id;
    CSs.insert({ c_id, c });
}

void PrintPipes(std::unordered_map<int, Pipe>::iterator& it_pipe, std::unordered_map<int, Pipe>& Pipes) {
    cout << "Pipes:\n ";
    it_pipe = Pipes.begin();
    for (int i = 0; it_pipe != Pipes.end(); it_pipe++) {
        cout << "ID: " << it_pipe->second.id << "\tDiameter: " << it_pipe->second.d << "\tLenght: " << it_pipe->second.l << "\tRepair: " << it_pipe->second.r << endl;
    }
}

void PrintCSs(std::unordered_map<int, CS>::iterator& it_cs, std::unordered_map<int, CS>& CSs) {
    cout << "Compressor Station:\n ";
    it_cs = CSs.begin();
    for (int i = 0; it_cs != CSs.end(); it_cs++) {
        cout << "ID: " << it_cs->second.id << "\tName: " << it_cs->second.name << "\tNumber of workshops: " << it_cs->second.numA << "\tNumber of workshops in olperation: " << it_cs->second.numW << endl;
    }
}

void DeletePipe(std::unordered_map <int, Pipe>::iterator& it_pipe, std::unordered_map <int, Pipe>& Pipes) {
    cout << "Enter ID to delete: ";
    vector <int> ids;
    int id;
    id = GetCorrectNumber(0, INT_MAX);
    while (id != 0) {
        ids.push_back(id);
        cout << "Press 0 to delete or add ID number ";
        id = GetCorrectNumber(0, INT_MAX);
    }
    it_pipe = Pipes.begin();
    for (int i = 0; i < ids.size(); i++) {
        it_pipe = Pipes.find(ids[i]);
        Pipes.erase(it_pipe);
    }
    ids.clear();
    cout << "Deleted." << endl;
}

void DeleteCS(std::unordered_map<int, CS>::iterator& it_cs, std::unordered_map <int, CS>& CSs) {
    cout << "Enter ID to delete: ";
    vector <int> ids;
    int id;
    id = GetCorrectNumber(0, INT_MAX);
    while (id != 0) {
        ids.push_back(id);
        cout << "Press 0 to delete or add ID number ";
        id = GetCorrectNumber(0, INT_MAX);
    }
    it_cs = CSs.begin();
    for (int i = 0; i < ids.size(); i++) {
        it_cs = CSs.find(ids[i]);
        CSs.erase(it_cs);
    }
    ids.clear();
    cout << "Deleted." << endl;
}*/

void RedactPipe(Pipe& p)
{
        if (p.id > 0) {
        cout << "Enter the state of the pipe (1 - under repair; 0 - not under repair)";
        p.r = GetCorrectNumber(0, 1);

        }
    else cout << "No pipe data available"; //данных о трубе нет
}

/*void RedactPipes(std::unordered_map <int, Pipe>::iterator& it_pipe, std::unordered_map <int, Pipe>& Pipes) {
    cout << "Enter ID to redact: ";
    vector <int> ids;
    int id;
    id = GetInt();
    while (id != 0) {
        ids.push_back(id);
        cout << "Tap 0 to redact or add ID number ";
        id = GetInt();
    }

    cout << "What status should I give to the pipes?" << endl
    << "1. All are used" << endl
    << "2. All are repaired" << endl;
        int menu;
        menu = GetInt();
        switch (menu) {
        case 1:
        {
            it_pipe = Pipes.begin();
            for (int i = 0; i < ids.size(); i++) {
                for (int j = 0; it_pipe != Pipes.end(); it_pipe++) {
                    if (it_pipe->first == ids[i]) {
                        Pipes[ids[i]].r = 0;
                    }
                }
            }
            ids.clear();
            break;

        }
        case 2:
        {
            it_pipe = Pipes.begin();
            for (int i = 0; i < ids.size(); i++) {
                for (int j = 0; it_pipe != Pipes.end(); it_pipe++) {
                    if (it_pipe->first == ids[i]) {
                        Pipes[ids[i]].r = 1;
                    }
                }
            }

            ids.clear();
            break;

        }
        default:
        {
            cout << "There is no such thing in the menu, choose 1 or 2 " << endl;
        }

        }
}*/

void RedactCS(CS& c) {

    if (c.id > 0) {
        cout << "How many workshops are in operation? ";
        c.numW = GetCorrectNumber(0, c.numA);
    }
    else cout << "No CS data available";
}



/*void Save(std::unordered_map<int, Pipe>& Pipes, std::unordered_map<int, CS>& CSs, std::unordered_map<int, Pipe>::iterator& it_pipe, std::unordered_map<int, CS>::iterator& it_cs)
{
    if (Pipes.empty() && CSs.empty())
    {
        cout << "No data." << endl;
    }
    else
    {
        ofstream file;
        cout << "Enter the file name: ";
        string str;
        str = GetString();
        file.open(str, ios_base::out);

        if (file.good())
        {
            it_pipe = Pipes.begin();
            for (int i = 0; it_pipe != Pipes.end(); it_pipe++)
            {
                file << "pipes" << endl
                    << it_pipe->second.id << endl
                    << it_pipe->second.d << endl
                    << it_pipe->second.l << endl
                    << it_pipe->second.r << endl;
            }

            it_cs = CSs.begin();
            for (int i = 0; it_cs != CSs.end(); it_cs++)
            {
                file << "cs" << endl
                    << it_cs->second.id << endl
                    << it_cs->second.name << endl
                    << it_cs->second.numA << endl
                    << it_cs->second.numW << endl;
            }
            file.close();
            cout << "Saved." << endl;

        }
        
    }
}
void Load(std::unordered_map<int, Pipe>& Pipes, std::unordered_map<int, CS>& CSs, std::unordered_map<int, Pipe>::iterator& it_pipe, std::unordered_map<int, CS>::iterator& it_cs)
{
    ifstream file;
    cout << "Enter thhe file name: ";
    string str;
    str = GetString();
    file.open(str, ios::in);
    if (file.good())
    {
        Pipes.clear();
        CSs.clear();

        while (!file.eof())
        {
            getline(file, str);
            if (str == "pipes")
            {
                Pipe p_p;
                file >> p_p.id;
                file >> p_p.d;
                file >> p_p.l;
                file >> p_p.r;
                Pipes.insert({ p_p.id, p_p });
            }
            if (str == "cs")
            {
                CS c_c;
                file >> c_c.id;
                file.ignore(32767, '\n');
                string(c_c.name);
                getline(file, c_c.name);
                file >> c_c.numA;
                file >> c_c.numW;
                CSs.insert({ c_c.id, c_c });

            }
      
        }
    }
    cout << "Loaded.";
}*/

void Savep(ofstream& fout, const Pipe& p)
{
    if (p.l != 0 && p.d != 0)
    {
        fout << p.id << endl << p.l << endl << p.d << endl << p.r << endl;
    }
     
}

void Savec(ofstream& fout, const CS& c)
{
    if (c.numA != 0)
    {
        fout << c.id << endl << c.name << endl << c.numA << endl << c.numW << endl;
    }
}

Pipe Loadp(ifstream& fin)
{
        Pipe p;
            fin >> p.id;
            fin >> p.l;
            fin >> p.d;
            fin >> p.r;

           return p;
     
}

CS Loadc(ifstream& fin)
{
    CS c;
        fin >> c.id;
        //getline(fin, str);
        // c.id = stoi(str);
        fin.ignore(256, '\n');
        //string(c.name);
        getline(fin, c.name);
        fin >> c.numA;
        fin >> c.numW;
    
    return c;
}


istream& operator >> (istream& in, Pipe& p)
{
    p.id = 1;
    cout << "Enter the diameter from 500 to 1428: ";
    p.d = GetCorrectNumber(500, 1428);

    cout << "Enter the lenght from 10 to 1000 ";
    p.l = GetCorrectNumber(10.0, 1000.0);

    p.r = 0;
    return in;
}

ostream& operator << (ostream& out, const Pipe& p)
{

    if (p.id > 0)
    {
        out << "Pipe ID number: " << p.id << "\tDiameter: " << p.d << " mm " << "\tLenght: " << p.l << " km" << "\tPipe under repair: " << p.r << endl;
    }
    else cout << "No data pipe.";
    return out;
}

istream& operator >> (istream& in, CS& c)
{
    c.id = 1;
    cout << "Name of the Compressor Station ";
    cin >> ws;
    getline(cin, c.name);
    cout << "Number of workshops from 0 to 20 ";
    c.numA = GetCorrectNumber(0, 20);

    cout << "Number of workshops in olperation ";
    c.numW = GetCorrectNumber(0, c.numA);
    return in;
}

ostream& operator << (ostream& out, const CS& c)
{

    if (c.id > 0) {
        
        cout << "CS ID number: " << c.id << "\tName of the Compressor Station: " << c.name << "\tNumber of workshops: " << c.numA << "\tNumber of workshops in olperation: " << c.numW << endl;
    }
    else cout << "No data CS." << endl;
    return out;
}

Pipe& SelectPipe(vector<Pipe>& Pipes)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, Pipes.size());
    return Pipes[index-1];
}

CS& SelectCS(vector<CS>& CSs)
{
    cout << "Enter index: ";
    unsigned int index = GetCorrectNumber(1u, CSs.size());
    return CSs[index - 1];
}
int main()
{
    int menu;

    //Pipe p = {};
    //CS c = {};

    //unordered_map <int, Pipe> Pipes = {};
    //unordered_map <int, CS> CSs = {};

    // int id;
    int p_id = 0;
    int c_id = 0;
    //string str;

    //unordered_map <int, Pipe> ::iterator it_pipe = Pipes.begin();
    //unordered_map <int, CS> ::iterator it_cs = CSs.begin();

    vector <Pipe> Pipes;
    vector <CS> CSs;
 

    for (;;) {
        cout << "\n 1. Add a pipe"
            << "\n 2. Add Compressor Station"
            << "\n 3. Viewing all objects"
            << "\n 4. Redact Pipe"
            << "\n 5. Redact CS"
            << "\n 6. Save"
            << "\n 7. Load"
            << "\n 0. Exit\n";

        menu = GetCorrectNumber(0, 9);

        switch (menu)
        {
        case 0:
            return 0;
        case 1:
        {
            Pipe p;
            cin >> p;
            Pipes.push_back(p);
            //AddPipeVector(p, p_id, Pipes);
            break;
        }
        case 2:
        {
            CS c;
            cin >> c;
            CSs.push_back(c);
            //AddCSVector(c, c_id, CSs);
            break;
        }
        case 3:
        {    
                cout << "Pipe " << endl << endl;
                for (int i = 0; i < Pipes.size(); i++)
                    cout << Pipes[i];

                cout << "Compressor Station " << endl << endl;
                for (int i = 0; i < CSs.size(); i++)
                    cout << CSs[i];
        
            break;
        }
        case 4:
        {
            //RedactPipes(it_pipe, Pipes);
            RedactPipe(SelectPipe(Pipes));
            break;
        }
        case 5:
        {
            RedactCS(SelectCS(CSs));

            break;
        }
        case 6:
        {
            ofstream fout;
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
            break;
        }
        case 7:
        {
            ifstream fin;
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
              
            }
           
            break;
        }
        case 8:
        {
            //DeletePipe(it_pipe, Pipes);
            break;
        }
        case 9:
        {
            //DeleteCS(it_cs, CSs);
            break;
        }
        default:
            cout << "There is no such number in the menu, enter another number";
            break;
        }
    }


}