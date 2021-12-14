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
char stringing(string a){
    return a[0];
}

map<char, long long> poly2(vector<char> org, map<string,string> rules, vector<string> combos, int times){
    map<string, long long> result;
    map<string, vector<string>> convert;
    map<char, long long> resulting;

    for (int i = 0; i < combos.size(); i++)
    {
        string a = rules[combos[i]];
        convert[combos[i]].push_back(charing(combos[i][0], stringing(rules[combos[i]])));
        convert[combos[i]].push_back(charing(stringing(rules[combos[i]]), combos[i][1]));
        result[combos[i]] = 0;
    }
    for (int i = 0; i < org.size(); i++)
    {
        string tmp = (i + 1 < org.size() ? charing(org[i], org[i + 1]) : "end");
        if (resulting.find(org[i]) != resulting.end())
        {
            resulting[org[i]]++;
        } else {
            resulting[org[i]] = 1;
        }
        if(tmp == "end") break;
        result[tmp]++;
    }
    for (int i = 0; i < times; i++)
    {
        map<string, long long> tmp;
        for (int j = 0; j < combos.size(); j++)
        {
            tmp[combos[j]] = 0;
        }
        for (int j = 0; j < combos.size(); j++)
        {
            string aaa = combos[j];
            if (result[combos[j]])
            {
                vector<string> t = convert[combos[j]];
                tmp[t.at(0)] += result[combos[j]];
                tmp[t.at(1)] += result[combos[j]];
                if (resulting.find(stringing(rules[combos[j]])) != resulting.end())
                {
                    resulting[stringing(rules[combos[j]])] += result[combos[j]];
                } else {
                    resulting[stringing(rules[combos[j]])] = result[combos[j]];
                }
            }
        }
        result = tmp;
    }
    
    
    
    return resulting;
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
    vector<string> combos;
    for (int i = 1; i < data.size(); i++)
    {
        rules[data[i]] = data[i + 2];
        combos.push_back(data[i]);
        i += 2;
    }
   
    
    map<char,long long> m = poly2(org, rules, combos, 40);

    string aa = "BCFHKNOPSV";
    long long smallest = 9223372036854775807;
    long long largest = -1;
    
    for (int i = 0; i < aa.length(); i++)
    {
        if (m.find(aa[i]) != m.end())
        {
            if (m[aa[i]] < smallest)
            {
                smallest = m[aa[i]];
            }
            if (m[aa[i]] > largest)
            {
                largest = m[aa[i]];
            }
        }
         
    }
    cout << largest - smallest << endl; 
    return 0;
}