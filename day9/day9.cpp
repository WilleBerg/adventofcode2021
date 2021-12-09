#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

string ctos(char a){
    string tmp = "";
    tmp += a;
    return tmp;
}

class Node{
    public:
            int i,j,val;
};


vector<vector<Node>> basin(vector<Node> curr, vector<string> data){
    vector<vector<Node>> result(curr.size(),vector<Node>());
    map<pair<int,int>, bool> m;
    
    for (int i = 0; i < curr.size(); i++)
    {
        queue<Node> q;
        q.push(curr[i]);
        while (!q.empty())
        {
            Node currentNode = q.front();
            pair<int,int> a;
            a.first = currentNode.i;
            a.second = currentNode.j;
            m[a] = true;
            result[i].push_back(currentNode);
            q.pop();

            vector<Node> tmp;

            if (currentNode.i > 0)
            {
                Node tmpNode;
                tmpNode.i = currentNode.i - 1;
                tmpNode.j = currentNode.j;
                tmpNode.val = stoi(ctos(data[currentNode.i - 1][currentNode.j]));
                tmp.push_back(tmpNode);            
            }
            if (currentNode.i < data.size() - 1)
            {
                Node tmpNode;
                tmpNode.i = currentNode.i + 1;
                tmpNode.j = currentNode.j;
                tmpNode.val = stoi(ctos(data[currentNode.i + 1][currentNode.j]));
                tmp.push_back(tmpNode);                
            }
            if (currentNode.j > 0)
            {
                Node tmpNode;
                tmpNode.i = currentNode.i;
                tmpNode.j = currentNode.j - 1;
                tmpNode.val = stoi(ctos(data[currentNode.i][currentNode.j - 1]));
                tmp.push_back(tmpNode);             
            }
            if (currentNode.j < data[currentNode.i].length() - 1)
            {
                Node tmpNode;
                tmpNode.i = currentNode.i;
                tmpNode.j = currentNode.j + 1;
                tmpNode.val = stoi(ctos(data[currentNode.i][currentNode.j + 1]));
                tmp.push_back(tmpNode);              
            }
            for (int j = 0; j < tmp.size(); j++)
            {
                pair<int,int> c;
                c.first = tmp[j].i;
                c.second = tmp[j].j;
                if (/*currentNode.val + 1 == tmp[j].val && */!m[c] && tmp[j].val != 9)
                {
                    q.push(tmp[j]);
                    m[c] = true;
                }
            }
        }
    }
    cout << m.size() << endl;
    return result;
}

bool checkAdj(vector<string> data, int i, int j){
    int dataSize = data.size() - 1;
    char curr = data[i][j];
    bool iOver0 = i > 0;
    bool iUnderSize = i < data.size() - 1;
    bool jOver0 = j > 0;
    bool jUnderSize = j < data[i].length() - 1;
    string tmp[4] = {"", "", "", ""};
    if (iOver0)
    {
        tmp[0] = ctos(data[i - 1][j]);
    }
    if (iUnderSize)
    {
        tmp[1] = ctos(data[i + 1][j]);
    }
    if (jOver0)
    {
        tmp[2] = ctos(data[i][j - 1]);
    }
    if (jUnderSize)
    {
        tmp[3] = ctos(data[i][j + 1]);
    }
    
    for (int l = 0; l < 4; l++)
    {
        if (tmp[l] != "")
        {
            int currI = stoi(ctos(data[i][j]));
            int currL = stoi(tmp[l]);
            if (currI >= currL)
            {
                return false;
            }
        }
    }
    
    return true;
}

int main(){
    ifstream my;
    vector<string> data;
    my.open("accounts.txt");
    if (my.is_open())
    {
        while (my)
        {
            string tmp;
            my >> tmp;
            if (tmp != "")
            {
                data.push_back(tmp);
            }
        }
    }
    vector<Node> bas;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].length(); j++)
        {
            if (checkAdj(data,i,j))
            {
                Node curr;
                curr.i = i;
                curr.j = j;
                curr.val = stoi(ctos(data[i][j]));
                bas.push_back(curr);
            }
        }
    }
    vector<vector<Node>> resulting = basin(bas, data);
    //bad solution time
    int b1 = 0;
    int b2 = 0;
    int b3 = 0;
    for (int i = 0; i < resulting.size(); i++)
    {
        int currSize = resulting[i].size();
        if (currSize > b3)
        {
            if (currSize > b2)
            {
                if (currSize > b1)
                {
                    b3 = b2;
                    b2 = b1;
                    b1 = currSize;
                } else {
                    b3 = b2;
                    b2 = currSize;
                }
                
            } else {
                b3 = currSize;
            }
        }
    }
    cout << b1 * b2 * b3 << endl;
    
    return 0;
}