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
#define path "./test.txt"

map<char, vector<string>> grammer; //文法
map<char, set<char>> First; //first集合
map<char, set<char>> Follow; //follow集合
map<char, bool>To_epsilon;  //first集合中是否存在空串
string first_non_terminal_symbol; //开始文法
string terminal_symbol;		//终结符
string non_terminal_symbol;	//非终结符

char input_str[30];  //输入字符串
typedef struct {
	char data[50];
	int num;
}midsta; //词法分析过后的字符串
midsta m[10];

void display_Set(string title, map<char, set<char>> ma) {  //打印
	cout << title<<"集合：" << endl;
	set<char> temp;
	for (auto it = ma.begin(); it != ma.end(); it++) {
		cout <<"\t"<< title <<"(" << it->first << ") = { ";
		temp = ma[it->first];
		int flag = 1;
		for (char ch : temp) {
			if (flag) {
				cout << ch;
			}
			else {
				cout << ", " << ch;
			}
			flag = 0;
		}
		cout << " }" << endl;
	}
	cout << endl;
}

void display_Str(string title, string str) {
	cout << title << "\n\t";
	for (int i = 0; i < str.length(); i++) {
		cout << str[i] << " ";
	}
	cout << endl << endl;
}

void display_Map(string title, map<char, vector<string>> ma) {
	cout << title ;
	for (auto it = ma.begin(); it != ma.end(); it++) {
		cout << it->first << "->";
		copy(it->second.begin(), it->second.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
	}
}

void display_struct(string title,int length) {
	cout << "\n" << title << "\n\t";
	for (int i = 0; i < length; i++) {
		cout << m[i].data << "，";
	}
	cout << endl;
}

bool is_in(char ch, string str) {
	for (int i = 0; i < str.length(); i++) {
		if (ch == str[i]) {
			return false;
		}
	}
	return true;
}


