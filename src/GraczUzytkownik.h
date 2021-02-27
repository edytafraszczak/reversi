#pragma once
#include "Gracz.h"
#include <iostream>
#include <string>
using namespace std;


class GraczUzytkownik : public Gracz {
public:

	GraczUzytkownik() :Gracz("Gracz uzytkownik", ' ') {}
	GraczUzytkownik(string nazwa, char znak) :Gracz(nazwa, znak) {}
	virtual int podajX() {
		cout << "Uzytkowniku " << this->getnazwa() << " podaj X" << endl;
		int x;
		while (!(cin >> x))
		{
			cout << "Podano bledna wartosc liczbowa dla X, podaj jeszcze raz" << endl;
			// wpisano coœ, co nie jest liczb¹
			cin.clear(); // czyœcimy flagi b³êdu strumienia
			cin.sync(); // czyœcimy bufor strumienia
			cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');//ignorowanie wsyzstkich znakow do nowej linii
		}

		return  x;
	}
	virtual int podajY() {
		cout << "Uzytkowniku " << this->getnazwa() << " podaj Y" << endl;
		int y;
		cin >> y;
		while (!cin)
		{
			// wpisano coœ, co nie jest liczb¹
			cout << "Podano bledna wartosc liczbowa dla Y, podaj jeszcze raz" << endl;
			cin.clear(); // czyœcimy flagi b³êdu strumienia
			cin.sync(); // czyœcimy bufor strumienia
			cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');//ignorowanie wsyzstkich znakow do nowej linii
			
		}
		return y;
	}
	virtual void powiadomZeMiejsceNieodpowiednie(int x, int y) {
		cout << "Podany ruch jest niedozwolony"<< endl;
	}
	virtual int podajOpcjeGry() {
		cout << "Uzytkowniku co chcesz zrobic ? 1 - polozyc pionek, 2 - pokaz obecne wyniki, 3 - zapisac stan, 4 - zakonczyc gre (bez zapisu), 5 - wczytac gre, 6 - pokaz wszystkie wyniki" << endl;
		int x;
		cin >> x;
		while (!cin)
		{
			// wpisano coœ, co nie jest liczb¹
			cout << "Podano bledna wartosc liczbowa, podaj jeszcze raz" << endl;
			cin.clear(); // czyœcimy flagi b³êdu strumienia
			cin.sync(); // czyœcimy bufor strumienia
			cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');//ignorowanie wsyzstkich znakow do nowej linii
		}
		return x;
	}
};