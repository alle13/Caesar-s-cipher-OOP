// Extra credit lab 2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<float> readDistribution(const char* url) {
	ifstream f(url);
	vector<float> arr;
	float freq;
	while (f >> freq)
	{
		arr.push_back(freq);
	}
	f.close();
	return arr;
}
float norm_freq(string text,char letter, vector<float> expected) {
	int s = 0;
	for (auto i : text) {
		if (letter==tolower(i))
			s = s + 1;
	}
	float expectedi = expected[letter - 'a'];
	float numerator = (s - expectedi) * (s - expectedi);
	return numerator / expectedi;
}
float chi_distance(string text, vector<float> expected) {
	float s = 0;
	for (char letter = 'a'; letter <= 'z'; letter++)
		s += norm_freq(text, letter, expected);
	return s;

}
string decrypt(string text, vector<float> expected) {
	string permEncr=text;
	string solution;
	float min = chi_distance(text,expected);
	do{
		for (auto &i : permEncr) {
			if (i == 'z')
				i = 'a';
			else
				if (i == 'Z')
					i = 'A';
				else
					if (isalpha(i))
						i++;
		}
		float chi = chi_distance(permEncr, expected);
		if (chi< min) {
			min = chi;
			solution = permEncr;
		}
	} while (text != permEncr);
	return solution;
}
string encrypt(string text,int shift) {
	string wanted=text;
	for (auto &i : wanted) {
		if (isalpha(i)) {
			if( i >='a')
				i = 'a' + ((i - 'a') + shift) % ('z' - 'a' + 1);
			else
				i = 'A' + ((i - 'A') + shift) % ('z' - 'a' + 1);
		}	
	}
	return wanted;
}
void UI(vector <float> expected) {
	int i=1;
	cout << endl;
	while (i != 0) {
		cout <<endl<< "Choose an option" << endl;
		cout << "0.Exit" << endl;
		cout << "1.Encrypt a text:" << endl;
		cout << "2.Decrypt a text:" << endl;	
		cout << "3.Decrypt the stored text:" << endl;	
		cout << "The option is :" << endl;
		cin >> i;
		if (i == 1) {
			string text1;
			int shift;
			cout << "The text is : " << endl;
			cin.get();
			getline(cin, text1);
			cout << "The shifting nb is : " << endl;
			cin >> shift;
			cout << encrypt(text1, shift);
		}
		else 
			if (i == 2) {
				string text2;
				cout << "The text is : " << endl;
				cin.get();
				getline(cin, text2);
				cout << "The decrypted text is : " << decrypt(text2, expected) << endl;
			}
			else
				if (i == 3)
				{
					string encrypted = "Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud";
					cout << decrypt(encrypted, expected);
				}
	}

}
int main()
{
	vector<float> Array = readDistribution("E:\\Projects vsc\\Extra credit lab 2\\x64\\Debug\\distribution.txt");
	/*cout << endl << encrypted << endl;
	cout << encrypt(decrypt(encrypted, Array), 12);*/
	UI(Array);

}