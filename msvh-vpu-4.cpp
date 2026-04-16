#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
using namespace std;
using u4 = uint8_t;

// 4-bit mask
u4 mask4(u4 x) {
    return x & 0x0F;
}

// Registers A and B
struct VPU {
    u4 A = 0;
    u4 B = 0;

    void setA(u4 value) {
        A = mask4(value);
    }

    void setB(u4 value) {
        B = mask4(value);
    }
};

// Main
int main()
{
    VPU vpu;

    string line;

    while (true)
    {
        cout << "> ";
        getline(cin, line);

        stringstream ss(line);

        string cmd;
        ss >> cmd;

        // Commands
        if (cmd.empty()) continue;
        if (cmd == "EXIT") break;

        if (cmd == "MOV")
        {
            char registry;
            int value;

            if (!(ss >> registry >> value))
            {
                cout << "Invalid MOV syntax. Use: MOV A 5" << endl;
            }
            else if (registry == 'A')
            {
                vpu.setA(value);
            }
            else if (registry == 'B')
            {
                vpu.setB(value);
            }
            else
            {
                cout << "Invalid registry, try A or B." << endl;
            }
        }
        else if (cmd == "GET")
        {
            char registry;
            ss >> registry;
            if (registry == 'A')
            {
                cout << (int)vpu.A << endl;
            }
            else if (registry == 'B')
            {
                cout << (int)vpu.B << endl;
            }
            else
            {
                cout << "Invalid registry, try A or B." << endl;
            }
        }
        else if (cmd == "ADD")
        {
            vpu.setA(mask4(vpu.A + vpu.B));
            cout << (int)vpu.A << endl;
        }
        else if (cmd == "SUB")
        {
            vpu.setA(mask4(vpu.A - vpu.B));
            cout << (int)vpu.A << endl;
        }
        else if (cmd == "MUL")
        {
            vpu.setA(mask4(vpu.A * vpu.B));
            cout << (int)vpu.A << endl;
        }
        else if (cmd == "DIV")
        {
            if (vpu.B == 0)
            {
                cout << "Divison by zero." << endl;
            }
            else
            {
                vpu.setA(mask4(vpu.A / vpu.B));
                cout << (int)vpu.A << endl;
            }
        }
    }

    return 0;
}