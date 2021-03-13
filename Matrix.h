#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
struct Tuple
{
	int linie;
	int coloana;
	TElem val;
};
class Iterator;

class Matrix {

private:
	//TODO - Representation
	int Linii;     //nr linii
	int Coloane;  //nr coloane
	int m;       //capacitatea
	int size;   //lungimea Array-ului T
	Tuple* T;

	//Complexitate: Ѳ(1)
	//iau fiecare linie din matrice si le scriu in Array ca o inlantuire de linii, dar ale caror elem trebuie sa le determin pozitia din Array
	int hashing(int i, int j, int k) const
	{
		int e = i * i + j * j; //calculez pozitia din Array-ul T a elem din matrice(linia i, col j)
		if (e < 0)
			return(int(-(e % m) + 0.5 * k + 0.5 * k * k) % m);
		return(int((e % m) + 0.5 * k + 0.5 * k * k) % m);
	}

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

	int search(int i, int j) const;

	//ADT Matrix: Iterator nur über eine Spalte (wird ls Parameter angegeben)
	Iterator iterator(int coloana);//
};

class Iterator
{
private:
	friend class Matrix;
	int linie;
	int coloana;
	Matrix& m;
	Iterator(Matrix& m, int coloana);//iterator pentru patcurgerea lui m pe coloane
public:
	//ma folosesc de ele pentru a putea traversa matricea
	bool valid();
	void next();
	TElem getCurrent();
};
