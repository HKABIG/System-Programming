#include <bits/stdc++.h>
using namespace std;

struct MNT{
    int index;
    string name;
    int mntIndex;
};

struct MDT{
    int mdtindex;
    string card;
};

struct MNT mnt[100];
struct MDT mdt[100];

void insertMDT(string macroName,int MNT_index,int MDT_index){
    mnt[MNT_index].index = MNT_index;
    mnt[MNT_index].name = macroName;
    mnt[MNT_index].mntIndex = MDT_index;
}

void insertMNT(string _card,int MDT_index){
    mdt[MDT_index].card = _card;
    mdt[MDT_index].mdtindex = MDT_index;
}

int main(){
    ifstream file;
    string filename, line;
    filename = "Assembly.asm";
    vector<string> expandedcode;
    map<string,int> mdtMap;
    file.open(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    int MDT_index = 21; 
    int MNT_index = 1;
    while (getline(file, line)){
        if(line.empty()) continue;
        if (line.compare(0, 5, "macro") == 0) {
            string macroName = line.substr(6,3); 
            mdtMap[macroName] = MDT_index;
            insertMDT(macroName,MNT_index++,MDT_index);
            // Reading MDT CARD
            while(getline(file,line)){
                if(line.compare(0,4,"mend")==0){
                    insertMNT("mend",MDT_index++);
                    break;
                }else{
                    insertMNT(line.substr(0,10),MDT_index++);
                }
            }
        }else{
            if(line.compare(0,5,".code")==0){
                continue;
            }
            else if(line.compare(0,4,"endp")==0){
                expandedcode.push_back("endp");
            }else{
                string card = line.substr(0,3);
                int ind = mdtMap[card];
                for(int i=ind;mdt[i].card!="mend";i++){
                    expandedcode.push_back(mdt[i].card);
                }
            }
        }
    }
    cout<<"MNT Table"<<endl;
    cout<<"Index"<<"\t"<<"Name"<<"\t"<<"MDT Index"<<endl;
    for(int i=1;i<MNT_index;i++){
        cout<<mnt[i].index<<"\t"<<mnt[i].name<<"\t"<<mnt[i].mntIndex<<endl;
    }cout<<endl;
    cout<<"MDT Table"<<endl;
    cout<<"Index"<<"\t"<<"Card"<<endl;
    for(int i=21;i<MDT_index;i++){
        cout<<mdt[i].mdtindex<<"\t"<<mdt[i].card<<endl;
    }cout<<endl;
    cout<<"Expanded Code: "<<endl;
    for(auto it:expandedcode){
        cout<<it<<endl;
    }
}