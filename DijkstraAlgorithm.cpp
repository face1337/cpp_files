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

struct AdjM
{
	int** tab;
	int size;
};

AdjM createMatrix(string nazwa_pliku);
void createMatrix_fromLN(Nlist** H, int rozmiar,int **&tab);
int** createMatrix_fromLE(Elist* H, int rozmiar);


Nlist** createLN(string nazwa_pliku); //utworzenie listy s¹siedztwa z pliku

Nlist** createLN_fromLE(Elist*& H, int rozmiar);

Elist* createLE_fromLN(Nlist** H, int rozmiar);

Elist* createLE(string nazwa_pliku);


void AddLE(Elist*& H, int x, int y, int z);
void showLE(Elist* H);

void AddLN(Nlist*& H, int x, int y);
void showLN(Nlist** H, int rozmiar);

void Dijkstra(Nlist** H, int rozmiar, int*kolor, int*o, int*p);
void showTab(int* tab, int rozmiar);
void showM(int** tab, int rozmiar);

int main()
{
	Nlist** LN = NULL, ** LNLE = NULL;
	Elist* LE = NULL, * LELN = NULL;
	int rozmiar, *kolor, *p ,*o;
	fstream plik;
	plik.open("graf.txt");
	plik >> rozmiar;


	LN = createLN("graf.txt");
	showLN(LN, rozmiar);

	LE = createLE("graf.txt");

	kolor = new int[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		kolor[i] = 0;
	}
	p = new int[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		p[i] = -1;
	}
	o = new int[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		o[i] = INT_MAX;
	}

	Dijkstra(LN, rozmiar, kolor, p, o);


	//int** M = new int* [rozmiar];
	//for (int i = 0; i < rozmiar; i++)
	//	M[i] = new int[rozmiar];



	//for (int i = 0; i < rozmiar; i++)
	//	for (int j = 0; j < rozmiar; j++)
	//	{
	//		M[i][j] = 0;
	//	}



	//p = LN[i];

	int wagi = 0;
	int od = 0;
	int dok = 0;



	//createMatrix_fromLN(LN, rozmiar, M);
	//M = createMatrix_fromLE(LE, rozmiar);
	//LNLE = createLN_fromLE(LE, rozmiar);

	//LELN = createLE_fromLN(LN, rozmiar);

	showM(M, rozmiar);
	//showLN(LNLE, rozmiar);
	//showLE(LELN);

	return 0;
}

AdjM createMatrix(string nazwa_pliku)
{
	AdjM M;
	fstream plik;
	int rozmiar;
	plik.open(nazwa_pliku);
	plik >> rozmiar;

	M.tab = new int* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		M.tab[i] = new int[rozmiar];
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			plik >> M.tab[i][j];
		}
	}

	plik.close();
	return M;
}

Nlist** createLN(string nazwa_pliku)
{
	fstream plik;
	int rozmiar, wartosci = 0;
	plik.open(nazwa_pliku);

	plik >> rozmiar;

	Nlist** LN = new Nlist * [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		LN[i] = NULL;
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			plik >> wartosci;
			if (wartosci > 0)
				AddLN(LN[i], j, wartosci);
		}
	}

	return LN;
}

void AddLE(Elist*& H, int x, int y,int z)
{
	Elist* p = new Elist;
	p->from = x;
	p->to = y;
	p->weight = z;
	p->next = H;
	H = p;
}

Elist* createLE(string nazwa_pliku)
{
	fstream plik;
	int rozmiar, wartosci = 0;
	Elist* LE;
	LE = NULL;

	plik.open(nazwa_pliku);
	plik >> rozmiar;

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			plik >> wartosci;
			if (wartosci > 0 )
			{
				AddLE(LE, i, j, wartosci);
			}
		}
	}
	return LE;
}

void AddLN(Nlist*& H, int x, int y)
{
	Nlist* p = new Nlist;
	p->to = x;
	p->weight = y;
	p->next = H;
	H = p;
}

void showLN(Nlist** H, int rozmiar)
{
	Nlist* p = NULL;
	for (int i = 0; i < rozmiar; i++)
	{
		p = H[i];
		cout << "LN[" << i + 1 << "]->";
		while (p)
		{
			cout << p->to + 1 << "(" << p->weight << ")->";
			p = p->next;
		}
		cout << "NULL" << endl;
	}
	cout << endl;
}

void showLE(Elist* H)
{
	Elist* p = H;
	cout << "MDR from/to/dist->";
	while (p)
	{
		cout << p->to + 1 << "/" << p->from + 1 << "/" << p->weight << "->";
		p = p->next;
	}
	cout << "NULL" << endl;
}

void Dijkstra(Nlist** H, int rozmiar, int *kolor, int*p, int*o)
{
	int i = 0, j = 0, v = 0, s = 0;
	Nlist* e = NULL;
	Elist* MDR = NULL;
	kolor[s] = 1;
	o[s] = 0;

	for (i = 0; i < rozmiar; i++)
	{
		showTab(kolor, rozmiar);
		showTab(p, rozmiar);
		showTab(o, rozmiar);
		cout << "--------------------------" << endl;
		for (j = 0; kolor[j] == 2; j++);
		for (v = j++; j < rozmiar; j++)
		{
			if (kolor[j] != 2 && (o[j] < o[v]))
			{
				v = j;
			}
		}
		kolor[v] = 2;

		for (e = H[v]; e; e = e->next)
		{
			if (kolor[e->to] != 2 && (o[e->to] > o[v] + e->weight))
			{
				kolor[e->to] = 1;
				o[e->to] = o[v] + e->weight;
				p[e->to] = v;
			}
		}

	}
	showTab(kolor, rozmiar);
	showTab(p, rozmiar);
	showTab(o, rozmiar);
	cout << "--------------------------" << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		AddLE(MDR, i, p[i], o[i]);
	}

	showLE(MDR);

}

void showTab(int* tab, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		cout << tab[i] << " ";
	}
	cout << endl;
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
}

void createMatrix_fromLN(Nlist** H, int rozmiar, int **&tab)
{
	for (int i = 0; i < rozmiar; i++)
	{
		Nlist* e = H[i];
		while (e)
		{
			tab[i][e->to] = e->weight;
			e = e->next;
		}
	}
}

/*
Napisz funkcjê, która z listy krawêdzi grafu tworzy macierz s¹siedztwa grafu. Funkcja jako parametry dostaje listê krawêdzi oraz iloœæ wierzcho³ków grafu a zwraca macierz s¹siedztwa.
*/

int** createMatrix_fromLE(Elist* H, int rozmiar)
{
	Elist* p = H;

	int** M = new int* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		M[i] = new int[rozmiar];

	for (int i = 0; i < rozmiar; i++)
		for (int j = 0; j < rozmiar; j++)
		{
			M[i][j] = 0;
		}
	while (p)
	{

		M[p->from][p->to] = p->weight;
		//M[p->to][p->from] = p->weight;  //Jeœli lista jest bez powtórzeñ -> nale¿y dodaæ t¹ linijkê aby pod przekatna te¿ by³y wagi
		p = p->next;
	}

	return M;
}

Nlist** createLN_fromLE(Elist*& H, int rozmiar)
{
	Nlist** LNLE = new Nlist * [rozmiar];
	Elist* p = H;
	for (int i = 0; i < rozmiar; i++)
	{
		LNLE[i] = NULL;
	}


	while (p)
	{
		AddLN(LNLE[p->from], p->to, p->weight);
		//AddLN(LNLE[p->to], p->from, p->weight); //to dodaæ jeœli lista wyst. bez powtorzen
		p = p->next;
	}


	return LNLE;

}

Elist* createLE_fromLN(Nlist** H, int rozmiar)
{
	Elist* LELN = new Elist;
	LELN = NULL;
	
	for (int i = 0; i < rozmiar; i++)
	{
		Nlist* p = H[i];
		Nlist* temp = p;
		while (p)
		{
			AddLE(LELN, i, p->to, p->weight);
			p = p->next;
		}


	}

	return LELN;
}