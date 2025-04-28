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
          
        }
        f.close();
    }

    return 0;
}