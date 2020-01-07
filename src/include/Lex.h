#pragma once
#include"basic.h"
#include<string>
#include<iostream>
using namespace std;

int Isdigit();  //数字判断
int Isletter(); //字符判断
int Isunderline(); //下划线判断
void concat(); //连接标识符
int Isoperator(); //运算符判断
char m_getch(); //读取字符
char ch; 
int m_i = 0, i_i = 0, i = 0;  //结构体中data的移动，输入字符串的移动，结构体数组的移动

void lex() {  //词法分析器
	int k = 0;
	m_getch();
	while (ch != '#') {
		if (Isletter()) {  //字符开头的ID
			while (Isunderline() || Isdigit() || Isletter()) { //以下划线，数字，字母结尾
				concat();
				m_getch();
			}
			symbolTables[i].value = 10;
		}
		else if (Isdigit()) {  //数字num
			while (Isdigit()) { //数字结尾
				concat();
				m_getch();
			}
			symbolTables[i].value = 1;
		}
		else if(Isoperator()) {  //运算符号
			m_getch();
			symbolTables[i].value = 0;
		}
		i++;
		m_i = 0;
	}
	display_struct("词法分析器:", i);
};

char m_getch() //读取字符
{
	ch = input_str[i_i];
	i_i++;
	return ch;
}

int Isoperator() { //运算符判断
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')') {
		symbolTables[i].data[0] = ch;
		return 1;
	}
	else {
		return 0;
	}
}

int Isdigit() {  //数字判断
	if (ch >= '0' && ch <= '9') {
		return 1;
	}
	else {
		return 0;
	}
}

int Isletter() {  //字符判断
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
		return 1;
	}
	else {
		return 0;
	}
}

int Isunderline() { //下划线判断
	if (ch == '_') {
		return 1;
	}
	else {
		return 0;
	}
}

void concat() //拼接单词
{
	symbolTables[i].data[m_i] = ch;
	m_i++;
	symbolTables[i].data[m_i] = '\0';
}