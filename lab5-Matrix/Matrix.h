#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
typedef int TKey;

struct Tupel {
	int linie;
	int coloana;
	TElem val;
};

//struct HashTable {
//	Tupel T;
//	Tupel info;
//	//int m;
//};

class Matrix {

private:
	//TODO - Representation
	Tupel* T; //array pt elem 
	//int i = 0;
	//int c1 = 0;
	//int c2=1;
	//int m; //lungimea array-ului
	//int size = 0;
	//int hashing(TKey key) const //functia hash
	//{
	//	for (int i = 0; i <= m - 1; i++);
	//	{
	//		if (key < 0)
	//			return (-1) * ((key % m) + c1 * i + c2 * i ^ 2);
	//		return (key % m);
	//	}
	//}
	int capacity = 16;
	int size;
	//int hashing(int e, int cap, int i)
	//{
	//	//Complexitate O(1)

	//	//Functia care returneaza elementul hashuit pentru gasirea pozitiei in vector
	//	//Capacitatea a fost aleasa ca fiind putere a lui 2, ca sa se poata alege constantele de calcul c1 si c2 ca fiind ambele 0.5
	//	if (e < 0)
	//		return(int(-(e % cap) + 0.5 * i + 0.5 * i * i) % cap);
	//	else
	//		return(int((e % cap) + 0.5 * i + 0.5 * i * i) % cap);

	//}

	int NrLinii;
	int NrCol;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	int hashing(int e, int cap, int i) const;
};
