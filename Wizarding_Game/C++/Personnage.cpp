#include <iostream>
#include <vector>
#include <cstdlib>
#include <ostream>
#include <string>



using namespace std;

template <typename T>
void echanger(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
void trier(vector <T> &tableau) {
	int indice = 0;
	int minimum;
	int indice_minimum;
	while (indice < tableau.size()){
			minimum = tableau[indice];
			indice_minimum = indice;
			for (int i = indice; i < tableau.size(); i++){
				if (tableau[i] < minimum){
					minimum = tableau[i];
					indice_minimum = i;
				}
			}
			echanger(tableau[indice++], tableau[indice_minimum]);
	}
}
int main()
{
	vector <char> x = {'a', 'z', 'h', 'r', 'y', 'e', 'j', 'e'};
	for (int i = 0; i < x.size(); i++){
		cout << x[i];
	}
	 cout << endl;
	trier(x);

	for (int i = 0; i < x.size(); i++){
		cout << x[i];
	}
}
