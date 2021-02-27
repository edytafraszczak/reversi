#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <iostream>
#include "Gra.h"
#include "GraczKomputerowy.h"
#include "GraczUzytkownik.h"
#include <time.h>
using namespace std;






int main() {
	time_t tt;
	srand(time(&tt));

	cout << "Witaj w grze reversi. Czy chcesz grac z komputerem? wybierz 1 " << endl << "czy z innym uzytkownikiem? wybierz 2" << endl;
	Gra<Gracz> gra;
	string nazwa1Uzytkownika, nazwa2Uzytkownika;
	int wybranaOpcja;
	cin >> wybranaOpcja;
	while (!cin)
	{
		// wpisano coœ, co nie jest liczb¹
		cout << "Podano bledna wartosc liczbowa, podaj jeszcze raz" << endl;
		cin.clear(); // czyœcimy flagi b³êdu strumienia
		cin.sync(); // czyœcimy bufor strumienia
		cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');//ignorowanie wsyzstkich znakow do nowej linii
	}
	if (wybranaOpcja == 1 || wybranaOpcja == 2) {
		cout << "Podaj nazwe pierwszego uzytkownika" << endl;
		cin >> nazwa1Uzytkownika;
		if (wybranaOpcja == 1) {
			gra.rozpocznijGre(new GraczUzytkownik(nazwa1Uzytkownika, 'X'), new GraczKomputerowy("Komputer", 'O'));
		}
		else {
			cout << "Podaj nazwe drugiegi uzytkownika" << endl;
			cin >> nazwa1Uzytkownika;
			gra.rozpocznijGre(new GraczUzytkownik(nazwa1Uzytkownika, 'X'), new GraczUzytkownik(nazwa1Uzytkownika, 'O'));
		}
	}

	else {
		cout << "Podano bledna opcje" << endl;
	}

}
