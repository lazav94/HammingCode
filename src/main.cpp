#include<iostream>
#include "Heming.h"
using  namespace std;

#define N 40


int main() { 
	//int n = N; TEST
	//1 1 0 1  0 1 0 1  0 0 1 0  1 0 1 1  0 1 0 0  1 0 0 0  1 0 0 1  0 0

	cout << "=========Hemingov kod=========" << endl << endl;
	// (7,4) (15,11) (31,26) -> bez bita parnosti
	// (8,4) (16,11) (32,26) -> sa  bit  parnosti
	// skraceni (x,y) .. x je manje nego sto je obicno ako je 1 to je onda obican kod sa ponavljanjem! 
		
	

	/***********************USER INSERT*******************************/
	int n;
	cout << "Uneti duzinu kodne reci (minimalno 7)" << endl;
	cin >> n;

	while (n < 7) {
		cout << "Broj n je manji od 7, uneti ponovo" << endl;
		cin >> n;
	}

	char yn;
	bool detection;

	cout << "Da li zelite detekciju 2 greske? y/n (Y/N)(1/0)" << endl;

	while (true) {
		cin >> yn;

		if (yn == 'y' || yn == 'Y' || yn == '1')
			detection = true;
		else if (yn == 'n' || yn == 'N' || yn == '0')
			detection = false;

		if (yn == 'y' || yn == 'Y' || yn == 'n' || yn == 'N') break;

		cout << "Uneta je pogresna opcija! Unesi ponovo y/n(Y/N)" << endl;

	}

	int k;
	cout << "Uneti duzinu informacionih bita" << endl;
	cin >> k;

	//bool detection = true; //TEST

	int uslovK = k + ceil(log2(k + 1)) + detection;
	cout << "Uslov za K: " << uslovK << endl;
	while (k < 1 || uslovK > n) {
		cout << "Unesi ponovo K" << endl;
		cin >> k;
		uslovK = k + ceil(log2(k + 1)) + detection;
	}

	/*********************END USERR INSERT******************************/

	Heming* H = new Heming(n, k, detection);
	H->code();
	
		
	system("PAUSE");
	return 0;


}

