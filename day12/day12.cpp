#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void readInput(vector<string> *d){
    ifstream m;
    m.open("input.txt");
    if (m.is_open())
    {
        while (m)
        {
            string tmp;
            m >> tmp;
            if(tmp != ""){
                (*d).push_back(tmp);
            }
        }
    }
}

pair<string,string> split(string s, char delim){
    string tmp = "";
    pair<string,string> p;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == delim)
        {
            p.first = tmp;
            tmp = "";
        } else {
            tmp += s[i];
        }
    }
    p.second = tmp;
    return p;
}

vector<string> paths;

int findPaths(map<string,int> timesTravelled, map<string, vector<string>> avail, string curr, string printString, bool allowTwo){
    printString += ", " + curr;
    timesTravelled[curr]++;
    if (curr == "end")
    {
        cout << printString << endl;
        paths.push_back(printString);
        return 1;
    }
    
    for (int i = 0; i < avail[curr].size(); i++)
    {
        if (avail[curr][i] != "start")
        {
            if (!islower(avail[curr][i][0]) || avail[curr][i] == "end")
            {
                findPaths(timesTravelled, avail, avail[curr][i], printString, allowTwo);
            } else
            {
                if (timesTravelled[avail[curr][i]] == 0)
                {
                    findPaths(timesTravelled, avail, avail[curr][i], printString, allowTwo);
                } else if (timesTravelled[avail[curr][i]] == 1 && allowTwo)
                {
                    findPaths(timesTravelled, avail, avail[curr][i], printString, false);
                }
                
            } 
        }
    }
    
    return 0;
}

int main(){
    vector<string> data;
    readInput(&data);
    vector<pair<string,string>> pairs(data.size(),pair<string,string>());
    map<string,int> timesTravelled;
    map<string, vector<string>> availablePaths;
    for (int i = 0; i < data.size(); i++) {
        pairs[i] = split(data[i], '-');
    }
    for (int i = 0; i < pairs.size(); i++) {
        //cout << "First : " << pairs[i].first << " | Second : " << pairs[i].second << endl;
        timesTravelled[pairs[i].first] = 0;
        timesTravelled[pairs[i].second] = 0;
        availablePaths[pairs[i].first].push_back(pairs[i].second);
        availablePaths[pairs[i].second].push_back(pairs[i].first);
    }
    int totalPaths = 0;
    for (int i = 0; i < availablePaths["start"].size(); i++)
    {
        string tmp = "start";
        findPaths(timesTravelled, availablePaths, availablePaths["start"][i], tmp, true);
    }
    cout << paths.size() << endl;
    
    return 0;
}
