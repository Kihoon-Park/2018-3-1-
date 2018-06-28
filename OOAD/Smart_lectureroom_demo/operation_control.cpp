#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "operation_control.h"

#define MAX_SIZE 1000

using namespace std;

void Oper_control::receive_sensor_data(char *dbname) {
	ifstream sensor(dbname);
	char inputString[MAX_SIZE];
	char* buf;

	sensor.getline(inputString, sizeof(inputString)); // inside sensor data

	sensor.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	i_degree = atoi(buf);

	sensor.getline(inputString, sizeof(inputString)); // inside humid
	buf = strstr(inputString, " ");
	buf += 1;
	i_humid = atoi(buf);

	sensor.getline(inputString, sizeof(inputString)); // inside co2
	buf = strstr(inputString, " ");
	buf += 1;
	i_co2 = atoi(buf);

	sensor.getline(inputString, sizeof(inputString)); // inside dust

	sensor.getline(inputString, sizeof(inputString)); // inside ismove
	buf = strstr(inputString, " ");
	buf += 1;
	i_ismove = atoi(buf);

	sensor.getline(inputString, sizeof(inputString)); // inside islight
	buf = strstr(inputString, " ");
	buf += 1;
	i_islight = atoi(buf);

	sensor.getline(inputString, sizeof(inputString)); // blank

	sensor.getline(inputString, sizeof(inputString)); // outside_sensor_data

	sensor.getline(inputString, sizeof(inputString)); // outside degree
	buf = strstr(inputString, " ");
	buf += 1;
	o_degree = atoi(buf);

	sensor.getline(inputString, sizeof(inputString)); // outside humid
	buf = strstr(inputString, " ");
	buf += 1;
	o_humid = atoi(buf);

	sensor.getline(inputString, sizeof(inputString)); // outside degree

	sensor.getline(inputString, sizeof(inputString)); // outside dust
	buf = strstr(inputString, " ");
	buf += 1;
	o_dust = atoi(buf);

	//cout << buf << endl;

	/*cout << "i_degree  : " << i_degree << endl;
	cout << "i_humid   : " << i_humid << endl;
	cout << "i_co2     : " << i_co2 << endl;
	cout << "i_ismove  : " << i_ismove << endl;
	cout << "i_islight : " << i_islight << endl << endl;

	cout << "o_degree  : " << o_degree << endl;
	cout << "o_humid   : " << o_humid << endl;
	cout << "o_dust    : " << o_dust << endl;*/
}

void Oper_control::receive_algo_data(char *algo_db) {
	ifstream algo(algo_db);
	char inputString[MAX_SIZE];
	char* buf;

	//algo.getline(inputString, sizeof(inputString)); // inside sensor data

	algo.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	min_i_degree = atoi(buf);

	algo.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	max_i_degree = atoi(buf);

	algo.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	max_i_humid = atoi(buf);

	algo.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	max_i_co2 = atoi(buf);

	algo.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	con_o_degree = atoi(buf);

	algo.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	con_o_humid = atoi(buf);

	algo.getline(inputString, sizeof(inputString)); // inside degree
	buf = strstr(inputString, " ");
	buf += 1;
	max_o_dust = atoi(buf);

	algo.close();

}


void Oper_control::operate(char *oper_db) {
	cout << i_ismove << " " << i_islight << endl;
	cout << i_degree << " " << min_i_degree << endl;
	if (i_ismove != 0 && i_islight != 0) { //�������� �ְ� ���� ������������ ����
		if (i_degree < min_i_degree) { // �ʹ� ����!
			heater = 1;
		}
		else if (i_degree > max_i_degree) { // �ʹ� ���
			window = 0;
			aircond = 1;
		}

		if (i_co2 > max_i_co2 && o_dust < max_o_dust) { //���Ⱑ Ź�Ҷ� (�̼������� ���� ��ġ ���Ͽ��� ��)
			window = 1;
		}
	}

	ofstream operdb(oper_db);

	operdb << "window:  " << window << endl;
	operdb << "aircond: " << aircond << endl;
	operdb << "heater:  " << heater << endl;
	operdb.close();
}