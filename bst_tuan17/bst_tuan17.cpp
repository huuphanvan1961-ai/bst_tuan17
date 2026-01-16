//Bài 1:
#include <iostream>
#include <string>
using namespace std;
struct MucLuc {
    int index;
    string tenMuc;
    int soTrang;
    int tongSoTrang;
    MucLuc* mucConDau;
    MucLuc* mucCungCap;

    MucLuc(int i, string t, int p) {
        index = i;
        tenMuc = t;
        soTrang = p;
        tongSoTrang = p;
        mucConDau = NULL;
        mucCungCap = NULL;
    }
};

int tinhTongSoTrang(MucLuc* muc) {
    if (muc == NULL) return 0;
    int tong = muc->soTrang;
    MucLuc* mucCon = muc->mucConDau;
    while (mucCon) {
        tong += tinhTongSoTrang(mucCon);
        mucCon = mucCon->mucCungCap;
    }
    muc->tongSoTrang = tong;
    return tong;
}

int demSoChuong(MucLuc* sach) {
    int dem = 0;
    MucLuc* chuong = sach->mucConDau;
    while (chuong) {
        dem++;
        chuong = chuong->mucCungCap;
    }
    return dem;
}

MucLuc* timChuongDaiNhat(MucLuc* sach) {
    tinhTongSoTrang(sach);
    MucLuc* ketQua = NULL;
    int maxTrang = -1;
    MucLuc* chuong = sach->mucConDau;
    while (chuong) {
        if (chuong->tongSoTrang > maxTrang) {
            maxTrang = chuong->tongSoTrang;
            ketQua = chuong;
        }
        chuong = chuong->mucCungCap;
    }
    return ketQua;
}

MucLuc* timMuc(MucLuc* muc, int id) {
    if (muc == NULL) return NULL;
    if (muc->index == id) return muc;
    MucLuc* mucCon = muc->mucConDau;
    while (mucCon) {
        MucLuc* kq = timMuc(mucCon, id);
        if (kq) return kq;
        mucCon = mucCon->mucCungCap;
    }
    return NULL;
}

void xoaCayMuc(MucLuc* muc) {
    if (muc == NULL) return;
    xoaCayMuc(muc->mucConDau);
    xoaCayMuc(muc->mucCungCap);
    delete muc;
}

bool xoaMucTheoIndex(MucLuc*& sach, int id) {
    if (sach == NULL) return false;
    if (sach->index == id) {
        xoaCayMuc(sach);
        sach = NULL;
        return true;
    }

    MucLuc* mucCha = sach;
    MucLuc* mucCon = sach->mucConDau;
    MucLuc* mucTruoc = NULL;

    while (mucCon) {
        if (mucCon->index == id) {
            if (mucTruoc == NULL)
                mucCha->mucConDau = mucCon->mucCungCap;
            else
                mucTruoc->mucCungCap = mucCon->mucCungCap;
            xoaCayMuc(mucCon);
            tinhTongSoTrang(sach);
            return true;
        }
        if (xoaMucTheoIndex(mucCon, id)) return true;
        mucTruoc = mucCon;
        mucCon = mucCon->mucCungCap;
    }
    return false;
}

void inDeMucChuong(MucLuc* chuong, int cap = 0) {
    if (chuong == NULL) return;
    for (int i = 0; i < cap; i++) cout << "  ";
    cout << chuong->index << " - " << chuong->tenMuc
        << " (" << chuong->tongSoTrang << ")\n";
    inDeMucChuong(chuong->mucConDau, cap + 1);
    inDeMucChuong(chuong->mucCungCap, cap);
}

//Bài 2:

struct NutNhiPhan {
    int index;
    string tenMuc;
    NutNhiPhan* trai;
    NutNhiPhan* phai;

    NutNhiPhan(int i, string t) {
        index = i;
        tenMuc = t;
        trai = phai = NULL;
    }
};

bool kiemTraBanCopy(NutNhiPhan* a, NutNhiPhan* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (a->index != b->index) return false;
    if (a->tenMuc != b->tenMuc) return false;
    return kiemTraBanCopy(a->trai, b->trai) &&
        kiemTraBanCopy(a->phai, b->phai);
}
int main() {
    MucLuc* sach = new MucLuc(0, "Muc luc sach", 0);

    MucLuc* chuong1 = new MucLuc(1, "Chuong 1", 5);
    MucLuc* chuong2 = new MucLuc(2, "Chuong 2", 8);
    MucLuc* chuong3 = new MucLuc(3, "Chuong 3", 10);

    sach->mucConDau = chuong1;
    chuong1->mucCungCap = chuong2;
    chuong2->mucCungCap = chuong3;

    MucLuc* muc11 = new MucLuc(11, "Muc 1.1", 4);
    MucLuc* muc12 = new MucLuc(12, "Muc 1.2", 6);
    chuong1->mucConDau = muc11;
    muc11->mucCungCap = muc12;

    MucLuc* muc31 = new MucLuc(31, "Muc 3.1", 3);
    chuong3->mucConDau = muc31;

    tinhTongSoTrang(sach);

    cout << "So chuong cua cuon sach: " << demSoChuong(sach) << endl;

    MucLuc* chuongDaiNhat = timChuongDaiNhat(sach);
    cout << "Chuong dai nhat: " << chuongDaiNhat->tenMuc << endl;

    cout << "\nDe muc Chuong 1:\n";
    inDeMucChuong(chuong1);

    xoaMucTheoIndex(sach, 12);
    cout << "\nSau khi xoa muc 1.2:\n";
    inDeMucChuong(chuong1);

    NutNhiPhan* sachA = new NutNhiPhan(1, "Chuong 1");
    sachA->trai = new NutNhiPhan(11, "Muc 1.1");
    sachA->phai = new NutNhiPhan(12, "Muc 1.2");

    NutNhiPhan* sachB = new NutNhiPhan(1, "Chuong 1");
    sachB->trai = new NutNhiPhan(11, "Muc 1.1");
    sachB->phai = new NutNhiPhan(12, "Muc 1.2");

    if (kiemTraBanCopy(sachA, sachB))
        cout << "\nHai cuon sach la ban copy cua nhau\n";
    else
        cout << "\nHai cuon sach khong phai ban copy\n";

    return 0;
}