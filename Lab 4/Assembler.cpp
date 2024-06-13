#include<bits/stdc++.h>
using namespace std;

class MOT{
public:
    string mneumonic;
    int opcode, operands;

    MOT(string mneumonic, int opcode, int operands){
        this->mneumonic = mneumonic;
        this->opcode = opcode;
        this->operands = operands;
    }
};

class mainp{
public:
    int line;
    string label;
    string memorial;
    string operand;
    int location;
    string output;

    mainp(int line, string label, string memorial, string operand, int location, string output){
        this->line = line;
        this->label = label;
        this->memorial = memorial;
        this->operand = operand;
        this->location = location;
        this->output = output;
    }
};

vector<MOT> mot;
map<string, int> pot;
map<string, int> mot_table;
int lineNumber = 1;
int location_count = 0;
vector<mainp> maintable;
map<string, int> sym_table;

void printMOT(){
    cout<<"\n";
    cout<<"Mnemonic"<<"\t"<<"Opcode"<<"\t"<<"No. Of Operands\n";
    for(auto it:mot){
        cout<<it.mneumonic<<"\t\t"<<it.opcode<<"\t"<<it.operands<<"\n";
    }
    cout<<"\n";
}

void printPOT(){
    cout<<"\n";
    cout<<"Pseudo-Opcode"<<"\t"<<"No. Of Operands\n";
    for(auto it:pot){
        cout<<it.first<<"\t\t"<<it.second<<"\n";
    }
    cout<<"\n";
}

void put_MOT(){
    ifstream file("MOT.txt");
    string line;
    if (!file.is_open()) {
        cerr << "Error: Unable to open POT.txt\n";
        return;
    }
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        vector<string> components;
        while (getline(ss, token, ' ')) {
            components.push_back(token);
        }
        mot_table[components[0]] = stoi(components[1]);
        mot.push_back(MOT(components[0],stoi(components[1]),stoi(components[2])));
    }
    printMOT();
}

void put_POT(){
    ifstream file("POT.txt");
    string line;
    if (!file.is_open()) {
        cerr << "Error: Unable to open POT.txt\n";
        return;
    }
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        vector<string> components;
        while (getline(ss, token, ' ')) {
            components.push_back(token);
        }
        pot[components[0]] = stoi(components[1]);
    }
    printPOT();
}

void take_input(){
    ifstream file("input.txt");
    string line;
    int ct = 2;
    while (getline(file, line))
    {
        istringstream iss(line);
        string token;
        vector<string> temp;
        while (getline(iss, token, ' '))
        {
            temp.push_back(token);
        }
        if (temp.size() == 2)
        {
            maintable.push_back(mainp(lineNumber, "", temp[0], temp[1], location_count, ""));
            location_count += ct;
        }
        else if (temp.size() == 3)
        {
            sym_table[temp[0]] = location_count;
            maintable.push_back(mainp(lineNumber, temp[0], temp[1], temp[2], location_count, ""));
            location_count += ct;
        }
        else if (temp[0] == "STOP")
        {
            maintable.push_back(mainp(lineNumber, "", temp[0], "", location_count, ""));
            ct = 1;
            location_count += ct;
            ct = 2;
        }
        lineNumber++;
    }
}

void secondPass()
{
    for (auto &i : maintable)
    {
        string memorial = i.memorial;
        string operand = i.operand;
        int opcode = mot_table[memorial];
        int location = sym_table[operand];

        i.output = to_string(opcode) + "_" + to_string(location);
    }
}

void printMainTable(){
    cout<<"\n";
    cout<<"Line"<<"\t"<<"Label"<<"\t       "<<"Mnemonic"<<"\t"<<"operand"<<"\t"<<"Location"<<"\t"<<"Output"<<endl;
    for (auto it : maintable){
        cout<<it.line<<"\t"<<it.label<<"\t\t"<<it.memorial<<"\t"<<it.operand<<"\t"<<it.location<<"\t\t"<<it.output<<endl;
    }
    cout<<"\n";
}

void printSymbTable(){
    cout<<"\n";
    cout<<"Symbol"<<"\t"<<"Address"<<endl;
    for(auto it:sym_table){
        cout<<it.first<<"\t"<<it.second<<endl;
    }
    cout<<"\n";
}

int main(){
    put_MOT();
    put_POT();
    take_input();
    printSymbTable();
    secondPass();
    printMainTable();
}