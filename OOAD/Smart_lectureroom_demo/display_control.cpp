#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "display_control.h"

#define MAX_SIZE 1000

using namespace std;


void Display_control::display(char *sensor, char *oper, char *ttable) {
	char inputString1[MAX_SIZE];
	char inputString2[MAX_SIZE];
	char inputString3[MAX_SIZE];
	
	ifstream sdb(sensor);
	while (!sdb.eof()) {
		sdb.getline(inputString1, 100);
		cout << inputString1 << endl;
	}

	ifstream odb(oper);
	while (!odb.eof()) {
		odb.getline(inputString2, 100);
		cout << inputString2 << endl;
	}

	ifstream tdb(ttable);
	while (!tdb.eof()) {
		tdb.getline(inputString3, 100);
		cout << inputString3 << endl;
	}
}