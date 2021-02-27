#pragma once
#include "Gracz.h"


class GraczKomputerowy : public Gracz {
public:
	GraczKomputerowy() :Gracz("Komputerowy", ' ') {}
	GraczKomputerowy(string nazwa, char znak) :Gracz(nazwa, znak) {}
	virtual int podajX() {
		return  rand() % 8 + 1;
	}
	virtual int podajY() {
		return  rand() % 8 + 1;
	}
};