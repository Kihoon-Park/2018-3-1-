#include <iostream>
#include "math.h"
#include <stdlib.h>
#include <algorithm>
using namespace std;


struct Min {
	int number;
	int num;   // 표현할 숫자 - 계산용
	int bsize; // # of input variables
	int numcount;
	char binary[6] = { 0, };   // 2진수화
	int combined; //1 만 출력
	int count1s = 0;
	int numsize = 0;
	int numpack[255] = { 0, };
	int epi = 0;
};

class Minterm {
private:
	//int *k = new int;
	//int min->numcount;
	Min * min = new Min[255]; // num_minterm 개의 minterm 구조체 선언
	Min *minbuf = new Min[255];
	Min *minresult = new Min[255];
	Min *minout = new Min[255];
	Min *minepi = new Min[255];
	Min *minNepi = new Min[255];
	int count = 0;

	int sum;
	int rcount = 0;
public:
	void initnum(int num_Var, int num_minterm);

	void minsort();

	void cmp();

	void minprint();

	void output();
};

void Minterm::initnum(int num_Var, int num_minterm) {
	min->bsize = num_Var;
	minbuf->bsize = num_Var;
	minresult->bsize = num_Var;
	minout->bsize = num_Var;
	minepi->bsize = num_Var;
	minNepi->bsize = num_Var;
	min->numcount = num_minterm;

	//min->numcount = num_minterm;


	for (int i = 0; i < min->numcount; i++) {
		cin >> min[i].num; // num 입력
		min[i].number = min[i].num;
		min[i].combined = 1;
		min[i].numsize = 1;
		min[i].numpack[0] = min[i].num;
		//2진수로 변환
		for (int k = min->bsize - 1; k >= 0; k--) {
			if (min[i].num - pow(2, k) >= 0) {
				min[i].binary[k] = 1;
				min[i].num -= pow(2, k);
				min[i].count1s += 1;
				//cout << int(min->binary[k])<<" ";
			}
			else
				min[i].binary[k] = 0;

			min[i].binary[k] += 48; //아스키 코드화 0 > 48 , 1 > 49 , '-' = -5 > 45
		}
	}
}


void Minterm::minsort() {
	Min *mtmp = new Min[20];

	for (int a = 0; a < min->numcount - 1; a++) {
		for (int a = 0; a < min->numcount - 1; a++) {
			if (min[a].count1s > min[a + 1].count1s) {
				//printf("%d %d\n", min[i].count1s, min[i + 1].count1s);
				mtmp[1].count1s = min[a].count1s;
				min[a].count1s = min[a + 1].count1s;
				min[a + 1].count1s = mtmp[1].count1s;

				for (int k = min->bsize - 1; k >= 0; k--) {
					//cout << min[i].binary[k] << " ";

					mtmp[1].binary[k] = min[a].binary[k];
					min[a].binary[k] = min[a + 1].binary[k];
					min[a + 1].binary[k] = mtmp[1].binary[k];
				}

				mtmp[1].combined = min[a].combined;
				min[a].combined = min[a + 1].combined;
				min[a + 1].combined = mtmp[1].combined;

				int z = 0;
				for (int r = 0; r < min[a].numsize; r++) {
					mtmp[1].numpack[r] = min[a].numpack[r];
					min[a].numpack[r] = min[a + 1].numpack[r];
					min[a + 1].numpack[r] = mtmp[1].numpack[r];

				}
			}
		}


	}

	/*
	for (int i = 0; i < min->numcount; i++) {
	//cout << "Number : " << min[i].number;
	cout << "  Count1 : " << min[i].count1s;
	cout << "  binary: ";

	for (int k = min->bsize - 1; k >= 0; k--) {
	cout << min[i].binary[k] << " ";
	}
	cout <<" combined: "<< min[i].combined << " ";

	cout << "numpack: ";

	int z = 0;
	for (int r = 0; r < min[i].numsize; r++) {
	cout << min[i].numpack[r] << " ";
	}
	cout << endl;


	}
	cout << endl;
	*/
}

void Minterm::cmp() {

	//cout << sum << endl;
	//각 원소의 갯수
	int s[7] = { 0, };

	for (int a = 0; a < min->numcount; a++) {
		for (int k = 0; k <= 6; k++) {
			if (min[a].count1s == k)
				s[k] ++;
		}
	}
	
	int cp = 0;
	int buf = 0;
	int c = 0;


	int sumbuf = 0;
	for (int q = 0; q < 6; q++) {// 6은 뭐지? = #of 1s 의 갯수 (최대)
		for (int i = 0; i < s[q]; i++) {
			for (int j = 0; j < s[q + 1]; j++) {

			

				cp = 0;
				int xy = 0;
			
				for (int k = min->bsize - 1; k >= 0; k--) {
					if ((min[sumbuf + i].binary[k] == min[sumbuf + j + s[q]].binary[k]))
						cp++;
				
					else
						buf = k;
				}

				if (cp == min->bsize - 1) {

					int out = 0;
					for (int k = minbuf->bsize - 1; k >= 0; k--) {
						if (minbuf[i].binary[k] == minbuf[c - 1].binary[k])
							out += 1;
					}

					memcpy(&minbuf[c], &min[sumbuf + i], sizeof(Min));
					minbuf[c].binary[buf] = 50;
					minbuf[c].numsize = min[sumbuf + i].numsize * 2;
					int w = 0;
					for (int u = min[sumbuf + i].numsize; u < minbuf[c].numsize; u++) {
						minbuf[c].numpack[u] = min[sumbuf + j + s[q]].numpack[w];
						w++;
					}

					minbuf[c].combined = 1;

					c++;

					min[sumbuf + i].combined = 0;
					min[sumbuf + j + s[q]].combined = 0;
					
				}
			}

		}
		sumbuf += s[q];

	}

	for (int i = 0; i < min->numcount; i++) {
		if (min[i].combined == 1) {
			memcpy(&minresult[rcount], &min[i], sizeof(Min));
			rcount++;
		}

	}
	for (int i = 0; i < c; i++) {
		memcpy(&min[i], &minbuf[i], sizeof(Min));
	}
	min->numcount = c;
}
void Minterm::output() {
	minresult->bsize = min->bsize;
	cout << "output: " << endl;

	memcpy(&minout[0], &minresult[0], sizeof(Min));
	int c = 1;
	for (int i = 1; i < rcount; i++) {
		int is = 0;
		for (int k = minresult->bsize - 1; k >= 0; k--) {
			if (minresult[i].binary[k] == minout[c - 1].binary[k])
				is += 1;
		}

		if (is != minresult->bsize) {
			memcpy(&minout[c], &minresult[i], sizeof(Min));
			c++;
		}
	}
	/*for (int i = 0; i < c; i++) {
	for (int k = minresult->bsize - 1; k >= 0; k--)
	cout << minresult[i].binary[k] << "";
	cout << endl;
	}*/


	int packbuf[100] = { 0, };
	int epicount = 0;
	int Nepicount = 0;
	for (int m = 0; m < 100; m++) {
		for (int i = 0; i < c; i++) {
			for (int r = 0; r < minout[i].numsize; r++) {
				if (minout[i].numpack[r] == m)
					packbuf[m] ++;
			}
		}
	}
	//for (int m = 0; m < 100; m++) {
	//	cout << packbuf[m] << " ";
	//}cout << endl;

	for (int m = 0; m < 100; m++) {
		if (packbuf[m] == 1) {
			for (int i = 0; i < c; i++) {
				for (int r = 0; r < minout[i].numsize; r++) {
					if (minout[i].numpack[r] == m)
						minout[i].epi = 1;
				}
			}
		}
	}
	/*
	for (int i = 0; i < c; i++) {
	//cout << "Number : " << min[i].number;
	// << "Count1 : " << minout[i].count1s;
	cout << "  binary: ";


	for (int k = minout->bsize - 1; k >= 0; k--) {
	cout << minout[i].binary[k] << "";
	}
	//cout << " combined: " << minout[i].combined << " ";

	cout << " numpack: ";

	int z = 0;
	for (int r = 0; r < minout[i].numsize; r++) {
	cout << minout[i].numpack[r] << " ";
	}
	cout << "  EPI: " << minout[i].epi << endl;
	}*/

	for (int i = 0; i < c; i++) {
		if (minout[i].epi == 1) {
			memcpy(&minepi[epicount], &minout[i], sizeof(Min));
			epicount++;
		}
		else {
			memcpy(&minNepi[Nepicount], &minout[i], sizeof(Min));
			Nepicount++;
		}

	}

	Min *mtmp = new Min[20];

	for (int k = minNepi->bsize - 1; k >= 0; k--) {
		int epi0 = 0;
		int epi1 = 0;
		int epi2 = 0;

		for (int x = 0; x < Nepicount; x++) {
			//cout << minepi[x].binary[k] << " ";
			if (minNepi[x].binary[k] == 48) { // 0
				epi0++;
			}

			if (minNepi[x].binary[k] == 49) { // 1
				epi1++;
			}

			if (minNepi[x].binary[k] == 50) { // -
				epi2++;
			}

		}
		//cout << epi0 << " " << epi1 << " " << epi2 << endl;
		int a1 = 0;

		for (int y = 0; y < Nepicount; y++) {
			if (minNepi[y].binary[k] == 48) {
				//memcpy(&mtmp[1], &minNepi[y], sizeof(Min));
				//memcpy(&minNepi[0], &minNepi[y], sizeof(Min));
				//memcpy(&minNepi[y], &mtmp[1], sizeof(Min));
			}
		}

	}


	//EPI 출력
	cout << "EPI  ";

	int tenepi[255] = { 0, };
	for (int i = 0; i < epicount; i++) {

		//cout << "Number : " << min[i].number;
		// << "Count1 : " << minout[i].count1s;
		//cout << "binary: ";

		int ten = pow(10, minepi->bsize - 1);


		for (int k = minepi->bsize - 1; k >= 0; k--) {

			tenepi[i] += ten * (minepi[i].binary[k] - 48);
			ten /= 10;

		}

		for (int i = 0; i < epicount; i++) {
			//cout << tenepi[i] << endl;
		}
	}
	sort(tenepi, tenepi + epicount);
	int countbuf = epicount;
	for (int i = 0; i < countbuf - 1; i++) {
		if (tenepi[i] == tenepi[i + 1]) {
			tenepi[i] = 10000000;
			epicount--;
		}
	}
	sort(tenepi, tenepi + countbuf);

	for (int i = 0; i < epicount; i++) {
		int ten = pow(10, minepi->bsize - 1);

		for (int k = minepi->bsize - 1; k >= 0; k--) {
			//if (minepi[i].binary[k] == 50)
			//	minepi[i].binary[k] -= 5;
			//cout << endl << ten <<" "<< tenNepi[i] <<" "<< (tenNepi[i] / ten)<< endl;
			minepi[i].binary[k] = (tenepi[i] / ten) + 48;
			//cout << minepi[i].binary[k] << " ";
			if (minepi[i].binary[k] != 48)
				tenepi[i] %= ten;
			ten /= 10;
		}//cout << endl;
	}
	for (int i = 0; i < epicount; i++) {
		for (int k = minepi->bsize - 1; k >= 0; k--) {
			if (minepi[i].binary[k] == 50)
				minepi[i].binary[k] -= 5;
			cout << minepi[i].binary[k] << "";
		}cout << "  ";
	}


	//NEPI 출력
	cout << "NEPI  ";

	int tenNepi[255] = { 0, };
	for (int i = 0; i < Nepicount; i++) {

		//cout << "Number : " << min[i].number;
		// << "Count1 : " << minout[i].count1s;
		//cout << "binary: ";

		int ten = pow(10, minNepi->bsize - 1);


		for (int k = minNepi->bsize - 1; k >= 0; k--) {

			tenNepi[i] += ten * (minNepi[i].binary[k] - 48);
			ten /= 10;

		}

		for (int i = 0; i < Nepicount; i++) {
			//cout << tenNepi[i] << endl;
		}
	}
	sort(tenNepi, tenNepi + Nepicount);
	int Ncountbuf = Nepicount;
	for (int i = 0; i < Ncountbuf - 1; i++) {
		if (tenNepi[i] == tenNepi[i + 1]) {
			tenNepi[i] = 10000000;
			Nepicount--;
		}
	}
	sort(tenNepi, tenNepi + Ncountbuf);

	for (int i = 0; i < Nepicount; i++) {
		int ten = pow(10, minNepi->bsize - 1);

		for (int k = minNepi->bsize - 1; k >= 0; k--) {

			minNepi[i].binary[k] = (tenNepi[i] / ten) + 48;

			if (minNepi[i].binary[k] != 48)
				tenNepi[i] %= ten;
			ten /= 10;
		}
	}
	for (int i = 0; i < Nepicount; i++) {
		for (int k = minNepi->bsize - 1; k >= 0; k--) {
			if (minNepi[i].binary[k] == 50)
				minNepi[i].binary[k] -= 5;
			cout << minNepi[i].binary[k] << "";
		}cout << "  ";
	}

}
void main(void)
{
	Minterm minterm;
	int num_Var, num_minterm;
	cout << "input:" << endl;
	cin >> num_Var >> num_minterm;

	minterm.initnum(num_Var, num_minterm);

	minterm.minsort();

	for (int i = 0; i < 10; i++) {
		minterm.cmp();
	}
	minterm.output();
	cout << endl;
}