#include "Matrix.h"
#include <exception>
using namespace std;
#define MIN_TABLE_SIZE 10

int Matrix::hashing(int e, int cap, int i) const
{
	//Complexitate O(1)

	//Functia care returneaza elementul hashuit pentru gasirea pozitiei in vector
	//Capacitatea a fost aleasa ca fiind putere a lui 2, ca sa se poata alege constantele de calcul c1 si c2 ca fiind ambele 0.5
	if (e < 0)
		return(int(-(e % cap) + 0.5 * i + 0.5 * i * i) % cap);
	else
		return(int((e % cap) + 0.5 * i + 0.5 * i * i) % cap);

}

Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	//m = 100;
	T = new Tupel[capacity];
	size = 0;
	for (int i = 0; i < capacity; i++)
	{
		T[i].linie = INT_MIN;
		T[i].coloana = INT_MIN;
		T[i].val = NULL_TELEM;
	}
	NrLinii = nrLines;
	NrCol = nrCols;
}


int Matrix::nrLines() const {
	//TODO - Implementation
	return NrLinii;
}


int Matrix::nrColumns() const {
	//TODO - Implementation
	return NrCol;
}


TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	//Daca pozitia nu e valida arinca exceptie
	if (i<0 || j<0 || i>NrLinii || j>NrCol)
	{
		throw exception();
	}

	i = 0;
	int pos = hashing(T[i].val, capacity, i);
	//daca hashcode-ul este < 0 sau > m, inseamna ca e pozitie invalida
	if (hashing(T[i].val, capacity, i) < 0 || hashing(T[i].val, capacity, i) > capacity)
	{
		throw exception();
	}

	Tupel aux;
	aux = T[pos];
	//daca aux nu e leere position si linia si coloana sunt cele cautate
	if (aux.val != -1 && aux.linie == i && aux.coloana == j)
		return aux.val;//il returnez

	//parcurg lista
	while (T[pos].val != INT_MIN && i<capacity)
	{
		if (T[pos].coloana == j && T[pos].linie == i)
			return aux.val;
		i = i + 1;
		pos= hashing(T[i].val, capacity, i);
	}

	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	//if (i<0 || j<0 || i>NrLinii || j>NrCol)
	//{
	//	throw exception();
	//}
	//if (hashing(j) < 0 || hashing(j) > m)
	//{
	//	throw exception();
	//}

	//Tupel t;
	//t.coloana = 0;
	//t.linie = 0;
	//t.val = 0;
	//Tupel change = t;//salvez vechea val pentru a o returna

	//j = 0;
	//int pos = hashing(j);
	//Tupel head;
	//head = T[pos];

	//Tupel nou;
	//nou.coloana = j;
	//nou.linie = i;
	//nou.val = e;

	////daca este liber
	//if (head.val == NULL_TELEM)
	//{
	//	//nu se schimba nimic in cazul in care si noua val e 0
	//	if (e == 0)
	//		return e;
	//	else//adaug noua val
	//	{
	//		T[pos]=nou;
	//		return change.val;
	//		size++;
	//	}
	//}
	////daca vechea val e dif de 0
	//else if (head.val != NULL_TELEM)
	//{
	//	//si noul elem e 
	//	Tupel current;
	//	current = T[pos];
	//	Tupel previous;
	//	previous = current;
	//	pos = pos + 1;
	//	current = T[pos];
	//}

	//Daca pozitia nu e valida arinca exceptie
	if (i<0 || j<0 || i>NrLinii || j>NrCol)
	{
		throw exception();
	}

	i = 0;
	int pos = hashing(T[i].val, capacity, i);
	//daca hashcode-ul este < 0 sau > m, inseamna ca e pozitie invalida
	if (hashing(T[i].val, capacity, i) < 0 || hashing(T[i].val, capacity, i) > capacity)
	{
		throw exception();
	}

	Tupel t;
	t.linie = INT_MIN;
	t.coloana = INT_MIN;
	t.val = NULL_TELEM;
	Tupel changed = t;

	Tupel nou;
	nou.coloana = j;
	nou.linie = i;
	nou.val = e;
	//daca e liber
	if (T[pos].val == INT_MIN)
	{
		//si e este tot 0 atunci nu fac nimic
		if (e == 0)
			return e;
		else
		{
			T[pos] = nou;
			return changed.val;
			size++;
		}
	}
	//else if (T[pos].val != INT_MIN)//daca pos nu e libera
	//{
	//	//si daca e este 0
	//	if (e == 0)
	//	{
	//		//atunci trebuie sa sterg elem de pe linia i col j
	//		Tupel c;
	//		c.linie = INT_MIN;
	//		c.coloana = INT_MIN;
	//		c.val = NULL_TELEM;
	//		Tupel current = c;

	//		Tupel p;
	//		p.linie = INT_MIN;
	//		p.coloana = INT_MIN;
	//		p.val = NULL_TELEM;
	//		Tupel prev = p;

	//		current = T[pos];
	//		prev = current;
	//		i = i + 1;
	//		pos= hashing(T[i].val, capacity, i);
	//		current = T[pos];

	//		//lista are un singur elem
	//		if (current.val == NULL_TELEM && prev.linie == i && prev.coloana == j)
	//		{
	//			changed = prev;
	//			return changed.val;
	//			changed.val = current.val;
	//		}
	//		while (current.val != NULL_TELEM)
	//		{
	//			if (current.coloana == j && current.linie == j)
	//			{
	//				TElem ret = current.val;
	//				i = i + 1;
	//				pos = hashing(T[i].val, capacity, i);
	//				current = T[pos];
	//				if (current.val != NULL_TELEM)//current e acum de fapt nextCurrent
	//				{
	//					Tupel cn;
	//					cn.linie = INT_MIN;
	//					cn.coloana = INT_MIN;
	//					cn.val = NULL_TELEM;
	//					Tupel currentNext = cn;

	//					currentNext = current;
	//					return ret;
	//				}
	//				else
	//				{

	//				}
	//			}
	//		}
	//	}
	//}
	while (i < capacity && T[pos].val != e && T[pos].val != INT_MIN)
	{
		if (nou.coloana == T[pos].coloana && nou.linie == T[pos].linie)
			return T[pos].val;
		i = i + 1;
		pos= hashing(T[i].val, capacity, i);
	}


	return NULL_TELEM;
}


