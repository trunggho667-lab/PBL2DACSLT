#ifndef MANAGER_DOCTOR_H
#define MANAGER_DOCTOR_H
#include <iostream>
#include <vector>
#include "Doctor.h"
#include <iomanip>
#include <algorithm>

#include <cctype>
using namespace std;

class Manager_Doctor
{
private:
    vector<Doctor> doctors;
    string toLower(string str)
    {
        transform(str.begin(), str.end(), str.begin(),
                  [](unsigned char c)
                  {
                      return static_cast<char>(tolower(c));
                  });
        return str;
    }

public:
    Doctor *findByCCCD(const string &cccd)
    {
        for (size_t i = 0; i < doctors.size(); i++)
            if (doctors[i].getcccd() == cccd)
                return &doctors[i];
        return nullptr;
    }

    void display()
    {
        cout << "\n=========================== DANH SACH BAC SI ===========================\n";
        cout << left
             << setw(5) << "STT"
             << setw(25) << "Ho ten"
             << setw(15) << "CCCD"
             << setw(20) << "Chuyen nganh"
             << setw(10) << "So ca" << endl;

        cout << "========================================================================\n";

        for (int i = 0; i < doctors.size(); i++)
        {
            cout << left
                 << setw(5) << i + 1
                 << setw(25) << doctors[i].getname()
                 << setw(15) << doctors[i].getcccd()
                 << setw(20) << doctors[i].getchuyennganh()
                 << setw(10) << doctors[i].getSoca()
                 << endl;
            cout << "------------------------------------------------------------------------\n";
        }

        cout << "========================================================================\n";
    }
    void input()
    {
        Doctor doctor;
        doctor.input();
        doctors.push_back(doctor);
    }
    void readFile(ifstream &file)
    {
        string empty;

        while (file.peek() != EOF)
        {
            Doctor doctor;
            doctor.readFile(file);
            doctors.push_back(doctor);
            getline(file, empty);
        }
    }
    void delete_cccddoctor(string cccd_delete,string file)
    {
        for (int i = 0; i < doctors.size(); i++)
        {
            if (doctors[i].getcccd() == cccd_delete)
            {
                doctors.erase(doctors.begin() + i);
                cout << "Da xoa thanh cong bac si co cccd: " << cccd_delete << endl;
                saveToFile(file);
                return;
            }
        }
        cout << "Khong tim thay bac si co cccd:" << cccd_delete << endl;
    }

    void saveToFile(string &filePath)
    {
        ofstream file(filePath);

        if (!file.is_open())
        {
            cout << "Loi khi mo file de ghi!\n";
            return;
        }

        for (size_t i = 0; i < doctors.size(); i++)
        {
            doctors[i].writeFile(file);

            if (i + 1 < doctors.size())
                file << "\n";
        }

        if (!file)
        {
            cout << "Loi khi ghi du lieu vao file!\n";
            return;
        }

        file.close();

        cout << "-> Da dong bo du lieu vao file "
             << filePath << " thanh cong!\n";
    }

    void change_doctor(string &filePath)
    {
        Manager_Doctor::display();
        int i;
        A:
        cout << "Chon stt de thay doi thong tin cua bac si:";
        cin >> i;
        if (i > 0 && i <= doctors.size())
        {
            doctors[i - 1].change_in4();
            saveToFile(filePath);
            return;
        }
        cout << "Vui long nhap stt phu hop!!!";
        goto A;
    }

    void search_namedoctor()
    {
        string namesearch;

        cout << "Nhap ten bac si muon tim kiem: ";

        if (!getline(cin, namesearch))
            return;
        bool found = false;
        string key = toLower(namesearch);

        for (size_t i = 0; i < doctors.size(); i++)
        {
            string currentName = toLower(doctors[i].getname());

            if (currentName.find(key) != string::npos)
            {
                cout << "\n========== Doctor "
                     << i + 1 << " ==========\n";

                doctors[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "Khong tim thay benh nhan co ten: "
                 << namesearch << endl;
        }
    }
    void search_chuyennganhdoctor()
    {
        cin.ignore(1000, '\n');
        string chuyennganh;

        cout << "Nhap chuyen nganh bac si muon tim: ";
        if (!getline(cin, chuyennganh))
            return;

        string key = toLower(chuyennganh);
        bool found = false;

        for (size_t i = 0; i < doctors.size(); i++)
        {
            string current = toLower(doctors[i].getchuyennganh());

            if (current.find(key) != string::npos)
            {
                cout << "\n========== Bac si " << i + 1 << " ==========\n";
                doctors[i].display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "Khong tim thay bac si thuoc chuyen nganh: "
                 << chuyennganh << endl;
        }
    }

    void writeFile(ofstream &file) {
    for (size_t i = 0; i < doctors.size(); i++) {
        doctors[i].writeFile(file);

        if (i + 1 < doctors.size())
            file << "\n";
    }
}
};
#endif
