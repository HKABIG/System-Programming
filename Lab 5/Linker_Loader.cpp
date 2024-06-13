#include<bits/stdc++.h>
using namespace std;

int getSize(const string& fname) {
    ifstream file(fname, ios::binary | ios::ate);
    streampos size = file.tellg();
    file.seekg(0, ios::beg);
    return static_cast<int>(size); // Convert streampos to int
}

int getVarSize(string& dataType){
    if(dataType=="int" || dataType=="float") return 4;
    if(dataType=="char" || dataType=="bool") return 1;
}

void parseExternVar(const string& fname, vector<vector<string>>& externSym, vector<vector<string>>& Sym) {
    ifstream file(fname);
    string line;
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << fname << "\n";
        return;
    }
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> components;
        while (getline(ss, token, ' ')) {
            components.push_back(token);
        }
        if (components.empty() || components[0] == "void" || components.size() < 2) continue;
        // for(auto it:components) cout<<it<<"->";
        // cout<<endl;
        if (components.size()==3) {
            int size = getVarSize(components[1]);
            externSym.push_back({ components[2], components[1], to_string(size) });
        }
        else {
            int size = getVarSize(components[0]);
            Sym.push_back({ components[1], components[0], to_string(size) });
        }
    }
}

void printTables(vector<vector<string>>& externSym,vector<vector<string>>& Sym,vector<vector<string>>& globalVar){
    int addr = 1000;
    cout<<"Symbol Table: "<<endl;
    cout<<"Var"<<"\t"<<"Type"<<"\t"<<"Size"<<"\t"<<"Addr"<<endl;
    for(auto it:Sym){
        globalVar.push_back({it[0],it[1],it[2],to_string(addr)});
        cout<<it[0]<<"\t"<<it[1]<<"\t"<<it[2]<<"\t"<<to_string(addr)<<endl;
        addr += stoi(it[2]);
    }
    int eaddr = 5000;
    cout<<"Extern Table: "<<endl;
    cout<<"Var"<<"\t"<<"Type"<<"\t"<<"Size"<<endl;
    for(auto it:externSym){
        globalVar.push_back({it[0],it[1],it[2],to_string(eaddr)});
        cout<<it[0]<<"\t"<<it[1]<<"\t"<<it[2]<<endl;
        eaddr += stoi(it[2]);
    }
}

int main() {
    int memorySize;
    cout << "Enter size of memory: ";
    cin >> memorySize;

    int sizeA = getSize("a.c");
    int sizeB = getSize("b.c");

    int totalSize = sizeA + sizeB;
    cout << "Total size is: " << totalSize << endl;

    if(totalSize <= memorySize){
        cout << "Sufficient Memory for both." << endl; 
    }else if(sizeA <= memorySize){
        cout << "Sufficient Memory for A." << endl;
    }else if(sizeB <= memorySize){
        cout << "Sufficient Memory for B." << endl;
    }else{
        cout << "Insufficient Memory." << endl;
    }

    vector<vector<string>> externSymA, externSymB;
    vector<vector<string>> SymA, SymB;
    parseExternVar("a.c", externSymA, SymA); 
    parseExternVar("b.c", externSymB, SymB);

    vector<vector<string>> globalVarA,globalVarB;
    cout<<"Tables for a.c "<<"\n";
    printTables(externSymA,SymA,globalVarA);
    cout<<"\n"<<endl;
    cout<<"Tables for b.c "<<"\n";
    printTables(externSymB,SymB,globalVarB);
    cout<<"\n"<<endl;
    cout<<"Global Variable Table "<<endl;
    cout<<"Var"<<"\t"<<"Type"<<"\t"<<"Size"<<"\t"<<"Addr"<<endl;
    for(auto it:globalVarB){
        cout<<it[0]<<"\t"<<it[1]<<"\t"<<it[2]<<"\t"<<it[3]<<endl;
    }
    return 0;
}