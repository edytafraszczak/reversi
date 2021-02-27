#pragma once
#include "Plansza.h"
#include "Gracz.h"
#include <string>
#include <iostream>
using namespace std;
template <typename KlasaGracza> class Gra {
private:
	Plansza plansza;
	KlasaGracza* gracz1;
	KlasaGracza* gracz2;

	KlasaGracza* obecnyGracz;

	void czekajAzGraczBedzieChcialPostawicPionek() {
		//dozwolone opcje 1-> gra, 2 -> pokaz wynik gracz 3->zapisz gre, 4->skoncz, 5->zalduj gre z pliku
		int opcjaGracza = 1;
		do {
			opcjaGracza = obecnyGracz->podajOpcjeGry();
			if (opcjaGracza == 2) {
				cout << "Twoj wynik to " << plansza.obliczWynik(obecnyGracz->getznak()) << endl;
			}
			else if (opcjaGracza == 3) {
				string nazwaGry;
				cout << "Podaj nazwe pliku do zapisu" << endl;
				cin >> nazwaGry;
				plansza.zapiszPlansze(nazwaGry);
			}
			else if (opcjaGracza == 4) {
				cout << "Dziekuje za gre" << endl;
				exit(0);
			}
			else if (opcjaGracza == 5) {
				string nazwaGry;
				cout << "Podaj nazwe pliku do odczytu" << endl;
				cin >> nazwaGry;
				if (plansza.wczytajPlansze(nazwaGry)) {
					cout << "Rozpoczynamy nowa gre" << endl;
					wybierzRozpoczynajacego();
					rozpocznijPojedynek();
				}
			}
			else if (opcjaGracza == 6) {
				wypiszWszsytkieWyniki();
			}
			else if(opcjaGracza != 1) {
				cout << "Podano bledna opcje" << endl;
			}
		} while (opcjaGracza != 1);
	}
	void rozpocznijPojedynek() {
		while (plansza.czyRuchMozliwy('X') || plansza.czyRuchMozliwy('O')) {
			int x, y;
			plansza.wypiszPlansze();
			cout << "Ruch ma " << obecnyGracz->getnazwa() << " jego znak to " << obecnyGracz->getznak() << endl;
			while (true) {
				czekajAzGraczBedzieChcialPostawicPionek();

				x = obecnyGracz->podajX();
				y = obecnyGracz->podajY();

				if (plansza.wykonajRuch(x, y, obecnyGracz->getznak())) {
					cout << "Wykonano ruch na " << x << " " << y << " postawiono " << obecnyGracz->getznak() << endl;
					cout << endl << endl;
					przelaczGracza();
					break;
				}
				else {
					obecnyGracz->powiadomZeMiejsceNieodpowiednie(x, y);
				}
			}
		}
		int wynikG1 = plansza.obliczWynik(gracz1->getznak());
		int wynikG2 = plansza.obliczWynik(gracz2->getznak());
		if (wynikG1 > wynikG2) {
			cout << "Wygral gracz " << gracz1->getnazwa() << "z wynikiem " << wynikG1 << " gracz 2 uzyskal wynik " << wynikG2 << endl;
		}
		else if (wynikG1 < wynikG2) {
			cout << "Wygral gracz " << gracz2->getnazwa() << "z wynikiem " << wynikG2 << " gracz 1 uzyskal wynik " << wynikG1 << endl;
		}
		else {
			cout << "Remis" << endl;
		}
		zapiszWyniki();
		cout << "Dziekuje za gre " << endl;
		system("pause");
	}

	void wybierzRozpoczynajacego() {
		if (rand() % 2 == 0) {
			obecnyGracz = gracz1;
		}
		else {
			obecnyGracz = gracz2;
		}
	}

	void przelaczGracza() {
		if (obecnyGracz == gracz1) {
			obecnyGracz = gracz2;
		}
		else {
			obecnyGracz = gracz1;
		}
		if (!plansza.czyRuchMozliwy(obecnyGracz->getznak())) {
			cout << "Gracz traci ruch ze wzledu na brak mozliwosci ruchu " << obecnyGracz->getnazwa() << endl;
			if (obecnyGracz == gracz1) {
				obecnyGracz = gracz2;
			}
			else {
				obecnyGracz = gracz1;
			}
		}
	}

	void wypiszWszsytkieWyniki() {
		fstream plik("wyniki.txt");
		if (plik.good())
		{
			cout << "Obecne wyniki" << endl;
			string linia;
			while (!plik.eof())
			{
				getline(plik, linia);
				cout << linia << endl;
			}
		}
		else {
			cout << "Blad! Problem z odczytem pliku wynikow " << endl;
		}
	}
	void zapiszWyniki() {
		fstream plik("wyniki.txt", std::ios::app);
		if (plik.good())
		{
			plik << gracz1->getnazwa() << " " << plansza.obliczWynik(gracz1->getznak()) << endl;
			plik << gracz2->getnazwa() << " " << plansza.obliczWynik(gracz2->getznak()) << endl;
			plik.close();
			cout << "Wyniki zostaly zapisane do pliku" << endl;
		}
		else {
			cout << "Blad! Problem z zapisem pliku wynikow " << endl;
		}
	}
public:

	Gra() : gracz1(NULL), gracz2(NULL), obecnyGracz(NULL), plansza() {

	}

	void rozpocznijGre(KlasaGracza* gracz1, KlasaGracza* gracz2) {
		this->gracz1 = gracz1;
		this->gracz2 = gracz2;
		this->wybierzRozpoczynajacego();

		rozpocznijPojedynek();
	}
};