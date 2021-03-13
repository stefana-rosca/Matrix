#include "Matrix.h"
#include <exception>
using namespace std;

// Complexitate: Ѳ(1)
Matrix::Matrix(int nrLines, int nrCols) 
{
	m = 16;
	size = 0;
	Linii = nrLines;
	Coloane = nrCols;
	T = new Tuple[m];
	for (int i = 0; i < m; i++)
	{
		T[i].linie = INT_MIN;
		T[i].coloana = INT_MIN;
		T[i].val = NULL_TELEM;
	}
}

// Complexitate: Ѳ(1)
int Matrix::nrLines() const 
{
	return Linii;
}

// Complexitate: Ѳ(1)
int Matrix::nrColumns() const
{
	return Coloane;
}

// Complexitate: best, avarage case Ѳ(1)
//               worst case: O(n)
TElem Matrix::element(int i, int j) const
{
	//daca i, j sunt mai mici ca 0 sau mai mari sau egale(indexarea incepe de la 0) cu linii, coloane inseamna ca este invalid 
	if (i < 0 || i >= Linii || j < 0 || j >= Coloane)
	{
		throw exception(); //arunc exceptie
	}
	//caut elementul
	int indexHash = 0;
	int index= hashing(i, j, indexHash++);
	while (indexHash < m && (T[index].linie != i || T[index].coloana != j)) //cat timp poz e valida si inca nu am gasit elem de pe linia i coloana j
	{
		if (T[index].val == 0 && T[index].linie != -1) //daca am ajuns aici inseamna ca suntem la final, deci nu exista in Array
			return NULL_TELEM;                        //deci return null_telem
		index = hashing(i, j, indexHash++);          //continui while-ul
	}

	if (index == -1)            //daca index =-1 inseamna ca nu l-am gasit
		return NULL_TELEM;     //deci returnez null_telem
	else return T[index].val; //index!=1 am gasit si returnez valoarea
}

// Complexitate: best, avarage case Ѳ(1)
//               worst case: O(n)
TElem Matrix::modify(int i, int j, TElem e)
{
	//daca i, j sunt mai mici ca 0 sau mai mari sau egale(indexarea incepe de la 0) cu linii, coloane inseamna ca este invalid 
	if (i < 0 || i >= Linii || j < 0 || j >= Coloane)
	{
		throw exception();
	}

	Tuple newVal;
	newVal.linie = i;
	newVal.coloana = j;
	newVal.val = e;

	//daca e este NULL_TELEM trebuie stears elem din array
	if (e == NULL_TELEM)                    
		newVal.linie = -1;    //egalez cu -1(il marchez ca si sters)

	int index = search(i, j);//Ѳ(1)
	//int indexHash = 0;
	//int index = hashing(i, j, indexHash++);
	//while (indexHash < cap && (T[index].linie != i || T[index].coloana != j)) 
	//{
	//	if (T[index].val == 0 && T[index].linie != -1) 
	//		index= -1;
	//	index = hashing(i, j, indexHash++); 
	//}
	//if (indexHash == cap)
	//	index= -1;
	
	//daca index!=-1 atunci inseamna ca a fost gasit in Array
	if (index != -1) 
	{	
		TElem OldValue = T[index].val;//retin in OldValue valoarea elem de pe index
		T[index] = newVal;           //inlocuiesc cu noua valoare
		return OldValue;            //returnez valoarea pe care am inlocuit-o
	}
	//daca index=-1 elem de pe acest index a fost deja sters sau nici nu a existat
	else if(index==-1)
	{
		//daca e este diferit de NULL_TELEM atunci T[Index] va primi newVal
		if (e != NULL_TELEM)
		{
			if (size / m >= 1) //size/cap=belegungsfaktor
			//RESIZE  Complexitate: O(m), unde m = Old Capacity
			{
				m *= 2;                                                                          //dublez capacitatea
				Tuple* deleted = T;                                                             //deleted->T
				T = new Tuple[m]();                                                            //T este de forma Tupel cu noua capacitate
				for (int i = 0; i < m / 2; i++)                                               //parcurg lista pana la jumate
					if (deleted[i].linie != -1)                                              //daca deleted[i].linie!=-1 inseamna ca pozitia e valida deci continui sa parcurg
						modify(deleted[i].linie, deleted[i].coloana, deleted[i].val);       //apelez fctia modify
				delete deleted;                                                            //sterg deleted
			}

			int indexHash = 0;
			int Index = hashing(i, j, indexHash++);
			while (indexHash < m && T[Index].val != 0)   //Ѳ(1) ca si la search
				Index = hashing(i, j, indexHash++);
			T[Index] = newVal;                         //inlocuiesc cu noua vaoare
			size++;                                   //crsc size-ul
		}
		return 0;
	}
}

// Complexitate: best, avarage case Ѳ(1)
//               worst case: O(n)
//am facut functie separata pentru search deoarece daca caut direct in modify
//dureaza in jur de 5 min sa termine de rulat, iar asa este gata mult mai repede
int Matrix::search(int i, int j) const
{
	int indexHash = 0;
	int index = hashing(i, j, indexHash++);

	while (indexHash < m && (T[index].linie != i || T[index].coloana != j)) //cat timp poz e valida si inca nu am gasit el de pe linia i coloana j
	{
		if (T[index].val == 0 && T[index].linie != -1) //daca am ajuns aici inseamna ca suntem la final, deci nu exista in Array
			return -1;                               
		index = hashing(i, j, indexHash++);          //continui sa caut
	}
	if (indexHash == m)                          
		return -1;
	return index;
}

//FUNCTIONALITATE
Iterator Matrix::iterator(int coloana)
{
	return Iterator::Iterator(*this, coloana);
}

//complexitatea este de Ѳ(1)
Iterator::Iterator(Matrix& m, int coloana) : m(m)
{
	//daca coloana este mai mica decat 0 sau depaseste sau e egala cu nr de coloane (deoarece indexarea incepe de la 0) atunci este invalida
	if (coloana < 0 || coloana >= m.nrColumns())
	{
		throw exception();//deci arunca exceptie
	}
	//in caz ca coloana e valida
	this->coloana = coloana;//coloana primeste prima coloana
	linie = 0;//deci linia este 0                              =>acum iteratorul este pe elem de pe lina 0, coloana 0
	                                                           //si va merge in jos pe prima coloana(crescand linia pana ajunge la una invalida)
}

//cand parcurg pe coloane trebuie sa ma asigur ca lina pe care ma aflu este valida
bool Iterator::valid()
{
	if (linie >= m.nrLines())//daca linia este mai mare sau egala(index incepe de la 0) cu nr liniilor din matrice
		return false;       //linia NU e valida
	return true;           //linia e valida
}
void Iterator::next()
{
	if (valid() == false)   //daca linia nu e valida nu pot trece mai departe
		throw exception(); //arunc exceptie
	linie++;              //altfel trec la urmatoarea linie
}
TElem Iterator::getCurrent()
{
	if (valid() == false)                  //daca linia nu e valida nu pot trece mai departe
		throw exception();                //arunc exceptie
	return m.element(linie, coloana);    //altfel returnez elementul pe care a ajuns iteratorul
}