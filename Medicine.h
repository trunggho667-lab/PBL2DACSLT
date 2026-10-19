#ifndef THUOC_H
#define THUOC_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Thuoc
{
private:
    string mathuoc;
    string tenthuoc;
    string donvitinh;
    string congdung;
    double dongia;
    int soluong;

public:
    string getmathuoc()
    {
        return mathuoc;
    }

    string gettenthuoc()
    {
        return tenthuoc;
    }

    string getdonvitinh()
    {
        return donvitinh;
    }

    string getcongdung()
    {
        return congdung;
    }

    double getdongia()
    {
        return dongia;
    }

    int getsoluong()
    {
        return soluong;
    }

    void setmathuoc(string &s)
    {
        while (s.empty())
        {
            cout << "Ma thuoc khong duoc de trong, nhap lai: ";
            getline(cin, s);
        }

        mathuoc = s;
    }

    void settenthuoc(string &s)
    {
        while (s.empty())
        {
            cout << "Ten thuoc khong duoc de trong, nhap lai: ";
            getline(cin, s);
        }

        tenthuoc = s;
    }

    void setdonvitinh(string &s)
    {
        while (s.empty())
        {
            cout << "Don vi tinh khong duoc de trong, nhap lai: ";
            getline(cin, s);
        }

        donvitinh = s;
    }

    void setcongdung(string &s)
    {
        while (s.empty())
        {
            cout << "Cong dung khong duoc de trong, nhap lai: ";
            getline(cin, s);
        }

        congdung = s;
    }

    void setdongia(double gia)
    {
        if (gia < 0)
            gia = 0;

        dongia = gia;
    }

    void setsoluong(int sl)
    {
        if (sl < 0)
            sl = 0;

        soluong = sl;
    }

    void input()
    {
        string s;
        double gia;
        int sl;

        cout << "Nhap ma thuoc: ";
        getline(cin, s);
        setmathuoc(s);

        cout << "Nhap ten thuoc: ";
        getline(cin, s);
        settenthuoc(s);

        cout << "Nhap don vi tinh: ";
        getline(cin, s);
        setdonvitinh(s);

        cout << "Nhap cong dung: ";
        getline(cin, s);
        setcongdung(s);

        while (true)
        {
            cout << "Nhap don gia: ";

            if (cin >> gia && gia >= 0)
                break;

            cout << "Don gia khong hop le! Vui long nhap lai.\n";

            cin.clear();
            cin.ignore(1000, '\n');
        }

        while (true)
        {
            cout << "Nhap so luong ton kho: ";

            if (cin >> sl && sl >= 0)
                break;

            cout << "So luong khong hop le! Vui long nhap lai.\n";

            cin.clear();
            cin.ignore(1000, '\n');
        }

        cin.ignore(1000, '\n');

        setdongia(gia);
        setsoluong(sl);
    }

    void display()
    {
        cout << "Ma thuoc: " << mathuoc << endl;
        cout << "Ten thuoc: " << tenthuoc << endl;
        cout << "Don vi tinh: " << donvitinh << endl;
        cout << "Cong dung: " << congdung << endl;
        cout << "Don gia: " << dongia << endl;
        cout << "So luong ton kho: " << soluong << endl;
    }

    void writeFile(ofstream &file)
    {
        file << mathuoc << '\n';
        file << tenthuoc << '\n';
        file << donvitinh << '\n';
        file << congdung << '\n';
        file << dongia << '\n';
        file << soluong;
    }

    void readFile(ifstream &file)
    {
        string gia;
        string sl;

        getline(file, mathuoc);
        getline(file, tenthuoc);
        getline(file, donvitinh);
        getline(file, congdung);
        getline(file, gia);
        getline(file, sl);

        dongia = stod(gia);
        soluong = stoi(sl);
    }
};

#endif
