#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

class Date
{
private:
    int ngay;
    int thang;
    int nam;

public:
    bool check(int n, int t, int nm)
    {
        if (nm <= 0)
            return false;

        int soNgayTrongThang[] =
        {
            0, 31, 28, 31, 30, 31,
            30, 31, 31, 30, 31, 30, 31
        };

        if ((nm % 4 == 0 && nm % 100 != 0) || nm % 400 == 0)
            soNgayTrongThang[2] = 29;

        if (t < 1 || t > 12)
            return false;

        if (n < 1 || n > soNgayTrongThang[t])
            return false;

        return true;
    }

    Date()
    {
        ngay = 1;
        thang = 1;
        nam = 2000;
    }

    Date(int n, int t, int nm)
    {
        if (!setDate(n, t, nm))
        {
            ngay = 1;
            thang = 1;
            nam = 2000;
        }
    }

    int getngay() const
    {
        return ngay;
    }

    int getthang() const
    {
        return thang;
    }

    int getnam() const
    {
        return nam;
    }

    bool setDate(int n, int t, int nm)
    {
        if (!check(n, t, nm))
            return false;

        ngay = n;
        thang = t;
        nam = nm;

        return true;
    }

    void nhap()
    {
        int n, t, nm;

        while (true)
        {
            cout << "Nhap ngay: ";

            if (!(cin >> n))
            {
                cout << "Ngay phai la so!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "Nhap thang: ";

            if (!(cin >> t))
            {
                cout << "Thang phai la so!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "Nhap nam: ";

            if (!(cin >> nm))
            {
                cout << "Nam phai la so!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (check(n, t, nm))
            {
                ngay = n;
                thang = t;
                nam = nm;
                break;
            }

            cout << "Ngay khong hop le! Vui long nhap lai.\n";
        }
    }

    void tangngay()
    {
        ngay++;

        if (!check(ngay, thang, nam))
        {
            ngay = 1;
            thang++;

            if (thang > 12)
            {
                thang = 1;
                nam++;
            }
        }
    }

    void xuat() const
    {
        cout << setfill('0')
             << setw(2) << ngay << "/"
             << setw(2) << thang << "/"
             << setw(4) << nam;

        cout << setfill(' ');
    }

    void readFile(ifstream &file)
    {
        string s;

        if (!getline(file, s))
            return;

        int n, t, nm;

        if (sscanf(s.c_str(), "%d/%d/%d", &n, &t, &nm) == 3)
        {
            if (!setDate(n, t, nm))
            {
                ngay = 1;
                thang = 1;
                nam = 2000;
            }
        }
        else
        {
            ngay = 1;
            thang = 1;
            nam = 2000;
        }
    }

    void writeFile(ofstream &file)
    {
        file << setfill('0')
             << setw(2) << ngay << "/"
             << setw(2) << thang << "/"
             << setw(4) << nam
             << setfill(' ') << endl;
    }
};

#endif
