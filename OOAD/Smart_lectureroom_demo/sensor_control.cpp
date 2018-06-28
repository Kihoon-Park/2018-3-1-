#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "sensor_control.h"

#define MAX_SIZE 1000

using namespace std;

void Sensor_control::inputSensor(char *sensor_db) {

	cout << "�������� �ﰢ ������ ǥ���ϱ� ���� ���������� �Է��մϴ�." << endl;
	cout << "�µ� ���� �̻�ȭź�� �̼����� �������� �����ӿ��� ������ �Է��մϴ�." << endl;
	
	cin >> degree >> humid >> co2 >> dust >> ismove >> islight;


	ofstream sensordb(sensor_db); // ������ ���ۼ� - ���� �ǽð����� �Էµǰ� ����Ǿ�� ������ ���� ������ ���� ���Է�
	sensordb << "degree:  " << degree << endl;
	sensordb << "humid:   " << humid << endl;
	sensordb << "co2:     " << co2 << endl;
	sensordb << "dust:    " << dust << endl;
	sensordb << "ismove:  " << ismove << endl;
	sensordb << "islight: " << islight << endl;

	sensordb.close();
}
void Sensor_control::Sensor_comb(char *in_db, char *out_db, char *comb_db) {
	ifstream indb(in_db);
	ifstream outdb(out_db);

	ofstream combdb(comb_db);

	char inputString[MAX_SIZE];
	char inputString2[MAX_SIZE];

	combdb << "inside_sensor_data" << endl;
	while (!indb.eof()) {
		indb.getline(inputString, 100);
		combdb << inputString << endl;
	}

	combdb << "outside_sensor_data" << endl;
	while (!outdb.eof()) {
		outdb.getline(inputString2, 100);
		combdb << inputString2 << endl;
	}

	indb.close();
	outdb.close();
	combdb.close();
}
void Sensor_control::Sensor_check() {
	cout << "���� Ȯ����..." << endl;
	Sleep(2000);
	cout << "���� ���� �۵� Ȯ��" << endl;
}