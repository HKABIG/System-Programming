#include<bits/stdc++.h>
using namespace std;

int main(){
    ifstream file;
    string filename, line;

    filename = "test.c";

    file.open(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    vector<vector<string>> sym_tab(20);
    int index = 0;
    while (getline(file, line)) {
        if (line.find("main()") != string::npos){
             continue;   
        }
        int ind=0;
        while(line[ind]==' '){
            ind++;
        }
        if(line[ind]=='/') continue;
        if(line.substr(ind,3)=="int"){
            sym_tab[index].push_back("int");
            sym_tab[index].push_back("4");
            ind += 3;
        }else if( line.substr(ind,5)=="float"){
            sym_tab[index].push_back("float");
            sym_tab[index].push_back("4");
            ind += 5;
        }
        else if(line.substr(ind,4)=="bool"){
            sym_tab[index].push_back("bool");
            sym_tab[index].push_back("1");
            ind += 4;
        }else if(line.substr(ind,4)=="char"){
            sym_tab[index].push_back("char");
            sym_tab[index].push_back("1");
            ind += 4;
        }
        else if(line.substr(ind,6)=="double"){
            sym_tab[index].push_back("double");
            sym_tab[index].push_back("8");
            ind += 6;
        }else{
            continue;
        }
        while(line[ind]==' '){
            ind++;
        }
        string str = "";
        while(line[ind]!=';'){
            if(line[ind]=='='){
                sym_tab[index].push_back(str);
                str = "";
            }
            else if(line[ind]==','){
                if(!isdigit(str[0]) && str[0]!='\'' && str[0]!='"'){
                    sym_tab[index].push_back(str);   
                }
                str = "";
            }
            else{
                if(line[ind]!=' ')
                    str += line[ind];
            }
            ind++;
            
        }
        if(!isdigit(str[0]) && str[0]!='\'' && str[0]!='"'){
            sym_tab[index].push_back(str);   
        }
        index++;
    }
    int address = 0;
    cout<<"\tSize"<<"\tType"<<"\tSymbol"<<"\tAddress"<<endl;
    for(auto it:sym_tab){
        string sz = it[1];
        string symbo = it[0];
        for(int i=2;i<it.size();i++){
            
            cout<<"\t"<<sz<<"\t"<<symbo<<"\t"<<it[i]<<"\t"<<address<<"\t"<<endl;
            address+=stoi(sz);
        }
    }
    file.close();
}