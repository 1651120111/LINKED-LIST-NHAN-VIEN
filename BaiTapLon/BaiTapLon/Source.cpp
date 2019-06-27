#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <math.h>
using namespace std;

struct date
{
	int ngay;
	int thang;
	int nam;
};
typedef struct date DATE;

struct nhanvien
{
	string hoten;
	string chucvu;
	DATE ngaysinh;
	float hsl;
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
void KhoiTaoDanhSach(LIST &l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

NODE *KhoiTaoNode(NHANVIEN x) {
	NODE *p = new NODE;
	if (p == NULL)
	{
		cout << "\n that bai";
		return NULL;
	}
	p->data = x;
	p->pNext = NULL;
	return p;
}

void ThemDau(LIST &l, NODE *p) {
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

void ThemCuoi(LIST &l, NODE *p) {
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

void DocDate(ifstream &filein, DATE &date) {
	filein >> date.ngay;
	filein.seekg(1, 1);
	filein >> date.thang;
	filein.seekg(1, 1);
	filein >> date.nam;
}

void DocThongTin1NhanVien(ifstream &filein, NHANVIEN &nv) {
	getline(filein, nv.hoten, ',');
	filein.seekg(1, 1);
	getline(filein, nv.chucvu, ',');
	filein.seekg(1, 1);
	DocDate(filein, nv.ngaysinh);
	filein.seekg(2, 1);
	filein >> nv.hsl;
	//Đọc kĩ tự xuống dòng
	string temp;
	getline(filein, temp);
}
void DocDanhSachNhanVien(ifstream &filein, LIST &l) {
	while (!filein.eof())
	{
		NHANVIEN nv;
		DocThongTin1NhanVien(filein, nv);
		NODE *p = KhoiTaoNode(nv);
		ThemCuoi(l, p);

	}
}
//lưu 1 NV vào file
void LuuThongTin1NhanVien(ofstream &fileout, NHANVIEN nv) {
	fileout << nv.hoten << ", ";
	fileout << nv.chucvu << ", ";
	fileout << nv.ngaysinh.ngay << "/" << nv.ngaysinh.thang << "/" << nv.ngaysinh.nam << ", ";
	fileout << nv.hsl;

}
void Xuat(NHANVIEN nv) {
	cout << "\n Ho Ten: " << nv.hoten;
	cout << "\n Chuc Vu: " << nv.chucvu;
	cout << "\n Ngay sinh: " << nv.ngaysinh.ngay << "/" << nv.ngaysinh.thang << "/" << nv.ngaysinh.nam;
	cout << "\n He so luong: " << nv.hsl;

}
void XuatDanhSachNhanVien(LIST l) {
	int dem = 1;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\n\t\t NHAN VIEN THU " << dem++;
		Xuat(k->data);
	}
}
void GiaiPhongVungNho(LIST &l) {
	NODE *k = NULL;
	while (l.pHead != NULL)
	{
		k = l.pHead;
		l.pHead = l.pHead->pNext;
		delete k;
	}
}
//so sanh date
//bool SoSanhNgay(date &ngay1,date &ngay2) {
//	if (ngay1.nam < ngay2.nam) return true;
//	if (ngay1.thang < ngay2.thang) return true;
//	if (ngay1.ngay < ngay2.ngay) return true;
//	return false;
//}
//CÁC HÀM BIẾN ĐỔI
int CompareStr(string s1, string s2)
{
	if (s1 == s2) {
		return 1;
	}
	else
	{
		return 0;
	}
}
string UpperToLower(string str) {
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A'&&str[i] <= 'Z')
		{
			str[i] = str[i] + 32;
		}
		++i;
	}
	return str;
}
int StrToInt(string str) {
	int num = 0;
	int size = str.size();
	for (int i = 0; i < size; i++) {
		num *= 10;
		num += str[i] - '0';
	}
	return num;
}
float StrToFloat(string str) {
	int vitridaucham = 0;
	float ketqua = 0.0;
	int length = str.length();
	for (int i = 0; i < length; i++) {
		if (str[i] == '.') {
			vitridaucham = str.size() - i - 1;

		}
		else
		{
			ketqua = ketqua * 10.0f;
			ketqua += str[i] - '0';
		}
	}
	while (vitridaucham--)
	{
		ketqua /= 10.0f;

	}

	return ketqua;

}
int CheckInterger(string a)
{
	int i = 0;
	while (a[i] != NULL)
	{
		if ('0' > a[i] || a[i] > '9')
			return 0;
		i++;
	}
	return 1;
}
bool isFloat(string s) {
	istringstream iss(s);
	float dummy;
	iss >> noskipws >> dummy;
	return iss && iss.eof();     //Kết quả trả về đến bool
}

bool SoSanhDate(date &date1, date &date2) {
	if (date1.nam > date2.nam) return true;
	else if (date1.nam == date2.nam)
	{
		if (date1.thang > date2.thang) {
			return true;
		}
		else if (date1.thang == date2.thang) {
			if (date1.ngay > date2.ngay) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
string LayTen(string w, int s, int e) {
	int i, j;
	int size = 0; size = (e - s);

	char *ten = new char[size + 1];

	for (i = 0, j = s; j < e; i++, j++)
	{
		ten[i] = w[j];
	}
	ten[i] = '\0';

	return ten;
}

int LengthStr(string s) {
	return s.length();
}
int ViTri(string s) {
	int vitri;
	int length = s.length();
	for (int i = 0; i <= length; i++) {
		if (s[i] == ' ') {
			vitri = i + 1;


		}
	}
	return vitri;

}
string TachTen(string ten) {
	int i;
	for (i = ten.length() - 1; i >= 0; i--)
		if (ten[i] == ' ') {
			break;
		}
	return LayTen(ten,ViTri(ten),LengthStr(ten));
}
//Hàm Compare trả về 1
int TraVeChucVu(string s) {

	string  s1 = "Nhan vien", s2 = "Quan li", s3 = "Giam doc", s4 = "Tong giam doc";
	if (CompareStr(UpperToLower(s), UpperToLower(s1))) {
		return  1;
	}
	else if (CompareStr(UpperToLower(s), UpperToLower(s2))) {
		return  2;
	}
	else if (CompareStr(UpperToLower(s), UpperToLower(s3))) {
		return 3;
	}
	else if (CompareStr(UpperToLower(s), UpperToLower(s4))) {
		return 4;
	}
	else {
		return 0;
	}
}

//KẾT THÚC BIẾN ĐỔI THÊM

void HoanViNode(NHANVIEN &x, NHANVIEN &y) {
	NHANVIEN tam = x;
	x = y;
	y = tam;
}
//so sanh theo ngày
void SapXepTheoNgay(LIST &l) {
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		for (NODE *h = k->pNext; h != NULL; h = h->pNext) {
			if (SoSanhDate(k->data.ngaysinh, h->data.ngaysinh))
			{
				HoanViNode(k->data, h->data);
			}

		}
	}
}
//so sanh theo chức vụ tăng dần
void SapXepTheoChucVu(LIST &l) {
	int dem = 1;	int tam = 1;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{	
		//cout << "So tra ve k lan "<< dem++ <<": "<< TraVeChucVu(k->data.chucvu) << endl;
		for (NODE *h = k->pNext; h != NULL; h = h->pNext) {	
			//cout << "So tra ve h lan " << tam++ << ": " << TraVeChucVu(h->data.chucvu) << endl;
			if (TraVeChucVu(k->data.chucvu) < TraVeChucVu(h->data.chucvu))
			{
				HoanViNode(k->data, h->data);
			}
		}
	}
}
//so sánh theo lương
void SapXepTheoHSL(LIST &l) {

	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		for (NODE *h = k->pNext; h != NULL; h = h->pNext) {
			if (k->data.hsl > h->data.hsl)
			{
				HoanViNode(k->data, h->data);
			}
		}
	}
}
//chèn nhân viên
void Nhap(NHANVIEN &nv)
{
	cin.ignore(); // thêm vào để xoá bộ nhớ đệm, tránh bị trôi lệnh
	cout << "Nhap ho ten nhan vien: ";
	getline(cin, nv.hoten);
	fflush(stdin);
	cout << "Nhap chuc vu: ";
	getline(cin, nv.chucvu);
	fflush(stdin);
	cout << "\n NHAP NGAY THANG NAM SINH ";
	do {
		cout << "\nNhap ngay sinh: ";
		cin >> nv.ngaysinh.ngay;
		fflush(stdin);
	} while (nv.ngaysinh.ngay > 31 || nv.ngaysinh.ngay < 1);
	do {
		cout << "Nhap thang sinh: ";
		cin >> nv.ngaysinh.thang;
		fflush(stdin);
	} while (nv.ngaysinh.thang > 12 || nv.ngaysinh.thang < 1);
	do {
		cout << "Nhap nam sinh: ";
		cin >> nv.ngaysinh.nam;
		fflush(stdin);
	} while (nv.ngaysinh.nam > 2004 || nv.ngaysinh.nam < 1930);
	cout << "Nhap he so luong: ";
	cin >> nv.hsl;
	
}

void KhoiTaoNhanVien(LIST &l) {
	NHANVIEN nv;
	cout << "NHAP THONG TIN NHAN VIEN CAN THEM \n";
	Nhap(nv);
	NODE *p = KhoiTaoNode(nv);
	ThemCuoi(l, p);

}

//xoa
void XoaDau(LIST &l) {
	if (l.pHead == NULL) {
		return;
	}
	NODE *p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
}
void XoaCuoi(LIST &l) {
	if (l.pHead == NULL) {
		return;
	}
	if (l.pHead->pNext == NULL) {
		XoaDau(l);
		return;
	}
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->pNext == l.pTail) {
			delete l.pTail;
			k->pNext = NULL;
			l.pTail = k;
			return;
		}
	}
}

//CÁC  HÀM XÓA
void XoaTheoNam(LIST &l, string x) {
	if (l.pHead == NULL) {
		cout << "Danh sach rong khong the xoa nua ! ";
		return;
	}
	int namoi = StrToInt(x);
	if (l.pHead != NULL) {
		if (l.pHead->data.ngaysinh.nam == namoi) {
			XoaDau(l);
			return;
		}
	}
	int dem = 0;
	NODE *q = l.pHead;
	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
	{
		if (k->data.ngaysinh.nam == namoi) {
			NODE *thimang = k;
			q->pNext = k->pNext;
			k = q;
			delete thimang;
			dem=1;
		}
		q = k; //gán node g trỏ đến node k
	}
	if (dem == 1) {
		cout << "Da xoa thanh cong! \n";
	}
}
void XoaTheoHSL(LIST &l, string x) {
	if (l.pHead == NULL) {
		cout << "Danh sach rong khong the xoa nua ! ";
		return;
	}
	float namoi = StrToFloat(x);
	if (l.pHead != NULL) {
		if (l.pHead->data.ngaysinh.nam == namoi) {
			XoaDau(l);
			return;
		}
	}

	NODE *q = l.pHead;
	
	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
	{
		if (k->data.ngaysinh.nam == namoi) {
			NODE *thimang = k;
			q->pNext = k->pNext;
			k = q;
			delete thimang;
		}
		q = k; //gán node g trỏ đến node k
	}
}
void XoaTheoTen(LIST &l, string ten) {
	if (l.pHead == NULL) {
		cout << "Danh sach rong khong the xoa nua ! ";
		return;
	}
	if (l.pHead != NULL) {
		string tentach = TachTen(l.pHead->data.hoten);
		if (CompareStr(UpperToLower(tentach), UpperToLower(ten))) {
			XoaDau(l);
			return;
		}
	}
	NODE *g = l.pHead;
	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
	{
		string tentach = TachTen(k->data.hoten);
		if (CompareStr(UpperToLower(tentach), UpperToLower(ten))) {
			NODE *thimang = k;
			g->pNext = k->pNext;
			k = g;
			delete thimang;
		}
		g = k; //gán node g trỏ đến node k
	}
}
void XoaTheoChucVu(LIST &l, string cv) {
	if (l.pHead == NULL) {
		cout << "Danh sach rong khong the xoa nua ! ";
		return;
	}
	if (l.pHead != NULL) {
		string tentach = TachTen(l.pHead->data.hoten);
		if (CompareStr(UpperToLower(tentach), UpperToLower(cv))) {
			XoaDau(l);
			return;
		}
	}
	NODE *g = l.pHead;
	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
	{
		string tentach = TachTen(k->data.hoten);
		if (CompareStr(UpperToLower(tentach), UpperToLower(cv))) {
			NODE *thimang = k;
			g->pNext = k->pNext;
			k = g;
			delete thimang;
		}
		g = k; //gán node g trỏ đến node k
	}
}
void XoaNhanVien(LIST &l) {
	cin.ignore();
	string tukhoa;
	cout << "Nhap du lieu muon xoa: ";
	getline(cin, tukhoa);
	if (CheckInterger(tukhoa)) {
		XoaTheoNam(l, tukhoa);
	}
	else{
		XoaTheoTen(l, tukhoa);
	}
}

//CÁC HÀM TÌM KIẾM
void TimKiemNhanVienTheoTen(LIST l, string ten) {
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		string tennv = TachTen(k->data.hoten);
		if (CompareStr(UpperToLower(ten),UpperToLower(tennv))) {
			Xuat(k->data);
			cout << endl << endl;
		
		}
	}
}
void TimKiemNhanVienTheoChucVu(LIST l, string cv) {

	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		string cvnv = k->data.chucvu; // gán dữ liệu vào chức vụ nhân viên
		if (CompareStr(UpperToLower(cv),UpperToLower(cvnv))) {
			Xuat(k->data);
			cout << endl << endl;
		
		}
	}

}
void TimKiemNhanVienTheoHSL(LIST l, string hsl) {
	float namoi = StrToFloat(hsl);
	int dem = 0;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext) {
		float hslmoi = k->data.hsl;
		if (hslmoi == namoi) {
			Xuat(k->data);
			cout << endl;
			dem++;

		}
	}
	if (dem == 0) {
		cout << "\nKhong tim thay!" << endl;
		cout << "Vui long nhap thong tin can tim lai." << endl << endl;
	}
}
void TimKiemNhanVienTheoNam(LIST l, string nam) {
	int namoi = StrToInt(nam);
	int dem=0;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext) {
		int namsan = k->data.ngaysinh.nam;
		if (namsan == namoi) {//chuyển thành int
			Xuat(k->data);
			cout << endl;
			dem++;
		}
		
	}	
	if (dem == 0) {
		cout << "\nKhong tim thay!" << endl;
		cout << "Vui long nhap thong tin can tim lai." << endl << endl;
	}
}
void TimKiemNhanVien(LIST l) {
	cin.ignore();
	string tukhoa;
	cout << "\nNhap tu khoa can tim ve nhan vien:";
	getline(cin, tukhoa);

	if (CheckInterger(tukhoa)) {
		TimKiemNhanVienTheoNam(l, tukhoa);

	}
	else if (isFloat(tukhoa)) {
		TimKiemNhanVienTheoHSL(l, tukhoa);
	}
	else {
		//if (_stricmp((char *)tukhoa.c_str(), (char *)ten1.c_str()) || _stricmp((char *)tukhoa.c_str(), (char *)ten2.c_str()) || _stricmp((char *)tukhoa.c_str(), (char *)ten3.c_str()) || _stricmp((char *)tukhoa.c_str(), (char *)ten4.c_str())) {
		TimKiemNhanVienTheoChucVu(l, tukhoa);
		//}
		//else
		//{
		TimKiemNhanVienTheoTen(l, tukhoa);
		//}
	}
}

void LuuDanhSachNhanVien(LIST l) {
	ofstream fileout;
	fileout.open("XUATNHANVIEN.txt", ios::out);
	for (NODE *k = l.pHead; k != NULL; k = k->pNext) {
		LuuThongTin1NhanVien(fileout, k->data);
		fileout << endl;
	}
	fileout.close();
}
//void LuuDanhSachNhanVienSX(LIST l) {
//	ofstream fileout;
//	fileout.open("NHANVIEN1.txt", ios::out);
//	SapXepTheoNgay(l);
//	for (NODE *k = l.pHead; k != NULL; k = k->pNext) {
//		
//		LuuThongTin1NhanVien(fileout, k->data);
//		fileout << endl;
//	}
//	fileout.close();
//}
//void XuatTheoForm(NHANVIEN nv) {
//	
//
//	cout << left << setw(25) << nv.hoten << "\t";
//	cout << left << setw(18) << nv.chucvu<<"\t";
//	cout << left << setw(0) << nv.ngaysinh.ngay << "/" << nv.ngaysinh.thang << "/" << nv.ngaysinh.nam<<"\t";
//	cout << left << setw(11) << nv.hsl <<"\t";
//	cout << endl;
//
//}
//void XuatDanhSachNhanVien1(LIST &l) {
//	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
//	{
//		XuatTheoForm(k->data);
//	}
//}
void TroLai()
{
	cout << "Nhan de tro lai menu";
	while (true) {
		fflush(stdin);
		char key;
		cin >> key;
		if (key == 10)
		{
			break;
		}
		else { continue; }
	}
}



void menu() {
	NHANVIEN nv;
	LIST l;
	KhoiTaoDanhSach(l);
	while (true)
	{
	menu:
		system("cls");
		cout << "\n\n\t\t\t************************** MENU **************************";
		cout << "\n\t\t\t*\t\t\t\t\t\t\t *";
		cout << "\n\t\t\t*\t\t1. Doc file text nhan vien \t\t *";
		cout << "\n\t\t\t*\t\t2. Sap xep nhan vien \t\t\t *";
		cout << "\n\t\t\t*\t\t3. Chen mot nhan vien \t\t\t *";
		cout << "\n\t\t\t*\t\t4. Xoa nhan vien \t\t\t *";
		cout << "\n\t\t\t*\t\t5. Tim kiem nhan vien \t\t\t *"; 
		cout << "\n\t\t\t*\t\t6. Xem danh sach nhan vien \t\t *";
		cout << "\n\t\t\t*\t\t7. Xuat ds nhan vien ra TEXT \t\t *";
		cout << "\n\t\t\t*\t\t0. Lam gon hien thi  \t\t\t *";
		cout << "\n\t\t\t*\t\t\t\t\t\t\t *";
		cout << "\n\t\t\t************************** END ***************************";
		while (true)
		{
			cout << "\nNhap lua chon: ";
			int luachon;
			cin >> luachon;
			switch (luachon)
			{
			case 1:
			{
				ifstream filein;
				filein.open("NHANVIEN.txt", ios::in);
				DocDanhSachNhanVien(filein, l);
				filein.close();
				cout << "Doc thanh cong.Vui long chon xem danh sach";
				break;
			}
			case 2:
			{
				system("cls");
				while (true) {
					cout << "\n\n\t\t\t****************** SAP XEP THEO TIEU CHI *****************";
					cout << "\n\t\t\t*\t\t\t\t\t\t\t *";
					cout << "\n\t\t\t*\t\t1. Ngay thang nam sinh \t\t\t *";
					cout << "\n\t\t\t*\t\t2. Theo chuc vu \t\t\t *";
					cout << "\n\t\t\t*\t\t3. Theo he so luong \t\t\t *";
					cout << "\n\t\t\t*\t\t0. Tro ve menu \t\t\t\t *";
					cout << "\n\t\t\t*\t\t\t\t\t\t\t *";
					cout << "\n\t\t\t************************** END ***************************";
					cout << endl;
					while (true) {
						int luachon;
						cout << "Nhap lua chon: ";
						cin >> luachon;

						switch (luachon)
						{
						case 0:
						{
							goto menu;
						}
						case 1:
						{
							SapXepTheoNgay(l);
							cout << "\t\tDanh sach sau khi sap xep la: ";
							XuatDanhSachNhanVien(l);
							cout << endl;
							system("pause");
							goto menu;
							break;
						}
						//Cần sắp xếp lại chức vụ
						case 2:
						{
							SapXepTheoChucVu(l);
							if (l.pHead == NULL) {
								cout << "Danh sach dang rong. Vui long them hoac doc file! ";
							}
							cout << "\t\tDanh sach sau khi sap xep theo chuc vu la: ";
							XuatDanhSachNhanVien(l);
							cout << endl;
							system("pause");
							goto menu;
							break;
						}
						case 3:
						{
							SapXepTheoHSL(l);
							cout << "\t\tDanh sach sau khi sap xep theo he so luong la: ";
							XuatDanhSachNhanVien(l);
							cout << endl;
							system("pause");
							goto menu;
							break;
						}
						default:
						{
							system("cls");
							cout << "Nhap lai.Ban nhap sai roi !";
							break;
						}
						}
					}
				}
			 }
			case 3:
			{
				system("cls");
				while (true)
				{
					cout << "\n\n\t\t\t*********************** CHEN THEO TIEU CHI ***********************";
					cout << "\n\t\t\t*\t\t\t\t\t\t\t\t *";
					cout << "\n\t                *                  1. Theo Ngay thang nam sinh \t\t\t *";
					cout << "\n\t                *                  2. Theo chuc vu \t\t\t\t *";
					cout << "\n\t                *                  3. Theo he so luong \t\t\t\t *";
					cout << "\n\t                *                  0. Quay ve \t\t\t\t\t *";
					cout << "\n\t\t\t*\t\t\t\t\t\t\t\t *\n\t\t\t*\t\t************ End ************\t\t\t *";
					while (true)
					{
						cout << "\nNhap lua chon: ";
						int luachon;
						cin >> luachon;

						switch (luachon)
						{
						case 0:
						{
							goto menu;
						}
						case 1:
						{
							KhoiTaoNhanVien(l);
							cout << "\n\n\t\t\t=========== Da them thanh cong =========== ";
							SapXepTheoNgay(l);
							cout << "\n\n\t\t=========== Danh sach nhan vien sau  khi sap xep theo ngay thang nam sinh ===========";
							XuatDanhSachNhanVien(l);
							system("pause");
							goto menu;
							break;
						}
						case 2:
						{
							KhoiTaoNhanVien(l);
							cout << "\n\n\t\t\t=========== Da them thanh cong =========== ";
							SapXepTheoChucVu(l);
							cout << "\n\n\t\t=========== Danh sach nhan vien sau  khi sap xep theo chuc vu ===========";
							XuatDanhSachNhanVien(l);
							system("pause");
							goto menu;
							break;
						}
						case 3:
						{
							KhoiTaoNhanVien(l);
							cout << "\n\n\t\t\t=========== Da them thanh cong =========== ";
							SapXepTheoHSL(l);
							cout << "\n\n\t\t=========== Danh sach nhan vien sau  khi sap xep theo he so luong ===========";
							XuatDanhSachNhanVien(l);
							cout << "\n";
							system("pause");
							goto menu;
							break;
						}
						default: {
							system("cls");
							cout << "Nhap lai !";
							system("pause");
							break;
						}
						}
					}
					TroLai();
				}
				break;
			}
			case 4:
			{
				XoaNhanVien(l);
				system("pause");
				break;
			}
			case 5:
			{

				TimKiemNhanVien(l);
				system("pause");
				break;
			}
			case 6:
			{
				//Hiển thị danh sách các nhân viên
				XuatDanhSachNhanVien(l);
				cout << "\n";
				system("pause");
				break;
			}
			case 7:
			{
				LuuDanhSachNhanVien(l);
				cout << "Xuat file thanh cong";
				system("pause");
				break;

			}
			case 0: {
				system("cls");
				goto menu;
				break;

			}
			default:
				break;
			}
		}
	}
}
int main() {
	
	menu();
	/*const char* s = "hoa thoi";
	int l = s.length();
	char *n=subString(s ,4,l);
	cout << "ten cat: "<<n;*/
	//string s;
	//cout << "Nhap vao chuoi:";
	//getline(cin, s);
	//cout<<"Ten da tach : "<<TachTen(s);
	
	//string s1 = "Quan Ly";
	//string s2 = "Nhan Vien";
	//cout << "So la: " << TraVeChucVu(s2)<<endl;
	//cout << "So la: " << TraVeChucVu(s1)<<endl;
	//if (TraVeChucVu(s1) > TraVeChucVu(s2)) {
	//	cout << "nguoc roi";
	//}
	//else
	//{
	//	cout << "dung chieu";
	//}

	//string s2 = "toi LA";
	//cout<< HoaSangThuong(s1)<<endl; cout<<HoaSangThuong(s2)<<endl;
	// if (ComStr(HoaSangThuong(s1),HoaSangThuong( s2))==1) {
	//	 cout << "2 chuoi bang nhau";
	//}

	//NHANVIEN nv;
	//LIST l;
	//KhoiTaoDanhSach(l);
	///*KhoiTaoNhanVien(l);
	//KhoiTaoNhanVien(l);
	//KhoiTaoNhanVien(l);*/


	//ifstream filein;
	//
	//filein.open("NHANVIEN.txt", ios::in);
	//DocDanhSachNhanVien(filein, l);
	//XuatDanhSachNhanVien(l);
	///*string tukhoa;
	//cout << "nhap tu khoa: ";
	//getline(cin, tukhoa);*/
	//TimKiemNhanVien(l);
	//
	///*cout << left << setw(30) << "HO TEN" << "\t" << left << setw(18) << "CHUC VU" << "\t" << left << setw(15) << "NGAY SINH" << "\t" << left << setw(11) << "HE SO LUONG"<<endl;
	//XuatDanhSachNhanVien1(l);*/
	///*cout << "\n\n\t\tNhap tu khoa: ";
	//getline(cin, tukhoa);
	//TimKiemNhanVienTheoNam(l, tukhoa);

	//GiaiPhongVungNho(l);
	//filein.close();*/
	///*string a;
	//cout << "Nhap tu khoa can tim kiem: ";
	//getline(cin, a);
	//if ((a >= "A") && (a <= "Z"))
	//{
	//	int k = a + 32;
	//	cout << " The upper case character corresponding to " << a << "  is ..." << char(k);
	//}
	//else if ((a >= 'a') && (a <= 'z'))
	//{
	//	int k = int(a) - 32;
	//	cout << " The lower case character corresponding to " << a << " is  : " << char(k);
	//}
	//else cout << " number  " << a;*/
	system("pause");
	return 0;
}