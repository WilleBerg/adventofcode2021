#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int calculateSteps(int val){
    int result = 0;
    for (int i = 0; i < val; i++)
    {
        result += i + 1;
    }
    return result;
}

vector<int> split(vector<string> vec, char delimiter){
    string tmp = "";
    vector<int> result;
    for (int i = 0; i < vec.size(); i++)
    {
        tmp = "";
        for (int j = 0; j < vec[i].length(); j++)
        {
            if (vec[i][j] == delimiter)
            {
                result.push_back(stoi(tmp));
                tmp = "";
            } else {
                tmp += vec[i][j];
            }
        }
        if (tmp != "")
        {
            result.push_back(stoi(tmp));
        }
    }
    return result;
}

int main(){
    ifstream myInput;
    vector<string> data;
    myInput.open("input.txt");
    if (myInput.is_open())
    {
        while (myInput)
        {
            string tmp;
            myInput >> tmp;
            data.push_back(tmp);
        }
    }
    
    vector<int> myData = split(data, ',');
    int curr;
    int omega = 0;
    int smallest;
    for (int i = 0; i < 2000; i++)
    {
        for (int j = 0; j < myData.size(); j++)
        {
            curr = abs(myData[j] - i);
            omega += calculateSteps(curr);
        }
        if(i == 0){
            smallest = omega;
        } else if(smallest > omega) {
            smallest = omega;
        }
        omega = 0;
    }
    cout << smallest << endl;
    return 0;
}