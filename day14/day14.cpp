#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void readInput(vector<string> *d){
    fstream file;
    file.open("input2.txt");
    if (file.is_open())
    {
        while (file)
        {
            string tmp;
            file >> tmp;
            if (tmp != "")
            {
                d->push_back(tmp);
            }
        }
    }
}

string charing(char a, char b){
    string tmp = "";
    tmp += a;
    tmp += b;
    return tmp;
}

vector<char> poly(vector<char> org, map<string,string> rules){
    vector<char> result;
    for (int i = 0; i < org.size(); i++)
    {
        string tmp = (i + 1 < org.size() ? charing(org[i], org[i + 1]) : "end");
        if (tmp == "end") break;
        string combo;
        if (rules.find(tmp) != rules.end())
        {
            combo = rules[tmp];
        } else {
            continue;
        }
        if (i == 0)
        {    
            result.push_back(tmp[0]);
        }
        result.push_back(combo[0]);
        result.push_back(tmp[1]);
    }
    
    return result;
}

int main(){
    vector<string> data;
    readInput(&data); 

    vector<char> org;
    for (int i = 0; i < data[0].length(); i++)
    {
        org.push_back(data[0][i]);
    }
    map<string, string> rules;
    for (int i = 1; i < data.size(); i++)
    {
        rules[data[i]] = data[i + 2];
        i += 2;
    }
    for (int i = 0; i < 4; i++)
    {
        org = poly(org, rules);
        for (int j = 0; j < org.size(); j++)
        {
            cout << org[j];
        }
        cout << endl;
    }
    

    return 0;
}