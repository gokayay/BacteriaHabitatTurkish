#include <iostream>
#include <fstream>
#include <string>
#include<stdlib.h>
using namespace std;

const int GIRDI_LIMITI = 100;
string bakteriTurleri[4];
string kurallarKayit[GIRDI_LIMITI][2];
string bakteriler[GIRDI_LIMITI];
string bakteriKonumlari[GIRDI_LIMITI][GIRDI_LIMITI];
int satir, sutun;
int bakteriYerleri[GIRDI_LIMITI][2];

void bakterileriAta(string satirS)
{
	char str[50];
	char * pch;
	strcpy(str, satirS.c_str());
	pch = strtok(str, " ");
	for (int i = 0; i < sizeof(pch); i++) {
		bakteriTurleri[i] = pch[i];
	}
}

void kurallariAta(string satirS, int ks)
{
	int s = 0;
	for (int x = 0; x < strlen(satirS.c_str()); x++)
	{
		if (satirS.c_str()[x] == ' ')
		{
			continue;
		}
		else if (satirS.c_str()[x] == '-')
		{
			continue;
		}
		else if (satirS.c_str()[x] == '>')
		{
			s++;
		}
		else
		{
			kurallarKayit[ks][s] = satirS.c_str()[x];
			//cout << kurallarKayit[rc][s] << "\t";
		}
	}
}

void kurallar(string degerler[], int satirC)
{
	int ks = 0;
	for (int x = satirC; x < GIRDI_LIMITI; x++)
	{
		if (degerler[x] != "size:")
		{
			kurallariAta(degerler[x], ks);
			ks++;
			cout << "\n";
		}
		else
		{
			break;
		}
	}
}

void boyut(string satirS)
{
	int s = 0, t = 0;
	string satirT, sutunT;
	for (int x = 0; x < strlen(satirS.c_str()); x++)
	{
		if (satirS.c_str()[x] == ' ')
		{
			continue;
		}
		else
		{
			if (satirS.c_str()[x] == 'x')
			{
				t = 1;
			}
			else
			{
				switch (t)
				{
				case 0:
					satirT += satirS.c_str()[x];
					break;
				case 1:
					sutunT += satirS.c_str()[x];
					break;
				default:
					break;
				}
			}
		}
	}
	satir = atoi(satirT.c_str());
	sutun = atoi(sutunT.c_str());

	//cout << satir << "\t" << sutun;
}

int karaktertamsayilari(char c) {
	switch (c) {
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case '0':
		return 0;
	}

}

int okunanNoktalar(char c1, char c2)
{
	if (c2 != ' ' && c2 != '\0')
	{
		return (karaktertamsayilari(c1) * 10) + karaktertamsayilari(c2);
	}
	else
	{
		return karaktertamsayilari(c1);
	}
}

void bakteriNoktalari(string satirS, int pc)
{
	int s = 0;
	for (int x = 0; x < strlen(satirS.c_str()); x++)
	{
		if (satirS.c_str()[x] == ' ')
		{
			s++;
		}
		else
		{
			if (s == 0)
			{
				bakteriler[pc] = satirS.c_str()[x];
			}
			else if (s == 1)
			{
				bakteriYerleri[pc][s - 1] = okunanNoktalar(satirS.c_str()[x], satirS.c_str()[x + 1]);
			}
			else if (s == 2)
			{
				bakteriYerleri[pc][s - 1] = okunanNoktalar(satirS.c_str()[x], satirS.c_str()[x + 1]);
			}
		}
	}

	//cout << bakteriler[pc] << "\t" << bakteriYerleri[pc][0] << "\t" << bakteriYerleri[pc][1] << "\n";
}

void baslangiclar(string degers[], int satirC)
{
	int pc = 0;
	for (int x = satirC; x < GIRDI_LIMITI; x++)
	{
		if (degers[x] == "")
		{
			return;
		}
		else
		{
			bakteriNoktalari(degers[x], pc);
			pc++;
		}
	}
}

void konumlar()
{
	for (int i = 0; i < GIRDI_LIMITI; i++)
	{
		if (bakteriYerleri[i][0] == 0 && bakteriYerleri[i][1] == 0 && bakteriler[i] == "")
		{
			continue;
		}
		else
		{
			bakteriKonumlari[bakteriYerleri[i][0]][bakteriYerleri[i][1]] = bakteriler[i];
		}
	}
}

void konumlariYazdir()
{
	for (int x = 0; x < satir; x++)
	{
		for (int y = 0; y < sutun; y++)
		{
			cout << bakteriKonumlari[x][y] << " ";
		}
		cout << "\n";
	}
}


bool boslukKontrol(string var)
{
	if (var == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}

string yemek(string bakteri1, string bakteri2)
{
	for (int x = 0; x < GIRDI_LIMITI; x++)
	{
		if (kurallarKayit[x][0] == bakteri1 && kurallarKayit[x][1] == bakteri2)
		{
			return bakteri1;
		}
		else if (kurallarKayit[x][0] == bakteri2 && kurallarKayit[x][1] == bakteri1)
		{
			return bakteri2;
		}
	}
	return bakteri2;
}

void tur()
{
	string GecicibakteriKonums[GIRDI_LIMITI][GIRDI_LIMITI];
	for (int x = 0; x < satir; x++)
	{
		for (int y = 0; y < sutun; y++)
		{
			GecicibakteriKonums[x][y] = bakteriKonumlari[x][y];
		}
	}
	for (int x = 0; x < satir; x++)
	{
		for (int y = 0; y < sutun; y++)
		{
			if (GecicibakteriKonums[x][y] != "")
			{
				if (x - 1 >= 0 && boslukKontrol(bakteriKonumlari[x - 1][y]))
				{
					bakteriKonumlari[x - 1][y] = GecicibakteriKonums[x][y];
				}
				else if (x - 1 >= 0)
				{
					bakteriKonumlari[x - 1][y] = yemek(GecicibakteriKonums[x][y], bakteriKonumlari[x - 1][y]);
				}
				if (y - 1 >= 0 && boslukKontrol(bakteriKonumlari[x][y - 1])) {
					bakteriKonumlari[x][y - 1] = GecicibakteriKonums[x][y];
				}
				else if (y - 1 >= 0)
				{
					bakteriKonumlari[x][y - 1] = yemek(GecicibakteriKonums[x][y], bakteriKonumlari[x][y - 1]);
				}
				if (x + 1 <= satir && boslukKontrol(bakteriKonumlari[x + 1][y])) {
					bakteriKonumlari[x + 1][y] = GecicibakteriKonums[x][y];
				}
				else if (x + 1 <= satir)
				{
					bakteriKonumlari[x + 1][y] = yemek(GecicibakteriKonums[x][y], bakteriKonumlari[x + 1][y]);
				}
				if (y + 1 <= sutun && boslukKontrol(bakteriKonumlari[x][y + 1])) {
					bakteriKonumlari[x][y + 1] = GecicibakteriKonums[x][y];
				}
				else if (y + 1 <= sutun)
				{
					bakteriKonumlari[x][y + 1] = yemek(GecicibakteriKonums[x][y], bakteriKonumlari[x][y + 1]);
				}
			}
		}
	}
	konumlariYazdir();
}

bool bitisKontrol()
{
	string tmpChar = "";
	for (int x = 0; x < satir; x++)
	{
		for (int y = 0; y < sutun; y++)
		{
			if (tmpChar == "")
			{
				tmpChar = bakteriKonumlari[x][y];
			}
			else if (tmpChar != bakteriKonumlari[x][y])
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	string gecici, siraDosya[GIRDI_LIMITI];
	int i = 0, limitI = 0, turn = 0;
	char myString[100];

	FILE *pFile = fopen("data.txt", "r");

	while (fgets(myString, 100, pFile))
	{
		puts(myString);
		siraDosya[i] = myString;
		if (i - 1 > 0)
			siraDosya[i - 1] = siraDosya[i - 1].substr(0, siraDosya[i - 1].length() - 1);
		limitI = i;
		i++;
	}

	for (int x = 0; x < limitI; x++)
	{
		if (siraDosya[x] == "" || x == 20)
		{
			continue;
		}
		else if (siraDosya[x] == "bacteria:")
		{
			bakterileriAta(siraDosya[x + 1]);
		}
		else if (siraDosya[x] == "rules:")
		{
			kurallar(siraDosya, x + 1);
		}
		else if (siraDosya[x] == "size:")
		{
			boyut(siraDosya[x + 1]);
		}
		else if (siraDosya[x] == "start:")
		{
			baslangiclar(siraDosya, x + 1);
		}
	}

	konumlar();
	konumlariYazdir();

	i = 0;
	while (!bitisKontrol())
	{
		cout << "Turn : " << i << "\n";
		tur();
		cout << "\n";
		i++;
	}

	getchar();
	getchar();
	return 0;
}