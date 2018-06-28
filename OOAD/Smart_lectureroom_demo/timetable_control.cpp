#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "timetable_control.h"
#define MAX_SIZE 1000

using namespace std;

void Timetable_control::init_timetable(char *ttable_db) {
	ofstream ttable(ttable_db);

	ttable << "요일:      " << c1_dw << endl;
	ttable << "시간:      " << c1_time << endl;
	ttable << "과목 이름: " << c1_name << endl;

	ttable << "요일:      " << c2_dw << endl;
	ttable << "시간:      " << c2_time << endl;
	ttable << "과목 이름: " << c2_name << endl;
}

void Timetable_control::show_timetable(char *ttable_db) {
	ofstream ttable(ttable_db);

	ttable << "요일:  " << c1_dw << endl;
	ttable << "시간   " << c1_time << endl;
	ttable << "과목 이름" << c1_name << endl;

	ttable << "요일:  " << c2_dw << endl;
	ttable << "시간   " << c2_time << endl;
	ttable << "과목 이름" << c2_name << endl;
}