#include "Lapin.hpp"
#include "Modele.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"

using namespace std;


int main(void)
{
	//simulation sur une période de 20 ans
	srand(825);
	Modele *m = new Modele(120);
	m->initializeSimulation("simulation10ans.csv");
	delete m;
	Modele *m2 = new Modele(120);
	m->initializeSimulation("simulation10ans.csv");
	delete m2;
	
	//clock_t begin = clock();
	//int somme = 0;
	//for(int i=0; i<100; ++i)
	//{
		//Modele m(60);
		//m.initializeSimulation();
		//somme += m.initializeSimulation();
	//}
	//std::cout << "moyenne :" << somme/100 << std::endl;

	//clock_t end = clock();
	
	/*std::cout << "--> " << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	std::cout << "size lapin : " << sizeof(Lapin) << std::endl;
	std::cout << "size lapin male : " << sizeof(LapinMale) << std::endl;
	std::cout << "size lapin femelle : " << sizeof(LapinFemelle) << std::endl;
	std::cout << "Test : " << sizeof(Test) << std::endl;*/
	
	/*Test *test = new Test[10000000];
	long tab[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int i = 0;
	while(i < 180)
	{
		for(int j=0; j<10000000;++j)
			test[j].incrementAge(tab);
		++i;
	}
	
	std::cout << "tab : ";
	for(int j=0; j<15;++j)
		std::cout << tab[j] << " ";
	std::cout << std::endl;
	std::cout << "tab% : ";
	for(int j=0; j<15;++j)
		std::cout << (float)tab[j]/10000000 << "% ";
	
	delete [] test;*/
	
	return 0;
}
