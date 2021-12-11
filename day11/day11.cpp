#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void readInput(vector<string> *d){
    ifstream m;
    m.open("input2.txt");
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

bool contains(vector<pair<int,int>> a, pair<int,int> b){
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].first == b.first && a[i].second == b.second)
        {
            return true;
        }
    }
    return false; 
}


int main(){
    vector<string> input;
    readInput(&input);
    vector<vector<int>> grid(input.size(), vector<int>());
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].length(); j++)
        {
            grid[i].push_back(ctoi(input[i][j]));
            cout << grid[i][j];
        }
        cout << endl;
    }
    int score = 0;
    for (int l = 0; l < 100; l++)
    {
        vector<pair<int,int>> over9;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                grid[i][j]++;
                if (grid[i][j] > 9)
                {
                    pair<int,int> p;
                    p.first = i;
                    p.second = j;
                    over9.push_back(p);
                }
            }
        }
        for (int i = 0; i < over9.size(); i++)
        {
            bool b[] = { 
                (over9[i].first > 0), 
                (over9[i].first < grid.size() - 1),
                (over9[i].second > 0),
                (over9[i].second < grid[i].size() - 1),
            };
            vector<pair<int,int>> c;
            c.push_back(pair<int,int>(over9[i].first - 1, over9[i].second));
            c.push_back(pair<int,int>(over9[i].first + 1, over9[i].second));
            c.push_back(pair<int,int>(over9[i].first, over9[i].second - 1));
            c.push_back(pair<int,int>(over9[i].first, over9[i].second + 1));
            c.push_back(pair<int,int>(over9[i].first - 1, over9[i].second - 1));
            c.push_back(pair<int,int>(over9[i].first + 1, over9[i].second + 1));
            c.push_back(pair<int,int>(over9[i].first - 1, over9[i].second + 1));
            c.push_back(pair<int,int>(over9[i].first + 1, over9[i].second - 1));
            for (int j = 0; j < 4; j++) {
                if (b[j] && !(contains(over9, c[j]))) {
                    grid[c[j].first][c[j].second]++;
                    if (grid[c[j].first][c[j].second] > 9) {
                        over9.push_back(c[j]);
                    }
                }
            }
            if (b[0] && b[2] && !(contains(over9, c[4])) )
            {
                grid[c[4].first][c[4].second]++;
                if (grid[c[4].first][c[4].second] > 9) {
                    over9.push_back(c[4]);
                }
            }
            if (b[1] && b[3] && !(contains(over9, c[5])) )
            {
                grid[c[5].first][c[5].second]++;
                if (grid[c[5].first][c[5].second] > 9) {
                    over9.push_back(c[5]);
                }
            }
            if (b[0] && b[3] && !(contains(over9, c[6])) )
            {
                grid[c[6].first][c[6].second]++;
                if (grid[c[6].first][c[6].second] > 9) {
                    over9.push_back(c[6]);
                }
            }
            if (b[1] && b[2]  && !(contains(over9, c[7])))
            {
                grid[c[7].first][c[7].second]++;
                if (grid[c[7].first][c[7].second] > 9) {
                    over9.push_back(c[7]);
                }
            }
        }
        for (int i = 0; i < over9.size(); i++)
        {
            grid[over9[i].first][over9[i].second] = 0;
        }
        int over9Size = over9.size();
        score += over9Size;
        cout << score << endl;
        /*
        for (int k = 0; k < grid.size(); k++)
        {
            for (int h = 0; h < grid[k].size(); h++)
            {
                cout << grid[k][h];
            }
            cout << endl;
        }
        */
    }
    
    
    
    return 0;
}