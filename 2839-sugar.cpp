#include <iostream>

using namespace std;

int main() {
	int i;
	cin >> i;
	
	int buf;

	int result1;
	int result2;
	
	buf = i;
	result1 = buf / 5;

	while (1) {	
		//cout << (buf - result1 * 5) % 3 << endl;
		if ((buf - result1 * 5) % 3 == 0) {
			result2 = (buf - (result1 * 5)) / 3;
			break;
		}
		else
			result1--;
	}

	//cout << result1 << " " << result2 << endl;
	if (result1 == -1)
		cout << result1;
	else
		cout << result1 + result2;
}