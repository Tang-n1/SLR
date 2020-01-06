#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <iterator>
#include <set>

using namespace std;

#define MAX 200
#define path "D://WorkSpace//Cpp//SLR_Parser//SLR//src//test.txt"

map<char, vector<string>> grammer; //文法
string first_non_terminal_symbol; //开始文法
string terminal_symbol;		//终结符
string non_terminal_symbol;	//非终结符
map<char, set<char>> First; //first集合
map<char, set<char>> Follow; //follow集合
map<char, bool>To_epsilon;  //first集合中是否存在空串

void display_Str(string title, string str) {
	cout << title << endl;
	for (int i = 0; i < str.length(); i++) {
		cout << str[i] << " ";
	}
	cout << endl << endl;
}

void display_Map(string title, map<char, vector<string>> ma) {
	cout << title << endl;
	for (auto it = ma.begin(); it != ma.end(); it++) {
		cout << it->first << "->";
		copy(it->second.begin(), it->second.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
	}
}

bool is_in(char ch, string str) {
	for (int i = 0; i < str.length(); i++) {
		if (ch == str[i]) {
			return false;
		}
	}
	return true;
}


