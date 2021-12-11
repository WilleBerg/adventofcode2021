#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>

using namespace std;

void createMaps(map<char,char> *m, map<char,int> *m2, map<char,bool> *m3, map<char,char> *m4){
    (*m)['{'] = '}';
    (*m)['['] = ']';
    (*m)['<'] = '>';
    (*m)['('] = ')';

    (*m2)['{'] = 3;
    (*m2)['['] = 2;
    (*m2)['<'] = 4;
    (*m2)['('] = 1;

    (*m3)['}'] = true;
    (*m3)[']'] = true;
    (*m3)[')'] = true;
    (*m3)['>'] = true;
    (*m3)['<'] = false;
    (*m3)['('] = false;
    (*m3)['['] = false;
    (*m3)['{'] = false;

    (*m4)['}'] = '{';
    (*m4)[']'] = '[';
    (*m4)['>'] = '<';
    (*m4)[')'] = '(';

}



int main(){
    stack<char> s;
    map<char,char> karta1;
    map<char,int> karta2;
    map<char, bool> isClosing;
    map<char,char> karta3;
    createMaps(&karta1, &karta2, &isClosing, &karta3);
    ifstream d;
    vector<string> v;
    d.open("input.txt");
    if (d.is_open())
    {
        while (d)
        {
            string tmp;
            d >> tmp;
            if (tmp != "")
            {
                v.push_back(tmp);
            }
        }
    }
    unsigned long long score = 0;
    bool corrupted = false;
    vector<string> incomplete;
    for (int i = 0; i < v.size(); i++)
    {
        stack<char> emptyMap;
        s = emptyMap;
        for (int j = 0; j < v[i].length(); j++)
        {
            if (!s.empty())
            {
                char curr = s.top();
                if (!isClosing[v[i][j]])
                {
                    s.push(v[i][j]);
                } else {
                    if (v[i][j] == karta1[curr])
                    {
                        s.pop();
                    } else {
                        corrupted = true;
                        break;
                    }
                    
                }
                
            } else {
                s.push(v[i][j]);
            }     
        }
        if (!s.empty() && !corrupted)
        {
            string tmp = "";
            int size = s.size();
            for (int j = 0; j < size; j++)
            {
                tmp += s.top();
                s.pop();
            }
            incomplete.push_back(tmp);
        }
        corrupted = false;
    }
    vector<unsigned long long> scores;
    for (int i = 0; i < incomplete.size(); i++)
    {
        score = 0;
        for (int j = 0; j < incomplete[i].length(); j++)
        {
            score *= 5;
            score += karta2[incomplete[i][j]];
        }
        scores.push_back(score);
    }
    unsigned long long smallest = scores[0];
    unsigned long long smallestIndex = 0;
    bool swi = false;
    for (int i = 0; i < scores.size(); i++)
    {
        smallest = scores[i];
        for (int j = i; j < scores.size(); j++)
        {
            unsigned long long curr = scores[j];
            if (curr < smallest)
            {
                smallest = curr;
                smallestIndex = j;
                swi = true;
            }
        }
        if (swi)
        {
            unsigned long long tmp = scores[i];
            scores[i] = scores[smallestIndex];
            scores[smallestIndex] = tmp;
        }
        swi = false;
        
        cout << i + 1 << " : " << scores[i] << endl;
    }
    cout << scores.size() << endl << ((scores.size() + 1) / 2 ) - 1 << endl;
    cout << scores[((scores.size() + 1) / 2) - 1] << endl;
    
    //cout << score << endl;
    return 0;
}