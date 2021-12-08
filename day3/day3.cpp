#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char returnSmallest(int a){
    if (a > 500){
        return '1';
    } else return '0';
}
char returnLargest(int a){
    if (a < 500)
    {
        return '1';
    } else return '0';
    
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
    
    int temp[] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < 12; j++)
        {

            if (input.at(i)[j] == '1')
            {
                temp[j]++;
            }
              
        }   
    }
    for (int a : temp)
    {
        cout << a << endl;
    }
    vector<char> epsilon;
    vector<char> gamma;
    cout << "here" << endl;
    for (int i = 0; i < 12; i++)
    {
        epsilon.push_back(returnLargest(temp[i]));
        
    }
    for (int i = 0; i < 12; i++)
    {
       gamma.push_back(returnSmallest(temp[i])); 
    }
    for (int i = 0; i < epsilon.size(); i++)
    {
        cout << epsilon.at(i);
    }
    cout << endl;
    for(int i = 0; i < gamma.size(); i++){
        cout << gamma.at(i);
    }   

    return 0;
}