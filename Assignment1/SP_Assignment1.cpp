#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

class tables
{
    string str, word, label, literal[10], symbol[10], ic[100]; 
    int litadd[10], symadd[10], pool[10], lit_pool=0, add, flag=0, flag1=0, lit_cnt=0, litadd_cnt=0, pool_cnt=0, sym_cnt=0;

    public:

    void generator()
    {
        fstream fp;
        pool[0]=0;
        fp.open("prog.txt", ios::in);

        while(!fp.eof() && getline(fp, str, '\n'))
        {
            istringstream s(str);

            if(isalpha(str[0]))
            {
                getline(s, label, ' ');
                symbol[sym_cnt]=label;
                symadd[sym_cnt]=add;
                sym_cnt++;
            }
    
            cout<<str<<'\t'<<'\t'<<add<<endl;

            while (getline(s, word, ' '))
            {
                if(word=="START" || word=="ORIGIN")
                flag1=1;

                else if(word[0]=='=')
                {
                    int lit_repeat=0;

                    for(int i=0; i<lit_cnt;i++)
                    if(word==literal[i])
                    {
                        lit_repeat++;
                        break;
                    }

                    if(lit_repeat!=1)
                    {
                        lit_pool++;
                        literal[lit_cnt]=word;
                        lit_cnt++;
                        lit_repeat=0;
                    }
                }

                else if(word=="LTORG" || word=="END")
                {
                    for(int i=0;i<lit_pool;i++)
                    {
                        litadd[litadd_cnt]=add;
                        add++;
                        litadd_cnt++;
                    }
                    pool_cnt++;
                    pool[pool_cnt]=pool[pool_cnt-1]+lit_pool;
                    lit_pool=0;
                    flag=1;
                }

                else if(flag1==1)
                {
                    if(isalpha(word[0]))
                    {
                        for(int i=0; i<lit_cnt; i++)
                        cout<<"l";
                    }

                    else
                    add=stoi(word)-1;
                    
                    flag1=0;
                }
            } 

            if(flag!=1)
            add++;
        
            flag=0;
        }

        fp.close();
    }

    void intermediateCode()
    {
        fstream fp;
        pool[0]=0;
        fp.open("prog.txt", ios::in);

        while(!fp.eof() && getline(fp, str, '\n'))
        {
            istringstream s(str);

            if(isalpha(str[0]))
            {
                getline(s, label, ' ');
                symbol[sym_cnt]=label;
                symadd[sym_cnt]=add;
                sym_cnt++;
            }
    
            cout<<str<<'\t'<<'\t'<<add<<endl;

            while (getline(s, word, ' '))
            {
                
            }
        }

        fp.close();
    }

    void littab()
    {
        cout<<endl<<endl<<"LITERAL TABLE :"<<endl;
        cout<<"Sr.no"<<'\t'<<"Literal"<<'\t'<<"Address"<<endl;

        for(int i=0;i<lit_cnt;i++)
        cout<<i<<'\t'<<literal[i]<<'\t'<<litadd[i]<<endl;
    }

    void symtab()
    {
        cout<<endl<<endl<<"SYMBOL TABLE :"<<endl;
        cout<<"Sr.no"<<'\t'<<"Symbol"<<'\t'<<"Address"<<endl;

        for(int i=0;i<sym_cnt;i++)
        cout<<i<<'\t'<<symbol[i]<<'\t'<<symadd[i]<<endl;
    }

    void pooltab()
    {
        cout<<endl<<endl<<"POOL TABLE :"<<endl;
        cout<<"Sr.no"<<'\t'<<"Literal number"<<endl;

        for(int i=0;i<pool_cnt;i++)
        cout<<i<<'\t'<<pool[i]<<endl;
    }
};

int main()
{
    tables obj; 

    obj.generator();
    obj.littab();
    obj.symtab();
    obj.pooltab();
    obj.intermediateCode();
    return 0;
}