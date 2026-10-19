#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <unordered_map>
#include <functional>

#include "Input_util.h"
#include "Manager_doctor.h"
#include "Manager_patient.h"
#include "Manager_Medicine.h"
#include "Manager_DonThuoc.h"

using namespace std;

const string FILE_PATIENT  = "1.patient.txt";
const string FILE_DOCTOR   = "2.Danhsachbacsi.txt";
const string FILE_THUOC    = "3.Thuoc.txt";
const string FILE_DON      = "4.Donthuoc.txt";
const string FILE_TAIKHOAN = "5.Taikhoan.txt";

unordered_map<string, size_t> userDatabase;

size_t bamMatKhau(const string &password)
{
    hash<string> hasher;
    return hasher(password);
}

void docFileTaiKhoan()
{
    ifstream f(FILE_TAIKHOAN);

    if (!f.is_open())
    {
        userDatabase["admin"] = bamMatKhau("123");
        return;
    }

    string username;
    size_t passwordHash;

    while (f >> username >> passwordHash)
    {
        userDatabase[username] = passwordHash;
    }

    f.close();
}

void ghiTaiKhoanVaoFile(
    const string &username,
    size_t passwordHash)
{
    ofstream f(FILE_TAIKHOAN, ios::app);

    if (!f.is_open())
    {
        cout << "Loi: Khong the luu tai khoan vao file!\n";
        return;
    }

    f << username << " "
      << passwordHash << "\n";

    f.close();
}

void dangKyTaiKhoan()
{
    string username;
    string password;

    cout << "\n========== DANG KY TAI KHOAN QUAN LY ==========\n";

    cout << "Nhap ten dang nhap moi: ";
    cin >> username;

    if (userDatabase.find(username) != userDatabase.end())
    {
        cout << "Loi: Ten dang nhap nay da ton tai!\n";
        cin.ignore(1000, '\n');
        return;
    }

    cout << "Nhap mat khau: ";
    cin >> password;

    size_t hashedPwd = bamMatKhau(password);

    userDatabase[username] = hashedPwd;

    ghiTaiKhoanVaoFile(username, hashedPwd);

    cout << "Dang ky tai khoan thanh cong!\n";

    cin.ignore(1000, '\n');
}

bool dangNhapHeThong(string &workingUser)
{
    string username;
    string password;

    cout << "\n========== DANG NHAP HE THONG ==========\n";

    cout << "Ten dang nhap: ";
    cin >> username;

    cout << "Mat khau: ";
    cin >> password;

    cin.ignore(1000, '\n');

    auto it = userDatabase.find(username);

    if (it != userDatabase.end())
    {
        if (bamMatKhau(password) == it->second)
        {
            workingUser = username;

            cout << "Dang nhap thanh cong!\n";
            cout << "Chao mung " << username
                 << " den voi he thong.\n";

            return true;
        }
    }

    cout << "Loi: Ten dang nhap hoac mat khau khong dung!\n";

    return false;
}

int docLuaChon(const string &thongbao)
{
    int x;

    if (!docSoNguyen(thongbao, x))
        return 0;

    return x;
}

void tamDung()
{
    cout << "\nNhan Enter de tiep tuc...";

    string s;
    getline(cin, s);
}

void menuBacSi(Manager_Doctor &ds)
{
    int chon;

    do
    {
        cout << "\n========== QUAN LY BAC SI ==========\n";
        cout << "1. Xem danh sach bac si\n";
        cout << "2. Them bac si moi\n";
        cout << "3. Tim bac si theo ten\n";
        cout << "4. Tim bac si theo chuyen nganh\n";
        cout << "5. Sua thong tin bac si\n";
        cout << "6. Xoa bac si theo CCCD\n";
        cout << "0. Quay lai\n";
        cout << "====================================\n";

        chon = docLuaChon("Lua chon cua ban: ");

        switch (chon)
        {
        case 1:
            ds.display();
            break;

        case 2:
            ds.input();
            ds.saveToFile(FILE_DOCTOR);
            break;

        case 3:
            ds.search_namedoctor();
            break;

        case 4:
            ds.search_chuyennganhdoctor();
            break;

        case 5:
            ds.change_doctor(FILE_DOCTOR);
            break;

        case 6:
        {
            string cccd;

            cout << "Nhap CCCD bac si can xoa: ";
            getline(cin, cccd);

            ds.delete_cccddoctor(
                cccd,
                FILE_DOCTOR
            );

            break;
        }

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

        if (chon != 0)
            tamDung();

    } while (chon != 0);
}

void menuBenhNhan(manager_patient &ds)
{
    int chon;

    do
    {
        cout << "\n========== QUAN LY BENH NHAN ==========\n";
        cout << "1. Xem danh sach benh nhan\n";
        cout << "2. Them benh nhan moi\n";
        cout << "3. Tim benh nhan theo ten\n";
        cout << "4. Tim benh nhan theo CCCD\n";
        cout << "5. Sua thong tin benh nhan\n";
        cout << "6. Xoa benh nhan\n";
        cout << "0. Quay lai\n";
        cout << "=======================================\n";

        chon = docLuaChon("Lua chon cua ban: ");

        switch (chon)
        {
        case 1:
            ds.display();
            break;

        case 2:
            ds.addPatient(FILE_PATIENT);
            break;

        case 3:
            ds.search_name();
            break;

        case 4:
            ds.search_cccd();
            break;

        case 5:
            ds.editPatient(FILE_PATIENT);
            break;

        case 6:
            ds.deletePatient(FILE_PATIENT);
            break;

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

        if (chon != 0)
            tamDung();

    } while (chon != 0);
}

void menuThuoc(Manager_Thuoc &kho)
{
    int chon;

    do
    {
        cout << "\n========== QUAN LY THUOC ==========\n";
        cout << "1. Xem danh sach thuoc\n";
        cout << "2. Them thuoc moi\n";
        cout << "3. Tim thuoc theo ten / ma\n";
        cout << "4. Cap nhat don gia / so luong ton\n";
        cout << "5. Xoa thuoc\n";
        cout << "6. Thuoc sap het hang\n";
        cout << "0. Quay lai\n";
        cout << "===================================\n";

        chon = docLuaChon("Lua chon cua ban: ");

        switch (chon)
        {
        case 1:
            kho.display();
            break;

        case 2:
            kho.addThuoc(FILE_THUOC);
            break;

        case 3:
            kho.searchThuoc();
            break;

        case 4:
            kho.updateThuoc(FILE_THUOC);
            break;

        case 5:
        {
            string ma;

            cout << "Nhap ma thuoc can xoa: ";
            getline(cin, ma);

            kho.deleteThuoc(
                ma,
                FILE_THUOC
            );

            break;
        }

        case 6:
            kho.displayLowStock();
            break;

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

        if (chon != 0)
            tamDung();

    } while (chon != 0);
}

void menuDonThuoc(
    Manager_DonThuoc &don,
    Manager_Doctor &bacsi,
    manager_patient &benhnhan,
    Manager_Thuoc &kho)
{
    int chon;

    do
    {
        cout << "\n========== KE DON THUOC ==========\n";
        cout << "1. Ke don thuoc moi\n";
        cout << "2. Xem tat ca don thuoc da ke\n";
        cout << "3. Xem don thuoc theo CCCD benh nhan\n";
        cout << "4. Xem don thuoc theo CCCD bac si\n";
        cout << "0. Quay lai\n";
        cout << "==================================\n";

        chon = docLuaChon("Lua chon cua ban: ");

        switch (chon)
        {
        case 1:
            don.keDon(
                bacsi,
                benhnhan,
                kho,
                FILE_DON,
                FILE_THUOC
            );
            break;

        case 2:
            don.displayAll();
            break;

        case 3:
            don.displayByPatient();
            break;

        case 4:
            don.displayByDoctor();
            break;

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

        if (chon != 0)
            tamDung();

    } while (chon != 0);
}

void chayChuongTrinhChinh(
    Manager_Doctor &doctors,
    manager_patient &patients,
    Manager_Thuoc &kho,
    Manager_DonThuoc &donthuoc,
    string userHienTai)
{
    int chon;

    do
    {
        cout << "\n################################################\n";
        cout << "#          QUAN LY BENH VIEN - PBL2            #\n";
        cout << "#          Nhan vien dang truc: "
             << userHienTai << "\n";
        cout << "################################################\n";

        cout << "  1. Quan ly bac si\n";
        cout << "  2. Quan ly benh nhan\n";
        cout << "  3. Quan ly thuoc\n";
        cout << "  4. Ke don thuoc\n";
        cout << "  0. Dang xuat he thong\n";

        cout << "################################################\n";

        chon = docLuaChon("Lua chon cua ban: ");

        switch (chon)
        {
        case 1:
            menuBacSi(doctors);
            break;

        case 2:
            menuBenhNhan(patients);
            break;

        case 3:
            menuThuoc(kho);
            break;

        case 4:
            menuDonThuoc(
                donthuoc,
                doctors,
                patients,
                kho
            );
            break;

        case 0:
            cout << "Dang dang xuat tai khoan "
                 << userHienTai << "...\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);
}

int main()
{
    docFileTaiKhoan();

    Manager_Doctor doctors;
    manager_patient patients;
    Manager_Thuoc kho;
    Manager_DonThuoc donthuoc;

    ifstream fd(FILE_DOCTOR);

    if (fd.is_open())
    {
        doctors.readFile(fd);
        fd.close();
    }
    else
    {
        cout << "Chua co file bac si: "
             << FILE_DOCTOR << endl;
    }

    ifstream fp(FILE_PATIENT);

    if (fp.is_open())
    {
        patients.readFile(fp);
        fp.close();
    }
    else
    {
        cout << "Chua co file benh nhan: "
             << FILE_PATIENT << endl;
    }

    ifstream fthuoc(FILE_THUOC);

    if (fthuoc.is_open())
    {
        kho.readFile(fthuoc);
        fthuoc.close();
    }
    else
    {
        cout << "Chua co file thuoc: "
             << FILE_THUOC << endl;
    }

    ifstream fdon(FILE_DON);

    if (fdon.is_open())
    {
        donthuoc.readFile(fdon);
        fdon.close();
    }
    else
    {
        cout << "Chua co file don thuoc: "
             << FILE_DON << endl;
    }

    int luaChonCong;
    string workingUser = "";

    do
    {
        cout << "\n============================================\n";
        cout << "        HE THONG BAO MAT BENH VIEN          \n";
        cout << "============================================\n";

        cout << "1. Dang nhap vao he thong lam viec\n";
        cout << "2. Dang ky tai khoan nhan vien moi\n";
        cout << "0. Tat nguon he thong (Thoat)\n";

        cout << "============================================\n";

        luaChonCong =
            docLuaChon("Moi ban chon (0-2): ");

        switch (luaChonCong)
        {
        case 1:

            if (dangNhapHeThong(workingUser))
            {
                chayChuongTrinhChinh(
                    doctors,
                    patients,
                    kho,
                    donthuoc,
                    workingUser
                );
            }

            break;

        case 2:
            dangKyTaiKhoan();
            break;

        case 0:
            cout << "He thong da tat hoan toan. Tam biet!\n";
            break;

        default:
            cout << "Lua chon khong hop le. "
                 << "Vui long chon lai!\n";
        }

    } while (luaChonCong != 0);

    return 0;
}
