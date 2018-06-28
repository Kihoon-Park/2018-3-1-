#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "algo_control.h"

#define MAX_SIZE 1000

using namespace std;

void Algo_control::init_algo(char *algo_db) {
	
	min_i_degree = 5; // ���� ������ ���� ��
	max_i_degree = 25; // ���� ������ ������ ��
	max_i_humid = 30;

	max_i_co2 = 30; // �Ѿ�� â�� ����

	con_o_degree = 30;  //������ �ܼ�ȭ�� ���� ����
	con_o_humid = 30;  //������ �ܼ�ȭ�� ���� ����
	max_o_dust = 80; //�Ѿ�� â�� ���� ����

	
	ofstream algodb(algo_db);
	
	algodb << "min_i_degree: " << min_i_degree << endl; // ���� ������ ���� ��
	algodb << "max_i_degree: " << max_i_degree << endl; // ���� ������ ������ ��
	algodb << "max_i_humid:  " << max_i_humid << endl;

	algodb << "max_i_co2:    " << max_i_co2 << endl; // �Ѿ�� â�� ����
	
	algodb << "con_o_degree: " << con_o_degree << endl; //������ �ܼ�ȭ�� ���� ����
	algodb << "con_o_humid:  " << con_o_humid << endl; // ������ �ܼ�ȭ�� ���� ����
	algodb << "max_o_dust:   " << max_o_dust << endl;  //�Ѿ�� â�� ���� ����
	
	
	algodb.close();

	
}
void Algo_control::check_algo(char *algo_db) {
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

	cout << "min_i_degree  : " << min_i_degree << endl; // ���� ������ ���� ��
	cout << "max_i_degree  : " << max_i_degree << endl; // ���� ������ ������ ��
	cout << "max_i_humid   : " << max_i_humid << endl;

	cout << "max_i_co2     : " << max_i_co2 << endl; // �Ѿ�� â�� ����
	
	cout << "con_o_degree  : " << con_o_degree << endl;// ������ �ܼ�ȭ�� ���� ����
	cout << "con_o_humid   : " << con_o_humid << endl;  //������ �ܼ�ȭ�� ���� ����
	cout << "max_o_dust    : " << max_o_dust << endl;  //�Ѿ�� â�� ���� ����
	
}

void Algo_control::change_algo(char *algo_db) {
	min_i_degree = 5; // ���� ������ ���� ��
	max_i_degree = 25; // ���� ������ ������ ��
	max_i_humid = 30;

	max_i_co2 = 30; // �Ѿ�� â�� ����

	con_o_degree = 30;  //������ �ܼ�ȭ�� ���� ����
	con_o_humid = 30;  //������ �ܼ�ȭ�� ���� ����
	max_o_dust = 80; //�Ѿ�� â�� ���� ����


	cout << endl << "�ٲ� ���ǰ� ����" << endl;
	cout << endl << "1.�ּҿµ� 2.�ִ�µ� 3.�ִ���� 4.�ִ�co2 " << endl << "5.�ܺ��ִ�µ� 6.�ܺ��ִ���� 7.�ܺ��ִ�̼�����" << endl;

	int c_select;
	int new_value;
	cin >> c_select;
	cout << "��ġ�� �Է��Ͻʽÿ�. >> ";
	cin >> new_value;
	if (c_select == 1) { min_i_degree = new_value; }
	if (c_select == 2) { max_i_degree = new_value; }
	if (c_select == 3) { max_i_humid = new_value; }
	if (c_select == 4) { max_i_co2 = new_value; }
	if (c_select == 5) { con_o_degree = new_value; }
	if (c_select == 6) { con_o_humid = new_value; }
	if (c_select == 7) { max_o_dust = new_value; }

	ofstream algodb(algo_db);

	algodb << "min_i_degree: " << min_i_degree << endl; // ���� ������ ���� ��
	algodb << "max_i_degree: " << max_i_degree << endl; // ���� ������ ������ ��
	algodb << "max_i_humid:  " << max_i_humid << endl;

	algodb << "max_i_co2:    " << max_i_co2 << endl; // �Ѿ�� â�� ����

	algodb << "con_o_degree: " << con_o_degree << endl; //������ �ܼ�ȭ�� ���� ����
	algodb << "con_o_humid:  " << con_o_humid << endl; // ������ �ܼ�ȭ�� ���� ����
	algodb << "max_o_dust:   " << max_o_dust << endl;  //�Ѿ�� â�� ���� ����


	algodb.close();
}