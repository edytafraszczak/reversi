#ifndef Plansza_H
#define Plansza_H

#include <string>
#include <iostream>
#include <istream>
#include <fstream>



using namespace std;
struct OdpowiedzCzyRuchWlasciwy {
	bool czyWlasciwy;
	int indeksyX[8];
	int indeksyY[8];
};

using namespace std;
class Plansza {
private:
	char plansza[8][8];
	void czyscPlansze() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				plansza[i][j] = ' ';
			}
		}
		plansza[3][3] = 'X';
		plansza[3][4] = 'O';
		plansza[4][3] = 'O';
		plansza[4][4] = 'X';
	}
	bool czyWspolrzedneSaNaPlanszy(int x, int y) {
		return x < 7 && y <7 && x > -1 && y > -1;
	}
	OdpowiedzCzyRuchWlasciwy& czyRuchDozwolony(int x, int y, char znak) {
		//przejscie ze wspolrzednych 1-8, na 1-7
		x--;
		y--;
		//przygotowanie wyniku
		OdpowiedzCzyRuchWlasciwy wynik;
		wynik.czyWlasciwy = false;
		for (int i = 0; i < 8; i++) {
			wynik.indeksyX[i] = -1;
			wynik.indeksyY[i] = -1;
		}
		int ostatnioUstawionyIndeksWTablicyOdpowiedzi = 0;
		//czy ruch w planszy
		if (!czyWspolrzedneSaNaPlanszy(x, y) || plansza[x][y] != ' ')
			return wynik;
		//zakladam ze znak moze byc tutaj ustawiony 
		plansza[x][y] = znak;
		char dozwolonySasiedniZnak = ' ';
		//wyznaczam sasiedni znak
		if (znak == 'X')
			dozwolonySasiedniZnak = 'O';
		else
			dozwolonySasiedniZnak = 'X';
		//sprawdzenie s¹siedztwa
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int xDoSprawdzenia = x + i, yDoSprawdzenia = y + j;
				if (czyWspolrzedneSaNaPlanszy(xDoSprawdzenia, yDoSprawdzenia) && plansza[xDoSprawdzenia][yDoSprawdzenia] == dozwolonySasiedniZnak) {
					xDoSprawdzenia += i;
					yDoSprawdzenia += j;
					//sprawdzenie czy obecnie sprawdzany sasiad znajduje sie w planszy
					if (!czyWspolrzedneSaNaPlanszy(xDoSprawdzenia, yDoSprawdzenia)) {
						continue;
					}
					//sprawdzaj w dozwolonym kierunku az znajdziesz znak taki sam jak dodawany lub skoncz gdy dojdziesz do konca planszy
					while (plansza[xDoSprawdzenia][yDoSprawdzenia] == dozwolonySasiedniZnak) {
						xDoSprawdzenia += i;
						yDoSprawdzenia += j;
						//doszedl do konca planszy
						if (!czyWspolrzedneSaNaPlanszy(xDoSprawdzenia, yDoSprawdzenia)) {
							break;
						}
					}
					//ruch nie jest dozwolony, poniewaz doszedl do konca planszy
					if (!czyWspolrzedneSaNaPlanszy(xDoSprawdzenia, yDoSprawdzenia)) {
						continue;
					}
					// na drodze znajduja sie pionki do przejecia
					if (plansza[xDoSprawdzenia][yDoSprawdzenia] == znak) {
						while (true) {
							xDoSprawdzenia -= i;
							yDoSprawdzenia -= j;
							//dotarlem do miejsca ustawienia pionka
							if (xDoSprawdzenia == x && yDoSprawdzenia == y) {
								break;
							}
							wynik.indeksyX[ostatnioUstawionyIndeksWTablicyOdpowiedzi] = xDoSprawdzenia;
							wynik.indeksyY[ostatnioUstawionyIndeksWTablicyOdpowiedzi] = yDoSprawdzenia;
							ostatnioUstawionyIndeksWTablicyOdpowiedzi++;
						}
					}
				}

			}
		}
		//przywracam stan poczatkowy
		plansza[x][y] = ' ';
		if (ostatnioUstawionyIndeksWTablicyOdpowiedzi > 0) {
			wynik.czyWlasciwy = true;
			if (ostatnioUstawionyIndeksWTablicyOdpowiedzi < 8) {
				wynik.indeksyX[ostatnioUstawionyIndeksWTablicyOdpowiedzi] = x;
				wynik.indeksyY[ostatnioUstawionyIndeksWTablicyOdpowiedzi] = y;
				ostatnioUstawionyIndeksWTablicyOdpowiedzi++;
			}
		}

		return wynik;
	};
public:

	Plansza() {
		czyscPlansze();
	}


	bool zapiszPlansze(string nazwaPliku) {
		fstream plik(nazwaPliku, ios::out);
		if (plik.good())
		{
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					plik << plansza[i][j] << endl;
				}
			}
			plik.close();
			cout << "Gra zostala zapisana do pliku " << nazwaPliku << endl;
			return true;
		}
		else {
			cout << "Blad! Nie zapisano gry do pliku o nazwie " << nazwaPliku << endl;
			return false;
		}
	}

	bool wczytajPlansze(string nazwaPliku) {
		fstream plik(nazwaPliku, ios::in);

		int testowaPlansza[8][8];
		if (plik.good())
		{
			string wiersz;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					//koniec pliku
					if (plik.eof()) {
						cout << "Blad! Zla skladnia pliku o nazwie " << nazwaPliku << endl;
						plik.close();
						return false;
					}
					getline(plik, wiersz);
					if (wiersz.length() == 0) {
						cout << "Blad! Zla skladnia pliku o nazwie " << nazwaPliku << endl;
						plik.close();
						return false;
					}
					char znak = wiersz.at(0);
					if (znak == 'X' || znak == 'O' || znak == ' ') {
						testowaPlansza[i][j] = znak;
					}
					else {
						cout << "Blad! Zla skladnia pliku o nazwie " << nazwaPliku << endl;
						plik.close();
						return false;
					}

				}
			}
			plik.close();
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					plansza[i][j] = testowaPlansza[i][j];
				}
			}
		}
		else {
			cout << "Blad! Nie udalo otworzyc sie pliku o nazwie " << nazwaPliku << endl;
			return false;
		}

	}
	bool czyRuchMozliwy(char znak) {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (czyRuchDozwolony(i, j, znak).czyWlasciwy) {
					return true;
				}
			}
		}
		return false;
	}
	bool wykonajRuch(int x, int y, char znak) {
		OdpowiedzCzyRuchWlasciwy& czyRuchDozwolonyWynik = czyRuchDozwolony(x, y, znak);
		if (czyRuchDozwolonyWynik.czyWlasciwy == true) {
			for (int i = 0; i < 8; i++) {
				if (czyRuchDozwolonyWynik.indeksyX[i] == -1) {
					break;
				}
				plansza[czyRuchDozwolonyWynik.indeksyX[i]][czyRuchDozwolonyWynik.indeksyY[i]] = znak;
			}
		}
		else {
			return false;
		}
	}

	void wypiszPlansze() {
		cout << "    1   2   3   4   5   6   7   8 " << endl;
		cout << "-----------------------------------" << endl;
		for (int i = 0; i < 8; i++) {
			cout << "  |   |   |   |   |   |   |   |   |" << endl;
			cout << i + 1 << " ";
			for (int j = 0; j < 8; j++) {
				cout << "| " << plansza[i][j] << " ";
			}
			cout << "|" << endl;
			cout << "  |   |   |   |   |   |   |   |   |" << endl;
			cout << "-----------------------------------" << endl;
		}
	}


	int obliczWynik(char znak) {
		return sumuj<char>(plansza, znak, 8, 8);
	}


	template <class T1>
	int sumuj(T1 tablica[8][8], T1 doSumowania, int rozmiarX, int rozmiarY)
	{
		int wynik = 0;
		for (int i = 0; i < rozmiarX; i++) {
			for (int j = 0; j < rozmiarY; j++) {
				if (tablica[i][j] == doSumowania) {
					wynik++;
				}
			}
		}
		return wynik;
	}

};
#endif