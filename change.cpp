/*
	Coin Change 
	-----------
	Result: accepted
	Original: http://acm.bnu.edu.cn/v3/problem_show.php?pid=17813

	Suppose there are 5 types of coins: 50-cent, 25-cent, 10-cent, 5-cent, and 1-cent. We want to make changes with these coins for a given amount of money.

	For example, if we have 11 cents, then we can make changes with one 10-cent coin and one 1-cent coin, two 5-cent coins and one 1-cent coin, one 5-cent coin and six 1-cent coins, or eleven 1-cent coins. So there are four ways of making changes for 11 cents with the above coins. Note that we count that there is one way of making change for zero cent.

	Write a program to find the total number of different ways of making changes for any amount of money in cents. Your program should be able to handle up to 7489 cents.

	Input 
	The input file contains any number of lines, each one consisting of a number for the amount of money in cents.

	Output 
	For each input line, output a line containing the number of different ways of making changes with the above 5 types of coins.
*/

#include <cstdio>
#include <vector>

#define K 5
const int coins[K] = {1, 5, 10, 25, 50};

long * solve(const long value);

int main(int argc, char const *argv[]) {
	using namespace std;
	
	vector<long> Ns;
	long *results;
	long max = 0;
	long temp;

	while(scanf("%ld\n", &temp) != EOF) {
		if (temp > max)
			max = temp;

		Ns.push_back(temp);
	}

	results = solve(max);

	for (vector<long>::iterator i = Ns.begin(); i != Ns.end(); i++)
		printf("%ld\n", results[*i]);
		// cout << results[*i] << endl;
	fflush(stdout);

	delete[] results;
 
	return 0;
}

long * solve(const long value) {	
	long *ways = new long[value + 1];
	long previous_ways[value + 1];
	long coin, rest;

	for (long amount = 0; amount <= value; amount++)
		ways[amount] = 1 + amount / coins[1];

	for (int i = 2; (i < K) && ((coin = coins[i]) <= value); i++) {	
		for (long amount = 0; amount <= value; amount++)
			previous_ways[amount] = ways[amount];

		for (long amount = coin; amount <= value; amount++)
			for (long way = coin; way <= amount; way += coin) {
				rest = amount - way;
				ways[amount] += previous_ways[rest];
			}
	}

	return ways;
}
