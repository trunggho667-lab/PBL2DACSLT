#ifndef BHYT_H
#define BHYT_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "Date.h"

using namespace std;

class BHYT
{
private:
    string so;
    Date A;

public:
    string getso() const
    {
        return so;
    }

    Date getngaymua() const
    {
        return A;
    }

    void setso(const string &s)
    {
        so = s;
    }

    bool setngaymua(int n, int t, int nm)
    {
        return A.setDate(n, t, nm);
    }

    void input()
    {
        do
        {
            cout << "Nhap so BHYT: ";
            cin >> so;

            if (so.empty())
                cout << "So BHYT khong duoc de trong!\n";

        } while (so.empty());

        cout << "Nhap ngay mua BHYT:\n";
        A.nhap();
    }

    void display() const
    {
        cout << "So BHYT: " << so << endl;

        cout << "Ngay mua BHYT: ";
        A.xuat();
        cout << endl;
    }

    void readFile(ifstream &file)
    {
        getline(file, so);

        A.readFile(file);
    }

    void writeFile(ofstream &file)
    {
        file << so << endl;

        A.writeFile(file);
    }
};

#endif
