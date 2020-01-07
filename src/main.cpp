#include "include/ReadGrammar.h"
#include "include/First.h"
#include "include/Follow.h"
#include "include/Lex.h"

int main() {
	readGrammar();
	setFirst();
	setFollow();

	cout << "ÇëÊäÈë²âÊÔ×Ö·û´®£¨ÒÔ#½áÎ²£©£º";//text£ºi_2a23_+34*ab
	cin >> input_str;
	lex();

}
