#ifndef MANAGER_THUOC_H
#define MANAGER_THUOC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include "Medicine.h"

using namespace std;

class Manager_Thuoc
{
private:
    vector<Thuoc> thuocs;

    int indexOf(const string &ma)
    {
        for (size_t i = 0; i < thuocs.size(); i++)
        {
            if (thuocs[i].getmathuoc() == ma)
                return (int)i;
        }

        return -1;
    }

public:
    Thuoc *find(const string &ma)
    {
        int i = indexOf(ma);

        if (i < 0)
            return nullptr;

        return &thuocs[i];
    }

    bool checkMaThuoc(const string &ma)
    {
        return indexOf(ma) != -1;
    }

    void display()
    {
        if (thuocs.empty())
        {
            cout << "Danh sach thuoc rong!\n";
            return;
        }

        cout << "\n========== DANH SACH THUOC ==========\n";

        for (size_t i = 0; i < thuocs.size(); i++)
        {
            cout << "\n---------- THUOC " << i + 1 << " ----------\n";
            thuocs[i].display();
        }
    }

    void addThuoc(const string &filePath)
    {
        cout << "\n========== THEM THUOC ==========\n";

        Thuoc thuoc;
        thuoc.input();

        if (checkMaThuoc(thuoc.getmathuoc()))
        {
            cout << "Loi: Ma thuoc "
                 << thuoc.getmathuoc()
                 << " da ton tai!\n";
            return;
        }

        thuocs.push_back(thuoc);

        saveToFile(filePath);

        cout << "Them thuoc thanh cong!\n";
    }

    void searchThuoc()
    {
        string key;

        cout << "Nhap ma hoac ten thuoc can tim: ";
        getline(cin, key);

        bool found = false;

        for (size_t i = 0; i < thuocs.size(); i++)
        {
            string ma = thuocs[i].getmathuoc();
            string ten = thuocs[i].gettenthuoc();

            if (ma.find(key) != string::npos ||
                ten.find(key) != string::npos)
            {
                cout << "\n---------- THUOC " << i + 1 << " ----------\n";
                thuocs[i].display();

                found = true;
            }
        }

        if (!found)
            cout << "Khong tim thay thuoc phu hop!\n";
    }

    void deleteThuoc(const string &ma, const string &filePath)
    {
        int index = indexOf(ma);

        if (index == -1)
        {
            cout << "Khong tim thay ma thuoc: "
                 << ma << endl;
            return;
        }

        cout << "\nThuoc se bi xoa:\n";
        thuocs[index].display();

        cout << "\nBan co chac chan muon xoa? (y/n): ";

        string xacNhan;
        getline(cin, xacNhan);

        if (xacNhan != "y" && xacNhan != "Y")
        {
            cout << "Da huy xoa thuoc.\n";
            return;
        }

        thuocs.erase(thuocs.begin() + index);

        saveToFile(filePath);

        cout << "Da xoa thuoc thanh cong!\n";
    }

    void updateThuoc(const string &filePath)
    {
        string ma;

        cout << "Nhap ma thuoc can cap nhat: ";
        getline(cin, ma);

        int index = indexOf(ma);

        if (index == -1)
        {
            cout << "Khong tim thay ma thuoc: "
                 << ma << endl;
            return;
        }

        Thuoc &t = thuocs[index];

        cout << "\n========== THONG TIN THUOC HIEN TAI ==========\n";
        t.display();

        cout << "\n1. Cap nhat don gia\n";
        cout << "2. Cap nhat so luong ton\n";
        cout << "3. Cap nhat ca hai\n";
        cout << "0. Huy\n";

        int chon;

        cout << "Lua chon: ";
        cin >> chon;
        cin.ignore(1000, '\n');

        double gia;
        int soLuong;

        switch (chon)
        {
        case 1:
            cout << "Nhap don gia moi: ";
            cin >> gia;

            if (cin.fail() || gia < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Don gia khong hop le!\n";
                return;
            }

            cin.ignore(1000, '\n');

            t.setdongia(gia);

            saveToFile(filePath);

            cout << "Cap nhat don gia thanh cong!\n";
            break;

        case 2:
            cout << "Nhap so luong ton moi: ";
            cin >> soLuong;

            if (cin.fail() || soLuong < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "So luong khong hop le!\n";
                return;
            }

            cin.ignore(1000, '\n');

            t.setsoluong(soLuong);

            saveToFile(filePath);

            cout << "Cap nhat so luong thanh cong!\n";
            break;

        case 3:
            cout << "Nhap don gia moi: ";
            cin >> gia;

            if (cin.fail() || gia < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Don gia khong hop le!\n";
                return;
            }

            cout << "Nhap so luong ton moi: ";
            cin >> soLuong;

            if (cin.fail() || soLuong < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "So luong khong hop le!\n";
                return;
            }

            cin.ignore(1000, '\n');

            t.setdongia(gia);
            t.setsoluong(soLuong);

            saveToFile(filePath);

            cout << "Cap nhat thuoc thanh cong!\n";
            break;

        case 0:
            cout << "Da huy cap nhat.\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }
    }

    void displayLowStock(int mucCanhBao = 10)
    {
        bool found = false;

        cout << "\n========== THUOC SAP HET HANG ==========\n";
        cout << "Muc canh bao: <= "
             << mucCanhBao << " san pham\n";

        for (size_t i = 0; i < thuocs.size(); i++)
        {
            if (thuocs[i].getsoluong() <= mucCanhBao)
            {
                cout << "\n---------- THUOC " << i + 1 << " ----------\n";
                thuocs[i].display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "Khong co thuoc nao sap het hang.\n";
        }
    }

    void saveToFile(const string &filePath)
    {
        ofstream file(filePath);

        if (!file.is_open())
        {
            cout << "Loi khi mo file de ghi thuoc!\n";
            return;
        }

        for (size_t i = 0; i < thuocs.size(); i++)
        {
            thuocs[i].writeFile(file);

            if (i + 1 < thuocs.size())
                file << "\n";
        }

        file.close();
    }

    void readFile(ifstream &file)
    {
        thuocs.clear();

        if (!file.is_open())
        {
            cout << "Khong mo duoc file thuoc!\n";
            return;
        }

        while (file)
        {
            file >> ws;

            if (file.peek() == EOF)
                break;

            Thuoc thuoc;

            try
            {
                thuoc.readFile(file);
                thuocs.push_back(thuoc);
            }
            catch (...)
            {
                cout << "Loi khi doc du lieu thuoc!\n";
                break;
            }
        }
    }
};

#endif