// MT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <map>

struct  command1
{
    std::string cmd;
    int number = -1;
};

struct  command2
{
    int number = -1;
    char ch;
    std::string cmd;
};

std::ifstream& operator>> (std::ifstream& in, command1& A)
{
    in >> A.cmd;
    in >> A.number;
    return in;
}

std::ifstream& operator>> (std::ifstream& in, command2& B)
{
    in >> B.number;
    in >> B.ch;
    in >> B.cmd;
    return in;
}

std::ostream& operator<< (std::ostream& out, command2& B)
{
    out << B.number << " ";
    out << B.ch << " ";
    out << B.cmd;
    return out;
}

std::ostream& operator<< (std::ostream& out, command1& A)
{
    out << A.cmd << " ";
    out << A.number;
    return out;
}

bool operator<(const command1& l, const command1& r) {
    return (l.cmd < r.cmd || (l.cmd == r.cmd && l.number < r.number));
}

int main()
{
    try 
    {
        const char* mtname = "MT.txt";
        const char* cmdname = "input.txt";
        const char* outname = "output.txt";
        std::map <command1, command2> mp;
        std::map <command1, bool> mpb;
        int pos = 1000000;
        command1 C;
        std::ifstream mtFile(mtname);
        std::ofstream outFile(outname);
        if (!mtFile)
        {
            throw "Can't open the file";
        }
        std::ifstream cmdFile(cmdname);
        if (!cmdFile)
        {
            throw "Can't open the file";
        }
        std::string ss,s;
        mtFile >> ss;
        for (int i = 0; i < 1000000; ++i)
        {
            s += '0';
        }
        s += ss;
        for (int i = 2000000 - s.length(); i < 2000000; ++i)
        {
            s += '0';
        }
        ss = "";
        while (cmdFile.peek() != EOF)
        {
            command1 A;
            ss = "";
            command2 B;
            cmdFile >> A;
            cmdFile >> ss;
            cmdFile >> B;
            if (C.number == -1) C = A;
            //std::cout << A << ":" << B << std::endl;
            mpb[A] = true;
            mp[A] = B;
        }
        //std::cout << C << std::endl;
        C.number = s[pos] - 48;
        int counter=0;
        while (mpb[C])
        {
            command2 B = mp[C];
            s[pos] = B.number + 48;
            if (B.ch == 'L')
            {
                --pos;
                if (pos == 0) throw "out of memory";
            }
            if (B.ch == 'R')
            {
                ++pos;
                if (pos == 1999999) throw "out of memory";
            }
            C.cmd = B.cmd;
            C.number = s[pos] - 48;
            ++counter;
            if (counter == 10000001) throw "not applicable";
        }
        int l = -1, r = -1;
        int length = s.length();
        l = s.find_first_of('1');
        r = s.find_last_of('1');
        //std::cout << l << "  " << r << std::endl;
        for (int i = std::min(l,pos); i <= std::max(pos,r); ++i)
            outFile << s[i];
        outFile << std::endl;
        if (l < pos)
        {
            for (int i = 0; i < pos-l; ++i)
                outFile << " ";
        }
        outFile << "^" << std::endl;
        mtFile.close();
        cmdFile.close();
        outFile.close();
    }
    catch (const char* str)
    {
        std::cout << "Error! " << str << std::endl;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
