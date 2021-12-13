#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

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

vector<string> splitInput(vector<string> data){
    vector<string> result;
    for (int i = data.size() - 1; i >= 0; i--)
    {
        if (data[i][0] == 'x' || data[i][0] == 'y')
        {
            result.push_back(data[i]);
        } else if(data[i][0] == 'f' || data[i][0] == 'a'){
            continue;
        } else {
            break;
        }
    }
   return result; 
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

vector<pair<string,int>> fixInput(vector<string> ins){
    vector<pair<string,int>> tmp;
    for (int i = ins.size() - 1; i >= 0; i--)
    {
        pair<string,string> b = split(ins[i], '=');
        pair<string,int> a(b.first, stoi(b.second));
        tmp.push_back(a);
    }
    return tmp;
}



vector<pair<int,int>> createPairs(vector<string> data, map<pair<int,int>, bool> *k, int *x, int *y){
    vector<pair<int,int>> result;
    for (int i = 0; i < data.size(); i++)
    {
        char curr = data[i][0];
        bool prop = curr != 'f' && curr != 'a' && curr != 'x' && curr != 'y';
        if (prop)
        {
            pair<string,string> a = split(data[i], ',');
            pair<int,int> b(stoi(a.first), stoi(a.second));
            (*k)[b] = true;
            if (b.first > *x)
            {
                *x = b.first;
            }
            if (b.second > *y)
            {
                *y = b.second;
            }
            result.push_back(b);
        } else break;
    }
    return result;
}

void printPaper(vector<vector<char>> paper){
    for (int i = 0; i < paper.size(); i++)
    {
        for (int j = 0; j < paper[i].size(); j++)
        {
            cout << paper[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}

vector<vector<char>> foldY(vector<vector<char>> paper, int foldLine, int maxY){
    vector<vector<char>> result(foldLine, vector<char>());
    for (int i = 0; i < foldLine; i++)
    {
        for (int j = 0; j < paper[i].size(); j++)
        {
            if (paper[i][j] == '#' || paper[maxY][j] == '#')
            {
                result[i].push_back('#');
            } else {
                result[i].push_back('.');
            }
        }
        maxY--;
    }
    return result;
}

vector<vector<char>> foldX(vector<vector<char>> paper, int foldLine, int maxX){
    vector<vector<char>> result(paper.size(), vector<char>());
    int tmp = maxX;
    for (int i = 0; i < paper.size(); i++)
    {
        for (int j = 0; j < foldLine; j++)
        {
            if (paper[i][j] == '#' || paper[i][tmp] == '#')
            {
                result[i].push_back('#');
            } else {
                result[i].push_back('.');
            }
            //cout << result[i][j];
            tmp--;
            
        }
        //cout << endl;
        tmp = maxX;
    }
    return result;
}

int main(){
    vector<string> data;
    readInput(&data);

    map<pair<int,int>, bool> m;

    int maxX = 0;
    int maxY = 0;

    vector<string> instructions = splitInput(data);
    vector<pair<string,int>> insPair = fixInput(instructions);
    vector<pair<int,int>> cord = createPairs(data, &m, &maxX, &maxY);

    vector<vector<char>> paper(maxY + 1,vector<char>(maxX + 1));

    int x = 0;
    int y = 0;
    while (true)
    {
        pair<int,int> a(x,y);
        if (y <= maxY)
        {
            if (x <= maxX)
            {
                if (m[a])
                {
                    paper[y][x] = '#';
                } else {
                    paper[y][x] = '.';
                }
                x++;         
            } else {
                x = 0;
                y++;
            }
        } else {
            break;
        }
    }
    
    
    for (int i = 0; i < insPair.size(); i++)
    {
        if (insPair[i].first == "x")
        {
            paper = foldX(paper, insPair[i].second, paper[0].size() - 1);
        } else {
            paper = foldY(paper, insPair[i].second, paper.size() - 1);
        }
        printPaper(paper);
    }
    

    //paper = foldX(paper, 655, paper[0].size() - 1);

    long long dots = 0;

    for (int i = 0; i < paper.size(); i++)
    {
        for (int j = 0; j < paper[i].size(); j++)
        {
            if (paper[i][j] == '#')
            {
                dots++;
            }
        }
    }
    cout << endl << dots << endl; 

    return 0;
}