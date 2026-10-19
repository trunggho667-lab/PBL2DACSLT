#ifndef MANAGER_DOCTOR_H
#define MANAGER_DOCTOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <string>
#include <limits>

#include "Doctor.h"

using namespace std;

class Manager_Doctor
{
private:
    vector<Doctor> doctors;

    string toLower(string str)
    {
        transform(
            str.begin(),
            str.end(),
            str.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(tolower(c));
            }
        );

        return str;
    }

public:
    Doctor *findByCCCD(const string &cccd)
    {
        for (size_t i = 0; i < doctors.size(); i++)
        {
            if (doctors[i].getcccd() == cccd)
                return &doctors[i];
        }

        return nullptr;
    }

    bool checkCCCD(const string &cccd)
    {
        return findByCCCD(cccd) != nullptr;
    }

    void display()
    {
        cout << "\n";
        cout << "=========================== DANH SACH BAC SI ===========================\n";

        cout << left
             << setw(5) << "STT"
             << setw(25) << "Ho ten"
             << setw(15) << "CCCD"
             << setw(20) << "Chuyen nganh"
             << setw(10) << "So ca"
             << endl;

        cout << "========================================================================\n";

        if (doctors.empty())
        {
            cout << "Danh sach bac si dang rong!\n";
            cout << "========================================================================\n";
            return;
        }

        for (size_t i = 0; i < doctors.size(); i++)
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

        if (checkCCCD(doctor.getcccd()))
        {
            cout << "CCCD nay da ton tai trong danh sach bac si!\n";
            cout << "Khong th? thêm bác s?.\n";
            return;
        }

        doctors.push_back(doctor);

        cout << "Them bac si thanh cong!\n";
    }

    void readFile(ifstream &file)
    {
        if (!file.is_open())
        {
            cout << "Khong mo duoc file bac si!\n";
            return;
        }

        doctors.clear();

        while (file.peek() != EOF)
        {
            Doctor doctor;

            doctor.readFile(file);

            if (!doctor.getcccd().empty())
            {
                doctors.push_back(doctor);
            }

            string empty;
            getline(file, empty);
        }
    }

    void delete_cccddoctor(
        const string &cccd_delete,
        const string &file
    )
    {
        for (size_t i = 0; i < doctors.size(); i++)
        {
            if (doctors[i].getcccd() == cccd_delete)
            {
                cout << "\nThong tin bac si se bi xoa:\n";

                doctors[i].display();

                char choice;

                cout << "Ban co chac chan muon xoa? (y/n): ";
                cin >> choice;

                if (choice != 'y' && choice != 'Y')
                {
                    cout << "Da huy thao tac xoa.\n";
                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n'
                    );
                    return;
                }

                doctors.erase(doctors.begin() + i);

                saveToFile(file);

                cout << "Da xoa thanh cong bac si co CCCD: "
                     << cccd_delete << endl;

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                return;
            }
        }

        cout << "Khong tim thay bac si co CCCD: "
             << cccd_delete << endl;
    }

    void saveToFile(const string &filePath)
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
             << filePath
             << " thanh cong!\n";
    }

    void change_doctor(const string &filePath)
    {
        if (doctors.empty())
        {
            cout << "Danh sach bac si dang rong!\n";
            return;
        }

        display();

        int i;

        while (true)
        {
            cout << "Chon STT de thay doi thong tin bac si: ";

            if (cin >> i &&
                i > 0 &&
                i <= static_cast<int>(doctors.size()))
            {
                break;
            }

            cout << "Vui long nhap STT hop le!\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
        }

        doctors[i - 1].change_in4();

        saveToFile(filePath);
    }

    void search_namedoctor()
    {
        string namesearch;

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "Nhap ten bac si muon tim kiem: ";
        getline(cin, namesearch);

        string key = toLower(namesearch);

        bool found = false;

        for (size_t i = 0; i < doctors.size(); i++)
        {
            string currentName =
                toLower(doctors[i].getname());

            if (currentName.find(key) != string::npos)
            {
                cout << "\n========== BAC SI "
                     << i + 1
                     << " ==========\n";

                doctors[i].display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "Khong tim thay bac si co ten: "
                 << namesearch << endl;
        }
    }

    void search_chuyennganhdoctor()
    {
        string chuyennganh;

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "Nhap chuyen nganh bac si muon tim: ";

        getline(cin, chuyennganh);

        string key = toLower(chuyennganh);

        bool found = false;

        for (size_t i = 0; i < doctors.size(); i++)
        {
            string current =
                toLower(doctors[i].getchuyennganh());

            if (current.find(key) != string::npos)
            {
                cout << "\n========== BAC SI "
                     << i + 1
                     << " ==========\n";

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

    void writeFile(ofstream &file)
    {
        for (size_t i = 0; i < doctors.size(); i++)
        {
            doctors[i].writeFile(file);

            if (i + 1 < doctors.size())
                file << "\n";
        }
    }
};

#endif
