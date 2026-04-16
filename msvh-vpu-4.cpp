#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

using u4 = uint8_t;

// 4-bit mask
u4 mask4(u4 x) {
    return x & 0x0F;
}

// Registers and flags
struct VPU {
    // Registers
    u4 A = 0;
    u4 B = 0;
    // Flags
    u4 Z = 0;
    u4 C = 0;

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

    vector<string> program;
    string line;

    cout << "Enter program (type RUN to execute):\n";

    // Program input phase
    while (true)
    {
        getline(cin, line);
        if (line == "RUN") break;
        program.push_back(line);
    }

    // Execution phase
    int PC = 0;

    while (PC < program.size())
    {
        stringstream ss(program[PC]);

        string cmd;
        ss >> cmd;

        if (cmd == "EXIT") break;

        if (cmd == "MOV")
        {
            char registry;
            int value;

            if (ss >> registry >> value)
            {
                if (registry == 'A') vpu.setA(value);
                else if (registry == 'B') vpu.setB(value);
            }
        }
        else if (cmd == "GET")
        {
            char registry;
            ss >> registry;

            if (registry == 'A') cout << (int)vpu.A << endl;
            else if (registry == 'B') cout << (int)vpu.B << endl;
        }
        else if (cmd == "ADD")
        {
            int result = vpu.A + vpu.B;

            vpu.C = (result > 0x0F);
            vpu.setA(result);
            vpu.Z = (vpu.A == 0);
        }
        else if (cmd == "SUB")
        {
            int result = vpu.A - vpu.B;

            vpu.C = (result < 0);
            vpu.setA(result);
            vpu.Z = (vpu.A == 0);
        }
        else if (cmd == "MUL")
        {
            int result = vpu.A * vpu.B;

            vpu.C = (result > 0x0F);
            vpu.setA(result);
            vpu.Z = (vpu.A == 0);
        }
        else if (cmd == "DIV")
        {
            if (vpu.B == 0)
            {
                cout << "Division by zero" << endl;
            }
            else
            {
                int result = vpu.A / vpu.B;

                vpu.C = 0;
                vpu.setA(result);
                vpu.Z = (vpu.A == 0);
            }
        }
        else if (cmd == "CMP")
        {
            vpu.Z = (vpu.A == vpu.B);
            vpu.C = (vpu.A < vpu.B);

            cout << "Z=" << (int)vpu.Z << " C=" << (int)vpu.C << endl;
        }
        else if (cmd == "JMP")
        {
            int target;
            ss >> target;

            if (target >= 0 && target < program.size())
            {
                PC = target;
                continue;
            }
            else
            {
                cout << "Invalid jump address" << endl;
            }
        }
        else if (cmd == "JZ")
        {
            int target;
            ss >> target;

            if (vpu.Z == 1)
            {
                PC = target;
                continue;
            }
        }
        else if (cmd == "JNZ")
        {
            int target;
            ss >> target;

            if (vpu.Z == 0)
            {
                PC = target;
                continue;
            }
        }

        PC++;
    }

    return 0;
}
