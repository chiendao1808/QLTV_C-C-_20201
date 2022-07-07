#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;
class sach;
class dau_sach;
class phieu_muon;
class ban_doc // Dinh nghia lop ban doc
{
    friend class phieu_muon; // Lop ban cua lop ban doc
    protected:
        string ten, ma, sodienthoai;
        phieu_muon* sachmuon[5];
        int somuon;
        static int sobandoc;
        static ban_doc* cacbandoc[100];
    public:
        ban_doc(string m, string t, string sdt)
        {
            ma = m; ten = t; sodienthoai = sdt;
            somuon = 0;
        }
        ~ban_doc()
        {

        }
        static void dangki();
        static void nhapsv(ifstream& in);//nhap du lieu truoc vao chuong trinh
        static ban_doc* timbd(string);// con tro timbd kiểu ban_doc
        phieu_muon* muon(string);
        void tra(dau_sach*);
        static void xoa_du_lieu();
        void muon(dau_sach* dausach);
        static void in_danh_sach();
        static void in_danh_sach_da_muon();
        
};
void ban_doc::in_danh_sach_da_muon()
{
	string mabandoc;
	cout << "Ma ban doc: ";
	getline(cin, mabandoc);
	ban_doc* bd = timbd(mabandoc);
	if (bd == 0)
		cout << "Ma ban doc nay chua duoc dang ki\n";
	else 
	{
        cout<<"";
	}
}
class sach
{
    friend class dau_sach;
    private:
        //string ma;
        string ma, ten, nha_xuat_ban;
        int sodausach;
        dau_sach** cacdausach;
        static int sosach;
        static sach* khosach[500];
    public:
        sach(string m, string t, string nxb, int n);
        ~sach();
        dau_sach* timchuamuon();
        static sach* timsach(string masach);
        static dau_sach* timdausach(string, int);
        static void nhapsach();
        static void nhapdulieusach(ifstream& in);//nhap du lieu truoc vao chuong trinh
        static void the_loai_sach(string masach);
        static void xoa_du_lieu();
        static void in_danh_sach();
};
class phieu_muon
{
    friend class ban_doc;
    private:
        dau_sach* dausach1;
        ban_doc* bandoc1;
    public:
        phieu_muon(dau_sach* ds, ban_doc* bd) : dausach1(ds), bandoc1(bd)
        {

        }
};
class dau_sach
{
    friend class phieu_muon;
    friend class ban_doc;
    friend class sach;
    private:
        sach* sach1;
        int id;
        phieu_muon* muon;
    public:
        dau_sach(sach* right, int _id)
            : sach1(right), id(_id), muon(0)
        {
        }
        ~dau_sach()
        {
            if (muon) delete muon;
        }
        int chuamuon()
        {
            return muon == 0;
        }
        phieu_muon* chomuon(ban_doc* bd)
        {
            muon = new phieu_muon(this, bd);
            return muon;
        }
        void tra()
        {
            delete[] muon;
            muon = 0;
        }
};
int ban_doc::sobandoc = 0;
ban_doc* ban_doc::cacbandoc[100];
// Dinh nghia cac ham thanh vien

// Nhap du lieu cac sinh vien da co
void ban_doc::nhapsv(ifstream& in)
{
    string ma, ten, sodienthoai;
    getline(in, ma);
    getline(in, ten);
    getline(in, sodienthoai);
    cacbandoc[sobandoc++] = new ban_doc(ma, ten, sodienthoai);
}

// Dang ky thanh vien
void ban_doc::dangki()
{
    string ma, ten, sodienthoai;
    cout << "Ma ban doc: ";
    getline(cin, ma);
    cout << "Ten ban doc: ";
    getline(cin, ten);
    cout << "So dien thoai lien he:";
    getline(cin, sodienthoai);
    cacbandoc[sobandoc++] = new ban_doc(ma, ten, sodienthoai);
    cout << "Ban doc " << ten << " da duoc dang ki \n ";
    // ghi them ban doc dang ki vao file
    ofstream out("sv.txt", ios::out | ios::app);
    out <<endl<< ma << endl << ten << endl << sodienthoai;
}

// Tim ban doc theo ma ban doc
ban_doc* ban_doc::timbd(string ma)
{
    for (int i = 0; i < sobandoc; i++)
        if (ma.compare(cacbandoc[i]->ma) == 0)
            return cacbandoc[i];
    return 0;
}

void ban_doc::xoa_du_lieu()
{
    for (int i = 0; i < sobandoc; i++)
        delete[] cacbandoc[i];
    sobandoc = 0;
}

// Kiem tra so luong sach muon
phieu_muon* ban_doc::muon(string masach)
{
    if (somuon == 5)
    {
        cout << "Ban da muon du 5 dau sach \n";
        return 0;
    }
    sach* sach = sach::timsach(masach);
    if (sach == 0)
    {
        cout << "Khong co ma sach " << masach << " trong kho \n";
        return 0;
    }
    dau_sach* dausach = sach->timchuamuon();
    if (dausach == 0)
    {
        cout << "Sach nay da bi muon het \n";
        return 0;
    }
    phieu_muon* phieu = dausach->chomuon(this);
    sachmuon[somuon++] = phieu;
    cout << "Ban da muon duoc dau sach so " << dausach->id << endl;
    return phieu;
}

void ban_doc::muon(dau_sach* dausach)
{
    sachmuon[somuon++] = dausach->chomuon(this);
}

void ban_doc::tra(dau_sach* right)
{
    for (int i = 0; i < somuon; i++)
        if (sachmuon[i]->dausach1 == right)
        {
            right->tra();
            for (int j = i + 1; j < somuon; j++)
                sachmuon[j - 1] = sachmuon[j];
            somuon--;
            cout << "Ban da tra xong sach \n";
            return;
        }
    cout << "Ban da khong muon quyen sach nay \n";
}

void ban_doc::in_danh_sach()
{
    cout<<"===================================DANH SACH BAN DOC CUA THU VIEN======================================"<<endl;
    cout << left;
    cout << setw(15) << "Ma ban doc" << setw(40) << " Ten ban doc " << setw(25) << "So dien thoai lien he" << setw(30) << "So luong sach dang muon";
    for (int i = 0; i < sobandoc; i++)
    {
        cout << endl;
        cout << setw(15) << cacbandoc[i]->ma << setw(45) << cacbandoc[i]->ten << setw(30) << cacbandoc[i]->sodienthoai << setw(25) << cacbandoc[i]->somuon;
    }
    cout<<endl<<"=======================================================================================================";
}


int sach::sosach = 0;
sach* sach::khosach[500];
sach::sach(string ma_, string ten_, string nha_xuat_ban_, int n)
{
    ma = ma_;
    ten = ten_;
    nha_xuat_ban=nha_xuat_ban_;
    sodausach = n;
    cacdausach = new dau_sach * [sodausach];
    for (int i = 0; i < sodausach; i++)
        cacdausach[i] = new dau_sach(this, i + 1);
}
sach::~sach()
{
    for (int i = 0; i < sodausach; i++)
        delete cacdausach[i];
        delete[] cacdausach;

}

// Tim cac dau sach chua muon
dau_sach* sach::timchuamuon()
{
    for (int i = 0; i < sodausach; i++)
        if (cacdausach[i]->chuamuon())
            return cacdausach[i];
    return 0;
}

// Ham thuc hien tim sach
sach* sach::timsach(string masach)
{
    for (int i = 0; i < sosach; i++)
        if (masach.compare(khosach[i]->ma) == 0)
            return khosach[i];
    return 0;
}

// Tim dau sach trong thu vien
dau_sach* sach::timdausach(string masach, int id)
{
    sach* sach1 = timsach(masach);
    if (sach1 == 0) return 0;
    for (int i = 0; i < sach1->sodausach; i++)
    {
        if (sach1->cacdausach[i]->id == id)
            return sach1->cacdausach[i];
    }
    return 0;

}

// nhap danh sach sach tu file sach.txt
void sach::nhapdulieusach(ifstream& in)
{
    string ma, ten, nha_xuat_ban;
    int n;
    getline(in, ma);
    getline(in, ten);
    getline(in, nha_xuat_ban);
    in >> n; in.get();
    khosach[sosach++] = new sach(ma, ten, nha_xuat_ban, n);
}

// Nhap danh sach sach
void sach::nhapsach()
{
    string ma, ten, nha_xuat_ban;
    int n;
    cout << "Ma sach :";
    getline(cin, ma);
    cout << "Ten sach : ";
    getline(cin, ten);
    cout << "Nha xuat ban :";
    getline(cin, nha_xuat_ban);
    cout << "So dau sach : ";
    cin >> n; cin.ignore();
    khosach[sosach++] = new sach(ma, ten, nha_xuat_ban, n);
    cout << "Sach nay da duoc nhap vao \n";
    ofstream out("sach.txt", ios::out | ios::app);
    out <<endl<< ma << endl << ten << endl << nha_xuat_ban<<endl<<n;
}

// Ham lay the loai sach thong qua ma sach
void sach::the_loai_sach(string masach)
{
    string theloai = "";
    if (masach[0] == 'M' && masach[1] == 'A' && masach[2] == 'T')// Mathematics
    {
        theloai += "Toan hoc";
        cout << theloai;
    }
    else if (masach[0] == 'P' && masach[1] == 'H' && masach[2] == 'Y')// Physics
    {
        theloai += "Vat ly";
        cout << theloai;
    }
    else if (masach[0] == 'E' && masach[1] == 'L' && masach[2] == 'E') // Electronics
    {
        theloai += "Dien tu";
        cout << theloai;
    }
    else if (masach[0] == 'S' && masach[1] == 'C' && masach[2] == 'I')// Science
    {
        theloai += " Khoa hoc co ban ";
        cout << theloai;
    }
    else if (masach[0] == 'L' && masach[1] == 'I' && masach[2] == 'T')// Literature
    {
        theloai += " Van hoc ";
        cout << theloai;
    }
    else if (masach[0] == 'M' && masach[1] == 'U' && masach[2] == 'S')// Music
    {
        theloai += " Am nhac ";
        cout << theloai;
    }
    else if (masach[0] == 'B' && masach[1] == 'U' && masach[2] == 'S')// Business
    {
        theloai += " Kinh Doanh ";
        cout << theloai;
    }
    else if (masach[0] == 'C' && masach[1] == 'O' && masach[2] == 'M')// Comics
    {
        theloai += " Truyen tranh ";
        cout << theloai;
    }
}

void sach::xoa_du_lieu()
{
    for (int i = 0; i < sosach; i++)
        delete khosach[i];
    sosach = 0;
}

// Ham in danh sach sach cua thu vien
void sach::in_danh_sach()
{
    cout<<"===================================DANH SACH SACH CUA THU VIEN============================================="<<endl;
    cout << left;
    cout << setw(10) << "  Ma   " << setw(30) << "     Ten    " << setw(25) << "Nha xuat ban" << setw(20) << "So luong sach" << setw(20) << "   The loai sach   " << endl;
    for (int i = 0; i < sosach; i++)
    {
        cout << setw(10) << khosach[i]->ma << setw(30) << khosach[i]->ten << setw(30) << khosach[i]->nha_xuat_ban << setw(20) << khosach[i]->sodausach << setw(20) ;
        the_loai_sach(khosach[i]->ma);cout << endl;
    }
    cout<<endl<<"============================================================================================================";
}

class Date
{
    friend class phieu_muon;
    int ngay, thang, nam;
    public:
        Date(int day = 1, int month = 1, int year = 2021)
        {
            this->ngay = day;
            this->thang = month;
            this->nam = year;
        }
        ~Date()
        {

        }
        friend istream& operator>>(istream& in, Date& d);
        friend ostream& operator<<(ostream& out, Date& d);
        friend bool operator <=(Date d, Date q);
        friend void muon();
        friend void tra();
        friend Date tinh_ngay(Date& d, int n);
};
istream& operator>>(istream& in, Date& d)
{
    cout << "Nhap ngay dd/mm/yy: " << endl;
    cout << "Nhap ngay:";
    cin >> d.ngay;
    cout << "Nhap thang:";
    cin >> d.thang;
    cout << "Nhap nam:";
    cin >> d.nam;
    return in;
}
ostream& operator<<(ostream& out, Date& d)
{
    string day, month;
    int year;
    if (d.ngay < 10)
    {
        day = "0" + to_string(d.ngay);
    }
    else day = to_string(d.ngay);
    if (d.thang < 10)
    {
        month = "0" + to_string(d.thang);
    }
    else month = to_string(d.thang);
    year = d.nam;
    out << day << "/" << month << "/" << year << endl;
    return out;
}
bool operator<=(Date p, Date q)
{
   if(p.nam>q.nam)
   return false;
   else if(p.nam<q.nam)
   return true;
   else
   {
       if (p.thang>q.thang)
       return false;
       else if(p.thang<q.thang)
       return true;
       else
            {
                if(p.ngay>q.ngay)
                return false;
                else return true;
            }   
   }
}
Date tinh_ngay(Date& d, int n)
{
    Date q;
    int so_ngay_thang2;
    if (((d.nam % 4 == 0) && (d.nam % 100 != 0)) || (d.nam % 400))
        so_ngay_thang2 = 29;
    else so_ngay_thang2 = 28;
    switch (d.thang)
    {
        case 1: case 3: case 5: 
        case 7: case 8: case 10:
        {
            if ((d.ngay + n) > 31)
            {
                q.ngay = d.ngay + n - 31;
                q.thang = d.thang + 1;
                q.nam = d.nam;
                break;
            }
            else {
                q.ngay = d.ngay + n;
                q.thang = d.thang;
                q.nam = d.nam;
            }
        }
        case 4: case 6: 
        case 9: case 11:
        {
            if ((d.ngay + n) > 30)
            {
                q.ngay = d.ngay + n - 30;
                q.thang = d.thang + 1;
                q.nam = d.nam;
            }
            else
            {
                q.ngay = d.ngay + n;
                q.thang = d.thang;
                q.nam = d.nam;
            }
            break;
        }
        case 2:
        {
            if ((d.ngay + n) > so_ngay_thang2)
            {
                q.ngay = d.ngay + n - so_ngay_thang2;
                q.thang = d.thang + 1;
                q.nam = d.nam;

            }
            else
            {
                q.ngay = d.ngay + n;
                q.thang = d.thang;
                q.nam = d.nam;
            }
            break;
        }
        case 12:
        {
            if (d.ngay + n > 31)
            {
                q.ngay = d.ngay + n - 31;
                q.thang = 1;
                q.nam = d.nam + 1;
            }
            else
            {
                q.ngay = d.ngay;
                q.thang = 12;
                q.nam = d.nam;
            }
            break;
        }
    }
    return q;
}

// Ham thuc hien chuc nang muon sach
void muon()
{
    string mabd;
    cout << "Ma ban doc : ";
    getline(cin, mabd);
    ban_doc* bd = ban_doc::timbd(mabd);
    if (bd == 0)
    {
        cout << "Ma ban doc nay chua duoc dang ki \n ";
        return;
    }
    string mas;
    cout << "Ma sach muon : ";
    getline(cin, mas);
    Date ngay_muon, ngay_tra;
    cin >> ngay_muon;
    cout<<"Ngay muon sach :";
    cout << ngay_muon;
    cout << "Han tra sach cua ban la:";
    ngay_tra = tinh_ngay(ngay_muon, 7);
    cout << ngay_tra << endl;
    bd->muon(mas);
    cout << "\nXIN VUI LONG TRA SACH DUNG HAN !";
}

// Ham thuc hien chuc nang tra sach
void tra()
{ 
    char mabd[80];
    cout << "Ma ban doc : ";
    cin.getline(mabd, sizeof(mabd));
    ban_doc* bd = ban_doc::timbd(mabd);
    if (bd == 0)
    {
        cout << "Ma ban doc nay chua duoc dang ki \n";
        return;
    }
    char ma_sach[80];
    cout << "Ma sach tra : ";
    cin.getline(ma_sach, sizeof(ma_sach));
    int id;
    cout << "Ma dau sach : ";
    cin >> id;
    cin.ignore();
    dau_sach* ds = sach::timdausach(ma_sach, id);
    if (ds == 0)
    {
        cout << " Khong co dau sach nay \n ";
        return;
    }
    bd->tra(ds);
}

// Ham hien thi danh sach chuc nang
void menu()
{
    cout << "\n ---------------------------------------------------------------------";
    cout << "\n XIN MOI AN CAC PHIM SO DE SU DUNG CAC DICH VU CUA THU VIEN !        -\n";
    cout << " 1. Dang ki ban doc                                                  -\n";
    cout << " 2. Nhap sach                                                        -\n";
    cout << " 3. Muon sach                                                        -\n";
    cout << " 4. Tra sach                                                         -\n";
    cout << " 5. Danh sach ban doc                                                -\n";
    cout << " 6. Danh sach sach                                                   -\n";
    cout << " 7. Thoat khoi chuong trinh                                          -\n";
    cout << " ---------------------------------------------------------------------" << endl;
}

void nhapdulieu()
{
    ifstream in1("sv.txt");
    while (!in1.eof())
    {
        ban_doc::nhapsv(in1);
    }
    in1.close();
    ifstream in2("sach.txt");
    while (!in2.eof())
    {
        sach::nhapdulieusach(in2);
    }
    in2.close();
}

int main()
{
    nhapdulieu();
    cout << "*****************CHAO MUNG CAC BAN DEN VOI THU VIEN*******************";
    cout<<endl;
    while (1)
    {
        menu();
        int i;
        cout<<"Xin moi nhap lua chon cua ban :"; 
        cin >> i; cin.ignore();
        switch (i)
        {
            case 1:
            {
                ban_doc::dangki();
                break;
            }
            case 2:
            {
                sach::nhapsach();
                break;
            }
            case 3:
            {
                sach::in_danh_sach();
                cout<<"Xin moi nhap cac thong tin sau de thu hien muon sach !";
                cout<<endl;
                muon();
                break;
            }
            case 4:
            {
                tra();
                break;
            }
            case 5:
            {
                ban_doc::in_danh_sach();
                break;
            }
            case 6: 
            {
                sach::in_danh_sach();
                break;
            }
            case 7: 
            {
                break;
            }
            default : 
            {
                cout<<"Lua chon cua ban khong co trong danh sach! "<<endl;
                cout<<"Xin vui long lua chon lai !";
            }
        }
        if(i==7)
        break;
    }
    cout<<endl;
    system("pause");
}

