#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

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

int ctoi(char a){
    map<char, int> b;
    b['0'] = 0;
    b['1'] = 1;
    b['2'] = 2;
    b['3'] = 3;
    b['4'] = 4;
    b['5'] = 5;
    b['6'] = 6;
    b['7'] = 7;
    b['8'] = 8;
    b['9'] = 9;

    return b[a];
}

char itoc(int a){
    map<int, char> b;
    b[0] = '0';
    b[1] = '1';
    b[2] = '2';
    b[3] = '3';
    b[4] = '4';
    b[5] = '5';
    b[6] = '6';
    b[7] = '7';
    b[8] = '8';
    b[9] = '9';
    
    return b[a];
}

/*
class Node{
    public:
        int x,y,val;
        bool visited;
        Node(int xa, int ya, long vala)
            : x(xa), y(ya), val(vala)
        {}
};  
*/

long calculateDist(pair<int,int> curr, pair<int,int> neigh, vector<string> data, map<pair<int,int>, long> *m, map<pair<int,int>, bool> *hasVisited){
    int neighVal = ctoi(data[neigh.first][neigh.second]);
    if (neighVal + (*m)[pair<int,int>(curr.first, curr.second)] < (*m)[pair<int,int>(neigh.first, neigh.second)])
    {
        return neighVal + (*m)[pair<int,int>(curr.first, curr.second)];
    }
    else return (*m)[pair<int,int>(neigh.first, neigh.second)];
}

bool qContains(queue<pair<int,int>> q, pair<int,int> a){
    while (!q.empty())
    {
        pair<int,int> curr = q.front();
        q.pop();
        if (curr == a)
        {
            return true;
        }
    }
    return false;
}

vector<string> createMap(vector<string> data){
    vector<string> result = data;
    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 1; k < 5; k++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                int nmbr = ctoi(data[i][j]) + k;
                int nmbr2 = 9 - nmbr;
                if (nmbr2 <= 0)
                {
                    nmbr = abs(nmbr2);
                }
                result[i] += itoc(nmbr);
            }
        }
    }
    
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].length(); j++)
        {
            cout << result[i][j];
        }
        cout << endl;
    }
    

    return result;
}

int main(){
    vector<string> data;
    readInput(&data); 
    queue<pair<int,int>> q;
    map<pair<int,int>, long> m;
    map<pair<int,int>, bool> hasVisited;
    map<pair<int,int>, bool> isInQueue;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            pair<int,int> a(i,j);
            m[a] = LONG_MAX;
            hasVisited[a] = false; 
            isInQueue[a] = false;
        }
    }
    pair<int,int> start(0,0);
    m[start] = 0;
    hasVisited[start] = true;
    vector<string> test = createMap(data);

    return 0;

    int width = data[0].size();
    int height = data.size();
    int trues = 0;
    int falses = 0;
    q.push(start);
    isInQueue[start] = true;
    while(!q.empty()){
        pair<int,int> curr = q.front();
        if (hasVisited[curr])
        {
            //cout << "True : " << trues++ << endl;
        } else {
            //cout << "False : " << falses++ << endl;
        }
        if (trues == 1000)
        {
            cout << "here";
        }
        
        q.pop();
        if (curr.second + 1 < width && !hasVisited[pair<int,int>(curr.first,curr.second + 1)]) {    
            pair<int,int> b(curr.first, curr.second + 1);
            long distance = calculateDist(curr, b, data, &m, &hasVisited);
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b);
                isInQueue[b] = true;
            }
        }
        if(curr.second - 1 > 0 && !hasVisited[pair<int,int>(curr.first,curr.second - 1)]){
            pair<int,int> b(curr.first, curr.second - 1);
            long distance = calculateDist(curr, b, data, &m, &hasVisited);
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b);
                isInQueue[b] = true;
            }
        }
        if (curr.first + 1 < height && !hasVisited[pair<int,int>(curr.first + 1,curr.second)]){
            pair<int,int> b(curr.first + 1, curr.second);
            long distance = calculateDist(curr, b, data, &m, &hasVisited);
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b);
                isInQueue[b] = true;
            }
        }
        if (curr.first - 1 > 0 && !hasVisited[pair<int,int>(curr.first - 1,curr.second)]){
            pair<int,int> b(curr.first - 1, curr.second + 1);
            long distance = calculateDist(curr, b, data, &m, &hasVisited);
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b);
                isInQueue[b] = true;
            }
        }  
        hasVisited[curr] = true; 
        isInQueue[curr] = false; 
    }

    cout << m[pair<int,int>(height - 1, width - 1)] << endl;

    return 0;
}