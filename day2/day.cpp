#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int main(){
    map<string,int> karta;
    karta.insert({"forward", 0});
    karta.insert({"depth", 0});
    karta.insert({"aim", 0});

    vector<string> input; 
    ifstream myfile;
    myfile.open("input.txt");
    if (myfile.is_open()){
        while (myfile){
          string tmp;
          myfile >> tmp;
          input.push_back(tmp);
        }
    }

    for (int i = 0; i < input.size(); i++)
    {
        if (i % 2 == 0){
            if (i + 1 >= input.size() - 1) {
               break; 
            }
            
            if (input.at(i) == "forward")
            {
                karta["forward"] += stoi(input.at(i + 1));
                karta["depth"] += karta["aim"] * stoi(input.at(i + 1));
            } else if (input.at(i) == "up"){
                karta["aim"] -= stoi(input.at(i + 1));
            } else {
                karta["aim"] += stoi(input.at(i + 1)); 
            }
        }
    }
    int result = karta["forward"] * karta["depth"];
    cout << result;
    

    return 0;
}