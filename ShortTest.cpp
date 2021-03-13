#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);

	//functionalitate
	Matrix m2(3, 3);                  //am o matrice de 3 pe 3
	for (int j = 0; j < 3; j++)      //o parcurg pe coloane
		for (int i = 0; i < 3; i++)
			m2.modify(i, j, i + j);//modific valoarea cu suma dintre linia si coloana acesteia

	for (int j = 0; j < 3; j++)                       //parcurg pe colana
	{
		auto it = m2.iterator(j);                   //it este iteratorul
		assert(it.valid() == true);                //verific daca e valid
		for (int i = 0; i < 3; i++, it.next())
			assert(it.getCurrent() == i + j);    //verific cu getCurrent daca val este de egala cu i+j
		assert(it.valid() == false);            //cand i=3 valid trebuie sa fie fals(deoarece am marticea de 3 pe 3 si indexarea incepe de la 0 deci ultima linie este i=2)
	}
}