#ifndef  __Oper_H__
#define  __Oper_H__

class Oper_control {
private:
	//input_sensor_data
	int i_degree = 0;  // i == inside  ���� ������ ��
	int i_humid = 0;
	int i_co2 = 0;
	bool i_ismove = 0;
	bool i_islight = 0;

	int o_degree = 0; // o = ouside �ܺ� ������ ��
	int o_humid = 0;
	int o_dust = 0;

	//algorithm data
	int min_i_degree; // ���� ������ ���� ��
	int max_i_degree; // ���� ������ ������ ��
	int max_i_humid;

	int max_i_co2; // �Ѿ�� â�� ����


	int con_o_degree;  //������ �ܼ�ȭ�� ���� ����
	int con_o_humid;  //������ �ܼ�ȭ�� ���� ����
	int max_o_dust;  //�Ѿ�� â�� ���� ����

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
