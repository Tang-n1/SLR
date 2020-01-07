#include "include/ReadGrammar.h"
#include "include/First.h"
#include "include/Follow.h"
#include "include/SLRparsing.h"

int main() {
	readGrammar();
	setFirst();
	setFollow();
	setDFA();
}
