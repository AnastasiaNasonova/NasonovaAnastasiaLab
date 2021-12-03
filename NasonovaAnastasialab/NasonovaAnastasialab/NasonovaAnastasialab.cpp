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

template<typename T>
int SearchByID(const T& map, int id) {
    if (map.find(id) != map.end())
        return id;
    return 0;
}

int RedactPipes(unordered_map<int, Pipe>& Pipes)
{
    cout << "Enter ID Pipe: " << endl;
    while (true) {
        int id = GetCorrectNumber(0, INT_MAX);
        if (SearchByID(Pipes, id) != 0)
        {
            Pipes[id].redact();
            cout << "Pipe edided." << endl;
            return id;
        }
        else cout << "No such pipe ID." << endl;
    }
}

int RedactCSs(unordered_map<int, CS>& CSs)
{
    cout << "Enter ID CS: " << endl;
    while (true) {
        int id = GetCorrectNumber(0, INT_MAX);
        if (SearchByID(CSs, id) != 0)
        {
            CSs[id].redact();
            cout << "CS edided." << endl;
            return id;
        }
        else cout << "No such CS ID." << endl;
    }
}

template <typename T>
void del(T& map, int id)
{
    if (map.find(id) != map.end())
        map.erase(id);
}

template <typename T>
void Delete(T& map) // для сони расписать для кс и труб отдельно, через каждую функцию без шаблона
{
    cout << "Enter ID: " << endl;
    while (true) {
        int id = GetCorrectNumber(0, INT_MAX);
        if (SearchByID(map, id) != 0) {
            del(map, id);
            cout << "Deleted." << endl;
            return;
        }
        else cout << "No such id." << endl;
    }
}

void Savep(const unordered_map <int, Pipe>& Pipes, ofstream& fout)
{
    for (auto& p : Pipes)
        fout << p.second;
}

void Savec(const unordered_map <int, CS>& CSs, ofstream& fout)
{
    for (auto& c : CSs)
        fout << c.second;
}


void Load(unordered_map<int, Pipe>& Pipes, unordered_map<int, CS>& CSs, ifstream& fin)
{
    int count1, count2, MaxPipeID, MaxCSID;
    string str;
    fin >> count1;
    fin >> MaxPipeID;
    while(count1--)
    {
        Pipe p;
        fin >> p;
        Pipes.insert({ p.getId(), p });
    }

    fin >> count2;
    fin >> MaxCSID;
    while(count2--)
    {
        CS c;
        fin >> c;
        CSs.insert({ c.getID(), c });

    }
    Pipe::setMaxID(MaxPipeID);
    CS::setMaxID(MaxCSID);
}



//Pipe& SelectPipe(unordered_map<int, Pipe>& Pipes)
//{
//    cout << "Enter index: ";
//    unsigned int index = GetCorrectNumber(1u, Pipes.size());
//    return Pipes[index - 1];
//}
//
//CS& SelectCS(unordered_map<int, CS>& CSs)
//{
//    cout << "Enter index: ";
//    unsigned int index = GetCorrectNumber(1u, CSs.size());
//    return CSs[index - 1];
//}

template<typename T, typename T_param>
using Filter = bool(*)(const T& map, T_param param);

template<typename T, typename T_param>
vector<int> search_filter(const unordered_map<int, T>& map, Filter<T, T_param> f, T_param param)
{
    vector<int> res;
    for (auto& m : map)
        if (f(m.second, param))
            res.push_back(m.first);
    return res;
}

//template<typename T>
//unordered_map <int, Pipe> FindPipebyFilter(const unordered_map<int, Pipe>& Pipes, Filter<T> f, T param)
//{
//    unordered_map <int, Pipe> res;
//    int i = 0;
//    for (auto& p : Pipes)
//    {
//        if (f(p, param))
//            res.insert({ i, p });
//        i++;
//    }
//    return res;
//}


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
            CSs.insert({c.getID(), c});
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
                cout << endl << "Compession Station: " << endl;
                PrintCS(CSs);
            }       
            break;
        }
        case 4:
        {
            if (Pipes.size() != 0)
                int id = RedactPipes(Pipes);
            else cout << "No Pipe." << endl;

            break;
        }
        case 5:
        {
            if (CSs.size() != 0)
                int id = RedactCSs(CSs);
            else cout << "No Station." << endl;
            break;
        }
        case 6:
        {
            string name;
            cout << "Enter name file: " << endl;
            cin.ignore(10000, '\n');
            getline(cin, name);
            ofstream fout;
            fout.open(name + ".txt", ios::out);
            if (fout.is_open())
            {
                if (Pipes.size() != 0) 
                {
                   fout << Pipes.size() << endl << Pipe::getMaxID() << endl;
                   Savep(Pipes, fout);
                }
                    
                if (CSs.size() != 0)
                {
                    fout << CSs.size() << endl << CS::getMaxID() << endl;
                    Savec(CSs, fout);
                }

                cout << "Saved.";
            }
            fout.close();
            break;
        }
        case 7:
        {
            string name;
            cout << "Enter name file: " << endl;
            cin.ignore(10000, '\n');
            getline(cin, name);
            ifstream fin;
            fin.open(name + ".txt", ios::in);
            
            if (fin.is_open())
                Load(Pipes, CSs, fin);
            fin.close();
            cout << "Loaded.";
           

            break;
        }
        case 8:
        {
            Delete(Pipes);
            break;
        }
        case 9:
        {
            Delete(CSs);
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