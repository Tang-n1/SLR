#pragma once
#include "basic.h"
#include "SqStack.h"
#include "SLRparsing.h"




string now = ""; //记录当前状态
/*读取字符*/
int ip = 0;
string advance() {  //读取字符队列中的单词
	return symbolTables[ip].data;
}
int advance_value() {  //读取字符队列中的单词
	return symbolTables[ip].value;
}


string find_index(string state, string a, int value) {
	string action = "error";
	if (value == 10) {
		a = "i";
	}
	if (value == 1) {
		a = "n";
	}
	for (int i = 0; i < slr_cnt; i++) {
		if (state[0] == slr[i].state && a[0]==slr[i].row) {
			action = slr[i].action;
		}
	}
	return action;
}

int action_goto(string s, string a, int value) {
	now = find_index(s, a, value);
	string action = now.substr(0, 1);
	if (action == "s") { //移进
		return 1;
	}
	else if (action == "r") { //归约
		return 2;
	}
	else if (action == "a") { //接受
		return 3;
	}
	else if (action == "e") { //出错
		return 4;
	}
	else {  //转移
		return 5;
	}
}

void displayAction(SqStack<string> *st, int ip, string action) {
	DispStack(st);
	cout << "\t\t\t\t\t\t\t";
	int i = ip-1;
	do {
		i++;
		cout << symbolTables[i].data << " ";
	} while (symbolTables[i].data[0] != '$'); 
	cout << "\t\t\t\t\t";
	cout << action << endl;
}

void Parsing_SLR(){   //gbk+68*h$
	SqStack<string>* st;
	InitStack(st);
	Push(st, string("0"));	//将状态0入栈
	string state;
	string a;
	bool flag = true;
	bool ok = false;
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	cout << "  栈"<<"\t\t\t\t\t\t\t"<<"输入"<< "\t\t\t\t\t" <<"动作" << endl;
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	string action;
	int index = ip;
	while (flag) {
		index = ip;
		GetTop(st, state); //出栈栈顶状态
		a = advance();
		int res = action_goto(state, a, advance_value());
		int len=0;
 		auto it=production.find(1);
		string css="";
		switch (res) {
		case 1:Push(st, a); Push(st, now.substr(1, 1)); ip++; action = "移进"; break; //移进
		case 2:
			it = production.find(char_int(now[1]));
			for (string temp : it->second) {
				len = temp.length() - 3;
				css = temp;
			}
			for (int j = 0; j < 2 * len; j++) {
				Pop(st, state);
			}
			GetTop(st, state);
			Push(st, css.substr(0,1));//产生式的左侧入栈
			action_goto(state, css.substr(0, 1), 0); //获得沟通序号
			Push(st, now.substr(0,1));//goto序号入栈
			action = "按" + css + "归约";
			break;
		case 3:flag = false; ok = true; action = "接受"; break; //接受
		case 4:flag = false; ok = false; action = "出错"; break;//出错
		}
		displayAction(st, index, action);
	}
	cout << "----------------------------------------------------------------------" << endl;
	if (ok == true) {
		cout << "正确的表达式" << endl;
	}
	else {
		cout << "错误的表达式" << endl;
	}
}