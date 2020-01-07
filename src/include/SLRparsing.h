#pragma once
#include "basic.h"


struct SLR_Table {
	int state;
	char row;
	string action;
};

SLR_Table slr[MAX];  
int slr_cnt = 0;

void create_SLRTable() {
	slr[slr_cnt] = { 1,'$',"acc" };
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
					string go_to = "r" + to_string(find_key(temp));
					slr[slr_cnt] = { i,ch, go_to };
					slr_cnt++;
				}
			}
		}
	}
}

void show_SLRTable() {
	create_SLRTable();
	cout <<endl << "SLR Table:" << endl;
	for (int i = 0; i < slr_cnt; i++) {
		cout << '\t' << slr[i].state << ": " << slr[i].row << ": " << slr[i].action << endl;
	}
}

void expandItems(int num) {  //扩展项目集族
	int cnt = 0, cnt2 = 0;
	do {
		string expand = after_point(num);
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
	auto it = items.find(num);
	for (string temp : it->second) {
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == '.' && temp[i + 1] != '\0') {
				if (temp[i + 1] == ch) {
					string temp2 = temp;
					temp2.erase(i, 1);
					temp2.insert(i + 1, ".");
					int flag = 0;
					for (int i = 0; i < items_key(); i++) {
						if (in_items(i, temp2)) {	//无已有状态
							flag = 1;//存在
						}
					}
					if (!flag) {
						items[items_key()].push_back(temp2);
						int x = items_key() - 1;
						string action;
						if (isupper(ch)) {
							action = to_string(x);
						}
						else {
							action = "s";
							action.insert(1, to_string(x));
						}
						//cout <<"action: " << h << endl;
						slr[slr_cnt] = { num,ch,action };
						slr_cnt++;
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
	int zt = 0, zt2 = 0;
	int x = 0;
	do {
		zt = items_key();
		//扩展项目集族+创建SLR分析表
		for (int num = 0; num < zt; num++) {
			auto it = items.find(num);
			string expand = after_point(num);
			for (int i = 0; i < expand.length(); i++) {
				new_item(num, expand[i]);
			}
		}
		zt2 = items_key();
		x++;
	} while (zt!=zt2);
	display_Map("DFA：", items);
	show_SLRTable();
}





