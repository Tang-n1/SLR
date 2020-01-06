#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;

map<char, vector<string>> GRAMMAR;          //文法
map<char, set<char>> FIRST;                 //非终结符的first集合
map<char, set<char>> FOLLOW;                //非终结符的follow集合
set<char> NonterminalSet;				   //非终结符集合
set<char> TerminalSet;                   //终结符集合
map<char, bool> toEpsilon;                  //First集合是否存在空串


void setFOLLOW() {	//计算FOLLOW集合
	bool update = true;
	while (update) {
		update = false;
		for (char nonTerminalChar : NonterminalSet) { //遍历非终结符集合
			int followSize = FOLLOW[nonTerminalChar].size();    //记录 Follow 集合初始大小
			for (auto iter = GRAMMAR.begin(); iter != GRAMMAR.end(); iter++) {      //遍历所有文法，auto可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型
				for (string rightSide : iter->second) {      //遍历所有产生式右部
					int i = 0;
					while (i < rightSide.length()) {    //遍历产生式右部字符
						for (; i < rightSide.length(); i++) {
							if (nonTerminalChar == rightSide[i]) {  //找到与 nonTerminalChar 相同的字符，即找到非终结符
								if (i == rightSide.length() - 1) { //判断找到的非终结符是否是右部最后一个字符
									for (char ch : FOLLOW[iter->first]) {   //把产生式左部非终结符的 Follow 加入到 nonTerminalChar 的 Follow 集合中
										FOLLOW[nonTerminalChar].insert(ch);
									}
								}
								i++;
								break;  //找到了就停止
							}
						}
						for (; i < rightSide.length(); i++) {   //遍历后续字符
							if (!isupper(rightSide[i])) {   //如果是终结符
								FOLLOW[nonTerminalChar].insert(
									rightSide[i]);   //直接将终结符加入到 nonTerminalChar 的 Follow 集合中
								break;      //直接退出
							}
							else {        //是非终结符
								for (char ch : FIRST[rightSide[i]]) {   //将该非终结符的 First/{ε} 集合加入到 nonTerminalChar 的 Follow 集合中
									if (ch != '@') {
										FOLLOW[nonTerminalChar].insert(ch);
									}
								}
								if (!toEpsilon[rightSide[i]]) {     //如果该非终结符的 First 集合中不存在空串，则退出循环
									break;
								}
								else if (i == rightSide.length() - 1) {        //该非终结符的 First 集合中存在空串，且为右部最后一个字符
									for (char ch : FOLLOW[iter->first]) {
										FOLLOW[nonTerminalChar].insert(ch);     //将左部非终结符的 Follow 加入到 nonTerminalChar 的 Follow 集合中
									}
								}
							}
							if (i == rightSide.length() - 1 && rightSide[i] == nonTerminalChar) { //如果最后一个字符是 nonTerminalChar
								for (char ch : FOLLOW[iter->first]) {
									FOLLOW[nonTerminalChar].insert(ch); //把产生式左部非终结符的 Follow 加入到 nonTerminalChar 的 Follow 集合中
								}
							}
						}
					}
				}
			}
			if (followSize != FOLLOW[nonTerminalChar].size()) {
				update = true;
			}
		}
	}
}

void printFOLLOW() {    //打印 FOLLOW 集合
	cout << "-----------FOLLOW集-----------" << endl;
	for (char chr : NonterminalSet) {
		cout << "FOLLOW(" ;
		cout << chr << ") = { ";
		set<char> follow;
		follow = FOLLOW[chr];
		for (char ch : follow) {
			cout << ch << ",";
		}
		cout << chr << " } ";
		cout << endl;
	}
	cout << endl;
}