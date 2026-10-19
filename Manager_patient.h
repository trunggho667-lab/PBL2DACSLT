#ifndef MANAGER_PATIENT_H
#define MANAGER_PATIENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <sstream>

#include "Patient.h"

using namespace std;

class manager_patient
{
private:
    vector<Patient> patients;

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

    bool docSo(
        const string &thongbao,
        int &x
    )
    {
        string dong;

        while (true)
        {
            cout << thongbao;

            if (!getline(cin, dong))
                return false;

            stringstream ss(dong);

            char kyTuThua;

            if ((ss >> x) && !(ss >> kyTuThua))
                return true;

            cout << "Vui long nhap mot so nguyen hop le!\n";
        }
    }

public:
    Patient *findByCCCD(const string &cccd)
    {
        for (size_t i = 0; i < patients.size(); i++)
        {
            if (patients[i].getcccd() == cccd)
                return &patients[i];
        }

        return nullptr;
    }

    Patient *getPatientByCCCD(const string &cccd)
    {
        return findByCCCD(cccd);
    }

    void display()
    {
        if (patients.empty())
        {
            cout << "Danh sach benh nhan rong!\n";
            return;
        }

        cout << "\n================ DANH SACH BENH NHAN ================\n";

        for (size_t i = 0; i < patients.size(); i++)
        {
            cout << "\n========== BENH NHAN "
                 << i + 1
                 << " ==========\n";

            patients[i].display();
        }
    }

    void addPatient(const string &filePath)
    {
        cout << "\n--- NHAP THONG TIN BENH NHAN MOI ---\n";

        Patient p;

        p.input();

        if (findByCCCD(p.getcccd()) != nullptr)
        {
            cout << "-> Loi: CCCD "
                 << p.getcccd()
                 << " da ton tai trong he thong!\n";

            cout << "Khong the them benh nhan.\n";

            return;
        }

        patients.push_back(p);

        saveToFile(filePath);

        cout << "-> Them benh nhan thanh cong!\n";
    }

    void readFile(ifstream &file)
    {
        patients.clear();

        if (!file.is_open())
        {
            cout << "Loi: File khong mo duoc!\n";
            return;
        }

        while (file)
        {
            file >> ws;

            if (file.peek() == EOF)
                break;

            Patient patient;

            patient.readFile(file);

            if (file.fail())
            {
                cout << "Loi khi doc du lieu benh nhan!\n";
                break;
            }

            if (!patient.getcccd().empty())
            {
                patients.push_back(patient);
            }

            string dongTrong;

            getline(file, dongTrong);
        }
    }

    void saveToFile(const string &filePath)
    {
        ofstream file(filePath);

        if (!file.is_open())
        {
            cout << "Loi khi mo file de ghi!\n";
            return;
        }

        for (size_t i = 0; i < patients.size(); i++)
        {
            patients[i].writeFile(file);

            if (i + 1 < patients.size())
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

    void search_name()
    {
        string namesearch;

        cout << "Nhap ten benh nhan muon tim kiem: ";

        if (!getline(cin, namesearch))
            return;

        string key = toLower(namesearch);

        bool found = false;

        for (size_t i = 0; i < patients.size(); i++)
        {
            string currentName =
                toLower(patients[i].getname());

            if (currentName.find(key) != string::npos)
            {
                cout << "\n========== BENH NHAN "
                     << i + 1
                     << " ==========\n";

                patients[i].display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "Khong tim thay benh nhan co ten: "
                 << namesearch << endl;
        }
    }

    void search_cccd()
    {
        string cccdsearch;

        cout << "Nhap CCCD benh nhan muon tim kiem: ";

        if (!getline(cin, cccdsearch))
            return;

        Patient *p = findByCCCD(cccdsearch);

        if (p != nullptr)
        {
            cout << "\n========== THONG TIN BENH NHAN ==========\n";

            p->display();

            return;
        }

        cout << "Hien tai khong co thong tin benh nhan co "
             << "CCCD la: "
             << cccdsearch
             << endl;
    }

    void deletePatient(const string &filePath)
    {
        string cccd;

        cout << "Nhap CCCD benh nhan can xoa: ";

        if (!getline(cin, cccd))
            return;

        for (size_t i = 0; i < patients.size(); i++)
        {
            if (patients[i].getcccd() == cccd)
            {
                cout << "\nThong tin benh nhan se bi xoa:\n";

                patients[i].display();

                char choice;

                cout << "\nBan co chac chan muon xoa? (y/n): ";
                cin >> choice;

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                if (choice != 'y' && choice != 'Y')
                {
                    cout << "Da huy thao tac xoa.\n";
                    return;
                }

                patients.erase(
                    patients.begin() + i
                );

                saveToFile(filePath);

                cout << "-> Da xoa benh nhan thanh cong!\n";

                return;
            }
        }

        cout << "Khong tim thay benh nhan co CCCD: "
             << cccd
             << endl;
    }

    void editPatient(const string &filePath)
    {
        string cccdEdit;

        cout << "Nhap CCCD cua benh nhan can sua thong tin: ";

        if (!getline(cin, cccdEdit))
            return;

        for (size_t i = 0; i < patients.size(); i++)
        {
            if (patients[i].getcccd() != cccdEdit)
                continue;

            Patient &p = patients[i];

            bool daSua = false;

            const int SO_MUC = 11;

            while (true)
            {
                p.display();

                cout << "\n===== CHON THONG TIN MUON SUA =====\n";
                cout << "1. Ho va ten\n";
                cout << "2. CCCD\n";
                cout << "3. So dien thoai\n";
                cout << "4. Gioi tinh\n";
                cout << "5. Tuoi\n";
                cout << "6. So BHYT\n";
                cout << "7. Ngay mua BHYT\n";
                cout << "8. Bac si kham\n";
                cout << "9. Chuan doan\n";
                cout << "10. So phong\n";
                cout << "11. Ngay kham\n";
                cout << "12. Tat ca thong tin\n";
                cout << "0. Hoan tat\n";

                int chon;

                if (!docSo(
                        "Lua chon cua ban: ",
                        chon))
                {
                    return;
                }

                if (chon == 0)
                    break;

                if (chon == 1)
                {
                    string s;

                    cout << "Nhap ho ten moi: ";
                    getline(cin, s);

                    if (!s.empty())
                    {
                        p.setname(s);
                        daSua = true;
                    }
                }

                else if (chon == 2)
                {
                    string s;

                    cout << "Nhap CCCD moi: ";
                    getline(cin, s);

                    if (s.empty())
                    {
                        cout << "CCCD khong duoc de trong!\n";
                    }
                    else
                    {
                        bool trung = false;

                        for (size_t j = 0;
                             j < patients.size();
                             j++)
                        {
                            if (j != i &&
                                patients[j].getcccd() == s)
                            {
                                trung = true;
                                break;
                            }
                        }

                        if (trung)
                        {
                            cout << "CCCD nay da ton tai!\n";
                        }
                        else
                        {
                            p.setcccd(s);
                            daSua = true;
                        }
                    }
                }

                else if (chon == 3)
                {
                    string s;

                    cout << "Nhap so dien thoai moi: ";
                    getline(cin, s);

                    if (!s.empty())
                    {
                        p.setnumber(s);
                        daSua = true;
                    }
                }

                else if (chon == 4)
                {
                    int a;

                    if (!docSo(
                            "Nhap gioi tinh moi (1 = Nu / 0 = Nam): ",
                            a))
                    {
                        return;
                    }

                    while (a != 0 && a != 1)
                    {
                        if (!docSo(
                                "Vui long nhap 0 hoac 1: ",
                                a))
                        {
                            return;
                        }
                    }

                    p.setgender(a == 1);

                    daSua = true;
                }

                else if (chon == 5)
                {
                    int a;

                    if (!docSo(
                            "Nhap tuoi moi: ",
                            a))
                    {
                        return;
                    }

                    if (p.setage(a))
                    {
                        daSua = true;
                    }
                    else
                    {
                        cout << "Tuoi phai tu 1 den 120!\n";
                    }
                }

                else if (chon == 6)
                {
                    string s;

                    cout << "Nhap so BHYT moi: ";
                    getline(cin, s);

                    if (!s.empty())
                    {
                        p.setso(s);
                        daSua = true;
                    }
                }

                else if (chon == 7)
                {
                    int a, b, c;

                    cout << "Nhap ngay mua BHYT moi:\n";

                    if (!docSo("Nhap ngay: ", a) ||
                        !docSo("Nhap thang: ", b) ||
                        !docSo("Nhap nam: ", c))
                    {
                        return;
                    }

                    if (p.setngaymua(a, b, c))
                    {
                        daSua = true;
                    }
                    else
                    {
                        cout << "Ngay khong hop le!\n";
                    }
                }

                else if (chon == 8)
                {
                    string s;

                    cout << "Nhap bac si kham moi: ";
                    getline(cin, s);

                    if (!s.empty())
                    {
                        p.setbacsikham(s);
                        daSua = true;
                    }
                }

                else if (chon == 9)
                {
                    string s;

                    cout << "Nhap chuan doan moi: ";
                    getline(cin, s);

                    if (!s.empty())
                    {
                        p.setchuandoan(s);
                        daSua = true;
                    }
                }

                else if (chon == 10)
                {
                    string s;

                    cout << "Nhap so phong moi: ";
                    getline(cin, s);

                    if (!s.empty())
                    {
                        p.setsophong(s);
                        daSua = true;
                    }
                }

                else if (chon == 11)
                {
                    int a, b, c;

                    cout << "Nhap ngay kham moi:\n";

                    if (!docSo("Nhap ngay: ", a) ||
                        !docSo("Nhap thang: ", b) ||
                        !docSo("Nhap nam: ", c))
                    {
                        return;
                    }

                    if (p.setngaykham(a, b, c))
                    {
                        daSua = true;
                    }
                    else
                    {
                        cout << "Ngay khong hop le!\n";
                    }
                }

                else if (chon == 12)
                {
                    cout << "\nDe sua toan bo thong tin, "
                         << "ban co the chon tung muc tu 1 den 11.\n";
                }

                else
                {
                    cout << "Lua chon khong hop le!\n";
                }
            }

            if (daSua)
            {
                saveToFile(filePath);

                cout << "-> Cap nhat thong tin thanh cong!\n";
            }
            else
            {
                cout << "-> Khong co thong tin nao duoc thay doi.\n";
            }

            return;
        }

        cout << "Khong tim thay benh nhan co CCCD: "
             << cccdEdit
             << endl;
    }
};

#endif
