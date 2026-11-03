#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

string chuanHoa(string s) {
    for (int i = 0; i < (int)s.length(); i++)
        s[i] = (char)toupper((unsigned char)s[i]);
    return s;
}

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(1) {}

    phuong_tien(int ma, string loai, int gio, int tg)
        : ma_xe(ma), loai_xe(chuanHoa(loai)), gio_vao(gio), tg_do(tg) {}

    int lay_ma_xe() const { return ma_xe; }
    string lay_loai_xe() const { return loai_xe; }

    double tinh_phi() const {
        double don_gia = 0;
        if (loai_xe == "CAR") don_gia = 6000;
        else if (loai_xe == "MOTORCYCLE") don_gia = 4000;
        else if (loai_xe == "BICYCLE") don_gia = 2000;
        else return 0;

        double tong = 0;
        bool cao_diem = (gio_vao >= 6 && gio_vao < 10) ||
                        (gio_vao >= 15 && gio_vao < 19);
        for (int i = 1; i <= tg_do; i++) {
            if (i <= 2)
                tong += don_gia * (cao_diem ? 1.30 : 0.95);
            else
                tong += don_gia * 0.90;
        }
        return tong;
    }

    void hien_thi() const {
        cout << "Ma xe: " << ma_xe
             << " | Loai xe: " << loai_xe
             << " | Gio vao: " << gio_vao
             << " | Thoi gian do: " << tg_do << " gio"
             << " | Phi: " << fixed << setprecision(0) << tinh_phi() << " VND\n";
    }
};

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe() : ma_bai(0), kich_thuoc('S'), co1(false), co2(false), co3(false) {}

    bai_xe(int ma, char kt)
        : ma_bai(ma), kich_thuoc((char)toupper((unsigned char)kt)),
          co1(false), co2(false), co3(false) {}

    int lay_ma() const { return ma_bai; }
    char lay_kich_thuoc() const { return kich_thuoc; }

    int so_xe() const {
        return (co1 ? 1 : 0) + (co2 ? 1 : 0) + (co3 ? 1 : 0);
    }

    int suc_chua() const {
        if (kich_thuoc == 'S') return 1;
        if (kich_thuoc == 'M') return 2;
        return 3;
    }

    bool them(phuong_tien v) {
        if (chua(v.lay_ma_xe())) return false;
        if (!co1) { pt1 = v; co1 = true; return true; }
        if (kich_thuoc != 'S' && !co2) { pt2 = v; co2 = true; return true; }
        if (kich_thuoc == 'L' && !co3) { pt3 = v; co3 = true; return true; }
        return false;
    }

    bool xoa(int ma_xe) {
        if (co1 && pt1.lay_ma_xe() == ma_xe) { co1 = false; return true; }
        if (co2 && pt2.lay_ma_xe() == ma_xe) { co2 = false; return true; }
        if (co3 && pt3.lay_ma_xe() == ma_xe) { co3 = false; return true; }
        return false;
    }

    bool chua(int ma_xe) const {
        return (co1 && pt1.lay_ma_xe() == ma_xe) ||
               (co2 && pt2.lay_ma_xe() == ma_xe) ||
               (co3 && pt3.lay_ma_xe() == ma_xe);
    }

    void hien_thi() const {
        cout << "\nMa bai: " << ma_bai << " | Kich thuoc: " << kich_thuoc
             << " | So xe: " << so_xe() << "/" << suc_chua() << "\n";
        if (so_xe() == 0) cout << "  Bai chua co xe.\n";
        if (co1) { cout << "  "; pt1.hien_thi(); }
        if (co2) { cout << "  "; pt2.hien_thi(); }
        if (co3) { cout << "  "; pt3.hien_thi(); }
    }

    bool co_loai(string loai, int& dem, double& tong) const {
        loai = chuanHoa(loai);
        bool tim_thay = false;
        if (co1 && pt1.lay_loai_xe() == loai) { dem++; tong += pt1.tinh_phi(); tim_thay = true; }
        if (co2 && pt2.lay_loai_xe() == loai) { dem++; tong += pt2.tinh_phi(); tim_thay = true; }
        if (co3 && pt3.lay_loai_xe() == loai) { dem++; tong += pt3.tinh_phi(); tim_thay = true; }
        return tim_thay;
    }

    void liet_ke_loai(string loai) const {
        loai = chuanHoa(loai);
        if (co1 && pt1.lay_loai_xe() == loai) pt1.hien_thi();
        if (co2 && pt2.lay_loai_xe() == loai) pt2.hien_thi();
        if (co3 && pt3.lay_loai_xe() == loai) pt3.hien_thi();
    }
};

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

    bool ton_tai_bai(int ma) const {
        return (co1 && bai1.lay_ma() == ma) ||
               (co2 && bai2.lay_ma() == ma) ||
               (co3 && bai3.lay_ma() == ma);
    }

    bool ton_tai_xe(int ma) const {
        return (co1 && bai1.chua(ma)) || (co2 && bai2.chua(ma)) || (co3 && bai3.chua(ma));
    }

    void tao_bai() {
        int ma; char kt;
        cout << "Nhap ma bai: "; cin >> ma;
        if (ton_tai_bai(ma)) { cout << "Ma bai da ton tai!\n"; return; }
        cout << "Nhap kich thuoc (S/M/L): "; cin >> kt;
        kt = (char)toupper((unsigned char)kt);
        if (kt != 'S' && kt != 'M' && kt != 'L') { cout << "Kich thuoc khong hop le!\n"; return; }
        if (!co1) { bai1 = bai_xe(ma, kt); co1 = true; }
        else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; }
        else if (!co3) { bai3 = bai_xe(ma, kt); co3 = true; }
        else { cout << "He thong da du 3 bai!\n"; return; }
        cout << "Tao bai xe thanh cong!\n";
    }

    void them_xe() {
        int ma, gio, tg; string loai;
        cout << "Nhap ma xe: "; cin >> ma;
        if (ton_tai_xe(ma)) { cout << "Ma xe da ton tai!\n"; return; }
        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): "; cin >> loai;
        loai = chuanHoa(loai);
        if (loai != "CAR" && loai != "MOTORCYCLE" && loai != "BICYCLE") {
            cout << "Loai xe khong hop le!\n"; return;
        }
        cout << "Nhap gio vao (0-23): "; cin >> gio;
        cout << "Nhap thoi gian do (1-23): "; cin >> tg;
        if (gio < 0 || gio > 23 || tg < 1 || tg > 23) { cout << "Thoi gian khong hop le!\n"; return; }
        phuong_tien xe(ma, loai, gio, tg);
        if (co1 && bai1.them(xe)) { cout << "Da them xe vao bai " << bai1.lay_ma() << "\n"; return; }
        if (co2 && bai2.them(xe)) { cout << "Da them xe vao bai " << bai2.lay_ma() << "\n"; return; }
        if (co3 && bai3.them(xe)) { cout << "Da them xe vao bai " << bai3.lay_ma() << "\n"; return; }
        cout << "Khong con cho trong trong he thong!\n";
    }

    void xoa_bai() {
        int ma; cout << "Nhap ma bai can xoa: "; cin >> ma;
        if (co1 && bai1.lay_ma() == ma) { co1 = false; cout << "Da xoa bai xe.\n"; return; }
        if (co2 && bai2.lay_ma() == ma) { co2 = false; cout << "Da xoa bai xe.\n"; return; }
        if (co3 && bai3.lay_ma() == ma) { co3 = false; cout << "Da xoa bai xe.\n"; return; }
        cout << "Khong tim thay bai xe!\n";
    }

    void lay_xe() {
        int ma; cout << "Nhap ma xe can lay ra: "; cin >> ma;
        if (co1 && bai1.xoa(ma)) { cout << "Da lay xe ra khoi bai " << bai1.lay_ma() << "\n"; return; }
        if (co2 && bai2.xoa(ma)) { cout << "Da lay xe ra khoi bai " << bai2.lay_ma() << "\n"; return; }
        if (co3 && bai3.xoa(ma)) { cout << "Da lay xe ra khoi bai " << bai3.lay_ma() << "\n"; return; }
        cout << "Khong tim thay xe!\n";
    }

    void hien_thi_tat_ca() const {
        if (!co1 && !co2 && !co3) { cout << "He thong chua co bai xe.\n"; return; }
        if (co1) bai1.hien_thi();
        if (co2) bai2.hien_thi();
        if (co3) bai3.hien_thi();
    }

    void hien_thi_mot_bai() const {
        int ma; cout << "Nhap ma bai: "; cin >> ma;
        if (co1 && bai1.lay_ma() == ma) { bai1.hien_thi(); return; }
        if (co2 && bai2.lay_ma() == ma) { bai2.hien_thi(); return; }
        if (co3 && bai3.lay_ma() == ma) { bai3.hien_thi(); return; }
        cout << "Khong tim thay bai xe!\n";
    }

    void liet_ke_theo_loai() const {
        string loai; cout << "Nhap loai xe (Car/Motorcycle/Bicycle): "; cin >> loai;
        loai = chuanHoa(loai);
        if (loai != "CAR" && loai != "MOTORCYCLE" && loai != "BICYCLE") { cout << "Loai xe khong hop le!\n"; return; }
        bool tim = false;
        if (co1) { cout << "Bai " << bai1.lay_ma() << ":\n"; bai1.liet_ke_loai(loai); }
        if (co2) { cout << "Bai " << bai2.lay_ma() << ":\n"; bai2.liet_ke_loai(loai); }
        if (co3) { cout << "Bai " << bai3.lay_ma() << ":\n"; bai3.liet_ke_loai(loai); }
        int dem = 0; double tong = 0;
        if (co1) bai1.co_loai(loai, dem, tong);
        if (co2) bai2.co_loai(loai, dem, tong);
        if (co3) bai3.co_loai(loai, dem, tong);
        tim = dem > 0;
        if (!tim) cout << "Khong co xe thuoc loai nay.\n";
    }

    void bao_cao() const {
        const string loai1 = "CAR", loai2 = "MOTORCYCLE", loai3 = "BICYCLE";
        int dem; double tong;
        cout << fixed << setprecision(0);
        cout << "\n--- PHI TRUNG BINH THEO LOAI XE ---\n";
        dem = 0; tong = 0;
        if (co1) bai1.co_loai(loai1, dem, tong);
        if (co2) bai2.co_loai(loai1, dem, tong);
        if (co3) bai3.co_loai(loai1, dem, tong);
        cout << "Car: " << (dem ? tong / dem : 0) << " VND (" << dem << " xe)\n";
        dem = 0; tong = 0;
        if (co1) bai1.co_loai(loai2, dem, tong);
        if (co2) bai2.co_loai(loai2, dem, tong);
        if (co3) bai3.co_loai(loai2, dem, tong);
        cout << "Motorcycle: " << (dem ? tong / dem : 0) << " VND (" << dem << " xe)\n";
        dem = 0; tong = 0;
        if (co1) bai1.co_loai(loai3, dem, tong);
        if (co2) bai2.co_loai(loai3, dem, tong);
        if (co3) bai3.co_loai(loai3, dem, tong);
        cout << "Bicycle: " << (dem ? tong / dem : 0) << " VND (" << dem << " xe)\n";

        cout << "\n--- PHAN TICH THEO TUNG BAI ---\n";
        if (co1) { dem = 0; tong = 0; bai1.co_loai("CAR", dem, tong); bai1.co_loai("MOTORCYCLE", dem, tong); bai1.co_loai("BICYCLE", dem, tong); cout << "Bai " << bai1.lay_ma() << ": " << dem << " xe, tong phi " << tong << " VND\n"; }
        if (co2) { dem = 0; tong = 0; bai2.co_loai("CAR", dem, tong); bai2.co_loai("MOTORCYCLE", dem, tong); bai2.co_loai("BICYCLE", dem, tong); cout << "Bai " << bai2.lay_ma() << ": " << dem << " xe, tong phi " << tong << " VND\n"; }
        if (co3) { dem = 0; tong = 0; bai3.co_loai("CAR", dem, tong); bai3.co_loai("MOTORCYCLE", dem, tong); bai3.co_loai("BICYCLE", dem, tong); cout << "Bai " << bai3.lay_ma() << ": " << dem << " xe, tong phi " << tong << " VND\n"; }
    }

public:
    SystemInterface() : co1(false), co2(false), co3(false) {}

    void runMenu() {
        int chon;
        do {
            cout << "\n========== QUAN LY BAI DO XE ==========\n";
            cout << "1. Tao bai xe moi\n";
            cout << "2. Them xe vao bai\n";
            cout << "3. Xoa bai xe\n";
            cout << "4. Lay xe ra khoi bai\n";
            cout << "5. Hien thi tat ca bai xe\n";
            cout << "6. Hien thi xe theo bai\n";
            cout << "7. Liet ke xe theo loai\n";
            cout << "8. Bao cao phi do xe trung binh\n";
            cout << "0. Thoat\n";
            cout << "Lua chon: "; cin >> chon;

            switch (chon) {
            case 1: tao_bai(); break;
            case 2: them_xe(); break;
            case 3: xoa_bai(); break;
            case 4: lay_xe(); break;
            case 5: hien_thi_tat_ca(); break;
            case 6: hien_thi_mot_bai(); break;
            case 7: liet_ke_theo_loai(); break;
            case 8: bao_cao(); break;
            case 0: cout << "Ket thuc chuong trinh!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
            }
        } while (chon != 0);
    }
};

int main() {
    SystemInterface ql;
    ql.runMenu();
    return 0;
}
