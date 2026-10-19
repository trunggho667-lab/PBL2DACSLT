#ifndef MANAGER_THUOC_H
#define MANAGER_THUOC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#include "Medicine.h"

using namespace std;

class Manager_Thuoc
{
private:
    vector<Thuoc> thuocs;
    int indexOf(const string &ma)
    {
        for (size_t i = 0; i < thuocs.size(); i++)
            if (thuocs[i].getmathuoc() == ma)
                return (int)i;
        return -1;
    }

public:
    Thuoc *find(const string &ma)
    {
        int i = indexOf(ma);
        return i < 0 ? nullptr : &thuocs[i];
    }

    bool checkMaThuoc(string ma)
    {
        for (size_t i = 0; i < thuocs.size(); i++)
        {
            if (thuocs[i].getmathuoc() == ma)
                return true;
        }
        return false;
    }

    void display()
    {
        cout << "\n================ DANH SACH THUOC ================\n";

        cout << left
             << setw(12) << "Ma thuoc"
             << setw(25) << "Ten thuoc"
             << setw(15) << "Don vi"
             << setw(15) << "Don gia"
             << setw(12) << "So luong"
             << endl;

        cout << "==================================================\n";

        for (size_t i = 0; i < thuocs.size(); i++)
        {
            cout << left
                 << setw(12) << thuocs[i].getmathuoc()
                 << setw(25) << thuocs[i].gettenthuoc()
                 << setw(15) << thuocs[i].getdonvitinh()
                 << setw(15) << thuocs[i].getdongia()
                 << setw(12) << thuocs[i].getsoluong()
                 << endl;
        }
    }

    void addThuoc(const string &filePath)
    {
        Thuoc thuoc;
        thuoc.input();

        if (checkMaThuoc(thuoc.getmathuoc()))
        {
            cout << "Ma thuoc da ton tai!\n";
            return;
        }

        thuocs.push_back(thuoc);
        saveToFile(filePath);

        cout << "Them thuoc thanh cong!\n";
    }

    void searchThuoc()
    {
        string ten;
        cout << "Nhap ten thuoc can tim: ";
        getline(cin, ten);

        bool found = false;

        for (size_t i = 0; i < thuocs.size(); i++)
        {
            if (thuocs[i].gettenthuoc().find(ten) != string::npos)
            {
                thuocs[i].display();
                cout << "-------------------------\n";
                found = true;
            }
        }

        if (!found)
            cout << "Khong tim thay thuoc!\n";
    }

    void deleteThuoc(const string &ma)
    {
        for (size_t i = 0; i < thuocs.size(); i++)
        {
            if (thuocs[i].getmathuoc() == ma)
            {
                thuocs.erase(thuocs.begin() + i);
                cout << "Da xoa thuoc thanh cong!\n";
                return;
            }
        }

        cout << "Khong tim thay ma thuoc!\n";
    }

    // bool keThuoc(vector<Thuoc> &thuocBN, const string &filePath)
    // {
    //     string ma;
    //     int sl;

    //     cout << "Nhap ma thuoc can ke: ";
    //     getline(cin, ma);

    //     for (size_t i = 0; i < thuocs.size(); i++)
    //     {
    //         if (thuocs[i].getmathuoc() == ma)
    //         {
    //             cout << "Ten thuoc: " << setw(25) << thuocs[i].gettenthuoc();
    //             cout << "so luong ton kho: " << setw(10)
    //                  << thuocs[i].getsoluong() << endl;

    //             cout << "Nhap so luong can ke: ";
    //             cin >> sl;
    //             cin.ignore(1000, '\n');

    //             if (sl <= 0)
    //             {
    //                 cout << "So luong phai lon hon 0!\n";
    //                 return false;
    //             }

    //             if (sl > thuocs[i].getsoluong())
    //             {
    //                 cout << "Khong du thuoc trong kho!\n";
    //                 return false;
    //             }

    //             Thuoc thuocKe = thuocs[i];
    //             thuocKe.setsoluong(sl);
    //             thuocBN.push_back(thuocKe);

    //             thuocs[i].setsoluong(
    //                 thuocs[i].getsoluong() - sl);

    //             saveToFile(filePath);

    //             cout << "Ke thuoc thanh cong!\n";
    //             cout << "So luong con lai: "
    //                  << thuocs[i].getsoluong() << endl;

    //             return true;
    //         }
    //     }

    //     cout << "Khong tim thay ma thuoc!\n";
    //     return false;
    // }

    void saveToFile(const string &filePath)
    {
        ofstream file(filePath);

        if (!file.is_open())
        {
            cout << "Loi khi mo file de ghi!\n";
            return;
        }

        for (size_t i = 0; i < thuocs.size(); i++)
        {
            thuocs[i].writeFile(file);

            if (i + 1 < thuocs.size())
                file << '\n';
        }

        if (!file)
        {
            cout << "Loi khi ghi du lieu vao file!\n";
            return;
        }

        file.close();
        cout << "Da luu danh sach thuoc!\n";
    }

    void readFile(ifstream &file)
    {

        if (!file.is_open())
        {
            cout << "Khong mo duoc file thuoc!\n";
            return;
        }

        thuocs.clear();

        while (file.peek() != EOF)
        {
            if (file.peek() == '\n' || file.peek() == '\r')
            {
                file.ignore(1000, '\n');
                continue;
            }

            Thuoc thuoc;
            thuoc.readFile(file);

            if (!file)
                break;

            thuocs.push_back(thuoc);

            if (file.peek() == '\r')
                file.get();

            if (file.peek() == '\n')
                file.get();
        }

        file.close();
    }
};

#endif
