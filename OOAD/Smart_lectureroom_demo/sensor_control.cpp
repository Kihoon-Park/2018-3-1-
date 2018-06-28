#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "sensor_control.h"

#define MAX_SIZE 1000

using namespace std;

void Sensor_control::inputSensor(char *sensor_db) {

	cout << "센서값의 즉각 변경을 표시하기 위해 임의적으로 입력합니다." << endl;
	cout << "온도 습도 이산화탄소 미세먼지 조도여부 움직임여부 순으로 입력합니다." << endl;
	
	cin >> degree >> humid >> co2 >> dust >> ismove >> islight;


	ofstream sensordb(sensor_db); // 데이터 재작성 - 원래 실시간으로 입력되고 적용되어야 하지만 임의 구현을 통해 재입력
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
	cout << "센서 확인중..." << endl;
	Sleep(2000);
	cout << "센서 정상 작동 확인" << endl;
}