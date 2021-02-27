#pragma once
#include <iostream>
using namespace std;
class Gracz {
private:
	string nazwa;
	char znak;
public:

	Gracz() : Gracz("Uzytkownik", ' ') {}
	Gracz(string nazwa, char znak) :nazwa(nazwa),znak(znak) {
	}
	string getnazwa() { return this->nazwa; }
	void setnazwa(string nazwa) { this->nazwa = nazwa; }

	char getznak() { return this->znak; }
	void setznak(char znak) { this->znak = znak; }

	virtual void powiadomZeMiejsceNieodpowiednie(int x, int y) {
	}
	virtual int podajOpcjeGry() {
		return 1;
	}
	virtual int podajX() { return -1; };
	virtual int podajY() { return -1; };
};