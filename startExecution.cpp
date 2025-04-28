#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char memory[100][4];
char buffer[40] = {'*'};
int IC = 0;
int c;
char IR[4];
char R[4];

int LINE_NO = -1;

int min(int a, int b)
{
    return a > b ? b : a;
}

void WRITE();
void READ();
void TERMINATE();

void load()
{
    cout << "load module called\n";
    ifstream f;
    f.open("input.txt");
    int lcnt = 0;
    if (f.is_open())
    {
        string line;
        while (getline(f, line))
        {
            lcnt++;
            if (lcnt <= LINE_NO)
            {
                continue;
            }
            else
            {
                for (int i = 0; i < min(line.length(), 40); i++)
                {
                    /* code */
                    buffer[i] = line[i];
                }
                int idx = 0;

                for (int i = 0; i < 100; i++)
                {
                    if (buffer[idx] == '*')
                        break;
                    for (int j = 0; j < 4; j++)
                    {
                        if (buffer[idx] == '*')
                            break;
                        memory[i][j] = buffer[idx];
                        idx++;
                    }
                }
                break;
            }
        }
        f.close();
    }

    cout << "Program Card stored in memory!\n";

    for (int i = 0; i < 100; i++)
    {
        cout << i << " ";
        for (int j = 0; j < 4; j++)
        {
            cout << memory[i][j];
        }
        cout << "\n";
    }
}

void init()
{

    cout << "Memory content cleared\n";

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            memory[i][j] = '*';
        }
    }
    for (int i = 0; i < 100; i++)
    {
        cout << i << " ";
        for (int j = 0; j < 4; j++)
        {
            cout << memory[i][j];
        }
        cout << "\n";
    }
    cout << "\nIR Cleared\n";

    for (int i = 0; i < 4; i++)
    {
        IR[i] = '*';
        R[i] = '*';
    }
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '*';
    }

    for (int i = 0; i < 4; i++)
    {
        cout << IR[i];
    }
    cout << "\n";
    cout << "R cleared\n";

    for (int i = 0; i < 4; i++)
    {
        cout << R[i];
    }

    load();
    return;
}

void EUP()
{
    for (int i = 0; i < 4; i++)
    {
        IR[i] = memory[IC][i];
    }
    IC = IC + 1;
    string t;
    t.push_back(IR[0]);
    t.push_back(IR[1]);
    if (t == "GD")
    {
        READ();
    }
    else if (t == "PD")
    {
        WRITE();
    }
    else if (t == "H*")
    {
        TERMINATE();
    }
}

void READ()
{
    ifstream f;
    f.open("input.txt"); 
    int cnt = 0;
    if (f.is_open())
    {
        string line;
        int linecnt = 0;
        while (getline(f, line))
        {

            linecnt++;

            if (linecnt <= LINE_NO)
            {
                continue;
            }
            else
            {
                for (int i = 0; i < min(40, line.length()); i++)
                {
                    buffer[i] = line[i];
                    cnt++;
                }

                break;
            }
        }

        f.close();
    }
    int loc = (IR[2] - '0') * 10 + (IR[3] - '0');
    //cout << loc << endl;
    int idx = 0;
    for (int i = loc; i <= loc + 9; i++)
    {
        if (cnt <= 0)
            break;
        for (int j = 0; j < 4 && cnt > 0; j++)
        {
            memory[i][j] = buffer[idx];
            cnt--;
            idx++;
        }
    }

    for (int i = 0; i < 100; i++)
    {
        cout << i << " ";
        for (int j = 0; j < 4; j++)
        {
            cout << memory[i][j] << " ";
        }
        cout << "\n";
    }
    EUP();
}

void WRITE()
{
    cout<<"\nWrite interrupt called\n";
    ofstream f;
    f.open("output.txt",ios::app);
    bool flag = true;
    int loc = (IR[2] - '0') * 10 + (IR[3] - '0');
    for (int i = loc; (i <= loc + 9) && flag; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            char c = memory[i][j];
            if( c != '*'){
                f << c;
            }
            else{
                flag = false;
                break;
            }
        }
        
    }
   
    f.close();
    EUP();
    
}

void TERMINATE()
{
    ofstream f;
    f.open("output.txt",ios::app);
    cout<<"\nProgram Terminated!\n";
    f<<"\n\n"<<endl;
    f.close();
}

void START_EXECUTION()
{
    cout<<"\nstart execution module called!\n";
    IC = 0;
    EUP();
}

int main()
{
    ifstream f;
    f.open("./input.txt");
    LINE_NO = 0;
    if (f.is_open())
    {

        char c;
        string s;
        while (getline(f, s))
        {
            LINE_NO++;
            for (int i = 0; i < min(40, s.length()); i++)
            {
                buffer[i] = s[i];
            }
            if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
            {
                init();
                s = "";
            }
            else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
            {
                START_EXECUTION();
            }
        }
        f.close();
    }

    return 0;
}