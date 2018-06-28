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
		cout << "1.��������  2.�˰��� ����   3.���� ����   4.�ð�ǥ ����   5.���÷��� ��� " << endl;
		cin >> select;

		if (select == 1) // ����_��Ʈ��
			sensor_control();
		else if (select == 2) //�˰���_��Ʈ��
			algo_control();
		else if (select == 3)
			oper_control();
		else if (select == 4)
			timetable_control();
		else if (select == 5)
			display_control();
		else {
			cout << "1���� 5 ������ ���ڸ� �Է� �����մϴ�." << endl;
			
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
	cout << "1)���� ������ ��������  2)�ܺ� ������ ��������  3)���� �߰�/����(�̱���)  4)���� ���� Ȯ��   5)ó������" << endl;
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
		cout << "���� �������� ���� ����Դϴ�." << endl;
	}
	else if (s_select == 4) {
		inside_sensor.Sensor_check();
		outside_sensor.Sensor_check();
	}
	else if (s_select == 5) {} // �ƹ��͵� ���� �ʰ� �⺻ ȭ������ ���ư�

	else
		cout << "1���� 5������ ���ڸ� �Է� �����մϴ�";
	
	
}

void algo_control() {
	Algo_control algo;
	char *algo_db = "algodb.txt";
	
	int is_algo_exist = _access(algo_db, 0);
	if (is_algo_exist == -1) {
		cout << "�˰��� DB �� ã�� ���� �⺻ ������ ������մϴ�" << endl;
		algo.init_algo(algo_db); // �˰��� DB �� �����Ǿ��ų� ���� �� ����Ʈ ������ �����
		cout << "�⺻ �˰��� DB �����Ϸ�" << endl;
	}
	int a_select;
	cout << "1)�˰��� Ȯ��  2)�˰��� ����  3)�˰��� �ʱ�ȭ 4)ó������" << endl;
	cin >> a_select;

	
	if (a_select == 1) {
		algo.check_algo(algo_db);
	}
	else if (a_select == 2) {
		algo.change_algo(algo_db);
	}
	else if (a_select == 3) {
		algo.init_algo(algo_db);
		cout << "�˰��� �⺻ �� �ʱ�ȭ �Ϸ�" << endl;
	}
	else if (a_select == 4) {} // �ƹ��͵� ���� �ʰ� �⺻ ȭ������ ���ư�

	else
		cout << "1���� 4������ ���ڸ� �Է� �����մϴ�";
}

void oper_control() {
	
	Oper_control oper;
	char *combined_sensor_db = "comb_sensor_db.txt";
	char *algo_db = "algodb.txt";
	char *oper_db = "operdb.txt";
	oper.receive_sensor_data(combined_sensor_db);
	oper.receive_algo_data(algo_db);                //������ ���� sensordb, algodb ������
	oper.operate(oper_db);
}

void timetable_control() {
	int t_select;
	char *ttable_db = "ttable_db.txt";
	Timetable_control ttable;
	
	int is_ttable_exist = _access(ttable_db, 0);
	if (is_ttable_exist == -1) {
		cout << "�ð�ǥ DB �� ã�� ���� �⺻ ������ ������մϴ�" << endl;
		ttable.init_timetable(ttable_db); // �ð�ǥ DB �� �����Ǿ��ų� ���� �� ����Ʈ ������ �����
		cout << "�⺻ �ð�ǥ DB �����Ϸ�" << endl;
	}

	cout << "1)�ð�ǥ Ȯ��  2)�ð�ǥ ����  3)�ð�ǥ �ʱ�ȭ 4)ó������" << endl;
	cin >> t_select;
	if (t_select == 1) {
		ttable.show_timetable(ttable_db);
	}
	if (t_select == 2) {} // �̱���
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
	cout << "... �ƹ� Ű�� �Է��Ͻʽÿ�." << endl << endl;
	_getch();
}