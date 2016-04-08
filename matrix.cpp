#include <iostream>

int main(int argc, char const *argv[]) {
	using namespace std;

	long N;
	char **matrix;

	cin >> N;

	matrix = new char*[N];
	for(long i = 0; i < N; i++) {
		matrix[i] = new char[N];

		for(long j = 0; j < N; j++)
			cin >> matrix[i][j];
	}
	
	for(long i = 0; i < N; i++) {
		for(long j = 0; j < N; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}

	for(long i = 0; i < N; i++)
		delete[] matrix[i];
	delete[] matrix;

	return 0;
}
