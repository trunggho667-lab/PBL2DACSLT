#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <fstream>
#include <string>

#include "Manager_Medicine.h"
#include "Manager_patient.h"
#include "Person.h"


using namespace std;

class Doctor : public Person
{
private:
    string chuyennganh;
    string id;
    int soca;

public:
    // bool keThuoc(manager_patient &managerPatient,Manager_Thuoc &managerMedicine, const string &filePath)
    // {
    //     string cccd;

    //     cout << "Nhap CCCD benh nhan can ke thuoc: ";
    //     getline(cin, cccd);

    //     Patient *bn = managerPatient.getPatientByCCCD(cccd);

    //     if (bn == nullptr)
    //     {
    //         cout << "Khong tim thay benh nhan!\n";
    //         return false;
    //     }

    //     cout << "\nThong tin benh nhan:\n";
    //     cout << "Ho ten: " << bn->getname() << endl;
    //     cout << "CCCD: " << bn->getcccd() << endl;

    //     cout << "\nTien hanh ke thuoc!!!\n";

    //     return managerMedicine.keThuoc(
    //         bn->getthuoc(), filePath);
    // }

    void change_in4()
    {
        cin.ignore(1000, '\n');
        string s;
        int a;

        cout << "Nhap ho ten moi: ";
        getline(cin, s);
        Person::setname(s);

        cout << "Nhap CCCD moi: ";
        getline(cin, s);
        Person::setcccd(s);

        cout << "Nhap so dien thoai moi: ";
        getline(cin, s);
        Person::setnumber(s);

        cout << "Nhap gioi tinh moi (1 = Nu / 0 = Nam): ";
        cin >> a;
        while (a != 0 && a != 1)
        {
            cout << "Vui long nhap 0 hoac 1: ";
            cin >> a;
        }
        Person::setgender(a == 1);

        cout << "Nhap tuoi moi: ";
        cin >> a;
        while (a < 1 || a > 120)
        {
            cout << "Tuoi khong hop le, nhap lai: ";
            cin >> a;
        }
        Person::setage(a);

        cin.ignore(1000, '\n');

        cout << "Chuyen chuyen nganh cua bac si thanh: ";
        getline(cin, chuyennganh);

        cout << "Chuyen doi ID cua bac si thanh: ";
        getline(cin, id);
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
        cin.ignore();

        cout << "Nhap chuyen nganh: ";
        getline(cin, chuyennganh);

        cout << "Nhap so ca kham: ";

        while (!(cin >> soca) || soca < 0)
        {
            cout << "So ca khong hop le! Vui long nhap lai: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
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
        file.ignore(numeric_limits<streamsize>::max(), '\n');
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