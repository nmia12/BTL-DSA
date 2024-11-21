#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class PhongTro {
private:
    int soPhong;
    string tenNguoiThue;
    int soNguoi;
    int thoiGianThue;
    int ngayThue;
    int thangThue;
    int namThue;
    double tienCoc;
    double giaThue;
    int soDienDauKy;
    int dichVu;
    
public:
    PhongTro() 
        : tenNguoiThue(""), soNguoi(0), thoiGianThue(0), ngayThue(0), thangThue(0),
		 namThue(0), tienCoc(0.0), giaThue(0.0), soDienDauKy(0), dichVu(0) {}

    PhongTro(string ten, int soLuong, int thoiGian, int ngay, int thang,
			 int nam, double coc, double gia, int dienDau, int dv)
        : tenNguoiThue(ten), soNguoi(soLuong), thoiGianThue(thoiGian), ngayThue(ngay), 
		 thangThue(thang), namThue(nam), tienCoc(coc), giaThue(gia), soDienDauKy(dienDau), dichVu(dv) {}

    // Nhap thong tin
    void nhap() {
        cout << "Nhap so phong:";
        cin >> soPhong;
        cout << "Nhap ten nguoi thue:";
        cin.ignore();
        getline(cin, tenNguoiThue);
        cout << "Nhap so luong nguoi o:";
        cin >> soNguoi;
        cout << "Nhap thoi gian thue (thang):";
        cin >> thoiGianThue;
        cout << "Nhap ngay thue (dd/mm/yy):";
        cin >> ngayThue >> thangThue >> namThue;
        cout << "Nhap so tien da coc (trieu vnd):";
        cin >> tienCoc;
        cout << "Nhap gia thue (trieu vnd):";
        cin >> giaThue;
        cout << "Nhap so dien dau ky:";
        cin >> soDienDauKy;
        cout << "Nhap gia dich vu (internet, cap, nuoc, may giat, dien chung, rac)(nghin VND/thang):";
        cin >> dichVu;
    }
    // Xuat thong tin
    void xuat() const {
        cout << "Phong " << soPhong << endl;
        cout << "Ten nguoi thue: " << tenNguoiThue << endl;
        cout << "Soluong nguoi o: " << soNguoi << endl;
        cout << "Thoi gian thue: " << thoiGianThue << " thang" << endl;
        cout << "Ngay thue: " << ngayThue << "/" << thangThue << "/" << namThue << endl;
        cout << "Tien coc: " << tienCoc << " trieu VND" << endl;
        cout << "Gia thue: " << giaThue << " trieu VND" << endl;
        cout << "So dien dau ky: " << soDienDauKy << endl;
        cout << "Dich vu: " << dichVu << "000 VND" << endl;
    }

    // Tinh tien dien
    double tinhTienDien(int soDienHienTai) const {
        int soDienSuDung = soDienHienTai - soDienDauKy;
        if (soDienSuDung < 0) {
            cout << "So dien hien tai khong hop le!" << endl;
            return 0;
        }
        return soDienSuDung * 3000.0;  
    }


    // Toan tu <<
    friend ostream& operator<<(ostream& out, const PhongTro& pt) {
        pt.xuat();
        return out;
    }
    // Toan tu >> 
    friend istream& operator>>(istream& in, PhongTro& pt) {
        pt.nhap();
        return in;
    }

    // Toan tu so sanh < gia thue tro
    bool operator<(const PhongTro& other) const {
        return this->giaThue < other.giaThue;
    }

   double getGiaThue() const {
       return giaThue;
   }
    string getTenNguoiThue() const {
        return tenNguoiThue;
    }

};
class DanhSachPhongTro {
private:
    vector<PhongTro> danhSach;
public:
    // Them 1 phong tro
    void themPhongTro(const PhongTro& pt) {
        danhSach.push_back(pt);
    }

    // Xoa phong tro theo ten nguoi thue
    void xoaPhongTro(const string& tenNguoiThue) {
        auto it = find_if(danhSach.begin(), danhSach.end(), [&tenNguoiThue](const PhongTro& pt) {
            return pt.getTenNguoiThue() == tenNguoiThue; 
        });

        if (it != danhSach.end()) {
            danhSach.erase(it);  
            cout << "Xoa phong tro thanh cong!" << endl;
        } else {
            cout << "Phong tro khong tim thay!" << endl;
        }
    }

    // Tim kiem phong tro theo ten
    void timPhongTroByTen(const string& tenNguoiThue) const {
        auto it = find_if(danhSach.begin(), danhSach.end(), [&tenNguoiThue](const PhongTro& pt) {
            return pt.getTenNguoiThue() == tenNguoiThue;
        });

        if (it != danhSach.end()) {
            cout << "Phong tro cua " << tenNguoiThue << " la:" << endl;
            cout << *it << endl;
        } else {
            cout << "Khong tim thay phong tro cua " << tenNguoiThue << endl;
        }
    }
    // Phong tro co gia thue cao nhat
    PhongTro timMaxGiaThue() const {
        return *max_element(danhSach.begin(), danhSach.end(), [](const PhongTro& a, const PhongTro& b) {
            return a.getGiaThue() < b.getGiaThue();
        });
    }

    // Phong tro co gia thue thap nhat
    PhongTro timMinGiaThue() const {
        return *min_element(danhSach.begin(), danhSach.end(), [](const PhongTro& a, const PhongTro& b) {
            return a.getGiaThue() < b.getGiaThue();
        });
    }

    // Sap xep danh sach phong tro theo gia thue
    void sapXep() {
        sort(danhSach.begin(), danhSach.end());
        if (danhSach.empty()) {
            cout << "Danh sach phong tro trong!" << endl;
            return;
        }
        for (const auto& pt : danhSach) {
            cout << pt << endl;
        }
    }

    // Xuat danh sach phong tro
    void xuatDanhSach() const {
        if (danhSach.empty()) {
            cout << "Danh sach phong tro trong!" << endl;
            return;
        }
        for (const auto& pt : danhSach) {
            cout << pt << endl;
        }
    }

    vector<PhongTro>& getDanhSach() {
        return danhSach;
    }

};
class App {
private:
    DanhSachPhongTro dsPhongTro;
public:
    void hienThiMenu() {
        cout << "====== Quan ly phong tro ======" << endl;
        cout << "1. Them phong tro" << endl;
        cout << "2. Xoa phong tro" << endl;
        cout << "3. Xuat danh sach phong tro" << endl;
        cout << "4. Tim phong tro co gia thue cao nhat" << endl;
        cout << "5. Tim phong tro co gia thue thap nhat" << endl;
        cout << "6. Sap xep danh sach phong tro" << endl;
        cout << "7. Tim kiem phong tro" << endl;
        cout << "8. Tinh tien dien cua phong tro" << endl; 
        cout << "9. Thoat" << endl;
        cout << "Chon thao tac: ";
    }

    void chay() {
        int luaChon;
        do {
            hienThiMenu();
            cin >> luaChon;
            switch (luaChon) {
                case 1: {
                    PhongTro pt;
                    cin >> pt;
                    dsPhongTro.themPhongTro(pt);
                    break;
                }
                case 2: {
                    string ten;
                    cout << "Nhap ten nguoi thue phong can xoa: ";
                    cin.ignore();
                    getline(cin, ten);
                    dsPhongTro.xoaPhongTro(ten);
                    break;
                }
                case 3:
                    dsPhongTro.xuatDanhSach();
                    break;
                case 4: {
                    PhongTro pt = dsPhongTro.timMaxGiaThue();
                    cout << "Phong tro co gia thue cao nhat: " << pt << endl;
                    break;
                }
                case 5: {
                    PhongTro pt = dsPhongTro.timMinGiaThue();
                    cout << "Phong tro co gia thue thap nhat: " << pt << endl;
                    break;
                }
                case 6:
                    dsPhongTro.sapXep();
                    cout << "Danh sach phong tro da duoc sap xep!" << endl;
                    break;
                case 7: {
                    string ten;
                    cout << "Nhap ten nguoi thue phong can tim: ";
                    cin.ignore();
                    getline(cin, ten);
                    dsPhongTro.timPhongTroByTen(ten);
                    break;
                }
                case 8: {  
                    string ten;
                    cout << "Nhap ten nguoi thue phong can tinh tien dien: ";
                    cin.ignore();
                    getline(cin, ten);
                    auto it = find_if(dsPhongTro.getDanhSach().begin(), dsPhongTro.getDanhSach().end(), [&ten](const PhongTro& pt) {
                    return pt.getTenNguoiThue() == ten;
                    });

                    if (it != dsPhongTro.getDanhSach().end()) {
                        int soDienHienTai;
                        cout << "Nhap so dien hien tai: ";
                        cin >> soDienHienTai;
                        double tienDien = it->tinhTienDien(soDienHienTai);
                        cout << "Tien dien cua phong tro: " << tienDien << " VND" << endl;
                    } else {
                        cout << "Khong tim thay phong tro cua " << ten << endl;
                    }
                    break;
                }
                case 9:
                    cout << "Thoat khoi chuong trinh." << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le!" << endl;
            }
        } while (luaChon != 7);
    }
};

int main() {
    App app;
    app.chay();
    return 0;
}
