//
// Book : Version du chapitre 26 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 28/09/2018 
// Commit en cours : Exos pages 1018 et 1019 - 29/09/2018
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @
// Paramétrage IDE : C/C++ Général Compilation multiprocesseur : OUI (debug/release)

#include "pch.h"		// En-tête indispensable sous Windows et VC++
#include "MyHeader.h"	// Header personnel (en partie dérivé de std_lib_facilities de BS)

#include <vector>
#include <iterator>
#include <algorithm>
#include <typeinfo>

using namespace std;

template<typename T, typename U>
bool binary_search (const T& v, const U x)	// Assume that v is sorted (caller responsibility)
{  
	// Check container emptiness
	int size = distance(v.begin(), v.end());
	if (size == 0) return false;

	int middle = size / 2;
	bool dichotomy = true;	// Flag : possible to continue dichotomy ?
	auto vb = v.begin();
	auto ve = v.end();
	auto vi = vb;
	advance(vi, middle);	// Put position on the middle of the range
	
	while (dichotomy) {
		if (x==*vi) 
			return true;
		
		else if(x<*vi) {
			ve = vi;
			if (distance(vi, vb) == -1)	// Traitement du cas au limite
				middle = -1;
			else
				middle = distance(vi, vb) / 2;
			
			if (distance(vi, vb) == 0) dichotomy = false;
			advance(vi, middle);
			
		}
		
		else if(x>*vi) {
			vb = vi;
			middle = distance(vi, ve) / 2;
			if (middle==0) dichotomy = false;
			advance(vi, middle);
			
		}
	
	
	}
	
	return false;

}

int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		// Test via une génération de nombres aléatoires
		//vector <double> v{};
		//for (unsigned int i = 0; i < 1000000; ++i) v.push_back(random_number(0, 1000000));
		//for (auto x : v) cout << x << ' ';
		
		//vector <int> v{ 1,2,3,4,5,6 };
		vector <string> v{ "Bohr","Darwin","Einstein","Lavoisier","Newton","Turing" };
		//vector <double> v{ 1.2,0,0,0,0,0,0,0,0,0,0,0.9 };
		sort(v.begin(), v.end());
			
		open_file_read("test.txt");

		cout << endl<<"Saisir valeur :" << endl;
		auto s = v[0];	// auto-to-stick technique in order to set the type of s regarding vector test
		while (cin >> s) {
		
			if (binary_search(v,s))
				cout << "Valeur trouvée !" << endl;
			else
				cout << "Valeur inexistante !" << endl;
		}

		keep_window_open();

		return 0;
	}
	/*
	catch (XXXXXXX::Invalid&)
	{
		cerr << "error: ???????????????????? ! \n";
		keep_window_open("q");	// For some Windows(tm) setup
		return 1;
	}
	*/

	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}
