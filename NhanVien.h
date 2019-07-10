#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <iomanip> 
#include <string>
#include <fstream>
#include <conio.h>
#include <sstream>
using namespace std;

struct date
{
	string ngay;
	string thang;
	string nam;
};
typedef struct date DATE;

struct nhanvien
{
	string hoten;
	string chucvu;
	DATE ngaysinh;
	string hsl;
};
typedef struct nhanvien NHANVIEN;

struct  node
{
	NHANVIEN data;
	struct node *pNext;
};
typedef struct node NODE;

struct list
{
	NODE *pHead;
	NODE *pTail;
};
typedef struct list LIST;

bool NamNhuan(int year);
int SoNgayTrongThang(int day, int Month, int Year);
//void Test();

void KhoiTaoDanhSach(LIST &l);
NODE *KhoiTaoNode(NHANVIEN x);
void ThemDau(LIST &l, NODE *p);
void ThemCuoi(LIST &l, NODE *p);
int SoSanhTen(string s1, string s2);

//mới thêm
void ThemNhanVien(LIST &l, int status);
void SapXepTheoTen(LIST &l);
void DocDate(ifstream &filein, DATE &date);
void DocThongTin1NhanVien(ifstream &filein, NHANVIEN &nv);
void DocDanhSachNhanVien(ifstream &filein, LIST &l);
void LuuThongTin1NhanVien(ofstream &fileout, NHANVIEN nv);
void Xuat(NHANVIEN nv);
void XuatDanhSachNhanVien(LIST l);
void GiaiPhongVungNho(LIST &l);
int CompareStr(string s1, string s2);
string UpperToLower(string str);
int StrToInt(string str);
float StrToFloat(string str);
int CheckInterger(string a);
bool isFloat(string s);
bool SoSanhDate(date &date1, date &date2);
string LayTen(string w, int s, int e);
int LengthStr(string s);
int ViTri(string s);
string TachTen(string ten);
//int TraVeChucVu(string s);
void HoanViNode(NHANVIEN &x, NHANVIEN &y);
void SapXepTheoNgay(LIST &l);
void SapXepTheoChucVu(LIST &l);
void SapXepTheoHSL(LIST &l);
void Nhap(NHANVIEN &nv);
void KhoiTaoNhanVien(LIST &l);
void XoaDau(LIST &l);
void XoaCuoi(LIST &l);
//void test(LIST &l, string key);
void XoaTheoChucVu(LIST &l, string key);
void XoaTheoHSL(LIST &l, string key);
void XoaTheoNam(LIST &l, string x);
void XoaTheoTen(LIST &l, string ten);
void XoaNhanVien(LIST &l);
void TimKiemNhanVienTheoTen(LIST l, string ten);
void TimKiemNhanVienTheoChucVu(LIST l, string cv);
void TimKiemNhanVienTheoHSL(LIST l, string hsl);
void TimKiemNhanVienTheoNam(LIST l, string nam);
void TimKiemNhanVien(LIST l);
void LuuDanhSachNhanVien(LIST l);
void TroLai();
void menu();