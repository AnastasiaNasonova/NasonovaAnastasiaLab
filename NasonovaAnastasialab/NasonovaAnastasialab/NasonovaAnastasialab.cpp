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

int GetInt(int min = 0, int max = INT_MAX)
{
    while (1)
    {
        int number;
        cin >> number;

        if (cin.fail() || number < min || number > max || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Error. Enter  a different value. ";
        }
        else
        {
            return number;
        }
    }
}
float GetFloat(float min = 0, float max = FLT_MAX)
{
    while (1)
    {
        float number;
        cin >> number;

        if (cin.fail() || number < min || number > max || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Error. Enter  a different value. ";
        }
        else
        {
            return number;
        }
    }
}
bool GetBool()
{
    while (1)
    {
        bool number;
        cin >> number;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << " Enter 1 or 0 ";
        }
        else
        {
            return number;
        }
    }
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

/*void PrintPipe(const Pipe& p)
{
    if (p.id > 0) {
        cout << "Pipe " << endl << endl;
        cout << "Pipe ID number: " << p.id << "  Diameter: " << p.d << " mm " << " Lenght: " << p.l << " km\n";
        cout << "Pipe under repair: " << p.r << endl << endl; \
    }
    else cout << "No data pipe" << endl;
}*/


/*void PrintCS(const CS& c)
{
    if (c.id > 0) {
        cout << "Compressor Station " << endl << endl;
        cout << "CS ID number: " << c.id << " Name of the Compressor Station: " << c.name << " Number of workshops: " << c.numA << " Number of workshops in olperation: " << c.numW;
    }
    else cout << "No data CS" << endl;
}*/

Pipe AddPipe()
{
    Pipe p = {};
    p.id = 1;
    cout << "Enter the diameter from 500 to 1428: ";
    p.d = GetInt(500, 1428);

    cout << "Enter the lenght from 10 to 1000 ";
    p.l = GetFloat(10, 1000);

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
    c.numA = GetInt(0, 20);

    cout << "Number of workshops in olperation ";
    c.numW = GetInt();
    while (c.numW > c.numA) {
        cout << "The number of workstation must not exceed the number of all station " << endl << "Enter another number ";
        c.numW = GetInt();
    };
    return c;
}

void AddPipeVector(Pipe& p, int& p_id, std::unordered_map<int, Pipe>& Pipes) {
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
    id = GetInt();
    while (id != 0) {
        ids.push_back(id);
        cout << "Press 0 to delete or add ID number ";
        id = GetInt();
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
    id = GetInt();
    while (id != 0) {
        ids.push_back(id);
        cout << "Press 0 to delete or add ID number ";
        id = GetInt();
    }
    it_cs = CSs.begin();
    for (int i = 0; i < ids.size(); i++) {
        it_cs = CSs.find(ids[i]);
        CSs.erase(it_cs);
    }
    ids.clear();
    cout << "Deleted." << endl;
}

/*void RedactPipe(Pipe& p)
{
        if (p.id > 0) {
        cout << "Enter the state of the pipe (1 - under repair; 0 - not under repair)";
        p.r = GetBool();

        }
    else cout << "No pipe data available"; //данных о трубе нет
}*/
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
        c.numW = GetInt();

        while (c.numW > c.numA) {
            cout << "The number of workstation must not exceed the number of all station " << endl << "Enter another number";
            c.numW = GetInt();
        };

    }
    else cout << "No CS data available";
}


/*void Save(const Pipe& p, const CS& c)
{
    ofstream f;
    f.open("save.txt", ios_base::out);

    if (f.good())
    {
        if (p.id > 0)
        {
            f << "pipe" << endl << p.id << endl << p.l << endl << p.d << endl << p.r << endl;
        }

        if (c.id > 0)
        {
            f << "station" << endl << c.id << endl << c.name << endl << c.numA << endl << c.numW << endl;

        }
        f.close();
        cout << "Saved";

    }
    else cout << "No pipe or station";

}*/

void Save(std::unordered_map<int, Pipe>& Pipes, std::unordered_map<int, CS>& CSs, std::unordered_map<int, Pipe>::iterator& it_pipe, std::unordered_map<int, CS>::iterator& it_cs) 
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
}

/*void Load(Pipe& p, CS& c)
{
    ifstream f;
    f.open("save.txt", ios::in);
    if (f.good())
    {
        while (!f.eof())
        {
            string str;
            f >> str;
            //cout << str;
            if (str == "pipe")
            {
                f >> p.id;
                f >> p.d;
                f >> p.l;
                f >> p.r;
            }

            if (str == "station")
            {
                f >> c.id;
                f.ignore(32767, '\n');
                string(c.name);
                getline(f, c.name);
                f >> c.numA;
                f >> c.numW;
            }

        }
        cout << "Loaded";
    }
}*/

void FilterSearchPipe( std::unordered_map <int, Pipe>& Pipes, std::unordered_map <int, Pipe>::iterator& it_pipe) {
   
    cout << "Search" << endl
        << "1. by ID" << endl
        << "2. on the basis of 'under repair'" << endl;
    int menu;
    menu = GetInt();
    switch (menu)
    {
        case 1:
        {
            cout << "Enter the pipe id: ";
            int id;
            id = GetInt();
            it_pipe;
        }
    default:
        break;
    }

}

int main()
{
    int menu;

    Pipe p = {};
    CS c = {};

    unordered_map <int, Pipe> Pipes = {};
    unordered_map <int, CS> CSs = {};

    // int id;
    int p_id = 0;
    int c_id = 0;
    //string str;

    unordered_map <int, Pipe> ::iterator it_pipe = Pipes.begin();
    unordered_map <int, CS> ::iterator it_cs = CSs.begin();


    for (;;) {
        cout << "\n 1. Add a pipe"
            << "\n 2. Add Compressor Station"
            << "\n 3. Viewing all objects"
            << "\n 4. Redact Pipe"
            << "\n 5. Redact CS"
            << "\n 6. Save"
            << "\n 7. Load"
            << "\n 0. Exit\n";

        menu = GetInt();

        switch (menu)
        {
        case 0:
            return 0;
        case 1:
        {
            AddPipeVector(p, p_id, Pipes);
            //p = AddPipe();
            break;
        }
        case 2:
        {
            AddCSVector(c, c_id, CSs);
            //c = AddCS();
            break;
        }
        case 3:
        {
            //PrintPipe(p);
            PrintPipes(it_pipe, Pipes);
            PrintCSs(it_cs, CSs);
            //PrintCS(c);

            break;
        }
        case 4:
        {
            //RedactPipes(it_pipe, Pipes);
            //RedactPipe(p);
            break;
        }
        case 5:
        {
            //RedactCS(c);
            break;
        }
        case 6:
        {
            Save(Pipes,CSs, it_pipe, it_cs);
            break;
        }
        case 7:
        {
            Load(Pipes, CSs, it_pipe, it_cs);
            break;
        }
        case 8:
        {
            DeletePipe(it_pipe, Pipes);
            break;
        }
        case 9:
        {
            DeleteCS(it_cs, CSs);
            break;
        }
        default:
            cout << "There is no such number in the menu, enter another number";
            break;
        }
    }


}