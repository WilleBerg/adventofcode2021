#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

void readInput(vector<string> *d, string fileName){
    fstream file;
    file.open(fileName);
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


class Node{
    public:
        pair<int,int> a;
        int val;
        bool visited;
        Node(pair<int,int> b, long vala)
            : a(b), val(vala)
        {}
};  

class CompareVal{
    public:
        bool operator()(Node a, Node b){
            return a.val > b.val;
        }
};

long calculateDist(pair<int,int> curr, pair<int,int> neigh, vector<string> data, map<pair<int,int>, long> *m, map<pair<int,int>, pair<int,int>> *n){
    int neighVal = ctoi(data[neigh.first][neigh.second]);
    if (neighVal + (*m)[pair<int,int>(curr.first, curr.second)] <= (*m)[pair<int,int>(neigh.first, neigh.second)])
    {
        (*n)[neigh] = curr;
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
                if (nmbr2 < 0)
                {
                    nmbr = abs(nmbr2);
                }
                result[i] += itoc(nmbr);
            }
        }
    }
    int resultSize = result.size();
    for (int l = 1; l < 5; l++)
    {
        for (int i = 0; i < resultSize; i++)
        {   
            string tmp = "";
            for (int j = 0; j < result[i].length(); j++)
            {
                int nmbr = ctoi(result[i][j]) + l;
                int nmbr2 = 9 - nmbr;
                if (nmbr2 < 0)
                {
                    nmbr = abs(nmbr2);
                }
                tmp += itoc(nmbr);
            }
            result.push_back(tmp);
        }
    }
    return result;
}

int main(){
    vector<string> data;
    vector<string> testData;
    readInput(&testData, "input3.txt");
    readInput(&data, "input.txt"); 

    priority_queue<Node, vector<Node>, CompareVal> q;
    map<pair<int,int>, long> m;
    map<pair<int,int>, bool> hasVisited;
    map<pair<int,int>, bool> isInQueue;
    map<pair<int,int>, pair<int,int>> name;

    data = createMap(data);

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
    name[start] = pair<int,int>(0,0);
    hasVisited[start] = true;
    

    int width = data[0].size();
    int height = data.size();

    int trues = 0;
    int falses = 0;

    long iterations = 0;

    Node startingNode = {start, 0};
    q.push(startingNode);
    isInQueue[start] = true;
    
    while(!q.empty() && !hasVisited[pair<int,int>(height - 1, width - 1)]){

        Node curr = q.top();
        iterations++;
        
        q.pop();
        if (curr.a.second + 1 < width && !hasVisited[pair<int,int>(curr.a.first, curr.a.second + 1)]) {    
            pair<int,int> b(curr.a.first, curr.a.second + 1);
            long distance = calculateDist(curr.a, b, data, &m, &name);
            Node b2 = {b, distance};
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b2);
                isInQueue[b] = true;
            }
        }
        if(curr.a.second - 1 > 0 && !hasVisited[pair<int,int>(curr.a.first,curr.a.second - 1)]){
            pair<int,int> b(curr.a.first, curr.a.second - 1);
            long distance = calculateDist(curr.a, b, data, &m, &name);
            Node b2 = {b, distance};
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b2);
                isInQueue[b] = true;
            }
        }
        if (curr.a.first + 1 < height && !hasVisited[pair<int,int>(curr.a.first + 1,curr.a.second)]){
            pair<int,int> b(curr.a.first + 1, curr.a.second);
            long distance = calculateDist(curr.a, b, data, &m, &name);
            Node b2 = {b, distance};
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b2);
                isInQueue[b] = true;
            }
        }
        if (curr.a.first - 1 > 0 && !hasVisited[pair<int,int>(curr.a.first - 1,curr.a.second)]){
            pair<int,int> b(curr.a.first - 1, curr.a.second);
            long distance = calculateDist(curr.a, b, data, &m, &name);
            Node b2 = {b, distance};
            m[b] = distance;
            if (!isInQueue[b])
            {
                q.push(b2);
                isInQueue[b] = true;
            }
        }  
        hasVisited[curr.a] = true; 
        isInQueue[curr.a] = false; 
    }
    pair<int,int> testi = name[pair<int,int>(height - 1, width - 1)];
    while (testi != pair<int,int>(0,0))
    {
        data[testi.first][testi.second] = 'X';
        testi = name[pair<int,int>(testi.first,testi.second)];
    }
    
    cout << "Cheapest path => " <<  m[pair<int,int>(height - 1, width - 1)] << " Iterations => " << iterations << endl;

    return 0;
}