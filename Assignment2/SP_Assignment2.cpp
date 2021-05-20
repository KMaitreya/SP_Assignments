#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

class Literal
{
    public:
    string index, address;

    Literal(string indexF, string addressF)
    {
        index=indexF;
        address=addressF;
    }
};

class Symbol
{
    public:
    string index, address;

    Symbol(string indexF, string addressF)
    {
        index=indexF;
        address=addressF;
    }
};

string getWord(string word, vector<Literal> littab, vector<Symbol> symbtab) {

    string text="";
    if(!(word[0]=='(')) 
    return "";

    if(word[1]=='A' || word[1]=='D')
    return "";

    if(word[1]=='I' && word[2]=='S')
    {
        text.push_back(word[4]);
        text.push_back(word[5]);
    }

    if(word[1]=='R' && word[2]=='E' && word[3]=='G')
    {
        text.push_back(word[5]);
        text.push_back(word[6]);
    }

    if(word[1]=='L')
    {
        for(int i=0; i<littab.size(); i++)
        if(string(1,word[3])==littab[i].index)
        {
            text.append(littab[i].address);
            break;
        }
    }

    if(word[1]=='S')
    {
        for(int i=0; i<symbtab.size(); i++)
        if(string(1,word[3])==symbtab[i].index)
        {
            text.append(symbtab[i].address);
            break;
        }
    }

    return text;
}

int main()
{
    fstream ic, literal, symbol, mCode;
    vector<Literal> literalTable;
    vector<Symbol> symbolTable;
    vector<string> output;

    ic.open("intermediateCode.txt", ios::in);
    literal.open("literalTable.txt", ios::in);
    symbol.open("symbolTable.txt", ios::in);

    string line;
    int add=200;

    if(!ic || !literal || !symbol)
    {
        cout<<"\nERROR: file couldn't be opened."<<endl;
        exit(0);
    }

    while (!literal.eof() && getline(literal, line, '\n'))
    {
        vector<string> words;
        istringstream s(line);
        string word;
        while(getline(s, word, ' ')) 
        words.push_back(word);
        literalTable.push_back(Literal(words[0], words.at(1)));
    }

    while (!symbol.eof() && getline(symbol, line, '\n'))
    {
        vector<string> words;
        istringstream s(line);
        string word;
        while(getline(s, word, ' '))
        words.push_back(word);
        symbolTable.push_back(Symbol(words[0], words.at(1)));
    }

    while(!ic.eof() && getline(ic, line, '\n'))
    {
        vector<string> words;
        istringstream s(line);
        string word, temp;

        while(getline(s, word, ' '))
        words.push_back(word);
        
        stringstream ss;
        ss<<add;
        ss>>temp;
        output.push_back(temp);
        output.push_back(" ");

        if(words[0].at(1)=='I')
        output.push_back(" + ");
        
        for (int i = 0; i < words.size(); i++)
        {
            string tokenText=getWord(words.at(i), literalTable, symbolTable);
            output.push_back(tokenText);
            output.push_back(" ");
        }
        output.push_back("\n");
        add++;
    }
    mCode.open("machineCode.txt", ios::out);
    for (int i=0; i<output.size(); i++)
    mCode.write(output.at(i).c_str(), output.at(i).size());

    cout<<"\nThe machine code has been saved in machineCode.txt";

    return 0;  
}