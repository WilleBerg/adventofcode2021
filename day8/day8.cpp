#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int seg(string input){
    int valueCounter = 0;
    for (int i = 0; i < input.length(); i++)
    {
        valueCounter += input[i]; 
    }
    int zero = 'a' + 'b' + 'c' + 'e'+ 'f'+ 'g'; 
    int one = 'c' + 'f';
    int two = 'a' + 'c' + 'd' + 'e' + 'g';
    int three = two - 'e' + 'f';
    int four = one + 'd' + 'b';
    int five = 'a' + 'b' + 'd' + 'f' + 'g';
    int six = five + 'e';
    int seven = one + 'a';
    int eight = zero + 'd';
    int nine = eight - 'e';
    vector<int> tmp;
    //usch
    tmp.push_back(zero); tmp.push_back(one); tmp.push_back(two); tmp.push_back(three); tmp.push_back(four); tmp.push_back(five); tmp.push_back(six); tmp.push_back(seven); tmp.push_back(eight); tmp.push_back(nine);
    int val;
    for (int i = 0; i < tmp.size(); i++)
    {
        if (valueCounter == tmp[i])
        {
            val = tmp[i];
            break;
        }
    }
    if (val == zero) return 0;
    else if(val == one) return 1;
    else if(val == two) return 2;
    else if(val == three) return 3;
    else if(val == four) return 4;
    else if(val == five) return 5;
    else if(val == six) return 6;
    else if(val == seven) return 7;
    else if(val == eight) return 8;
    else if(val == nine) return 9;

    return 0;
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
            if (seg(output[i][j]) == 1)
            {
                times++;
            } else if (seg(output[i][j]) == 4)
            {
                times++;
            } else if (seg(output[i][j]) == 7)
            {
                times++;
            } else if (seg(output[i][j]) == 8)
            {
                times++;
            }
        }
    }
    cout << times << endl; 
    cout << seg("gfecba") << endl;
    cout << seg("fc") << endl;
    cout << seg("dcega") << endl;
    cout << seg("acdfg") << endl;
    cout << seg("bcdf") << endl;
    cout << seg("abdfg") << endl;
    cout << seg("abdefg") << endl;
    cout << seg("acf") << endl;
    cout << seg("abcdefg") << endl;
    cout << seg("abcdfg") << endl;
    
    
    
    return 0;
}