/*
	Solutions to an Equation
	------------------------
	Status: wrong answer
	Original: http://acm.bnu.edu.cn/v3/problem_show.php?pid=13225

	You have to find the number of solutions of the following equation:
		Ax + By + C = 0
	Where A, B, C, x, y are integers and x1 ≤ x ≤ x2 and y1 ≤ y ≤ y2.

	Input
	Input starts with an integer T (≤ 10000), denoting the number of test cases.
	Each case starts with a line containing seven integers A, B, C, x1, x2, y1, y2 (x1 ≤ x2, y1 ≤ y2). The value of each integer will lie in the range [-108, 108].

	Output
	For each case, print the case number and the total number of solutions.
*/

#include <iostream>

int mmc(int a, int b) {
	if (a < 0)
		a *= -1;

	if (b < 0)
		b *= -1;

	while (a != b) {
		if (a > b)
			a -= b;
		else
			b -= a;
	}

	return a;
}

int main(int argc, char const *argv[]) {
	using namespace std;
	
	int T, A, B, C, x1, x2, y1, y2;
	int dx, dy, aux;
	int x, y;
	int n;

	cin >> T;
	for (int i = 1; i <= T; i++) {
		cin >> A >> B >> C >> x1 >> x2 >> y1 >> y2;

		n = 0;
		dx = x2 - x1 + 1;
		dy = y2 - y1 + 1;

		if ( (A == 0) && (B == 0) ) {
			if (C == 0)
				n = dx * dy;
		}

		else if (A == 0) {
			y = -C / B;

			if ( (C % B == 0) && (y >= y1) && (y <= y2) )
				n = dx;
		}

		else if (B == 0) {
			x = -C / A;

			if ( (C % A == 0) && (x >= x1) && (x <= x2) )
				n = dy;
		}

		else {
			aux = B / mmc(A, B);
			if (aux < 0)
				aux *= -1;

			for (x = x1; (n == 0) && (x < (x1 + aux)); x++) {
				y = -(A * x + C) / B;

				if (-(A * x + C) % B == 0)
					n = 1;
			}

			n = 0;
			for (x -= 1; x <= x2; x += aux) {
				y = -(A * x + C) / B;

				if ( (y >= y1) && (y <= y2) )
					n++;
			}
		}

		cout << "Case " << i << ": " << n << endl;
	}

	return 0;
}
