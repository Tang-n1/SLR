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
map<int, vector<string>> production;	//产生式
map<int, vector<string>> items; //项目集
string first_non_terminal_symbol; //开始文法
string terminal_symbol;		//终结符
string non_terminal_symbol;	//非终结符
map<char, set<char>> First; //first集合
map<char, set<char>> Follow; //follow集合
map<char, bool>To_epsilon;  //first集合中是否存在空串

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
	cout << title<<"集合\n\t";
	for (int i = 0; i < str.length(); i++) {
		cout << str[i] << " ";
	}
	cout << endl << endl;
}

template<typename T> void display_Map(string title, map<T, vector<string>> ma) {
	cout << title <<"\n";
	for (auto it = ma.begin(); it != ma.end(); it++) {
		cout <<"\t"<< it->first << ": ";
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

int items_number(int num) {  //map中某个key的value数
	int cnt = 0;
	auto it = items.find(num);
	for (string temp : it->second) {
		cnt++;
	}
	return cnt;
}

int items_key() { //map中key的数量
	int cnt = 0;
	for (auto it = items.begin(); it != items.end(); it++) {
		cnt++;
	}
	return cnt;
}

bool in_items(int num,string str) { //key中是否存在该字符串
	auto it = items.find(num);
	for (string temp : it->second) {
		if (temp == str) {
			return true;
		}
	}
	return false;
}

string after_point(int num) {  //点后的字符
	auto it = items.find(num);
	string expand = "";
	for (string temp : it->second) {
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == '.'&&temp[i+1]!='\0') {
				string::size_type index;
				index = expand.find(temp[i + 1]);
				if (index == string::npos) {
					expand += temp[i + 1];
				}
			}
		}
	}
	return expand;
}


int find_key(string temp) {
	int len = temp.length() - 1;
	temp.erase(len, 1);
	for (auto it = production.begin(); it != production.end(); it++) {
		for (string str : it->second) {
			if (temp == str) {
				return it->first;
			}
		}
	}
}




