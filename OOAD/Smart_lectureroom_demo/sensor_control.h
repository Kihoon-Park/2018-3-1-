#ifndef  __SENSOR_H__
#define  __SENSOR_H__

class Sensor_control {
private:
	int degree = 0;
	int humid = 0;
	int co2 = 0;
	int dust = 0;
	bool ismove = 0;
	bool islight = 0;
public:
	void inputSensor(char *sensor_db);
	void Sensor_comb(char *in_db, char *out_db, char *comb_db);
	void Sensor_check();
};


#endif // ! __SENSOR_H__
