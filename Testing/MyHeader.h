/*
MyHeader.h
*/

/*
first own header

Revised July 21, 2018:		initial release
Revised August 16, 2018:	open file added
Revised August 23, 2018:	RunAndMeasure added
Revised September 14, 2018: error renamed to My_error to avoid side effect with Matrix.h from BS
Revised September 29, 2018: file functions reviewed (more C++17 style)

*/

#ifndef MY_HEADER_GUARD	// Pour �viter que mon header soit compil� deux fois
#define MY_HEADER_GUARD

#include<string>
#include<iostream>
#include<fstream>
#include<chrono>

using namespace std;

inline void keep_window_open() // From "std_lib_facilities.h" of BS
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}

inline void keep_window_open(string s)
{
	if (s == "") return;
	cin.clear();
	cin.ignore(120, '\n');
	for (;;) {
		cout << "Please enter " << s << " to exit\n";
		string ss;
		while (cin >> ss && ss != s)
			cout << "Please enter " << s << " to exit\n";
		return;
	}
}

struct Exit : runtime_error {
	Exit() : runtime_error("Exit") {}
};

// error() simply disguises throws:
inline void My_error(const string& s)
{
	throw runtime_error(s);
}

inline void My_error(const string& s, const string& s2)
{
	My_error(s + s2);
}

int random_number(const int min, const int max)
{
	// Cette fonction helper g�re le tirage de nombres al�atoires entre deux bornes pass�es en arguments
	// On pr�f�re la fonction C rand() � randint(min, max) incluse dans std_lib_facilities.h
	// Le seeding doit �tre r�alis� dans le main() et permet une g�n�ration pseudo-al�atoire (meilleurs outils � partir de C++ 11)
	// srand((int)time(0));	// Seeding du moteur de g�n�ration al�atoire en partant de l'heure
	int a = rand() % max + min;
	return a;
}

ifstream open_file_read(string filename)
{
	// Cette fonction helper permet d'ouvrir un fichier en lecture : la m�moire occup�e par in_file sera lib�r�e via RAII � la sortie du scope du callee (= close explicite inutile)
	ifstream in_file{ filename.data(), ios::in };
	if (!in_file.is_open()) My_error("Impossible d'ouvrir le fichier ", filename);
	return in_file;

}

ofstream open_file_write(string filename)
{
	// Cette fonction helper permet d'ouvrir un fichier en �criture : la m�moire occup�e par out_file sera lib�r�e via RAII � la sortie du scope du callee (= close explicite inutile)
	ofstream out_file{ filename.data(), ios::out | ios::trunc };
	if (!out_file.is_open()) My_error("Impossible d'ouvrir le fichier ", filename);
	return out_file;

}

template <typename TFunc> void RunAndMeasure(TFunc func)
{
	// To use : RunAndMeasure([&]() {Code to insert });
	const auto start = chrono::steady_clock::now();
	func();
	const auto end = chrono::steady_clock::now();
	cout << chrono::duration <double, milli>(end - start).count() << " ms\n";
}



#endif


