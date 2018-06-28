#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "algo_control.h"

#define MAX_SIZE 1000

using namespace std;

void Algo_control::init_algo(char *algo_db) {
	
	min_i_degree = 5; // 보다 낮으면 히터 온
	max_i_degree = 25; // 보다 높으면 에어컨 온
	max_i_humid = 30;

	max_i_co2 = 30; // 넘어가면 창문 오픈

	con_o_degree = 30;  //조건의 단순화를 위해 배제
	con_o_humid = 30;  //조건의 단순화를 위해 배제
	max_o_dust = 80; //넘어가면 창문 오픈 차단

	
	ofstream algodb(algo_db);
	
	algodb << "min_i_degree: " << min_i_degree << endl; // 보다 낮으면 히터 온
	algodb << "max_i_degree: " << max_i_degree << endl; // 보다 높으면 에어컨 온
	algodb << "max_i_humid:  " << max_i_humid << endl;

	algodb << "max_i_co2:    " << max_i_co2 << endl; // 넘어가면 창문 오픈
	
	algodb << "con_o_degree: " << con_o_degree << endl; //조건의 단순화를 위해 배제
	algodb << "con_o_humid:  " << con_o_humid << endl; // 조건의 단순화를 위해 배제
	algodb << "max_o_dust:   " << max_o_dust << endl;  //넘어가면 창문 오픈 차단
	
	
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

	cout << "min_i_degree  : " << min_i_degree << endl; // 보다 낮으면 히터 온
	cout << "max_i_degree  : " << max_i_degree << endl; // 보다 높으면 에어컨 온
	cout << "max_i_humid   : " << max_i_humid << endl;

	cout << "max_i_co2     : " << max_i_co2 << endl; // 넘어가면 창문 오픈
	
	cout << "con_o_degree  : " << con_o_degree << endl;// 조건의 단순화를 위해 배제
	cout << "con_o_humid   : " << con_o_humid << endl;  //조건의 단순화를 위해 배제
	cout << "max_o_dust    : " << max_o_dust << endl;  //넘어가면 창문 오픈 차단
	
}

void Algo_control::change_algo(char *algo_db) {
	min_i_degree = 5; // 보다 낮으면 히터 온
	max_i_degree = 25; // 보다 높으면 에어컨 온
	max_i_humid = 30;

	max_i_co2 = 30; // 넘어가면 창문 오픈

	con_o_degree = 30;  //조건의 단순화를 위해 배제
	con_o_humid = 30;  //조건의 단순화를 위해 배제
	max_o_dust = 80; //넘어가면 창문 오픈 차단


	cout << endl << "바꿀 조건값 선택" << endl;
	cout << endl << "1.최소온도 2.최대온도 3.최대습도 4.최대co2 " << endl << "5.외부최대온도 6.외부최대습도 7.외부최대미세먼지" << endl;

	int c_select;
	int new_value;
	cin >> c_select;
	cout << "수치를 입력하십시오. >> ";
	cin >> new_value;
	if (c_select == 1) { min_i_degree = new_value; }
	if (c_select == 2) { max_i_degree = new_value; }
	if (c_select == 3) { max_i_humid = new_value; }
	if (c_select == 4) { max_i_co2 = new_value; }
	if (c_select == 5) { con_o_degree = new_value; }
	if (c_select == 6) { con_o_humid = new_value; }
	if (c_select == 7) { max_o_dust = new_value; }

	ofstream algodb(algo_db);

	algodb << "min_i_degree: " << min_i_degree << endl; // 보다 낮으면 히터 온
	algodb << "max_i_degree: " << max_i_degree << endl; // 보다 높으면 에어컨 온
	algodb << "max_i_humid:  " << max_i_humid << endl;

	algodb << "max_i_co2:    " << max_i_co2 << endl; // 넘어가면 창문 오픈

	algodb << "con_o_degree: " << con_o_degree << endl; //조건의 단순화를 위해 배제
	algodb << "con_o_humid:  " << con_o_humid << endl; // 조건의 단순화를 위해 배제
	algodb << "max_o_dust:   " << max_o_dust << endl;  //넘어가면 창문 오픈 차단


	algodb.close();
}