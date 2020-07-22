#include <iostream>
#include <fstream>

using namespace std;

struct Nlist
{
	int to;
	int weight;
	Nlist* next;
};

struct Elist
{
	int from;
	int to;
	int weight;
	Elist* next;
};

void showM(int** tab, int rozmiar);
void showTab(int* tab, int rozmiar);

void show_Nlist(Nlist** H, int rozmiar);
void AddLN(Nlist*& H, int x, int y);

void AddLE(Elist*& H, int x, int y, int z);
void show_Elist(Elist* H);

void Prima(Nlist** H,int s ,int* tab, int rozmiar, Elist *&K);

int main()
{

	int rozmiar, ** AdjM, * kolor, s;
	Nlist** LN = NULL;
	Elist* LE = NULL;

	fstream plik;
	plik.open("graf.txt");
	plik >> rozmiar;

	AdjM = new int* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		AdjM[i] = new int[rozmiar];

	//Wypelnienie AdjM
	for(int i = 0;i<rozmiar;i++)
		for (int j = 0; j < rozmiar; j++)
			plik >> AdjM[i][j];

	LN = new Nlist * [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		LN[i] = NULL;

	//wypelnienie LN
	for (int i = 0; i < rozmiar; i++)
		for (int j = 0; j < rozmiar; j++)
			if (AdjM[i][j] != 0)
				AddLN(LN[i], j, AdjM[i][j]);

	show_Nlist(LN, rozmiar);
	//Inicjacja tabeli kolor oraz wype³nienie zerami
	kolor = new int[rozmiar];
	for (int i = 0; i < rozmiar; i++)
		kolor[i] = 0;
	////////////////////////////////////////////////



	/*
	1. s -> wierzcho³ek startowy
	2. ustawiamy kolor[s] na 1;
	3. szukamy najmniejszej œcie¿ki do wierzcho³ków s¹siaduj¹cych z wybranym wierzch. pocz¹tkowym
	*/

	s = 0; // 3 wierzcholek -> iteracja od 0..1..2 -> 3
	kolor[s] = 1;
	showTab(kolor, rozmiar);
	Prima(LN, s, kolor, rozmiar, LE);

	delete[] kolor, LN, AdjM;
	delete LE;

}

void showM(int** tab, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void show_Nlist(Nlist** H,int rozmiar)
{
	Nlist* p = NULL;

	for (int i = 0; i < rozmiar; i++)
	{
		p = H[i];
		cout << "LN[" << i+1 << "]->";
		while (p)
		{
			cout << p->to + 1 << "(" << p->weight << ")->";
			p = p->next;
		}
		cout << "NULL" << endl;
	}

	cout << endl;

}

void AddLN(Nlist*& H, int x, int y)
{
	Nlist* p = new Nlist;
	p->to = x;
	p->weight = y;
	p->next = H;
	H = p;
}

void AddLE(Elist*& H, int x, int y, int z)
{
	Elist* p = new Elist;
	p->from = x;
	p->to = y;
	p->weight = z;
	p->next = H;
	H = p;
}

void showTab(int* tab, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		cout << tab[i] << " ";
	}
	cout << endl;
}

void show_Elist(Elist* H)
{
	Elist* p = NULL;

	p = H;
	cout << "MDR->";
	while (p)
	{
		cout << p->from + 1 << "/" << p->to+1 << "/"<< p->weight << "->";
		p = p->next;
	}
	cout << "NULL" << endl;

	cout << endl;

}

void Prima(Nlist** H,int s, int* tab, int rozmiar, Elist *&K)
{
	int liczba_krawedzi = 0, V = s, min = 0, from = 0;
	Nlist* temp = NULL,* p = NULL;

	while (liczba_krawedzi < rozmiar - 1)
	{
		min = INT_MAX;
		for (int i = 0; i < rozmiar; i++)
		{
			if (tab[i] == 1)
			{
				for (p = H[i]; p; p = p->next)
				{
					if (min > p->weight && tab[p->to] == 0)
					{
						min = p->weight;
						V = p->to;
						from = i;
						temp = p;
					}
				}
			}

		}
		tab[V] = 1;
		AddLE(K, from, temp->to, temp->weight);
		++liczba_krawedzi;
		showTab(tab, rozmiar);
	}

	show_Elist(K);
}