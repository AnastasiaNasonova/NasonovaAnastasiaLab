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
#include <unordered_set>
#include <set>
#include "Sort.h"


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
    if (map.find(id) != map.end()) {
        return id;
    }
    return 0;
}



template<typename T>
int Redact(T& map)
{
    cout << "Enter ID : " << endl;
    while (true) {
        int id = GetCorrectNumber(0, INT_MAX);
        if (SearchByID(map, id) != 0)
        {
            map[id].redact();
            cout << "Redacted." << endl;
            return id;
        }
        else cout << "No such ID." << endl;
    }
}

template <typename T>
void DeleteItemFromMap(unordered_map<int, T>& map, int id)
{
    if (map.find(id) != map.end())
        map.erase(id);
}

template <typename T>
void Delete(T& map) 
{
    cout << "Enter ID: " << endl;
    while (true) {
        int id = GetCorrectNumber(0, INT_MAX);
        if (SearchByID(map, id) != 0) {
            DeleteItemFromMap(map, id);
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
    fin >> count1;
    fin >> MaxPipeID;
    fin >> count2;
    fin >> MaxCSID;
    for (int i = 0; i< count1; i++)
    {
        Pipe p;
        fin >> p;
        Pipes.insert({ p.getId(), p });
    }

    for (int i = 0; i < count2; i++)
    {
        CS c;
        fin >> c;
        CSs.insert({ c.getID(), c });

    }
    Pipe::setMaxID(MaxPipeID);
    CS::setMaxID(MaxCSID);
}


vector<int> searchByRepear(unordered_map<int, Pipe>& Pipes, bool& r)
{
    vector<int> res;
    for (auto& p : Pipes) {
        if (p.second.getRepair() == r)
        {
            res.push_back(p.first);
            cout << p.second;
        }
    }
    
    return res;
}

vector<int> searchByName(unordered_map<int, CS>& CSs, string& name)
{
    vector<int> res;
    for (auto& c : CSs) {
        if (c.second.getName() == name) {
            res.push_back(c.first);
            cout << c.second;
        }
    }
    return res;
}

vector<int> searchByPercent(unordered_map<int, CS>& CSs, double& proc)
{
    vector<int> res;
    for (auto& c : CSs) {
        if (round((((double(c.second.getNumA()) - double(c.second.getNumW())) / double(c.second.getNumA()) * 100) >= proc))) {
            res.push_back(c.first);
            cout << c.second;
        }
    }
    return res;
}

void CreatLink(unordered_map<int, Pipe>& Pipes, unordered_map<int, CS>& CSs)
{
    cout << "Enter ID pipe you want to attach " << endl;
    int id = SearchByID(Pipes, GetCorrectNumber(1, Pipe::getMaxID()));
    while (Pipes[id].getRepair() != 0)
    {
        cout << " Pipe under repair enter another ID" << endl;
        id = SearchByID(Pipes, GetCorrectNumber(1, Pipe::getMaxID()));
    }
    cout << "Enter the ID of the cs from which the pipe exits" << endl;
    int out = SearchByID(CSs, GetCorrectNumber(1, CS::getMaxID()));
    cout << "Enter the ID of the cs that the pipe is included in" << endl;
    int in = SearchByID(CSs, GetCorrectNumber(1, CS::getMaxID()));

    //if (CSs[in].col_pipe >= CSline[in].getWork() && CSline[out].col_pipe >= CSline[out].getWork())
        //cout << " Недостаточно рабочих цехов в станции" << endl;
    if (id != 0 && Pipes[id].pin == 0 && Pipes[id].pout == 0 && in != out && out != 0 && in != 0 ) //&& CSs[in].col_pipe < CSs[in].getNumW() && CSse[out].col_pipe < CSs[out].getNumW())
    {
        Pipes[id].link(in, out);
        CSs[in].link();
        CSs[out].link();
    }
    else cout << "Error..." << endl;
}

void DeleteLink(unordered_map<int, Pipe>& Pipes, unordered_map<int, CS>& CSs)
{
    cout << "Enter the ID of the pipe you want to delete: " << endl;
    int id = SearchByID(Pipes, GetCorrectNumber(1, Pipe::getMaxID()));
    if (id != 0 && Pipes[id].pin > 0 && Pipes[id].pout > 0)
    {
        for (auto& p : Pipes)
        {
            CSs[Pipes[id].pin].ClearLink();
            CSs[Pipes[id].pout].ClearLink();
            Pipes[id].ClearLink();
        }
        cout << "Deleted. " << endl;
    }
    else   cout << "Such a pipe is not connected to the network" << endl;
}

void PrintLink(unordered_map<int, Pipe>& Pipes)
{
    for (auto& p : Pipes)
        if (p.second.pin > 0 && p.second.pout > 0)
            cout << "kc " << p.second.pout << " --> pipe " << p.first << " -->kc " << p.second.pin << ((p.second.getRepair() == true) ? " Under repair " : " At work ") << endl;
}

vector<vector<int>> CreateGraph(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, CS>& CSs) {
    set<int> vertices;
    for (const auto& p : Pipes)
        if (p.second.pin > 0 && p.second.pout > 0 && p.second.getRepair() == 0 && CSs.count(p.second.pin) && CSs.count(p.second.pout))
        {
            vertices.insert(p.second.pout);
            vertices.insert(p.second.pin);
        }

    unordered_map<int, int> VerticesIndex;
    int i = 0;
    for (const int& v : vertices)
        VerticesIndex.insert({ v, i++ });
    vector<vector<int>> r;
    r.resize(vertices.size());
    for (const auto& p : Pipes)
        if (p.second.pin > 0 && p.second.pout > 0 && p.second.getRepair() == false)
            r[VerticesIndex[p.second.pout]].push_back(VerticesIndex[p.second.pin]);
    return r;
}

void editPipes(unordered_map<int, Pipe>& Pipes)
{
    if (Pipes.size() == 0)
        cout << "No pipes." << endl;
    else {
        for (;;)
        {
            cout << " Search Pipe by ... " << endl
                << " 1. Search by ID" << endl
                << " 2. Search for pipes for repair" << endl
                << " 0. Exit" << endl;
            switch (GetCorrectNumber(0, 2))
            {
            case 1: // поиск по ID
            {
                cout << " Enter ID pipes for editing or enter 0: " << endl;
                int id;
                vector<int> editID;
                do {
                    id = GetCorrectNumber(0, Pipe::getMaxID());
                    if (SearchByID(Pipes, id) != 0)
                        editID.push_back(id);
                } while (id != 0);
                for (auto i : editID)
                    cout << Pipes[i];

                cout << " 1. Change the status of pipe repair " << endl
                    << " 2. Delete pipe" << endl
                    << " 0. exit" << endl;
                switch (GetCorrectNumber(0, 2))
                {
                case 1:
                {
                    cout << " Enter 1 ID you want redact or redact all 0 ";
                        if (GetCorrectNumber(0, 1) == 0)
                        {
                            if (editID.size() != 0) {
                                cout << "Redacted." << endl;
                                for (auto& id : editID)
                                    Pipes[id].redact();
                            }
                            else cout << "No pipes." << endl;
                        }
                        else {
                            unordered_set<int> subres;
                            cout << "Enter pipe's id to redact or 0 to complete: ";
                            int id = GetCorrectNumber(0, Pipe::getMaxID());
                            while (id)
                            {
                                subres.insert(id);
                                id = GetCorrectNumber(0, Pipe::getMaxID());
                            }
                            for (auto& pID : editID)
                                if (subres.count(pID) > 0)
                                    Pipes[pID].redact();
                        }
                    PrintPipe(Pipes);
                    break;
                }
                case 2:
                {
                    cout << " Enter 1 ID you want delete or delete all 0 ";
                    if (GetCorrectNumber(0, 1) == 0)
                    {
                        if (editID.size() != 0) {
                            cout << "Deleted." << endl;
                            for (auto& id : editID)
                                DeleteItemFromMap(Pipes, id);
                        }
                        else cout << "No pipes." << endl;
                    }
                    else {
                        unordered_set<int> subres;
                        cout << "Enter pipe's id to delete or 0 to complete: ";
                        int id = GetCorrectNumber(0, Pipe::getMaxID());
                        while (id)
                        {
                            subres.insert(id);
                            id = GetCorrectNumber(0, Pipe::getMaxID());
                        }
                        for (auto& pID : editID)
                            if (subres.count(pID) > 0)
                                DeleteItemFromMap(Pipes, pID);
                    }
                    PrintPipe(Pipes);
                    break;
                }
                    
                case 0:
                    return;
                }
                break;
            }
            case 2: // поиск по статусу ремонта
            {
                bool stat;
                cout << "Press 1 to find all pipes in repair or 0 to find all working pipes " << endl;
                stat = GetCorrectNumber(0, 1);
                vector <int> res = searchByRepear(Pipes, stat);
                for (auto i : res)
                    cout << Pipes[i];
               
                cout << " 1. Change the status of pipe repair " << endl
                    << " 2. Delete pipes " << endl
                    << " 0. Exit " << endl;
                switch (GetCorrectNumber(0, 2))
                {
                case 1:
                {
                    cout << " Enter 1 ID you want redact or redact all 0 ";
                    if (GetCorrectNumber(0, 1) == 0)
                    {
                        if (res.size() != 0) {
                            cout << "Redacted." << endl;
                            for (auto& id : res)
                                Pipes[id].redact();
                        }
                        else cout << "No pipes." << endl;
                    }
                    else {
                        unordered_set<int> subres;
                        cout << "Enter pipe's id to redact or 0 to complete: ";
                        int id = GetCorrectNumber(0, Pipe::getMaxID());
                        while (id)
                        {
                            subres.insert(id);
                            id = GetCorrectNumber(0, Pipe::getMaxID());
                        }
                        for (auto& pID : res)
                            if (subres.count(pID) > 0)
                                Pipes[pID].redact();
                    }
                    PrintPipe(Pipes);
                    break;
                }
                case 2:
                {
                    cout << "Enter 1 ID you want delete or  delete all 0 " << endl;
                    switch (GetCorrectNumber(0,1))
                    {
                    case 1:
                    {
                        unordered_set<int> subres;
                        cout << "Enter pipe's id to delete or 0 to complete: ";
                        int id = GetCorrectNumber(0, Pipe::getMaxID());
                        while (id)
                        {
                            subres.insert(id);
                            id = GetCorrectNumber(0, Pipe::getMaxID());
                        }
                        for (auto& pID : res)
                            if (subres.count(pID) > 0)
                                DeleteItemFromMap(Pipes, pID);

                        PrintPipe(Pipes);
                        break;
                    }
                    case 0:
                    {
                        if (res.size() != 0)
                        {
                            for (auto& id : res)
                                DeleteItemFromMap(Pipes, id);
                        }
                        else cout << "No pipes." << endl;

                        PrintPipe(Pipes);
                        break;
                    }
                    }
                   
                    break;
                }
                case 0:
                    return;
                }
                break;
            }
            case 0:
                return;
            }
        }
    }
}
void editCSs(unordered_map<int, CS>& CSs)
{
    if (CSs.size() == 0)
        cout << "No stations." << endl;
    else {
        for (;;)
        {
            cout << " Search CS by ... " << endl
                << " 1. Search by ID" << endl
                << " 2. Search by name" << endl
                << " 3. Search by % of unused workshops" << endl
                << " 0. Exit" << endl;
            switch (GetCorrectNumber(0, 3))
            {
            case 1: // поиск по ID
            {
                cout << " Enter ID cs for editing or enter 0: " << endl;
                int id;
                vector<int> editID;
                do {
                    id = GetCorrectNumber(0, INT_MAX);
                    if (SearchByID(CSs, id) != 0)
                        editID.push_back(id);
                } while (id != 0);

                cout << " 1. Change the number of workshops " << endl
                    << " 2. Delete pipe" << endl
                    << " 0. exit" << endl;
                switch (GetCorrectNumber(0, 2))
                {
                case 1:
                {
                    if (editID.size() != 0) {
                        for (auto& id : editID)
                            CSs[id].redact();
                        cout << "Redacted." << endl;
                    }
                    else cout << "No CS." << endl;
                    PrintCS(CSs);
                    break;
                }
                case 2:
                {
                    if (editID.size() != 0)
                    {
                        for (auto& id : editID)
                            DeleteItemFromMap(CSs, id);
                    }
                    else cout << "No CS." << endl;
                    PrintCS(CSs);
                    break;
                }
                case 0:
                    return;
                }
                break;
            }
            case 2: // поиск по имени 
            {
                cout << "Enter name satations" << endl;
                string name;
                cin.ignore(10000, '\n');
                getline(cin, name);
                vector <int> res = searchByName(CSs, name);
                if (res.size() != 0)
                {
                    for (auto& id : res)
                        cout << CSs[id];
                }
                cout << " 1. Change the number of workshops " << endl
                    << " 2. Delete pipe" << endl
                    << " 0. exit" << endl;
                switch (GetCorrectNumber(0, 2))
                {
                case 1:
                {
                    if (res.size() != 0) {
                        cout << "Redacted.";
                        for (auto& id : res)
                            CSs[id].redact();
                    }
                    else cout << "No CS." << endl;
                    PrintCS(CSs);
                    break;
                }
                case 2:
                {
                    if (res.size() != 0)
                    {
                        for (auto& id : res)
                            DeleteItemFromMap(CSs, id);
                    }
                    else cout << "No CS." << endl;
                    PrintCS(CSs);
                    break;
                }
                case 0:
                    return;
                }
                break;
            
            }
            case 3: //по проценту незадействованных цехов
            {
                cout << "Enter %  of unused workshops" << endl;
                double proc = GetCorrectNumber(0.0, 100.0);
                vector <int> res = searchByPercent(CSs, proc);
                if (res.size() != 0)
                {
                    for (auto& id : res)
                        cout << CSs[id];
                }
                else cout << "No CS." << endl;
                cout << " 1. Change the number of workshops " << endl
                    << " 2. Delete pipe" << endl
                    << " 0. exit" << endl;
                switch (GetCorrectNumber(0, 2))
                {
                case 1:
                {
                    if (res.size() != 0) {
                        cout << "Redacted.";
                        for (auto& id : res)
                            CSs[id].redact();
                    }
                    else cout << "No CS." << endl;
                    PrintCS(CSs);
                    break;
                }
                case 2:
                {
                    if (res.size() != 0)
                    {
                        for (auto& id : res)
                            DeleteItemFromMap(CSs, id);
                    }
                    else cout << "No CS." << endl;
                    PrintCS(CSs);
                    break;
                }
                case 0:
                    return;
                }

                break;
            }
            case 0:
                return;
            }
        }
    }

}
void RedactingByFilter(unordered_map<int, Pipe>& Pipes, unordered_map<int, CS>& CSs)
{
    for (;;) {
        cout << "1. Redact Pipes " << endl
            << "2. Redact Stations " << endl
            << "0. Exit " << endl;
        switch (GetCorrectNumber(0,2))
        {
        case 1:
        {
            editPipes(Pipes);
            break;
        }
        case 2:
        {
            editCSs(CSs);
            break;
        }
        case 0:
            return;
        }
    }
}

int main()
{

    unordered_map <int, Pipe> Pipes;
    //unordered_map <int, Pipe>::iterator iter_pipe;

    unordered_map <int, CS> CSs = {};
    //unordered_map <int, CS>::iterator iter_cs;


    for (;;)
    {
        cout << "\n 1. Add a pipe"
            << "\n 2. Add Compressor Station"
            << "\n 3. Viewing all objects"
            << "\n 4. Redact Pipe"
            << "\n 5. Redact CS"
            << "\n 6. Save"
            << "\n 7. Load"
            << "\n 8. Delete pipe"
            << "\n 9. Delete station"
            << "\n 10. Pacet Redact"
            << "\n 11. Add a pipe to the network"
            << "\n 12. Delete Links"
            << "\n 13. Show links"
            << "\n 14. Topological sorting"
            << "\n 0. Exit\n";

        switch (GetCorrectNumber(0, 14))
        {
        case 1:
        {
            Pipe p;
            cin >> p;
            Pipes.insert({ p.getId(), p });
            break;
        }
        case 2:
        {
            CS c;
            cin >> c;
            CSs.insert({ c.getID(), c });
            break;
        }
        case 3:
        {
            if (Pipes.size() != 0)
            {
                cout << "Pipes: " << endl;
                PrintPipe(Pipes);
            }
            else cout << "No pipes." << endl;

            if (CSs.size() != 0)
            {
                cout << endl << "Compession Station: " << endl;
                PrintCS(CSs);
            }
            else cout << "No stations." << endl;
            break;
        }
        case 4:
        {
            if (Pipes.size() != 0)
                int id = Redact(Pipes);
            else cout << "No Pipe." << endl;

            break;
        }
        case 5:
        {
            if (CSs.size() != 0)
                int id = Redact(CSs);
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
            fout.open(name, ios::out);
            if (fout.is_open())
            {
                if (Pipes.size() != 0)
                    fout << Pipes.size() << endl << Pipe::getMaxID() << endl;
                else fout << 0 << endl << 0 << endl;
                if (CSs.size() != 0)
                    fout << CSs.size() << endl << CS::getMaxID() << endl;
                else fout << 0 << endl << 0 << endl;

                if (Pipes.size() != 0)
                    Savep(Pipes, fout);
                if (CSs.size() != 0)
                    Savec(CSs, fout);
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
            fin.open(name, ios::in);

            if (fin.is_open())
                Load(Pipes, CSs, fin);
            else cout << "error";
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
        case 10:
        {
            RedactingByFilter(Pipes, CSs);
            break;
        }
        case 11:
        {
            if (Pipes.size() > 0 && CSs.size() > 1)
                CreatLink(Pipes, CSs);
            else cout << " No data " << endl;
            break;
        }
        case 12:
        {
            if (Pipes.size() > 0 && CSs.size() > 1)
                DeleteLink(Pipes, CSs);
            else cout << "Eerrorrr..." << endl;
            break;
        }
        case 13:
        {
            if (Pipes.size() > 0 && CSs.size() > 1)
                PrintLink(Pipes);
            else cout << " No data " << endl;
            break;
        }
        case 14:
        {
            vector<vector<int>> r = CreateGraph(Pipes, CSs);
            Sort Topolog(r);
            set<int> vertices;
            for (const auto& p : Pipes)
                if (p.second.pin > 0 && p.second.pout > 0 && p.second.getRepair() == false && CSs.count(p.second.pin) && CSs.count(p.second.pout))
                {
                    vertices.insert(p.second.pout);
                    vertices.insert(p.second.pin);
                }
            unordered_map<int, int> VerticesIndex;
            int i = 0;
            for (const int& v : vertices)
                VerticesIndex.insert({ i++, v });
            Topolog.TopSort(VerticesIndex);
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