#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> split(vector<string> tmp, char delimiter){
    string tmpString = "";
    vector<int> result;
    for (int i = 0; i < tmp.size(); i++)
    {
        tmpString = "";
        for (int j = 0; j < tmp[i].length(); j++)
        {
            if (tmp[i][j] == delimiter)
            {
                result.push_back(stoi(tmpString));
                tmpString = ""; 
            } else {
                tmpString += tmp[i][j];
            }
            
        }
        if (tmpString != "")
        {    
            result.push_back(stoi(tmpString)); 
        }
        
    }
    return result;
}


map<int, unsigned long long> func(map<int, unsigned long long> ha, int max) {
    int count = 0;
    int counter = 0;
    for (int i = 0; i < max; i++)
    {
        map<int, unsigned long long> temp = ha;
        for (int j = 0; j < temp.size(); j++)
        {
            if (j == 0)
            {
                ha[10] = ha[0];
                ha[9] = ha[0];
                ha[0] = 0;
            } else if(j != 9 && j != 10){
                ha[j - 1] += temp[j];
                ha[j] = 0;
            }
        }
        ha[8] += ha[10];
        ha[6] += ha[9];

    }
    return ha;
}

int main(){
    ifstream myInput;
    myInput.open("input.txt");
    vector<string> data;
    if (myInput.is_open())
    {
        while (myInput)
        {
            string tmp;
            myInput >> tmp;
            data.push_back(tmp);
        }
    }
    map<int,unsigned long long> mapping;
    
    for (int i = 0; i < 10; i++)
    {
        mapping[i] = 0;
    }
    vector<int> dataInt = split(data, ',');
    for (int i = 0; i < dataInt.size(); i++)
    {
        mapping[dataInt[i]]++;
    }
    map<int, unsigned long long> test;
    test[1] = 1;
    test[0] = 0;
    test[2] = 1;
    test[3] = 2;
    test[4] = 1;
    test[5] = 0;
    test[6] = 0;
    test[7] = 0;
    test[8] = 0; 
    test = func(test, 18);
    mapping = func(mapping, 256);
    unsigned long long counting = 0;
    for (int i = 0; i < 9; i++)
    {
        counting += mapping[i];   
    }
    
    cout << counting << endl;
    return 0;
}