#include <iostream>
#include <cmath> 
using namespace std;

int main()
{
	int num, sum, n;
	cin >> n;
	sum = 0;
	if (n <= 0) {
		return 0;
	}
	else if (n == 1) {
		for (int i = 0; i <= 9; i++) {
			cout << i << endl;
		}
	}
	else {
		int min = pow(10, n - 1);
		int max = pow(10, n) - 1;
		for (num = min; num <= max; num++) {
			int former = num;
			while (num != 0){
				sum += pow(num % 10, n);
				num = num / 10;
				cout << min <<" "<< max << endl;
				cout << sum <<" "<< num << endl;
			}
			if (sum == former) {
				cout << former << endl;
			}
		}
	}

	return 0;
}
