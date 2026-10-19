#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "Person.h"

using namespace std;

class Doctor : public Person
{
private:
    string chuyennganh;
    string id;
    int soca;

public:
    void change_in4()
    {
        string s;
        int a;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nhap ho ten moi: ";
        getline(cin, s);

        while (s.empty())
        {
            cout << "Ho ten khong duoc de trong!\n";
            cout << "Nhap lai: ";
            getline(cin, s);
        }

        Person::setname(s);

        cout << "Nhap CCCD moi: ";
        getline(cin, s);
        Person::setcccd(s);

        cout << "Nhap so dien thoai moi: ";
        getline(cin, s);
        Person::setnumber(s);

        cout << "Nhap gioi tinh moi (1 = Nu / 0 = Nam): ";

        while (!(cin >> a) || (a != 0 && a != 1))
        {
            cout << "Vui long nhap 0 hoac 1: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Person::setgender(a == 1);

        cout << "Nhap tuoi moi: ";

        while (!(cin >> a) || a < 1 || a > 120)
        {
            cout << "Tuoi khong hop le, nhap lai: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Person::setage(a);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Chuyen nganh cua bac si thanh: ";
        getline(cin, chuyennganh);

        while (chuyennganh.empty())
        {
            cout << "Chuyen nganh khong duoc de trong!\n";
            cout << "Nhap lai: ";
            getline(cin, chuyennganh);
        }

        cout << "ID cua bac si thanh: ";
        getline(cin, id);

        while (id.empty())
        {
            cout << "ID khong duoc de trong!\n";
            cout << "Nhap lai: ";
            getline(cin, id);
        }
    }

    string getcccd()
    {
        return Person::getcccd();
    }

    void input()
    {
        Person::input();

        cout << "Nhap ID bac si: ";
        cin >> id;

        while (id.empty())
        {
            cout << "ID khong duoc de trong!\n";
            cout << "Nhap lai: ";
            cin >> id;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nhap chuyen nganh: ";
        getline(cin, chuyennganh);

        while (chuyennganh.empty())
        {
            cout << "Chuyen nganh khong duoc de trong!\n";
            cout << "Nhap lai: ";
            getline(cin, chuyennganh);
        }

        cout << "Nhap so ca kham: ";

        while (!(cin >> soca) || soca < 0)
        {
            cout << "So ca khong hop le! Vui long nhap lai: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string getchuyennganh()
    {
        return chuyennganh;
    }

    int getSoca()
    {
        return soca;
    }

    void readFile(ifstream &file)
    {
        Person::readFile(file);

        getline(file, chuyennganh);
        getline(file, id);

        file >> soca;

        file.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }

    void writeFile(ofstream &file)
    {
        Person::writeFile(file);

        file << chuyennganh << endl;
        file << id << endl;
        file << soca << endl;
    }
};

#endif
