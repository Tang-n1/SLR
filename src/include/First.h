#pragma once
#include "basic.h"

int FirstSize;

void printfirst() {  //打印
	cout << "First集：" << endl;
	for (char ch_f : non_terminal_symbol) { //取非终结符集合
		cout << "First(";
		cout << ch_f << ") = { ";
		set<char> print_first;
		print_first = First[ch_f];  //取每个非终结符的first集
		for (char ch : print_first) {
			cout << ch << ",";
		}
		cout << " }" << endl;
	}
}

void Getfirst() {  //获取first集
	bool flag = true;
	while (flag) {
		flag = false;
		for (char nonte_Char : non_terminal_symbol) { //遍历非终结符（等式的左边）
			FirstSize = First[nonte_Char].size(); //记录非终结符个数
			for (string RightSide : grammer[nonte_Char]) { //遍历产生式的右部
				for (char ch : RightSide) {  //遍历产生式右部的所有字符
					//不是大写字母，如果是终结符,说明该产生式遍历完成
					if (!isupper(ch)) { 
						//将该终结字符加入到非终结符的first集合中
						First[nonte_Char].insert(ch);
						break;  //结束循环
					}
					else {
						bool Epsilon_falg = false; //first中是否存在空
						for (char temp : First[ch]) {
							if (temp == 'ε') { //存在空串
								Epsilon_falg = true;
							}
							//将非终结符ch的first集合加入到非终结符的first集合中
							First[nonte_Char].insert(temp); 
						}
						if (!Epsilon_falg) {//如果不存在空串
							break;
						}
					}
				}
			}
			if (FirstSize != First[nonte_Char].size()) {  //非终结符没有遍历完
				flag = true;
			}
		}
	}
	for (char nonte_Char : non_terminal_symbol) { //遍历非终结符集合
		//当找到的ε是结束字符end()，返回0；否则返回To_epsilon[nonte_Char]=1
		To_epsilon[nonte_Char] = First[nonte_Char].find('ε') != First[nonte_Char].end();
	}
	printfirst();
}

