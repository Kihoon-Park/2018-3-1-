#ifndef  __Oper_H__
#define  __Oper_H__

class Oper_control {
private:
	//input_sensor_data
	int i_degree = 0;  // i == inside  내부 센서의 값
	int i_humid = 0;
	int i_co2 = 0;
	bool i_ismove = 0;
	bool i_islight = 0;

	int o_degree = 0; // o = ouside 외부 센서의 값
	int o_humid = 0;
	int o_dust = 0;

	//algorithm data
	int min_i_degree; // 보다 낮으면 히터 온
	int max_i_degree; // 보다 높으면 에어컨 온
	int max_i_humid;

	int max_i_co2; // 넘어가면 창문 오픈


	int con_o_degree;  //조건의 단순화를 위해 배제
	int con_o_humid;  //조건의 단순화를 위해 배제
	int max_o_dust;  //넘어가면 창문 오픈 차단

	//operation data
	int window = 0;
	int aircond = 0;
	int heater = 0;

public:
	void receive_sensor_data(char *dbname);
	void receive_algo_data(char *algo_db);
	void operate(char *oper_db);
	//void change_algo();
};


#endif // ! __Oper_H__
