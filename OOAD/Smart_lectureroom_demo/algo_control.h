#ifndef  __ALGO_H__
#define  __ALGO_H__

class Algo_control {
private:
	//algorithm data
	int min_i_degree; // ���� ������ ���� ��
	int max_i_degree; // ���� ������ ������ ��
	int max_i_humid;

	int max_i_co2; // �Ѿ�� â�� ����
	

	int con_o_degree;  //������ �ܼ�ȭ�� ���� ����
	int con_o_humid;  //������ �ܼ�ȭ�� ���� ����
	int max_o_dust;  //�Ѿ�� â�� ���� ����

public:
	void init_algo(char *algodb);
	void check_algo(char *algodb);
	void change_algo(char *algodb);
};


#endif // ! __ALGO_H__
