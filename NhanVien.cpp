#include "NhanVien.h";
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
	getline(filein , date.ngay,'/');
	getline(filein, date.thang, '/');
	getline(filein, date.nam,',');
}

void DocThongTin1NhanVien(ifstream &filein, NHANVIEN &nv) {
	
	getline(filein, nv.hoten, ',');
	filein.seekg(1, 1);
	getline(filein, nv.chucvu, ',');
	filein.seekg(1, 1);
	DocDate(filein, nv.ngaysinh);
	filein.seekg(1, 1);
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
		cout << left << setw(22) << nv.hoten << "\t";
		cout << left << setw(18) << nv.chucvu << "\t";
		cout << right<<  setw(2)<< nv.ngaysinh.ngay << "/"<< right<< setw(2) << nv.ngaysinh.thang <<  "/" << setw(4)<< nv.ngaysinh.nam << "\t   ";
		cout << left << setw(11) << nv.hsl << "\t";
		cout << endl;
	/*cout << "\n Ho Ten: " << nv.hoten;
	cout << "\n Chuc Vu: " << nv.chucvu;
	cout << "\n Ngay sinh: " << nv.ngaysinh.ngay << "/" << nv.ngaysinh.thang << "/" << nv.ngaysinh.nam;
	cout << "\n He so luong: " << nv.hsl;*/
}
void XuatDanhSachNhanVien(LIST l) {
	int dem = 1;
	cout << "\n\t\tSTT"<<left << setw(20) << "\t   Ho Ten \t" << left << setw(13) << "  Chuc Vu" << "\t" << left << setw(10) << "\tNgay Sinh " << "\t" << left << setw(13) << "He So Luong" << "\t\n";

	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		cout  <<"\t\t"<< dem++<<"\t";
		
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
	float ketqua = 0.0f;
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
	if (StrToInt(date1.nam )> StrToInt(date2.nam)) return true;
	else if(StrToInt( date1.nam) == StrToInt(date2.nam))
	{
		if (StrToInt(date1.thang) > StrToInt(date2.thang)) {
			return true;
		}
		else if (StrToInt(date1.thang) == StrToInt(date2.thang)) {
			if (StrToInt(date1.ngay) > StrToInt(date2.ngay)) {
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
	return LayTen(ten, ViTri(ten), LengthStr(ten));
}
//Hàm Compare trả về 1
int SoSanhChucVu(string s) {

	string  s1 = "Nhan vien", s2 = "Quan li", s4 = "Giam doc", s5 = "Tong giam doc",s3="Thu ky";
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
	else if (CompareStr(UpperToLower(s), UpperToLower(s5))) {
		return 5;
	}
	else {
		return 0;
	}
}
int SoSanhTen(string s1,string s2) {
	if(UpperToLower(s1) > UpperToLower(s2)){
		return true;
	}
	return false;
}
//KẾT THÚC BIẾN ĐỔI THÊM
//mới thêm
void ThemNhanVien(LIST &l, int status)
{
	NHANVIEN nv;
	Nhap(nv);
	NODE *p = KhoiTaoNode(nv);
	NODE *q = NULL;
	if (status == 0) {
		ThemCuoi(l, p);
	}
	else if (status == 1) {
		if (!SoSanhDate(p->data.ngaysinh, l.pHead->data.ngaysinh)) {
			ThemDau(l, p);
		}
		else if (SoSanhDate(p->data.ngaysinh, l.pTail->data.ngaysinh)) {
			ThemCuoi(l, p);
		}
		else {
			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
			{

				if (!SoSanhDate(k->data.ngaysinh, p->data.ngaysinh) && SoSanhDate(k->pNext->data.ngaysinh, p->data.ngaysinh)) {
					q = k;
					p->pNext = q->pNext;
					q->pNext = p;
					break;
				}

			}
		}
	}
	else if (status == 2) {
		if (SoSanhChucVu(p->data.chucvu) > SoSanhChucVu(l.pHead->data.chucvu)) {
			ThemDau(l, p);
		}
		else if (SoSanhChucVu(p->data.chucvu) < SoSanhChucVu(l.pTail->data.chucvu)) {
			ThemCuoi(l, p);
		}
		else {
			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
			{
				if (SoSanhChucVu(k->data.chucvu) <= SoSanhChucVu(p->data.chucvu)) {
					q = k;
					p->pNext = q->pNext;
					q->pNext = p;
					break;
				}
			}
		}
	}
	else if (status == 3) {
		if (p->data.hsl < l.pHead->data.hsl) {
			ThemDau(l, p);
		}
		else if (p->data.hsl > l.pTail->data.hsl) {
			ThemCuoi(l, p);
		}
		else {
			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
			{
				if (k->data.hsl >= p->data.hsl) {
					q = k;
					p->pNext = q->pNext;
					q->pNext = p;
					break;
				}
			}
		}
	}
	else if (status == 4) {
		if (UpperToLower( TachTen(p->data.hoten))< UpperToLower(TachTen(l.pHead->data.hoten))) {
			ThemDau(l, p);
		}
		else if (UpperToLower(TachTen(p->data.hoten))> UpperToLower(TachTen(l.pTail->data.hoten))) {
			ThemCuoi(l, p);
		}
		else
		{
			for (NODE *k = l.pHead; k != NULL; k = k->pNext)
			{
				if (UpperToLower(TachTen(k->data.hoten))< UpperToLower(TachTen(p->data.hoten)) && SoSanhTen(UpperToLower(TachTen(k->pNext->data.hoten)) , (UpperToLower(TachTen(p->data.hoten))))) {
					q = k;
					p->pNext = q->pNext;
					q->pNext = p;
					break;
				}
			}
		}
	}
	
}
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
void SapXepTheoTen(LIST &l) {
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		for (NODE *h = k->pNext; h != NULL; h = h->pNext) {
			if (SoSanhTen(TachTen(k->data.hoten),TachTen( h->data.hoten)))
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
			if (SoSanhChucVu(k->data.chucvu) < SoSanhChucVu(h->data.chucvu))
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
bool NamNhuan(int Year) {
	if ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0) {
		return true;
	}
	return false;
}
int SoNgayTrongThang(int day,int Month,int Year) {
	int soNgay;
	switch (Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		soNgay = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		soNgay = 30;
		break;
	case 2:
		if (NamNhuan(Year)) {
			soNgay = 29;
		}
		else
		{
			soNgay = 28;
		}
	default:
		break;
	}
	return soNgay;
}
//void Test() {
//	int year;
//	cout << "Nhap nam";
//	cin >> year;
//	if (NamNhuan(year)) {
//		cout << "la nam nhuan" << endl;
//	}
//	else
//	{
//		cout << "khong";
//	}
//	
//}

//đưa ngay thang nam trong struct và string hết rồi để chuyển đổi thanh int so sánh.
void Nhap(NHANVIEN &nv)
{
	string  s1 = "Nhan vien", s2 = "Quan li", s3 = "Giam doc", s4 = "Tong giam doc", s5 = "Thu ky";
	do {
		cout << "Nhap ho ten nhan vien: ";
		getline(cin, nv.hoten);
		fflush(stdin);
	} while (CheckInterger(nv.hoten));
	
	do {
		cout << "Vui long nhap 1 trong 5 CVU: Giam doc , Tong giam doc , Quan li , Thu ky , Nhan vien.\n";
		cout << "Nhap chuc vu: ";
		getline(cin, nv.chucvu);
		fflush(stdin);
		//Bị nhầm dấu || và dấu && chú ý :))
	} while (UpperToLower( nv.chucvu) != UpperToLower(s1) && UpperToLower(nv.chucvu) != UpperToLower(s2) && UpperToLower(nv.chucvu) != UpperToLower(s3) && UpperToLower(nv.chucvu) != UpperToLower(s4) && UpperToLower(nv.chucvu) != UpperToLower(s5));
	cout << "\n *** NHAP NGAY THANG NAM SINH ***" << endl;;
	do {
		cout << "Nhap nam sinh: ";
		
		 getline(cin, nv.ngaysinh.nam);
		fflush(stdin);
	} while (StrToInt(nv.ngaysinh.nam) > 2004 || StrToInt(nv.ngaysinh.nam) < 1930);
	do {
		cout << "Nhap thang sinh: ";
		getline(cin, nv.ngaysinh.thang);
		fflush(stdin);
	} while (StrToInt(nv.ngaysinh.thang) > 12 || StrToInt(nv.ngaysinh.thang) < 1);
	do {
		cout << "Nhap ngay sinh: ";
		getline(cin, nv.ngaysinh.ngay);
		fflush(stdin);
	} while (StrToInt(nv.ngaysinh.ngay) > SoNgayTrongThang(StrToInt(nv.ngaysinh.ngay), StrToInt(nv.ngaysinh.thang), StrToInt(nv.ngaysinh.nam)) || StrToInt(nv.ngaysinh.ngay) < 1);
	do {
		cout << "Nhap he so luong: ";
		getline(cin, nv.hsl);
		StrToFloat(nv.hsl);
	} while (!isFloat(nv.hsl));
}

void KhoiTaoNhanVien(LIST &l) {
	NHANVIEN nv;
	cout << "NHAP THONG TIN NHAN VIEN CAN THEM (nhan Enter de them)"<<endl;
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
//Xoa theo pointer-to-pointer

//CÁC  HÀM XÓA
//void XoaTheoNam(LIST &l, string x) {
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	int namoi = StrToInt(x);
//	
//	int count = 0;
//	NODE *q = l.pHead;
//	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
//	{		
//		if (l.pHead->data.ngaysinh.nam == namoi) {
//			XoaDau(l);
//			return;
//		}
//		if (l.pTail->data.ngaysinh.nam == namoi) {
//			XoaCuoi(l);
//			return;
//		}
//		if (k->data.ngaysinh.nam == namoi) {
//			NODE *thimang = k;
//			q->pNext = k->pNext;
//			k = q;
//			delete thimang;
//			count = 1;
//		}
//		q = k; //gán node g trỏ đến node k
//	}
//	if (count == 1) {
//		cout << "Da xoa thanh cong nhan vien co nam:  " << x << endl;
//	}
//}

//void XoaTheoNam(LIST &l,string key)
//{
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	int namoi = StrToInt(key);
//	 NODE **pp = &l.pHead;
//	 int dem = 0;
//	while (*pp) {
//		NODE *thimang = *pp;
//		if (thimang->data.ngaysinh.nam == namoi) {
//			*pp = thimang->pNext;
//			delete (thimang);
//			cout << "Da xoa thanh cong lan "<<++dem<<" thong tin ve nam : " << namoi << endl;
//		}
//		else
//			pp = &(thimang->pNext);
//		
//	}
//}

//void XoaTheoHSL(LIST &l, string hsl)
//{
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	float hslmoi = StrToFloat(hsl);
//	NODE **pp = &l.pHead;
//	int dem = 0;
//	while (*pp) {
//		NODE *thimang = *pp;
//		if (thimang->data.hsl == hslmoi) {
//			*pp = thimang->pNext;
//			delete (thimang);
//			cout << "Da xoa thanh cong lan " << ++dem << " thong tin ve he so luong : " << hslmoi << endl;
//		}
//		else
//			pp = &(thimang->pNext);
//
//	}
//}

//void XoaTheoTen(LIST &l, string ten)
//{
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	NODE **pp = &l.pHead;
//	int dem = 0;
//	while (*pp) {
//		NODE *thimang = *pp;
//		string tentach = TachTen(thimang->data.hoten);
//		if (CompareStr(UpperToLower(tentach), UpperToLower(ten))==1) {
//			*pp = thimang->pNext;
//			delete thimang;
//			cout << "Da xoa thanh cong lan " << ++dem << " thong tin ve he so luong : " << ten << endl;
//		}
//		else
//			pp = &(thimang->pNext);
//
//	}
//}
//void XoaTheoChucVu(LIST &l, string cv)
//{
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	NODE **pp = &l.pHead;
//	int dem = 0;
//	while (*pp) {
//		NODE *thimang = *pp;
//		string cvmoi = thimang->data.chucvu;
//		if (CompareStr(UpperToLower(cvmoi), UpperToLower(cv))) {
//			*pp = thimang->pNext;
//			delete thimang;
//			cout << "Da xoa thanh cong lan " << ++dem << " thong tin ve chuc vu : " << cv << endl;
//		}
//		else
//			pp = &(thimang->pNext);
//
//	}
//}
//void XoaTheoHSL(LIST &l, string x) {
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	float namoi = StrToFloat(x);
//	if (l.pHead != NULL) {
//		if (l.pHead->data.hsl == namoi) {
//			XoaDau(l);
//			return;
//		}
//		if (l.pTail->data.hsl == namoi) {
//			XoaCuoi(l);
//			return;
//		}
//	}
//
//	NODE *q = l.pHead;
//	int count;
//	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
//	{
//		if (k->data.hsl == namoi) {
//			NODE *thimang = k;
//			q->pNext = k->pNext;
//			k = q;
//			delete thimang;
//			count = 1;
//		}
//		q = k; //gán node g trỏ đến node k
//	}
//	if (count == 1) {
//		cout << "Da xoa thanh cong nhan vien co he so luong " << x << endl;
//	}
//}
//void XoaTheoTen(LIST &l, string ten) {
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	if (l.pHead != NULL) {
//		string tentach = TachTen(l.pHead->data.hoten);
//		if (CompareStr(UpperToLower(tentach), UpperToLower(ten))) {
//			XoaDau(l);
//			return;
//		}
//		string tentach1 = TachTen(l.pTail->data.hoten);
//		if (CompareStr(UpperToLower(tentach1), UpperToLower(ten))) {
//			XoaCuoi(l);
//			return;
//		}
//	}
//	NODE *g = l.pHead;
//
//	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
//	{
//		string tentach = TachTen(k->data.hoten);
//		if (CompareStr(UpperToLower(tentach), UpperToLower(ten))) {
//			NODE *thimang = k;
//			g->pNext = k->pNext;
//			k = g;
//			delete thimang;
//
//		}
//		g = k; //gán node g trỏ đến node k
//	}
//
//}
//void XoaTheoChucVu(LIST &l, string cv) {
//	if (l.pHead == NULL) {
//		cout << "Danh sach rong khong the xoa nua ! ";
//		return;
//	}
//	if (l.pHead != NULL) {
//		string cvu = l.pHead->data.chucvu;
//		if (CompareStr(UpperToLower(cv), UpperToLower(cvu))) {
//			XoaDau(l);
//			return;
//		}
//		string cvu1 = l.pTail->data.chucvu;
//		if (CompareStr(UpperToLower(cv), UpperToLower(cvu1))) {
//			XoaCuoi(l);
//			return;
//		}
//	}
//	NODE *g = l.pHead;
//
//	for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
//	{
//		string cvu2 = k->data.chucvu;
//		if (CompareStr(UpperToLower(cv), UpperToLower(cvu2))) {
//			NODE *thimang = k;
//			g->pNext = k->pNext;
//			k = g;
//			delete thimang;
//
//		}
//		g = k; //gán node g trỏ đến node k
//	}
//
//}

//Xoa theo pointer
//Bị lỗi xóa vẫn còn phần tử cuối mất NULL - đã sửa
void XoaTheoNam(LIST &l,string key)
{
	int dem = 0;
	int moi = StrToInt(key);
	while (l.pHead && StrToInt(l.pHead->data.ngaysinh.nam) == moi)
	{
		node * tmp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete tmp;
		cout << "Da xoa thong tin cua nhan vien thu  " << ++dem << " theo nam " << key <<endl;
	}
	
	for (node * k = l.pHead; k != NULL; k = k->pNext)
	{
		while (k->pNext != NULL && StrToInt(k->pNext->data.ngaysinh.nam) == moi)
		{
			if (k->pNext==l.pTail) {
				delete l.pTail;
				k->pNext = NULL;
				l.pTail = k;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " theo nam " << key << endl;
			}
			else {
				node * tmp = k->pNext;
				k->pNext = tmp->pNext;
				delete tmp;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " theo nam " << key << endl;
			}
		}
	}
}
//void test(LIST &l, string key) {
//	if (StrToFloat(l.pHead->data.hsl) == StrToFloat(key)) {
//		cout << "bang nhau";
//	}
//	else
//	{
//		cout << "khong bang nhau";
//	}
//}
void XoaTheoHSL(LIST &l, string key)
{
	int dem = 0;
	while (l.pHead && StrToFloat(l.pHead->data.hsl) == StrToFloat(key))
	{
		node * tmp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete tmp;
		cout << "Da xoa thong tin cua nhan vien thu  " << ++dem << " theo he so luong " << key << endl;
	}

	for (node * k = l.pHead; k != NULL; k = k->pNext)
	{
		while (k->pNext != NULL && StrToFloat(k->pNext->data.hsl) == StrToFloat(key))
		{
			if (k->pNext == l.pTail) {
				delete l.pTail;
				k->pNext = NULL;
				l.pTail = k;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " he so luong " << key << endl;
			}
			else {
				node * tmp = k->pNext;
				k->pNext = tmp->pNext;
				delete tmp;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " theo he so luong " << key << endl;
			}
		}
	}
}
void XoaTheoTen(LIST &l, string key)
{
	int dem = 0;
	while (l.pHead && CompareStr(UpperToLower(TachTen( l.pHead->data.hoten)), UpperToLower(key))==1)
	{
		node * tmp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete tmp;
		cout << "Da xoa thong tin cua nhan vien thu  " << ++dem << " theo  ten: " << key << endl;
	}

	for (node * k = l.pHead; k != NULL; k = k->pNext)
	{
		while (k->pNext != NULL && CompareStr(UpperToLower(TachTen(k->pNext->data.hoten)), UpperToLower(key)) == 1)
		{
			if (k->pNext == l.pTail) {
				delete l.pTail;
				k->pNext = NULL;
				l.pTail = k;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " theo ten: " << key << endl;
			}
			else {
				node * tmp = k->pNext;
				k->pNext = tmp->pNext;
				delete tmp;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " theo ten: " << key << endl;
			}
		}
	}
}
void XoaTheoChucVu(LIST &l, string key)
{
	int dem = 0;
	while (l.pHead && CompareStr(UpperToLower(l.pHead->data.chucvu), UpperToLower(key)) == 1)
	{
		node * tmp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete tmp;
		cout << "Da xoa thong tin cua nhan vien thu  " << ++dem << " theo chuc vu: " << key << endl;
	}

	for (node * k = l.pHead; k != NULL; k = k->pNext)
	{
		while (k->pNext != NULL && CompareStr(UpperToLower(k->pNext->data.chucvu), UpperToLower(key)) == 1)
		{
			if (k->pNext == l.pTail) {
				delete l.pTail;
				k->pNext = NULL;
				l.pTail = k;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " theo nam " << key << endl;
			}
			else {
				node * tmp = k->pNext;
				k->pNext = tmp->pNext;
				delete tmp;
				cout << "Da xoa thong tin cua nhan vien thu " << ++dem << " theo chuc vu: " << key << endl;
			}
		}
	}
}
void XoaNhanVien(LIST &l) {
	string tukhoa;
	cout << "Nhap du lieu muon xoa: ";
	getline(cin, tukhoa);
	if (l.pHead == NULL) {
		cout << "Danh sach rong khong the xoa nua ! \n";
		return;
	}
	else if (isFloat(tukhoa))
	{
		XoaTheoHSL(l, tukhoa);
		if (CheckInterger(tukhoa)) {
			XoaTheoNam(l, tukhoa);
		}
	}
	else {
		XoaTheoTen(l, tukhoa);
		XoaTheoChucVu(l, tukhoa);
	}
	cout << "\nKhong con thong tin nhan vien muon xoa. ";
	cout << "Vui long kiem tra danh sach.\n";
}

//CÁC HÀM TÌM KIẾM
void TimKiemNhanVienTheoTen(LIST l, string ten) {
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		string tennv = TachTen(k->data.hoten);
		if (CompareStr(UpperToLower(ten), UpperToLower(tennv))) {
			Xuat(k->data);
			cout << endl << endl;

		}
	}
}
void TimKiemNhanVienTheoChucVu(LIST l, string cv) {

	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		string cvnv = k->data.chucvu; // gán dữ liệu vào chức vụ nhân viên
		if (CompareStr(UpperToLower(cv), UpperToLower(cvnv))) {
			Xuat(k->data);
			cout << endl << endl;

		}
	}

}
void TimKiemNhanVienTheoHSL(LIST l, string hsl) {
	float namoi = StrToFloat(hsl);
	int dem = 0;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext) {
		if (StrToFloat(k->data.hsl) == namoi) {
			Xuat(k->data);
			cout << endl;
			dem = 1;
		}
	}
	if (dem == 0) {
		cout << "\nKhong tim thay!" << endl;
		cout << "Vui long nhap thong tin can tim lai." << endl << endl;
	}
}
void TimKiemNhanVienTheoNam(LIST l, string nam) {
	int namoi = StrToInt(nam);
	int dem = 0;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext) {
		int namsan = StrToInt(k->data.ngaysinh.nam);
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
	string tukhoa;
	cout << "Nhap tu khoa can tim ve nhan vien: ";
	
	getline(cin, tukhoa);
	if (l.pHead == NULL) {
		cout << "Danh sach rong khong the xoa nua tim ! \n";
		return;
	}
	else if (CheckInterger(tukhoa) && StrToInt(tukhoa) > 1900) {
		TimKiemNhanVienTheoNam(l, tukhoa);

	}
	else if (isFloat(tukhoa))
	{
		TimKiemNhanVienTheoHSL(l, tukhoa);

	}

	else {
		//if (_stricmp((char *)tukhoa.c_str(), (char *)ten1.c_str()) || _stricmp((char *)tukhoa.c_str(), (char *)ten2.c_str()) || _stricmp((char *)tukhoa.c_str(), (char *)ten3.c_str()) || _stricmp((char *)tukhoa.c_str(), (char *)ten4.c_str())) {

		//}
		//else
		//{
		TimKiemNhanVienTheoTen(l, tukhoa);
		TimKiemNhanVienTheoChucVu(l, tukhoa);
		//}
	}
}

void LuuDanhSachNhanVien(LIST l) {
	ofstream fileout;
	fileout.open("XUATNHANVIEN.txt", ios::out);
	fileout << "Ho Ten, Chuc Vu, Ngay Sinh, He So Luong\n";
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
	int luuluachon = 0;
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
		cout << "\n\t\t\t*\t\t7. Xuat ds nhan vien ra file TEXT \t *";
		cout << "\n\t\t\t*\t\t0. TRO VE MENU  \t\t\t *";
		cout << "\n\t\t\t*\t\t\t\t\t\t\t *";
		cout << "\n\t\t\t************************** END ***************************";
		while (true)
		{
			
			string luachon1;
			cout << "\n\nNhap lua chon (so nguyen): ";
			getline(cin, luachon1);
			
			int luachon = StrToInt(luachon1);
			switch (luachon)
			{
			case 1:
			{
				ifstream filein;
				filein.open("NHANVIEN.txt", ios::in);
				DocDanhSachNhanVien(filein, l);
				filein.close();
				cout << "\nDoc thanh cong file NHANVIEN.txt.";
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
					cout << "\n\t\t\t*\t\t4. Theo ho ten \t\t\t *";
					cout << "\n\t\t\t*\t\t0. Tro ve menu \t\t\t\t *";
					cout << "\n\t\t\t*\t\t\t\t\t\t\t *";
					cout << "\n\t\t\t************************** END ***************************";
					cout << endl;
					while (true) {
						string luachon1;
						cout << "Nhap lua chon: ";
						getline(cin, luachon1);
						int luachon = StrToInt(luachon1);
						cout << endl;
						switch (luachon)
						{
						case 0:
						{
							goto menu;
						}
						case 1:
						{
							luuluachon = luachon;
							if (l.pHead == NULL) {
								cout << "Danh sach dang rong. Vui long them hoac doc file! \n\n";
							}
							SapXepTheoNgay(l);
							cout << "\t\t\t\t| DANH SACH SAU KHI SAP XEP THEO NGAY THANG NAM |\n\n";
							XuatDanhSachNhanVien(l);
							cout << endl;
							system("pause");
							goto menu;
							break;
						}
						//Cần sắp xếp lại chức vụ
						case 2:
						{
							luuluachon = luachon;
							SapXepTheoChucVu(l);
							if (l.pHead == NULL) {
								cout << "Danh sach dang rong. Vui long them hoac doc file! \n\n";
							}
							cout << "\t\t\t\t| DANH SACH SAU KHI SAP XEP THEO CHUC VU | \n\n";
							XuatDanhSachNhanVien(l);
							cout << endl;
							system("pause");
							goto menu;
							break;
						}
						case 3:
						{
							luuluachon = luachon;
							if (l.pHead == NULL) {
								cout << "Danh sach dang rong. Vui long them hoac doc file! \n\n";
							}
							SapXepTheoHSL(l);
							cout << "\t\t\t\t| DANH SACH SAU KHI SAP XEP THEO HE SO LUONG | \n\n";
							XuatDanhSachNhanVien(l);
							cout << endl;
							system("pause");
							goto menu;
							break;
						}
						case 4: {
							luuluachon = luachon;
							if (l.pHead == NULL) {
								cout << "Danh sach dang rong. Vui long them hoac doc file! \n\n";
							}
							SapXepTheoTen(l);
							cout << "\t\t\t\t| DANH SACH SAU KHI SAP XEP THEO TEN | \n\n";
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
				cout << "\n\n\t\t\t*********************** CHEN NHAN VIEN ***********************\n";

				ThemNhanVien(l, luuluachon);
				cout << "\n\n\t\t\t=========== Da them thanh cong =========== ";
				cout << "\n Danh sach sau khi them la: \n";
				XuatDanhSachNhanVien(l);
				system("pause");
				goto menu;
				system("cls");
				break;
			
			TroLai();
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
				cout << "\n\t\t\t\t\t | DANH SACH CAC NHAN VIEN | \n";
				XuatDanhSachNhanVien(l);
				cout << "\n";
				system("pause");
				break;
			}
			case 7:
			{
				LuuDanhSachNhanVien(l);
				cout << "Xuat file thanh cong. Vui long mo file XUATNHANVIEN.txt \n";
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
