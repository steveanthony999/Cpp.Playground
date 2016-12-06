#include <iostream>
using namespace std;

/*
	https://projecteuler.net/problem=5
	2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

	What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

int main(){

	int usrQR = 0;

	//user input prompt (for debugging)
	cout << "Smallest Multiple of 1 - n: ";
	cin >> usrQR;

	int usrParam = usrQR; //user adjustable parameters (1 - usrParam)

	long result = 0;
	int nCount = 0;
	int nTarget = usrParam;

	long n = 1;
	for(int i = 1; i < usrParam; i++){
		n = n * i;
	}

	while(n > 0){

		

		int d = 1;
		while(d < nTarget + 1){



			if((n % d) == 0){
				nCount++;
			}
			d++;
		}

		if(nCount == nTarget){
			result = n;
		}

		nCount = 0;
		n--;
	}

	cout << result << endl;
	cout << endl;
	return 0;
}
