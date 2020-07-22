#include <iostream>
#include <fstream>

using namespace std;

struct Elist
{
	int from;
	int to;
	int weight;
	Elist* next;
};

void showM(int** tab, int rozmiar);
void showTab(int* tab, int rozmiar);

void AddLE(Elist*& H, int x, int y, int z);
void sortLE(Elist*& H, Elist*& Sorted);
void showLE(Elist* H);

void Kruskal(Elist*& H, int* kolor, int* las, int it_las, int rozmiar, Elist*& MDR);

int main()
{
	int** AdjM, * kolor, * las, it_las, rozmiar;
	Elist* LE = NULL, * sortedLE = NULL, * MDR = NULL;
	fstream plik;
	plik.open("graf.txt");
	plik >> rozmiar;

	AdjM = new int* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		AdjM[i] = new int [rozmiar];

	for (int i = 0; i < rozmiar; i++)
		for (int j = 0; j < rozmiar; j++)
			plik >> AdjM[i][j];

	kolor = new int[rozmiar];
	for (int i = 0; i < rozmiar; i++)
		kolor[i] = 0;

	las = new int[rozmiar];
	it_las = 0;
	for (int i = 0; i < rozmiar; i++)
		las[i] = 0;

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (AdjM[i][j] != 0 && i <= j)
				AddLE(LE, i, j, AdjM[i][j]);
		}

	}

	sortLE(LE, sortedLE);
	showLE(sortedLE);

	Kruskal(sortedLE, kolor, las, it_las, rozmiar, MDR);

	return 0;
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

void showLE(Elist* H)
{
	Elist* p = H;
	cout << "LE->";
	while (p)
	{
		cout << p->from + 1 << "/" << p->to + 1 << "/" << p->weight << "->";
		p = p->next;
	}
	cout << "NULL" << endl << endl;
}

void sortLE(Elist*& H, Elist*& nowa)
{
	while (H)
	{
		if (nowa == NULL || nowa->weight > H->weight)
			AddLE(nowa, H->from, H->to, H->weight);
		else
		{
			Elist* p = H;
			Elist* p1 = nowa;
			while (p1->next && p1->next->weight < p->weight)
			{
				//p = p->next;
				p1 = p1->next;
			}
			AddLE(p1->next, p->from, p->to, p->weight);
		}
		H = H->next;
	}
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

void showTab(int* tab, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		cout << tab[i];
	}
	cout << " ";
}

void Kruskal(Elist*&H, int*kolor, int*las,int it_las, int rozmiar, Elist*&MDR)
{
	int liczba_krawedzi = 0;
	int from = 0, to = 0, weight = 0, x = 0, y = 0;
	Elist* p = NULL, * e = NULL;
	p = H;
	while (liczba_krawedzi<rozmiar)
	{
		from = p->from;
		to = p->to;
		weight = p->weight;
		for (int i = 0; i < rozmiar; i++)
		{
			if (kolor[from] == 0 && kolor[to] == 0)
			{
				kolor[from] = 1;
				kolor[to] = 1;

				it_las++;
				las[from] = it_las;
				las[to] = it_las;
				AddLE(MDR, from, to, weight);
			}

			else if (kolor[from] == 1 && kolor[to] == 0)
			{
				kolor[to] = 1;
				las[to] = las[from];
				AddLE(MDR, from, to, weight);
			}

			else if (kolor[from] == 0 && kolor[to] == 1)
			{
				kolor[from] = 1;
				las[from] = las[to];
				AddLE(MDR, from, to, weight);
			}

		}

		if (kolor[from] == 1 && kolor[to] == 1)
		{
			if (las[from] != las[to])
			{
				x = las[from];
				y = las[to];
				it_las++;
				{
					for (int j = 0; j < rozmiar; j++)
					{
						if (las[j] == x || las[j] == y)
							las[j] = it_las;
					}
				}
				AddLE(MDR, from, to, weight);
			}

		}

		showTab(kolor, rozmiar);
		showTab(las, rozmiar);
		cout << endl;

		p = p->next;
		++liczba_krawedzi;
	}
	showLE(MDR);
}