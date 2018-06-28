#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <io.h>
#include "sensor_control.h"
#include "algo_control.h"
#include "operation_control.h"
#include "timetable_control.h"
#include "display_control.h"

//#include "display_control.cpp"

using namespace std;

void sensor_control();
void algo_control();
void oper_control();
void timetable_control();
void display_control();
void pressanykey();

void main() {
	int select;

	while (1) {
		cout << "SMART LECTURE BETA" << endl << endl;
		cout << "1.센서관리  2.알고리즘 관리   3.연산 실행   4.시간표 관리   5.디스플레이 출력 " << endl;
		cin >> select;

		if (select == 1) // 센서_컨트롤
			sensor_control();
		else if (select == 2) //알고리즘_컨트롤
			algo_control();
		else if (select == 3)
			oper_control();
		else if (select == 4)
			timetable_control();
		else if (select == 5)
			display_control();
		else {
			cout << "1부터 5 까지의 숫자만 입력 가능합니다." << endl;
			
		}
		pressanykey();
		system("cls");
	}
}

void sensor_control() {
	Sensor_control inside_sensor;
	Sensor_control outside_sensor;
	Sensor_control combined;

	char *in_sensor_db = "in_sensor_db.txt";
	char *out_sensor_db = "out_sensor_db.txt";
	char *combined_sensor_db = "comb_sensor_db.txt";



	int s_select;
	cout << "1)내부 센서값 임의지정  2)외부 센서값 임의지정  3)센서 추가/삭제(미구현)  4)센서 연결 확인   5)처음으로" << endl;
	cin >> s_select;
	if (s_select == 1) {
		inside_sensor.inputSensor(in_sensor_db);
		combined.Sensor_comb(in_sensor_db, out_sensor_db, combined_sensor_db);
	}
	else if (s_select == 2) {
		outside_sensor.inputSensor(out_sensor_db);
		combined.Sensor_comb(in_sensor_db, out_sensor_db, combined_sensor_db);
	}
	else if (s_select == 3) {
		cout << "아직 구현되지 않은 기능입니다." << endl;
	}
	else if (s_select == 4) {
		inside_sensor.Sensor_check();
		outside_sensor.Sensor_check();
	}
	else if (s_select == 5) {} // 아무것도 하지 않고 기본 화면으로 돌아감

	else
		cout << "1부터 5까지의 숫자만 입력 가능합니다";
	
	
}

void algo_control() {
	Algo_control algo;
	char *algo_db = "algodb.txt";
	
	int is_algo_exist = _access(algo_db, 0);
	if (is_algo_exist == -1) {
		cout << "알고리즘 DB 를 찾지 못해 기본 값으로 재생성합니다" << endl;
		algo.init_algo(algo_db); // 알고리즘 DB 가 삭제되었거나 없을 시 디폴트 값으로 재생성
		cout << "기본 알고리즘 DB 생성완료" << endl;
	}
	int a_select;
	cout << "1)알고리즘 확인  2)알고리즘 변경  3)알고리즘 초기화 4)처음으로" << endl;
	cin >> a_select;

	
	if (a_select == 1) {
		algo.check_algo(algo_db);
	}
	else if (a_select == 2) {
		algo.change_algo(algo_db);
	}
	else if (a_select == 3) {
		algo.init_algo(algo_db);
		cout << "알고리즘 기본 값 초기화 완료" << endl;
	}
	else if (a_select == 4) {} // 아무것도 하지 않고 기본 화면으로 돌아감

	else
		cout << "1부터 4까지의 숫자만 입력 가능합니다";
}

void oper_control() {
	
	Oper_control oper;
	char *combined_sensor_db = "comb_sensor_db.txt";
	char *algo_db = "algodb.txt";
	char *oper_db = "operdb.txt";
	oper.receive_sensor_data(combined_sensor_db);
	oper.receive_algo_data(algo_db);                //연산을 위해 sensordb, algodb 가져옴
	oper.operate(oper_db);
}

void timetable_control() {
	int t_select;
	char *ttable_db = "ttable_db.txt";
	Timetable_control ttable;
	
	int is_ttable_exist = _access(ttable_db, 0);
	if (is_ttable_exist == -1) {
		cout << "시간표 DB 를 찾지 못해 기본 값으로 재생성합니다" << endl;
		ttable.init_timetable(ttable_db); // 시간표 DB 가 삭제되었거나 없을 시 디폴트 값으로 재생성
		cout << "기본 시간표 DB 생성완료" << endl;
	}

	cout << "1)시간표 확인  2)시간표 변경  3)시간표 초기화 4)처음으로" << endl;
	cin >> t_select;
	if (t_select == 1) {
		ttable.show_timetable(ttable_db);
	}
	if (t_select == 2) {} // 미구현
	if (t_select == 3) {
		ttable.show_timetable(ttable_db);
	}
	if (t_select == 4) {}
}

void display_control() {
	Display_control disp;

	char *combined_sensor_db = "comb_sensor_db.txt";
	char *oper_db = "operdb.txt";
	char *ttable_db = "ttable_db.txt";

	disp.display(combined_sensor_db, oper_db, ttable_db);
}


void pressanykey() {
	cout << "... 아무 키나 입력하십시오." << endl << endl;
	_getch();
}