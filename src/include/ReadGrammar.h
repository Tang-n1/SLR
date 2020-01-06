#pragma once
#include "basic.h"

void deleteBlank(string& str) {
	int begin = 0;
	begin = str.find(" ", begin);	//查找空格在str中第一次出现的位置
	while (begin != -1){	//表示字符串中存在空格
		str.replace(begin, 1, "");	//用空串替换str中从begin开始的1个字符
		begin = str.find(" ", begin);	//查找空格在替换后的str中第一次出现的位置
	}
}

void readGrammar() {   //读入文法，初始化终结符集合与非终结符集合
	ifstream in;
	in.open(path);	//读入文法
	if (!in.is_open()) {
		cout << "Can't open the file" << endl;
		exit(0);	//结束程序
	}
	string temp;
	bool flag = true;
	cout << "文法：" << endl;
	while (getline(in, temp)) {
		deleteBlank(temp);
		cout << temp << endl;
		grammer[temp[0]].push_back(temp.substr(3)); //添加文法
		if (flag) {
			first_non_terminal_symbol = temp[0]; //起始符号
			flag = false;
		}
		if (is_in(temp[0], non_terminal_symbol)) {
			non_terminal_symbol += temp[0]; //非终结符
		}
		for (int i = 3; i < temp.length(); i++) {
			if (!isupper(temp[i]) && (temp[i] != '@')&&is_in(temp[i],terminal_symbol)) { //不是大写（非终结符）和空串
				terminal_symbol += temp[i];	//终结符
			}
		}
	}
	cout << endl;
	display_Str("终结符：", terminal_symbol);
	display_Str("非终结符：", non_terminal_symbol);
}


