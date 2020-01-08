#pragma once
#include "basic.h"


struct SLR_Table {
	char state;
	char row;
	string action;
};

SLR_Table slr[MAX];  
int slr_cnt = 0;

bool inSLR(char state, char row, string action) {
	for (int i = 0; i < slr_cnt; i++) {
		if (state == slr[i].state && row == slr[i].row && action == slr[i].action) {
			return true;
		}
	}
	return false;
}


void create_SLRTable() {
	slr[slr_cnt] = { '1','$',"acc" };
	slr_cnt++;
	int num = items_key();
	for (int i = 0; i < num; i++) {
		auto it = items.find(i);
		for (string temp : it->second) {
			char point = temp[temp.length() - 1];
			if (point == '.' && temp[0] != 'S') {
				//cout << temp[0] << ": "<<temp<<" ::";
				auto it = Follow.find(temp[0]);
				for (char ch : it->second) {
					//cout << ch << " ";
					string go_to = "r";
					go_to += int_char(find_key(temp));
					if (!inSLR(int_char(i), ch, go_to)) {
						slr[slr_cnt] = { int_char(i),ch, go_to };
						slr_cnt++;
					}
				}
			}
		}
	}
}

void show_SLRTable() {
	create_SLRTable();
	cout <<endl << "SLR Table:" << endl;
	string row = terminal_symbol + "$" + non_terminal_symbol;
	for (int i = 0; i < slr_cnt; i++) {
		cout << slr[i].state << ": " << slr[i].row << ": " << slr[i].action << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
	cout << "  "<<"\t";
	for (int i = 0; i < row.length(); i++) {
		cout << row[i] << "\t";
	}
	cout <<endl<< "-----------------------------------------------------------------------------------------------------" << endl;
	//for (int i = 0; i < slr_cnt; i++) {
	int len = char_int(slr[slr_cnt - 1].state);
	for (int i = 0; i <= len; i++) {
		cout << int_char(i) << "\t";
		for (int j = 0; j < row.length(); j++) {
			int flag = 0;
			for (int k = 0; k < slr_cnt; k++) {
				if (slr[k].state == int_char(i) && slr[k].row == row[j]) {
					cout << slr[k].action << "\t";
					flag = 1;
				}
			}
			if (!flag) {
				cout <<"error"<< "\t";
			}
		}
		cout << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
}

void expandItems(int num) {  //扩展项目集族
	int cnt = 0, cnt2 = 0;
	do {
		string expand = after_point(num);
		//cout << expand << endl;
		cnt = items_number(num);
		for (int i = 0; i < expand.length(); i++) {
			char symbol = expand[i];
			for (auto it = production.begin(); it != production.end(); it++) {
				for (string css : it->second) {
					css.insert(3, ".");
					if (symbol == css[0] && !in_items(num, css) && css[4] != '@') {
						items[num].push_back(css);
					}
				}
			}
		}
		cnt2 = items_number(num);
	} while (cnt != cnt2);
}

void new_item(int num, char ch) {
	int item_cnt = items_key();
	auto it = items.find(num);
	int have_new = 0;
	for (string temp : it->second) {
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == '.' && temp[i + 1] != '\0') {
				if (temp[i + 1] == ch) {
					string temp2 = temp;
					temp2.erase(i, 1);
					temp2.insert(i + 1, ".");
					int flag = 0;
					for (int i = 0; i < items_key(); i++) {
						if (in_items(i, temp2)&&have_new==0) {	//无已有状态
							flag = 1;//存在
							string action="";
							if (isupper(ch)) {
								action += int_char(i);
								cout << "action:" << action << endl;
							}
							else {
								action = "s";
								action += int_char(i);
								cout << "action:" << action << endl;
							}
							if (!inSLR(int_char(num), ch, action)) {
								slr[slr_cnt] = { int_char(num),ch,action };
								slr_cnt++;
							}
						}
					}
					if (!flag) {
						items[item_cnt].push_back(temp2);
						have_new = 1;
						int x = items_key() - 1;
						string action="";
						if (isupper(ch)) {
							action += int_char(x);
							cout << "action:" << action << endl;
						}
						else {
							action = "s";
							action += int_char(x);
							cout << "action:" << action << endl;
						}
						if (!inSLR(int_char(num), ch, action)) {
							slr[slr_cnt] = { int_char(num),ch,action };
							slr_cnt++;
						}
					}
				}
			}
		}
	}
	expandItems(items_key()-1);
}


void setDFA() {
	int num = 0;
	expandItems(0);
	int zt = 0, zt2 = 1;
	int x = 0;
	do {
		int index = zt;
		zt = items_key();
		//扩展项目集族+创建SLR分析表
		for (int num = index; num < zt; num++) {
			auto it = items.find(num);
			string expand = after_point(num);
			//cout << expand << endl;
			for (int i = 0; i < expand.length(); i++) {
				new_item(num, expand[i]);
				//display_Map("DFA：", items);
			}
		}
		zt2 = items_key();
		x++;
	} while (zt!=zt2);
	display_Map("DFA：", items);
	show_SLRTable();
}





