#include <iostream>
#include <math.h>
#include <bitset>
#include "Heming.h"
using namespace std;



int Heming::calculateNumberOfSecurityBits(int k) {
	if (k >= 2 && k <= 4) {
		return 3;
	}
	else if (k >= 5 && k <= 11) {
		return 4;
	}
	else if (k >= 12 && k <= 26) {
		return 5;

	}
	else if (k >= 27 && k <= 57) {
		return 6;
	}
	else if (k == 1) {
		return 2;
	}
}

void Heming::insertCodeWord() {
	//Unos informacionih bita
	cout << "Unesi kodnu rec bit po bit:" << endl;
	for (int i = 0; i < k; ) {
		char temp;
		cin >> temp;

		if (temp == '0')      infWord[i++] = false;
		else if (temp == '1') infWord[i++] = true;
		else                  cout << "Uneti ponvo " << i+1 << "-ti bit infromacione reci" << endl;
	}	
	
	cout << endl << "=======Sablon=======" << endl;

	this->numOfSecurSecurityBits = calculateNumberOfSecurityBits(k);

	for (int i = 1, maska = 1, j = 1, p = 1; i <= n; i++) {
		string binary = bitset<BIT_LENGHT>(i).to_string();
		cout << i << "\t" << binary<< "\t";
		if (i & maska) {
			if (j > numOfSecurSecurityBits)
				cout << "---Z" << endl;
			else 
				cout << "Z" << j << endl;
			maska <<= 1;
			j++;
		}
		else {
			if(p > k)
				cout << "---" << endl;
			else 
				cout << "I" << p << endl;
			p++;
		}
	}

	n = k + numOfSecurSecurityBits;
	//cout << "N:  " << n << "   Number of Security Bits is  " << numOfSecurSecurityBits << endl; //TEST
}

void Heming::initCodeWord() {
	int maska = 1, j = 0;

	for (int i = 0; i < n; i++) {
		if ((i + 1) & maska) {
			codeWord[i] = -1;
			maska <<= 1;
		}
		else {
			codeWord[i] = infWord[j++];
		}
	}

	cout << "Kodna rec bez zastinih bita je: " << endl;

	for (int i = 0, j = 0, maska = 1; i < n; i++) {
		if ((i + 1) & maska) {
			cout << "Z" << ++j << " ";
			maska <<= 1;
		}
		else
			if (codeWord[i] == INIT_ERROR)
				cout << "X" << "  "; 
			else
				cout << codeWord[i] << "  ";
	}
	if (d) 
		cout << "ZP";
	
	cout << endl;
}

void Heming::insertSecurityBits() {

	//Odredjivanje zastitnih bita (bez bita parnosti)
	for (int i = 0, maska = 1; i < numOfSecurSecurityBits; i++, maska <<=1) {
		for (int j = 0; j < n; j++) {
			if (codeWord[j] != -1 && (j+1)&maska ) {
				if (codeWord[j] == INIT_ERROR) continue;
				securyBits[i] ^= codeWord[j];
				//cout << codeWord[j] << " + "; //TEST
			}
		}
		//cout << endl; //TETSs
	}
	//Ubacivanje zastgitnih bita u poruku koju prenostimo (bez bita parnosti)
	for (int i = 0, j = 0; i < n; i++) {
		if (codeWord[i] == -1) {
			if(codeWord[i] != INIT_ERROR)
				codeWord[i] = securyBits[j++];
		}
	}

	//Odredjivanje bita parnosti i ubacivanje u poruku, ako je zahtevano!
	if (d) { 
		for (int i = 0; i < n; i++) 
			if(codeWord[i] != INIT_ERROR)
				securyBits[numOfSecurSecurityBits] ^= codeWord[i];
		
		codeWord[n] = securyBits[numOfSecurSecurityBits];
	}
	
	//Ispis zastitnih bitova 
	cout << "Zastitni biti: " << endl;
	for (int i = 0; i < numOfSecurSecurityBits + d; i++) 
		cout << "Z" << i + 1 << " = " << securyBits[i] << endl;
	cout << endl;

	//Ispis poruke koju trebamo da prenesemo (jos se nije desila greska)!
	n += d;
	cout << "Kodna rec od N = " << n << " bita:"  << endl;
	
	for (int i = 0; i < n; i++) {
		cout << codeWord[i] << "  ";
	}
	cout << endl;
}

void Heming::invertBit(int e, bool print) {
	for (int i = 0; i < n; i++) {
		if (i + 1 == e) {
			if (codeWordWithError[i] == 0)
				codeWordWithError[i] = 1;
			else
				codeWordWithError[i] = 0;
		}
	}

	if (print) {
		cout << "Kod posle korigovanje greske na mestu koje nam sindrom pokazuje: " << endl;
		for (int i = 0; i < n; i++)
			cout << codeWordWithError[i] << "  ";
		cout << endl;
	}
}
bool Heming::bitPermutation(int e) {
	
	for (int i = 0;i < n + d;i++) 
		codeWordWithError[i] = codeWord[i];
	
	//Greska na bitu!
	if (e == -1) {
		short numOfError = 0;
		cout << "Unesi broj gresaka (1 ili 2)" << endl;
		cin >> numOfError;

		if (numOfError == 0) {
			cout << "Nema greske!" << endl;
			return false;
		}
		for (short i = 0; i < numOfError; i++) {
			
			cout << "Unesi poziciju " << i+1 << ". greske: " << endl;
			cin >> errors[i];

			while (errors[i] < 0 || errors[i] > n + d) {
				cout << "Pogresna vrednost je uneta za pozicju greske, unesi ponovo" << endl;
				cin >> errors[i];
			}
			if(errors[i] != 0)
				invertBit(errors[i],false);
		}
	}
	

	//Ispis
	cout << "Kod sa greskom: " << endl;
	for (int i = 0; i < n; i++) 
		cout << codeWordWithError[i] << "  ";
	cout << endl;

	return true;
}

void Heming::findSindrom() {
	
	int lengthSyndrom = ceil(log2(n));

	sindrom = 0;

	for (int i = 0, s = 0, maska = 1; i < lengthSyndrom; i++, s = 0, maska <<= 1) {
		for (int j = 0; j < n; j++) {
			//cout << codeWordWithError[j] << " + ";
			if (((j + 1)&maska) && (codeWordWithError[j] != INIT_ERROR)) {
				s ^= codeWordWithError[j];
			}
		}
		//cout << endl;
		sindrom |= (s << i);

	}
	cout << "Sindorm: " << sindrom << endl;

	if (d) {
		sindromLastBit = 0;
		for (int i = 0;i < n + d;i++) 
			sindromLastBit ^= codeWordWithError[i];
		cout << "Last Bit sindrom : " << sindromLastBit << endl; //TEST
	}
}

void Heming::writeCommenar() {
	if (d) {
		/*
		1) S = 0 , Sp = 0 - nije bilo greske!
		2) S = 0 , Sp = 1 - greska je na bitu parnosti!
		3) S > 0 , Sp = 0 - paran broj gresaka   (najverovtnije 2)
		4) S > 0	, Sp = 1 - neparan broj gresaka (najverovatnije 1)
		*/
	
		cout << "Poslednji bit :" << codeWordWithError[n - 1] << endl;
		if (sindrom == 0) {
			if (sindromLastBit == 0)
				cout << "Nije bilo greske!" << endl;
			else
				cout << "Greska je na bitu parnosti!" << endl;
		}
		else {
			if (sindromLastBit == 0)
				cout << "Paran broj gresaka! Ispravljen kod nije validan, sindrom ne pokazuje poziciju greske" << endl;
			else
				cout << "Neparan broj gresaka! Sindrom pokazuje gresku. Greska je bila na " << sindrom << "-bitu" << endl;
		}

	}
	else {
		if (sindrom == 0) {
			cout << "Greske nije bilo!" << endl;
		}
		else cout << "Greske je bilo na " << sindrom << "-bitu" << endl;
	}
}

Heming::Heming(int n, int k, bool d) {
	this->n = n;
	this->k = k;
	this->d = d;
}

void Heming::code() {

	insertCodeWord();
	initCodeWord();
	insertSecurityBits();

	//Ako vrati false => nije se desila greska, program se zavrsava u suprotnom nastavljamo sa algoritmom
	if (bitPermutation(-1)) {
		findSindrom();
		invertBit(sindrom, true);
		writeCommenar();
	}
}

Heming::~Heming() {
	n = k = d = 0;

	delete infWord;
	delete securyBits;
	delete codeWord;
	delete codeWordWithError;
}

