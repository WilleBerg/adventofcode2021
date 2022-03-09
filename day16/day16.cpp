#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<char, string> binary;

void readInput(vector<string> *d, string fileName){
    fstream file;
    file.open(fileName);
    if (file.is_open())
    {
        while (file)
        {
            string tmp;
            file >> tmp;
            if (tmp != "")
            {
                d->push_back(tmp);
            }
        }
    }
}

void createMap(){
    binary['0'] = "0000";
    binary['1'] = "0001";
    binary['2'] = "0010";
    binary['3'] = "0011";
    binary['4'] = "0100";
    binary['5'] = "0101";
    binary['6'] = "0110";
    binary['7'] = "0111";
    binary['8'] = "1000";
    binary['9'] = "1001";
    binary['A'] = "1010";
    binary['B'] = "1011";
    binary['C'] = "1100";
    binary['D'] = "1101";
    binary['E'] = "1110";
    binary['F'] = "1111";
}

string convertToBinary(vector<string> input){
    string result = "";
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].length(); j++)
        {
            result += binary[input[i][j]];
        }
    }
    return result; 
}

int getVal(string bin){
    int sum = 0;
    for (int i = 0; i < bin.length(); i++)
    {
        if (bin[i] == '1')
        {
            sum += pow(2, bin.length() - 1 - i);
        }
        // 11101
    }
    
    return sum;
}


string getSubstring(string s, int start, int end){
    string result = "";
    for (int i = start; i < end + 1; i++)
    {    
        result += s[i];
    }
    return result;
}

class Packet{
    public:
        int version;
        int typeID;
        int val;
        int currBit;

    
};

Packet getV4(string s){
    Packet pack;

    string firstThree = getSubstring(s, 0 , 2);
    string secondThree = getSubstring(s, 3, 5);

    pack.version = getVal(firstThree);
    pack.typeID = getVal(secondThree);

    int currBit = 0;
    string value = "";
    for (int i = 6; i < s.length(); i++)
    {
        if (s[i] == '1')
        {
            for (int j = 0; j < 4; j++)
            {
                i++;
                value += s[i];
            }
        } else {
            for (int j = 0; j < 4; j++)
            {
                i++;
                value += s[i];
            }
            currBit = i;
            break;
        }
        
        currBit = i;
    }
    pack.val = getVal(value);
    if ((currBit + 1) % 4 == 0)
    {
        pack.currBit = currBit;
    } else {
        while (true)
        {
            currBit++;
            if ((currBit + 1) % 4 == 0)
            {
                pack.currBit = currBit;
                break;
            }
        }
    }
    
    return pack;
}

int main(){
    vector<string> input;
    readInput(&input, "input2.txt");
    createMap();
    for (int i = 0; i < input.size(); i++)
    {
        cout << input[i] << endl;
    }
    string test = convertToBinary(input);
    cout << getV4(test).val << endl;


}