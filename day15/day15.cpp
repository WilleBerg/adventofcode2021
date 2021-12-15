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
    file.open("input.txt");
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

class Node{
    public:
        int x,y,val;
        bool visited;
        Node(int xa, int ya, long vala, bool a)
            : x(xa), y(ya), val(vala), visited(a)
        {}
};  

class nodeCompare{
    public:
    bool operator()(Node a, Node b){
        return (a.y == b.y && a.x == b.x);
    }
};

class nodeCmp{
    public:
    bool operator()(Node a, Node b){
        return (a.val < b.val);
    }
};

int main(){
    vector<string> data;
    readInput(&data); 
    queue<Node> q;
    auto cmp = [](Node a, Node b){return (a.val <= b.val) ;};
    set<Node, decltype(cmp)> s(cmp);
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            Node a { j, i, LONG_MAX, false};
            s.insert(a);
        }
    }
    
    Node start {0, 0, 0, false};
    q.push(start);
    while(!q.empty()){

    }


    return 0;
}