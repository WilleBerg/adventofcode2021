#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void thisFunc(int x1, int y1, int x2, int y2, vector<vector<int>> *tmp){
    int equalCount = 0;
    if (x1 == x2)
    {
        equalCount++;
    }
    if (y1 == y2)
    {
        equalCount++;
    }
    if (equalCount == 0)
    {
        bool x1Larger = (x1 - x2 > 0);
        bool y1Larger = (y1 - y2 > 0);
        while(true){
            if (x1 == x2 && y1 == y2)
            {
                (*tmp)[y1][x1]++;
                break;
            }
            (*tmp)[y1][x1]++;
            x1Larger ? x1-- : x1++;
            y1Larger ? y1-- : y1++;
        }
        return;
    }
    for (int i = ((y1 - y2 > 0) ? y2 : y1); i <= ((y1 - y2 > 0) ? y1 : y2); i++)
    {
        for (int j = ((x1 - x2 > 0) ? x2 : x1); j <= ((x1 - x2 > 0) ? x1 : x2); j++)
        {
            (*tmp)[i][j] += 1; 
        }
        
    }
    return;
}
vector<int> translateInput(vector<string> tmp){
    vector<int> resultingVector;
    for (int i = 0; i < tmp.size(); i++) {
        string tmpString = "";
        for (int j = 0; j < tmp[i].length(); j++)
        {
            if (tmp[i][j] == ',')
            {
                resultingVector.push_back(stoi(tmpString));
                tmpString = ""; 
            } else {
                tmpString += tmp[i][j];
            }
        }
        resultingVector.push_back(stoi(tmpString));
    }
    return resultingVector;
}
int main(){
    ifstream inputFile;
    inputFile.open("input.txt");
    vector<string> inputVector;
    if (inputFile.is_open()){
        while (inputFile)
        {
            string tmp;
            inputFile >> tmp;
            inputVector.push_back(tmp);
        }
        
    }
    vector<vector<string>> cordVector(500,vector<string>(0));
    int y = 0;
    int x = 0;
    for (int i = 0; i < inputVector.size(); i++)
    {
        if (inputVector[i] != "->")
        {
            cordVector[y].push_back(inputVector[i]);
            x++;
            if (x == 2)
            {
                x = 0;
                y++;
            }
            
        }
         
    }
    vector<vector<int>> testVector(1000,vector<int>(1000));
    for (int i = 0; i < cordVector.size(); i++)
    {
        vector<int> coordinatesInt = translateInput(cordVector[i]);
        thisFunc(coordinatesInt[0], coordinatesInt[1], coordinatesInt[2], coordinatesInt[3], &testVector);
    }
    int overTwo = 0;
    for (int i = 0; i < testVector.size(); i++)
    {
        for (int j = 0; j < testVector[i].size(); j++)
        {
            if (testVector[i][j] >= 2)
            {
                overTwo++;
            }
            
        }
    }
    
    
    cout << overTwo; 

    return 0;
}