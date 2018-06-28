#ifndef  __TTABLE_H__
#define  __TTABLE_H__

class Timetable_control {
private:
	char *c1_dw = "월";
	char *c1_time = "03:00~04:15";
	char *c1_name = "객체지향분석및설계";

	char *c2_dw = "수";
	char *c2_time = "09:00~10:15";
	char *c2_name = "데이터베이스";
public:
	void init_timetable(char *ttable_db);
	void show_timetable(char *ttable_db);
};


#endif // ! __TTABLE_H__
