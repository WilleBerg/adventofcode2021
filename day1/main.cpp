#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
    string stringArray[2000]; 
    ifstream myfile;
    myfile.open("accounts.txt");
    if (myfile.is_open()){
        int counter = 0;
        while (myfile){
            myfile >> stringArray[counter];
            counter++;
        }
    }
    int mesCount = 0;
    int prev = stoi(stringArray[0]) + stoi(stringArray[1]) + stoi(stringArray[2]);
    for (int i = 2; i < 2000; i++)
    {
        int curr = stoi(stringArray[i]) + stoi(stringArray[i - 1]) + stoi(stringArray[i - 2]);

        cout << "i : " << i << "\n";
        cout << "curr: " << curr << "\nprev: " << prev << "\n";
        cout << "\n";
        if (curr > prev)
        {
           mesCount++;
        }
        prev = curr;
    }
   cout << "\n" << mesCount; 
   return 0; 
}