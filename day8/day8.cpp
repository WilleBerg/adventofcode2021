#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string seg2(string input){
    char ch;
    string tmp = input;
    int length = tmp.length();
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < (length - 1); j++)
        {
            if(input[j]>input[j+1])
            {
                ch = input[j];
                input[j] = input[j+1];
                input[j+1] = ch;
            }
        }
    }
    
    if (input == "abcefg") return "0";
    else if(input == "cf" || input.length() == 2) return "1";
    else if(input == "acdeg") return "2";
    else if(input == "acdfg") return "3";
    else if(input == "bcdf" ||input.length() == 4) return "4";
    else if(input == "abdfg") return "5";
    else if(input == "abdefg") return "6";
    else if(input == "acf" || input.length() == 3) return "7";
    else if(input == "abcdefg" || input.length() == 7) return "8";
    else if(input == "abcdfg") return "9";
    
    

    return "-1";
}

string seg3(vector<string> input, vector<string> output){
    string one,four,seven;
    for (int i = 0; i < input.size(); i++) {
        if (input[i].length() == 2) {
            one = input[i];
        } else if (input[i].length() == 4) {
            four = input[i];
        } else if(input[i].length() == 3){
            seven = input[i];
        }
    }
    map<char,int> kart;
    kart['a'] = 0;
    kart['b'] = 0;
    kart['c'] = 0;
    kart['d'] = 0;
    kart['e'] = 0;
    kart['f'] = 0;
    kart['g'] = 0;
    map<int,char> mapping;
    string a = "abcdefg";
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].length(); j++)
        {
            kart[input[i][j]]++;
        }
    }
    for (int i = 0; i < a.length(); i++)
    {
        if (kart[a[i]] == 6) {
            mapping[2] = a[i];
        } else if(kart[a[i]] == 4){
            mapping[5] = a[i];
        } else if(kart[a[i]] == 9){
            mapping[6] = a[i];
        }
    } 
    for (int i = 0; i < one.length(); i++)
    {
        if (one[i] != mapping[6])
        {
            mapping[3] = one[i];
        }
    }
    for (int i = 0; i < seven.length(); i++)
    {
        if (seven[i] != mapping[3] && seven[i] != mapping[6])
        {
            mapping[1] = seven[i];
        }
        
    }
    for (int i = 0; i < four.length(); i++)
    {
        if (four[i] != mapping[2] && four[i] != mapping[3] && four[i] != mapping[6])
        {
            mapping[4] = four[i];
        }
    }
    bool key = false;
    char curr;
    int ll = 0;
    int currInt = 0;
    for (int i = 0; i < a.length(); i++)
    {
        currInt = 0;
        for (int j = 1; j < mapping.size() + 1; j++)
        {
            if (a[i] != mapping[j])
            {
                currInt++;
            } else {
                break;
            }
        }
        if (currInt == mapping.size())
        {
            mapping[7] = a[i];
            break;
        }
    }
    
    map<char,char> translation;
    for (int i = 0; i < a.length(); i++)
    {
        translation[mapping[i + 1]] = a[i];
    }

    string result = "";
    for (int i = 0; i < output.size(); i++)
    {
        string tmpo = "";
        for (int j = 0; j < output[i].length(); j++)
        {
            tmpo += translation[output[i][j]];
        }
        seg2(tmpo) != "-1" ? result += seg2(tmpo) : result += ""; 
    }
    
    return result;
}

int main(){
    ifstream myFile;
    myFile.open("input.txt");
    vector<string> data;
    if (myFile.is_open())
    {
        while (myFile)
        {
            string tmp;
            myFile >> tmp;
            data.push_back(tmp);
        }
    }
    int counter = 0;
    string tmp = "";
    vector<vector<string>> input(200,vector<string>(0));
    vector<vector<string>> output(200,vector<string>(0));
    for (int i = 0; i < data.size() - 1; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            input[counter].push_back(data[i + j]);
        }
        for (int j = 11; j < 15; j++)
        {
            output[counter].push_back(data[i + j]);
        }
        counter++;
        i += 14;
    }
    int times = 0;
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 0; j < output[i].size(); j++)
        {
            string thi = seg2(output[i][j]);
            if (seg2(output[i][j]) == "1")
            {
                times++;
            } else if (seg2(output[i][j]) == "4")
            {
                times++;
            } else if (seg2(output[i][j]) == "7")
            {
                times++;
            } else if (seg2(output[i][j]) == "8")
            {
                times++;
            }
        }
    }
    cout << times << endl; 
    int resultingSum = 0;
    for (int i = 0; i < 200; i++)
    {
        resultingSum += stoi(seg3(input[i],output[i]));
    }
    cout << resultingSum << endl;
    
    return 0;
}