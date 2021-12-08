#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool checkRow(vector<bool> tmp){
    int tmp2 = 0;
    for (int i = 0; i < 5; i++)
    {
        if (tmp[i] == true)
        {
            tmp2++;   
        }
        
    }
    if (tmp2 == 5)
    {
        return true;
    } else return false;
}

bool checkColumn(vector<vector<bool>> tmp, int index){
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (tmp[i][index] == true)
        {
            counter++;
        }
        
    }
    if (counter == 5)
    {
        return true;
    } else return false;
        
}

int main(){
    vector<string> input;
    ifstream inputFile;
    inputFile.open("input.txt");
    if (inputFile.is_open()){
        while (inputFile)
        {
           string tmp;
           inputFile >> tmp;
           input.push_back(tmp);
        }
        
    }

    vector<vector<vector<string>>> remadeVector(100, vector<vector<string>>(5, vector<string>(5)));
    vector<vector<vector<bool>>> booleanVector(100, vector<vector<bool>>(5, vector<bool>(5)));

    string firstLine = input.at(0);
    string tmp = "";
    vector<string> bingoNumbers;
    for (int i = 0; i < firstLine.length(); i++)
    {
        if (firstLine[i] != ',')
        {
            tmp += firstLine[i];
        } else {
            bingoNumbers.push_back(tmp);
            tmp = "";
        }
    }
    
    

    input.erase(input.begin());
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    for (int i = 0; i < input.size() - 1; i++)
    {
        if (count3 < 4)
        {
            remadeVector[count][count2][count3] = input[i];
            count3++;
        } else {
            remadeVector[count][count2][count3] = input[i];
            count2++;
            count3 = 0;
        }
        if (count2 > 4)
        {
            count2 = 0;
            count++;
        }
    }
    int breakIt = 0;
    int winningBoard;
    int lastNumber;
    int numberOfWinners = 0;
    map<int, bool> winningBoards;
    for (int l = 0; l < bingoNumbers.size(); l++)
    {    
        lastNumber = stoi(bingoNumbers[l]);
        for (int i = 0; i < remadeVector.size(); i++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if(bingoNumbers[l] == remadeVector[i][j][k] && !winningBoards[i]){
                        booleanVector[i][j][k] = true;
                        if (checkRow(booleanVector[i][j]) || checkColumn(booleanVector[i], k))
                        {
                            winningBoard = i;
                            numberOfWinners++;
                            winningBoards[i] = true;
                            cout << "Board " << i << " just won!" << endl;
                        } 
                    }
                    if (numberOfWinners >= 100)
                    {
                        breakIt = 1;
                        break; 
                    }
                    
                }
                if (breakIt)
                {
                    break;
                }
                
            }
            if (breakIt)
            {
                break;
            }
        }
        if (breakIt)
        {
            break;
        }
    }
    cout << lastNumber << endl;
    int counting = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << booleanVector[winningBoard][i][j] << " ";
            if (!booleanVector[winningBoard][i][j]){
                counting += stoi(remadeVector[winningBoard][i][j]);
            }
        }
       cout << endl; 
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << remadeVector[winningBoard][i][j] << " ";
        }
       cout << endl; 
    }
    cout << endl << counting << endl;
    cout << lastNumber * counting << endl; 
    return 0;
}