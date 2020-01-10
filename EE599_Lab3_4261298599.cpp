#include <iostream>
#include <fstream>
#include<string>
#include <stdlib.h>


using namespace std;
#define N 512

class Pancake {
public:
	int pancakeSize;
	bool panckaeBurnt;

public:
	Pancake() {
		pancakeSize = 50;
		panckaeBurnt = 1;
	}
	Pancake(int s, int b) {
		pancakeSize = s;
		panckaeBurnt = b;
	}
	void setSize(int s) {
		pancakeSize = s;
	}
	void setBurnt(bool b) {
		panckaeBurnt = b;
	}

	int getSize() {
		return pancakeSize;
	}
	bool getBurnt() {
		return panckaeBurnt;
	}
	void flip_pancake() {

		panckaeBurnt = !panckaeBurnt;
	}

};

class PancakePile {
public:
	int pancakeNum;
	Pancake *pile;

public:
	PancakePile() {
		pancakeNum = 10;
		pile = new Pancake[pancakeNum];
	}
	PancakePile(int z) {
		pancakeNum = z;
		pile = new Pancake[pancakeNum];
	}
	void setZ(int hh) {
		pancakeNum = hh;
	}
	int getZ() {
		return pancakeNum;
	}

	void setPile(Pancake p, int i) {
		pile[i] = p;
	}

	Pancake getPile(int i) {
		return pile[i];

	}

	void pancake_sort_ascending() {

		int m = pancakeNum;
		for (int i = 0; i < pancakeNum; i++) {
			int mp = 0;
			int index = 0;

			for (int j = 0; j < m; j++) {

				if (pile[j].getSize() > mp) {
					mp = pile[j].getSize();
					index = j;
				}
			}

			rvs(pile, index);
			rvs(pile, m - 1);
			m = m - 1;
		}

	}

	void pancake_sort_descending() {
		int m = pancakeNum;
		for (int i = 0; i < pancakeNum; i++) {
			int mp = 512;
			int index = 0;

			for (int j = 0; j < m; j++) {

				if (pile[j].getSize() < mp) {
					mp = pile[j].getSize();
					index = j;
				}
			}

			rvs(pile, index);
			rvs(pile, m - 1);
			m = m - 1;
		}


	}

	void pancake_sort_ascending_burnt_down() {
		int m = pancakeNum;
		for (int i = 0; i < pancakeNum; i++) {
			int mp = 0;
			int index = 0;

			for (int j = 0; j < m; j++) {

				if (pile[j].getSize() > mp) {
					mp = pile[j].getSize();
					index = j;
				}
			}

			rvs(pile, index);
			rvs(pile, m - 1);
			m = m - 1;
		}


		for (int j = 0; j < pancakeNum; j++) {
			if (pile[j].getBurnt() == 1) {
				pile[j].flip_pancake();
			}

		}

	}

	void pancake_sort_descending_burnt_up() {
		int m = pancakeNum;
		for (int i = 0; i < pancakeNum; i++) {
			int mp = 512;
			int index = 0;

			for (int j = 0; j < m; j++) {

				if (pile[j].getSize() < mp) {
					mp = pile[j].getSize();
					index = j;
				}
			}

			rvs(pile, index);
			rvs(pile, m - 1);
			m = m - 1;
		}
		for (int j = 0; j < pancakeNum; j++) {
			if (pile[j].getBurnt() == 0) {
				pile[j].flip_pancake();
			}
		}
	}

	void rvs(Pancake *ple, int index) {
		for (int i = 0, j = index; i < j; i++, j--) {
			Pancake temp = pile[j];
			ple[j] = ple[i];
			ple[i] = temp;
		}
	}
};


class MPancakePiles {
public:
	int X, Y;
	PancakePile **mpp;

public:
	MPancakePiles() {
		X = 20;
		Y = 20;

		mpp = new PancakePile*[X];
		for (int i = 0; i < X; i++) {
			mpp[i] = new PancakePile[Y];
		}
	}

	MPancakePiles(int x, int y) {
		X = x;
		Y = y;
		mpp = new PancakePile*[X];
		for (int i = 0; i < X; i++) {
			mpp[i] = new PancakePile[Y];
		}
	}


	void setMPP(PancakePile pp, int i, int j) {

		mpp[i][j] = pp;

	}

	PancakePile& getMPP(int x, int y) {

		return mpp[x][y];
	}


	void sort_interior() {
		for (int i = 1; i < X - 1; i++) {
			for (int j = 1; j < Y - 1; j++) {
				mpp[i][j].pancake_sort_ascending_burnt_down();
			}
		}

	}

	void sort_exterior() {
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				if (i == 0 or j == 0 or i == X - 1 or j == Y - 1) {
					mpp[i][j].pancake_sort_descending_burnt_up();
				}

			}
		}
	}
};


int main()
{
	ifstream inFile("input.txt");
	if (!inFile) {
		cerr << "Error opening file.." << endl;
		return(1);
	}

	int x, y, z;


	inFile >> x;
	inFile >> y;
	inFile >> z;

	string a[N];


	int c = 0;
	while (!inFile.eof()) {
		getline(inFile, a[c], ',');
		++c;
		getline(inFile, a[c], ' ');
		++c;
	}

	int h[N];
	for (int i = 0; i < c - 2; i++) {
		h[i] = atoi(a[i].c_str());
	}

	int ***sze;
	sze = new int**[x];
	for (int i = 0; i < x; i++) {

		sze[i] = new int*[y];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			sze[i][j] = new int[z];
		}
	}

	bool ***brnt;
	brnt = new bool**[x];
	for (int i = 0; i < x; i++) {

		brnt[i] = new bool*[y];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			brnt[i][j] = new bool[z];
		}
	}

	MPancakePiles MPP(x, y);

	int m = 0;
	int n = 1;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {

				sze[i][j][k] = h[m];
				brnt[i][j][k] = (bool)h[n];

				MPP.getMPP(i, j).getPile(z).setSize(sze[i][j][k]);
				MPP.getMPP(i, j).getPile(z).setBurnt(brnt[i][j][k]);

				MPP.getMPP(i, j).setZ(z);
				MPP.mpp[i][j].pile[k].setSize(sze[i][j][k]);

				m = m + 2;
				n = n + 2;
			}
		}
	}


	MPP.sort_interior();
	MPP.sort_exterior();

	ofstream outFile("output.txt");
	outFile << x << " " << y << " " << z << "\n";
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {
				outFile << MPP.mpp[i][j].pile[k].getSize();
				outFile << ','<< MPP.mpp[i][j].pile[k].getBurnt()<<" ";
			}
			outFile<< "\n";
		}
	}

	inFile.close();
	return 0;
}

