#ifndef __ALGORITMO_H__
#define __ALGORITMO_H__

#include <iostream>
#include <vector>
#include <windows.h>
#pragma comment(lib, "user32.lib") 

using namespace std;
class UFDS {
public:
	vector<int> p, rank, setSizes, maxSizes, pinmediato;
	int numSets;
public:
	//Constructor
	UFDS() {
		int p = { 0 };
		int rank = { 0 };
		int setSizes = { 0 };
		int maxSizes = { 0 };
		int pinmediato = { 0 };
		numSets = 0;
	}

	//Métodos a ser usados en el algoritmo
	void makeSet(int N);
	int findSet(int i);
	int findSetPinmediato(int i);
	bool isSameSet(int i, int j);
	void unionSet(int i, int j);
	void unionSimple(int i, int j);
	int setSize(int i);
	int numDisjointSets();
	vector <int> getPadres();
	int getChildren(int i);
	vector <int> getHijos(int i);
};

void UFDS::makeSet(int N) {
	numSets = N;
	rank.assign(N, 0);
	p.assign(N, 0);
	pinmediato.assign(N, 0);
	for (int i = 0; i < N; i++) {
		p[i] = i;
		pinmediato[i] = i;
	}
	setSizes.assign(N, 1);
}

int UFDS::findSet(int i) {
	return (p[i] == i) ? i : p[i] = findSet(p[i]);
}

int UFDS::findSetPinmediato(int i) {
	return (pinmediato[i] == i) ? i : findSetPinmediato(pinmediato[i]);
}
int UFDS::getChildren(int i) {
	int MAX = 0;
	if (p[i] != i) {
		return MAX = setSizes[i] - 1;
	}
	else {
		return MAX;
	}
}

bool UFDS::isSameSet(int i, int j) {
	return findSet(i) == findSet(j);
}
void UFDS::unionSet(int i, int j) {
	unionSimple(i, j);
	if (!isSameSet(i, j)) {
		int x = findSet(i), y = findSet(j);
		if (rank[x] > rank[y]) {
			setSizes[findSet(x)] += setSizes[findSet(y)];
			p[y] = x;
		}
		else {
			setSizes[findSet(y)] += setSizes[findSet(x)];
			p[x] = y;
			if (rank[x] == rank[y])
				rank[y]++;
		}
		numSets--;
	}
}

void UFDS::unionSimple(int i, int j) {
	int xRoot = findSetPinmediato(i);    //Obtengo la raiz de la componente del vértice X
	int yRoot = findSetPinmediato(j);    //Obtengo la raiz de la componente del vértice Y
	pinmediato[xRoot] = yRoot;   //Mezclo ambos arboles o conjuntos, actualizando su padre de alguno de ellos como la raiz de otro
}

int UFDS::setSize(int i) {
	return setSizes[findSet(i)];
}
int UFDS::numDisjointSets() {
	return numSets;
}
vector <int> UFDS::getPadres() {
	vector <int> padres;
	for (int i = 0; i < p.size(); i++) {
		if (p[i] == i) {
			padres.push_back(i);
		}
	}
	return padres;
}

vector<int>  UFDS::getHijos(int padre) {
	vector<int> hijosXP;
	for (int i = 0; i < pinmediato.size(); i++) {
		if (padre == pinmediato[i] && padre != i ) {
			hijosXP.push_back(i);
		}	
	}
	return hijosXP;
}


#endif