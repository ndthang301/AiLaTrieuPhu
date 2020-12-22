#include <stdio.h>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef char str[30];
str moctien[15] = { "    200,000 USD    ", "    400,000 USD    ", "    600,000 USD    ", "   1,000,000 USD   ", "   2,000,000 USD   ", "   4,000,000 USD   ", "   6,000,000 USD   ", "   8,000,000 USD   ", "  10,000,000 USD   ", "  15.000,000 USD   ", "  20,000,000 USD   ", "  30,000,000 USD   ", "  40,000,000 USD   ", "  60,000,000 USD   ", "  100,000,000 USD  " };
str thaotac[5] = { "1. Play Game", "2. Quan Li Game", "3. Best Player", "4. Information Product", "5. Exit" };
str trogiup[4] = { "An phim 1: Goi ba me", "An phim 2: Loai 2 dap an sai", "An phim 3: Hoi Khan gia", "An phim 4: Tu van tai cho" };


#pragma comment(lib, "winmm.lib")
struct ALTP
{
	int ID;
	char cauhoi[256];
	char A[200];
	char B[200];
	char C[200];
	char D[200];
	int dapan;
} data;

//------------------------------------------//
struct NguoiChoi
{
	char ten[25];
	int socau;
};
//-------------------------------------------//
struct Node
{
	ALTP data;
	Node *pNext;
};
//-------------------------------------------//
struct List
{
	Node *pHead, *pTail;
};
//-------------------------------------------//
void gotoxy(int x, int y);
void textcolor(int x);
void resizeConsole(int width, int height);
void DoiMau(int x, char *s);
void BoiDen(int x, int y, int z, int t);
void ThaoTacUpDown(int x, int y[], str thaotac[], int &tt, int n);
void VeGiaoDien();
void VeAiLaTrieuPhu(int i);
void MocTien(int &tt, str muctien[]);
void NhacNen(Node *p);
void NhacCauTraLoiDung(Node *p);

void TaoList(List &l);
Node* GetNode(ALTP data);
void DocFile(List &l);
void ThemCuoi(List &l, Node *p);
void NhapCauHoi(ALTP &data);


void ThaoTacMenu();
void GioiThieu();
void Choi(List &l);
void QuanLiCauHoi();
void version();
void BatPhim_DungCuocChoi(int temp);
void XuLiKetThuc(int temp);

void QuanLi_ThemCauHoi(List &l);
void QuanLi_TimTheoID(List &l);
void QuanLi_XuatCauHoi(List l);


void Rank_DocFileXepHang(NguoiChoi a[], int &n);
void Rank_GhiFileXepHang(NguoiChoi a);
void Rank_XuatXepHang();

void TroGiup(Node *p);
void TroGiup_GoiNguoiThan(Node *p);
void TroGiup_ToTuVan(Node *p);
void TroGiup_KhanGia(Node *p);
void TroGiup_Loai2CauSai(Node *p, str thaotac[]);




//-----------------------------------------------------------//
int main()
{
	GioiThieu();
	ThaoTacMenu();
	//getch();
	return 0;
}

//----------------------------------------------------------//


void TaoList(List &l)
{
	l.pHead = l.pTail = NULL;
}
//--------------------------------------------//
Node* GetNode(ALTP data)
{
	Node *p = new Node;
	if (p == NULL)
		return NULL;
	else
	{
		p->data = data;
		p->pNext = NULL;
	}
	return p;
}
//--------------------------------------------//
void ThemCuoi(List &l, Node *p)
{
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;

	}
}
//-------------------------------------------//
void NhapCauHoi(ALTP &data)
{
	fflush(stdin);
	printf("Nhap ID:");
	scanf("%d", &data.ID);
	printf("\nCau Hoi:");
	fflush(stdin);
	gets(data.cauhoi);
	printf("\nA:");
	fflush(stdin);
	gets(data.A);
	printf("\nB:");
	fflush(stdin);
	gets(data.B);
	printf("\nC:");
	fflush(stdin);
	gets(data.C);
	printf("\nD:");
	fflush(stdin);
	gets(data.D);
	printf("\nCau Dung:");
	scanf("%d", &data.dapan);

}

//--------------------------------------------//
void Xuat(List l)
{
	Node *p = l.pHead;
	while (p != NULL)
	{
		printf("Cau Hoi %d :%s \n", p->data.ID, p->data.cauhoi);
		printf("%s\n", p->data.A);
		printf("%s\n", p->data.B);
		printf("%s\n", p->data.C);
		printf("%s\n", p->data.D);
		printf("Cau Dung:%d \n", p->data.dapan);
		printf("-------------------------------------------------------------------------------\n");
		p = p->pNext;
	}
}
//--------------------------------------------------//
void GhiFile(List &l)
{
	FILE *f;
	f = fopen("AiLaTrieuPhu.txt", "wb");
	if (f == NULL)
	{
		printf("Khong Co Du Lieu\n");
	}
	Node *p = l.pHead;
	while (p)
	{
		fwrite(&p->data, sizeof(ALTP), 1, f);
		p = p->pNext;
	}
	fclose(f);
}
//--------------------------------------------------//
void DocFile(List &l)
{
	FILE *f;
	f = fopen("AiLaTrieuPhu.txt", "rb");
	if (f == NULL)
	{
		printf("Khong Co Du Lieu\n");
	}
	ALTP x;
	Node *p = new Node;
	TaoList(l);
	while (fread(&x, sizeof(ALTP), 1, f)>0)
	{
		p = GetNode(x);
		ThemCuoi(l, p);
	}
	fclose(f);
}
//-----------------------------------------//
void GhiFileXepHang(NguoiChoi a)
{
	FILE *f;
	f = fopen("xephang.txt", "ab");
	if (f == NULL)
	{
		printf("Khong Co Du Lieu\n");
	}
	fwrite(&a, sizeof(NguoiChoi), 1, f);
	fclose(f);
}
//------------------------------------------//
void DocFileXepHang(NguoiChoi a[], int &n)
{
	n = 0;
	FILE *f;
	f = fopen("xephang.txt", "rb");
	if (f == NULL)
	{
		printf("Khong Co Du Lieu\n");
	}
	while (fread(&a[n], sizeof(NguoiChoi), 1, f)>0)
	{
		n++;
	}
	fclose(f);
}
//------------------------------------------//
void XuatXepHang()
{
	NguoiChoi a[100];
	int n = 0;
	DocFileXepHang(a, n);
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i].socau < a[j].socau)
			{
				NguoiChoi tam = a[i];
				a[i] = a[j];
				a[j] = tam;
			}
		}
	}
	textcolor(236);
	printf("\n\t\t\t=====Bang Xep Hang=====\n\n");
	textcolor(7);
	printf("|%10s|%20s|%20s|\n", "Hang", "Ten nguoi choi", "So tien");
	printf("------------------------------------------------------\n");
	for (int i = 0; i < 3; i++)
	{
		printf("|%10d|%-20s|%-20s|\n", i + 1, a[i].ten, moctien[a[i].socau]);
	}

}
//----------------------------------------//
void ThemCauHoi(List &l)
{
	DocFile(l);
	ALTP x;
	NhapCauHoi(x);
	Node *p = GetNode(x);
	ThemCuoi(l, p);
	GhiFile(l);
}
//-----------------------------------------//
void TimTheoID(List &l)
{
	DocFile(l);
	int maID;
	printf("Nhap ID Can Tim:\n");
	scanf("%d", &maID);
	int check = 0;
	for (Node *p = l.pHead; p; p = p->pNext)
	{
		if (p->data.ID == maID)
		{
			printf("Cau Hoi %d :%s \n", p->data.ID, p->data.cauhoi);
			printf("A:%s\n", p->data.A);
			printf("B:%s\n", p->data.B);
			printf("C:%s\n", p->data.C);
			printf("D:%s\n", p->data.D);
			check = 1;
		}
	}
	if (check == 0)
	{
		printf("Khong Tim Thay\n");
	}
}
// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
//-------------------------------------------------------------------------------
void DoiMau(int x, char *s)
{
	textcolor(x);
	printf("%s", s);
	textcolor(7);
}
//---------------------------------------------------------------------------------//
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm d?ch chuy?n con tr? d?n t?a d? x, y.
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1, y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

//---------------------------------------------------------------------------------------//
void GioiThieu()
{
	resizeConsole(970, 650);
	FILE *f;
	PlaySound("2.wav", NULL, SND_ASYNC);

	VeAiLaTrieuPhu(2);

	int j;
	for (int i = 1; i <= 25; i++)
	{
		if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19 || i == 22 || i == 25)
			j = 9;
		if (i == 2 || i == 5 || i == 8 || i == 11 || i == 14 || i == 17 || i == 20 || i == 23)
			j = 12;
		if (i == 3 || i == 6 || i == 9 || i == 12 || i == 15 || i == 18 || i == 21 || i == 24)
			j = 14;
		textcolor(j);
		system("cls");
		
		VeAiLaTrieuPhu(0);
		Sleep(150);
	}
	textcolor(7);
}
//=----------------------------------------------------
void ThaoTacUpDown(int x, int y[], str thaotac[], int &tt, int n)
{
	if (GetAsyncKeyState(VK_DOWN))
	{
		Sleep(200);
		if (tt != n - 1)
		{
			gotoxy(x, y[tt]);  DoiMau(7, thaotac[tt]);
			gotoxy(x, y[tt] + 2);  DoiMau(299, thaotac[tt + 1]);
			tt++;
		}
	}

	if (GetAsyncKeyState(VK_UP))
	{
		Sleep(200);
		if (tt != 0)
		{
			gotoxy(x, y[tt]);  DoiMau(7, thaotac[tt]);
			gotoxy(x, y[tt] - 2);  DoiMau(299, thaotac[tt - 1]);
			tt--;
		}
	}
}
//--------------------------------------------------------//
void GoiNguoiThan(Node *p)
{
	PlaySound("goi dien thoai.wav", NULL, SND_ASYNC);
	int da = p->data.dapan;
	int random[14] = { 0, da, 1, da, 2, 3, da, 0, 1, da, 2, da, 3, da };
	gotoxy(3, 20);
	printf("Nguoi than dang chem gio");
	Sleep(800);
	printf(".");
	Sleep(800);
	printf(".");
	Sleep(800);
	printf(".\n");

	srand(time(0));
	int temp = 0 + rand() % 12;
	if (random[temp] == 0)
		printf("Nguoi than khuyen ban chon: %s", p->data.A);
	if (random[temp] == 1)
		printf("Nguoi than khuyen ban chon: %s", p->data.B);
	if (random[temp] == 2)
		printf("Nguoi than khuyen ban chon: %s", p->data.C);
	if (random[temp] == 3)
		printf("Nguoi than khuyen ban chon: %s", p->data.D);
}

void ToTuVan(Node *p)
{
	PlaySound("tu van tai cho.wav", NULL, SND_ASYNC);
	int da = p->data.dapan;
	int random[19] = { da, 0, da, 1, da, 2, da, 3, da, da, 0, da, 1, da, 2, da, 3, da, da };

	srand(time(0));

	gotoxy(3, 20);
	printf("Dang hoi to tu van");
	Sleep(800);
	printf(".");
	Sleep(800);
	printf(".");
	Sleep(800);
	printf(".\n");

	for (int i = 1; i <= 3; i++)
	{
		int temp = 0 + rand() % 19;
		if (random[temp] == 0)
			printf("\nNguoi thu %d chon: %s", i, p->data.A);
		if (random[temp] == 1)
			printf("\nNguoi thu %d chon: %s", i, p->data.B);
		if (random[temp] == 2)
			printf("\nNguoi thu %d chon: %s", i, p->data.C);
		if (random[temp] == 3)
			printf("\nNguoi thu %d chon: %s", i, p->data.D);
		Sleep(1997);
	}
}

//-----------------------------------------------------//
void KhanGia(Node *p)
{
	PlaySound("y kien khan gia.wav", NULL, SND_ASYNC);
	srand(time(0));
	int da = p->data.dapan;

	int random[100];
	for (int i = 0; i <= 99; i++)
	{
		random[i] = da;
	}
	int tiledung = 20 + rand() % 61;
	for (int i = 0; i < 100 - tiledung; i++)
	{
		Sleep(1);
		int temp = 0 + rand() % 4;
		random[i] = temp;
	}
	int A = 0, B = 0, C = 0, D = 0;

	for (int i = 0; i < 100; i++)
	{
		if (random[i] == 0)
			A++;
		if (random[i] == 1)
			B++;
		if (random[i] == 2)
			C++;
		if (random[i] == 3)
			D++;
	}
	int i, j;

	for (i = 1, j = 32; i <= A / 4; i++, j--)
	{
		gotoxy(20, j);
		DoiMau(299, "   ");
		Sleep(300);
	}
	gotoxy(20, j); printf("%d", A);

	for (i = 1, j = 32; i <= B / 4; i++, j--)
	{
		gotoxy(25, j);
		DoiMau(299, "   ");
		Sleep(300);
	}
	gotoxy(25, j); printf("%d", B);

	for (i = 1, j = 32; i <= C / 4; i++, j--)
	{
		gotoxy(30, j);
		DoiMau(299, "   ");
		Sleep(300);
	}
	gotoxy(30, j); printf("%d", C);

	for (i = 1, j = 32; i <= D / 4; i++, j--)
	{
		gotoxy(35, j);
		DoiMau(299, "   ");
		Sleep(50);
	}
	gotoxy(35, j); printf("%d", D);

	gotoxy(20, 33); DoiMau(8, "A");
	gotoxy(25, 33); DoiMau(8, "B");
	gotoxy(30, 33); DoiMau(8, "C");
	gotoxy(35, 33); DoiMau(8, "D");
}
//---------------------------------------------//
void Loai2CauSai(Node *p, str thaotac[])
{
	PlaySound("5050.wav", NULL, SND_ASYNC);
	Sleep(2700);
	int da = p->data.dapan;
	srand(time(0));
	int temp1;
	int temp2;
	Sleep(100);
	while (1)
	{
		temp1 = 0 + rand() % 4;
		temp2 = 0 + rand() % 4;

		if (temp1 != da && temp2 != da && temp1 != temp2)
		{
			gotoxy(3, 3 + temp1 * 2); printf("                          ");
			strcpy(thaotac[temp1], "");

			gotoxy(3, 3 + temp2 * 2); printf("                          ");
			strcpy(thaotac[temp2], "");
			break;
		}

	}
}

//-----------------------------------------------------//
void MocTien(int &tt, str muctien[])
{
	int y[15] = { 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6 };


	for (int i = 0; i < 15; i++)
	{
		if (i % 2 == 0)
		{
			gotoxy(95, y[i]); textcolor(26); printf(muctien[i]);
		}
		else
		{
			gotoxy(95, y[i]); textcolor(666); printf(muctien[i]);
		}
	}
	tt++;
	if (tt == 0)
	{
		gotoxy(95, y[0]);  DoiMau(236, muctien[tt]);
	}
	else
	{
		gotoxy(95, y[tt]);  DoiMau(236, muctien[tt]);
		gotoxy(95, y[tt - 1]);  DoiMau(666, muctien[tt - 1]);
	}
}
//---------------------------------------------------
void TroGiup(Node *p, str thaotac[], str trogiup[])
{

	if (GetAsyncKeyState(0x31))
	{
		Sleep(200);
		BoiDen(1, 11, 50, 35);
		if (strcmp(trogiup[0], "") != 0)
		{
			strcpy(trogiup[0], "");
			GoiNguoiThan(p);	
		}
	}

	if (GetAsyncKeyState(0x32))
	{
		Sleep(200);
		BoiDen(1, 11, 50, 35);
		if (strcmp(trogiup[1], "") != 0)
		{
			strcpy(trogiup[1], "");
			Loai2CauSai(p, thaotac);
		}
	}

	if (GetAsyncKeyState(0x33))
	{
		Sleep(200);
		BoiDen(1, 11, 50, 35);
		if (strcmp(trogiup[2], "") != 0)
		{
			strcpy(trogiup[2], "");
			KhanGia(p);
		}

	}
	if (GetAsyncKeyState(0x34))
	{
		Sleep(200);
		BoiDen(1, 11, 50, 35);
		if (strcmp(trogiup[3], "") != 0)
		{
			strcpy(trogiup[3], "");
			ToTuVan(p);
		}

	}
}
//--------------------------------------------------------//
void version()
{
	gotoxy(35, 6); textcolor(236); printf("Information Product"); textcolor(7);
	gotoxy(25, 10); printf("|%-30s| %-30s|\n", "Propety", "Value");
	gotoxy(25, 11); printf("----------------------------------------------------------------\n");
	gotoxy(25, 12); printf("|%-30s| %-30s|\n", "Product Name", "Ai la trieu phu");
	gotoxy(25, 14); printf("|%-30s| %-30s|\n", "Product Version", "1.00.00");
	gotoxy(25, 16); printf("|%-30s| %-30s|\n", "Size", "3KB");
	gotoxy(25, 18); printf("|%-30s| %-30s|\n", "Date Modfied", "17/11/2016 2:40 PM");
	gotoxy(25, 20); printf("|%-30s| %-30s|\n", "Language", "Tieng Viet");
	gotoxy(25, 22); printf("|%-30s| %-30s|\n", "Design By", "Team 4T");
}
//--------------------------------------------//
//-----------------Ham quan li cau hoi-------------------//
void QuanLiCauHoi()
{
	int x = 40, y[4] = { 10, 12, 14, 16 }, tt = 0, n = 4;
	str thaotac[] = { "1. Xuat tat ca cau hoi", "2. Tim kiem cau hoi   ", "3. Them cau hoi       ","4. Quay lai           " };
	gotoxy(x + 5, 8); textcolor(666); printf("MENU");
	gotoxy(x, y[0]); textcolor(299); printf("%s", thaotac[0]); textcolor(7);
	gotoxy(x, y[1]); textcolor(7); printf("%s", thaotac[1]);
	gotoxy(x, y[2]); textcolor(7); printf("%s", thaotac[2]);
	gotoxy(x, y[3]); textcolor(7); printf("%s", thaotac[3]);
	while (1)
	{
		ThaoTacUpDown(x, y, thaotac, tt, n);
		if (GetAsyncKeyState(VK_SPACE))
		{
			List l;
			DocFile(l);
			Sleep(200);
			if (tt == 0)
			{
				system("cls");
				Xuat(l);
				textcolor(299);
				printf("Quay lai ");
				textcolor(7);
				while (1)
				{
					if (GetAsyncKeyState(VK_SPACE))
					{
						Sleep(200);
						system("cls");
						QuanLiCauHoi();
					}
				}
			}
			if (tt == 1)
			{
				system("cls");
				TimTheoID(l);
				textcolor(299);
				printf("Quay lai ");
				textcolor(7);
				while (1)
				{
					if (GetAsyncKeyState(VK_SPACE))
					{
						Sleep(200);
						system("cls");
						QuanLiCauHoi();
					}
				}
			}
			if (tt == 2)
			{
				system("cls");
				fflush(stdin);
				ThemCauHoi(l);
				textcolor(299);
				printf("Quay lai ");
				textcolor(7);
				while (1)
				{
					if (GetAsyncKeyState(VK_SPACE))
					{
						Sleep(200);
						system("cls");
						QuanLiCauHoi();
					}
				}
			}
			if (tt == 3)
			{
				system("cls");
				VeAiLaTrieuPhu(0);
				ThaoTacMenu();
			}
		}
	}

}
//-----------------Ham Nguoi Choi-----------------------//
void Choi(List &l)
{
	DocFile(l);

	strcpy(trogiup[0], "An phim 1: Goi ba me");
	strcpy(trogiup[1], "An phim 2: Loai 2 dap an sai");
	strcpy(trogiup[2], "An phim 3: Hoi Khan gia");
	strcpy(trogiup[3], "An phim 4: Tu van tai cho");

	int w = 0;
	int tt = 0, temp = -1, n = 4, x = 3, y[4] = { 3, 5, 7, 9 };

	Node *p = new Node;
	p = l.pHead;
	str thaotac[4];
	VeGiaoDien();

pmt:
	MocTien(temp, moctien);
	strcpy(thaotac[0], p->data.A);
	strcpy(thaotac[1], p->data.B);
	strcpy(thaotac[2], p->data.C);
	strcpy(thaotac[3], p->data.D);

	gotoxy(x, 1); printf("Cau hoi so %d: %s ", p->data.ID, p->data.cauhoi);
	gotoxy(x, y[0]); DoiMau(299, thaotac[0]);
	for (int i = 1; i <= n - 1; i++)
	{
		gotoxy(x, y[i]); printf("%s", thaotac[i]);
	}

	NhacNen(p);
	long s = 15000000;
	int z = 55;
	while (s > 0)
	{
		
		while (1)
		{
			TroGiup(p, thaotac, trogiup);
			ThaoTacUpDown(x, y, thaotac, tt, n);
			if (GetAsyncKeyState(0x57))
			{
				BatPhim_DungCuocChoi(temp);
			}
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				exit(0);
			}
			if (GetAsyncKeyState(VK_SPACE))
			{

				Sleep(200);
				if (tt == p->data.dapan)
				{
					NhacCauTraLoiDung(p);
				}

				for (int i = 0; i < 15; i++)
				{
					Sleep(100);
					gotoxy(x, y[p->data.dapan]); DoiMau(236, thaotac[p->data.dapan]);
					Sleep(200);
					gotoxy(x, y[p->data.dapan]); DoiMau(299, thaotac[p->data.dapan]);
				}

				if (tt == p->data.dapan)
				{
					w++;
					if (temp == 14)
					{
						char s[25];
						NguoiChoi a;
						system("cls");
						gotoxy(40, 15);
						printf("chuc mung ban da vuot qua tat ca 15 cau hoi cua chuong trinh ");
						gotoxy(40, 16);
						printf("ban duoc ban  : %s", moctien[14]);
						fflush(stdin);
						gotoxy(40, 17);
						printf("\nNhap ten nguoi choi de luu ket qua: ");
						gets(s);
						strcpy(a.ten, s);
						a.socau = temp - 1;
						GhiFileXepHang(a);
						
					}
					system("cls");
					VeGiaoDien();
					tt = 0;
					p = p->pNext;
					goto pmt;
				}
				else
				{
//					k = 1;
					XuLiKetThuc(temp);
					fflush(stdin);
					system("cls");
					ThaoTacMenu();
				}
			}
			s--;
			if (s % 300000 == 0)
			{
				gotoxy(z--, 35); printf(" ");
			}
			if (s == 0)
			{
				system("cls");
				XuLiKetThuc(temp);
				system("cls");
				ThaoTacMenu();

			}
				
		}
	}

}
//----------------------------------------------------//
void ThaoTacMenu()
{
	textcolor(14);
	VeAiLaTrieuPhu(0);
	textcolor(7);
	resizeConsole(970, 650);
	List l;

	int x = 50, tt = 0, n = 5,
		y[5] = { 26, 28, 30, 32, 34 };
tt:
	gotoxy(x, y[0]);  DoiMau(299, thaotac[0]);
	for (int i = 1; i <= n - 1; i++)
	{
		gotoxy(x, y[i]);  printf("%s", thaotac[i]);
	}

	while (1)
	{
		ThaoTacUpDown(x, y, thaotac, tt, n);

		if (GetAsyncKeyState(VK_SPACE))
		{
			Sleep(200);
			if (tt == 0)
			{
				system("cls");
				Choi(l);
				goto tt;
			}
			if (tt == 1)
			{
				system("cls");
				QuanLiCauHoi();
			}

			if (tt == 2)
			{
				system("cls");
				XuatXepHang();
				gotoxy(10, 15);
				textcolor(299);
				printf("Quay lai ");
				textcolor(7);
				while (1)
				{
					if (GetAsyncKeyState(VK_SPACE))
					{
						system("cls");
						Sleep(200);
						VeAiLaTrieuPhu(0);
						ThaoTacMenu();
					}
						
				}

			}

			if (tt == 3)
			{
				system("cls");
				version();
				gotoxy(8,35);
				textcolor(299);
				printf("Quay lai ");
				textcolor(7);
				while (1)
				{
					if (GetAsyncKeyState(VK_SPACE))
					{
						system("cls");
						Sleep(200);
						VeAiLaTrieuPhu(0);
						ThaoTacMenu();
					}

				}
			}

			if (tt == 4)
			{
				exit(0);
			}
		}
	}
}

//--------------------------------------------//
void BoiDen(int x,int y,int z,int t)
{

	for (int i = y; i < t; i++)
	{
		for (int j = x; j < z; j++)
		{
			gotoxy(j, i); printf(" ");
		}
	}
}

void NhacNen(Node *p)
{
	if (p->data.ID <6)
	{
		PlaySound("nhacnen1-5.wav", NULL, SND_ASYNC);
	}
	else
	{
		PlaySound("nhacnencau6.wav", NULL, SND_ASYNC);
	}
}

void NhacCauTraLoiDung(Node *p)
{
	if (p->data.ID < 6)
	{
		PlaySound("caudung1-5.wav", NULL, SND_ASYNC);
	}
	else
	{
		if (p->data.dapan == 0)
			PlaySound("cau a.wav", NULL, SND_ASYNC);
		if ((p->data.dapan == 1))
			PlaySound("cau b.wav", NULL, SND_ASYNC);
		if ((p->data.dapan == 2))
			PlaySound("cau c.wav", NULL, SND_ASYNC);
		if ((p->data.dapan == 3))
			PlaySound("cau d.wav", NULL, SND_ASYNC);
	}
}
//-----------------------------------------------------//
void VeAiLaTrieuPhu(int i)
{
	system("cls");
	FILE *f;
	f = fopen("a.txt", "r");
	char c;
	while (!feof(f))
	{
		fscanf(f, "%c", &c);
		printf("%c", c);
		Sleep(i);
	}
}
//---------------------------------------------//
void  VeGiaoDien()
{
	for (int i = 1; i <= 40; i++)
	{
		gotoxy(62, i);
		DoiMau(9, "||");
	}
	gotoxy(67, 26); textcolor(4); printf("W - Dung Cuoc Choi");
	gotoxy(71, 28);  printf("Esc - Exit"); textcolor(7);

	gotoxy(69, 8);  DoiMau(444, "Quyen Tro Giup");
	gotoxy(65, 11);  DoiMau(13, trogiup[0]);
	gotoxy(65, 13);  DoiMau(13, trogiup[1]);
	gotoxy(65, 15);  DoiMau(13, trogiup[2]);
	gotoxy(65, 17);  DoiMau(13, trogiup[3]);

	gotoxy(65, 11);  DoiMau(13, trogiup[0]);
	gotoxy(65, 13);  DoiMau(13, trogiup[1]);
	gotoxy(65, 15);  DoiMau(13, trogiup[2]);
	gotoxy(65, 17);  DoiMau(13, trogiup[3]);

	for (int i = 5; i <= 55; i++)
	{
		gotoxy(i, 35); DoiMau(19, " ");
	}
}
//--------------------------------------------//
void BatPhim_DungCuocChoi(int temp)
{
	system("cls");
	char s[30];
	textcolor(14);
	gotoxy(40, 15); printf("Ban da dung cuoc choi!");
	gotoxy(40, 17); printf("Ban duoc ban: %s", moctien[temp - 1]);
	gotoxy(40, 19); printf("Nhap ten nguoi choi: ");
	fflush(stdin);
	gets(s);
	NguoiChoi a;
	strcpy(a.ten, s);
	a.socau = temp - 1;
	GhiFileXepHang(a);
	fflush(stdin);
	system("cls");
	ThaoTacMenu();
}
void XuLiKetThuc(int temp)
{
	system("cls");
	char s[25];
	NguoiChoi a;
	textcolor(14);
	gotoxy(40, 15);
	printf("Ban da tra loi sai :) ");
	gotoxy(40, 17);
	if (temp < 5)
	{
		printf("Ban duoc ban: 0 USD ");
	}
	if (temp >= 5 && temp < 10)
	{
		printf("ban duoc ban  : %s", moctien[4]);
	}
	if (temp >= 10)
	{
		printf("ban duoc ban  : %s", moctien[9]);
	}
	fflush(stdin);
	gotoxy(40, 19);
	printf("Nhap ten nguoi choi de luu ket qua: ");
	gets(s);
	strcpy(a.ten, s);
	a.socau = temp - 1;
	GhiFileXepHang(a);
}