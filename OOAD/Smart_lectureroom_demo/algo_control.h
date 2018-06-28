#ifndef  __ALGO_H__
#define  __ALGO_H__

class Algo_control {
private:
	//algorithm data
	int min_i_degree; // 보다 낮으면 히터 온
	int max_i_degree; // 보다 높으면 에어컨 온
	int max_i_humid;

	int max_i_co2; // 넘어가면 창문 오픈
	

	int con_o_degree;  //조건의 단순화를 위해 배제
	int con_o_humid;  //조건의 단순화를 위해 배제
	int max_o_dust;  //넘어가면 창문 오픈 차단

public:
	void init_algo(char *algodb);
	void check_algo(char *algodb);
	void change_algo(char *algodb);
};


#endif // ! __ALGO_H__
