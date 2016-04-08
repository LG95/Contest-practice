/*
	The new President
	-----------------
	Status: accepted
	Original: http://acm.bnu.edu.cn/v3/problem_show.php?pid=28807

	Finally, it is time to vote for a new president and you are really excited about that. You know that the final results may take weeks to be announced, while you can't really wait to see the results.

	Somehow you managed to get the preferences list for every voter (we don't care how you managed to get this piece of information!). Each voter sorted out all candidates starting by his most preferred candidate and ending with his least preferred one. When voting, a voter votes for the candidate who comes first in his preferences list. For example, if there are 5 candidates (numbered 1 to 5), and the preferences list for one voter is [3, 2, 5, 1, 4] and the current competing candidates in the voting process are candidates 2 and 4, the voter will vote for candidate number 2.

	Here are the rules for the election process:
		There are C candidates (numbered from 1 to C), and V voters (V is always an odd number).
		The election process consists of up to 2 rounds. All candidates compete in the the first round. If a candidate receives more than 50% of the votes, he wins, otherwise another round takes place, in which only the top 2 candidates compete for the presidency. The candidate who receives more votes than his opponent wins and becomes the new president.
		You can safely assume that the given preferences will never cause a situation in which the second and the third candidates from the first round receive the same number of votes.
		The voters' preferences are the same in both rounds, and each voter must vote exactly once in each round for a currently competing candidate according to his preferences.

	Given the preferences lists, you need to write a program to figure out which candidate will win and in which round.

	Input
	Your program will be tested on one or more test cases. The first line of the input will be a single integer T, the number of test cases (1 <= T <= 100). Followed by the test cases, the first line of a test case contains two integers C and V separated by a single space. C and V (1 <= C, V <= 100)represent the number of candidates and voters respectively, followed by V lines each line contains C integers separated by a single space, representing the preferences list for a single voter (the first is his most preferable candidate while the last is his least preferable one). Each integer from 1 to C will appear exactly once in each line.

	Output
	For each test case, print on a single line two integers separated by a single space. The first integer is the ID of the winner candidate (a number from 1 to C), the second integer is either 1 or 2 indicating whether this candidate will win in the first round or the second one respectively.
*/

#include <iostream>

int main(int argc, char const *argv[]) {
	using namespace std;

	short ps[100][100];
	short rs[100];
	int c, f, s, v;
	int C, T, V;

	cin >> T;

	for (int t = 0; t < T; t++) {
		cin >> C >> V;
		f = s = 0;

		for (v = 0; v < V; v++)
			for (c = 0; c < C; c++) {
				cin >> ps[v][c];
				--ps[v][c];
			}	
		
		for (c = 0; c < C; c++)
			rs[c] = 0;
		
		for (v = 0; v < V; v++)
			rs[ ps[v][0] ]++;

		for (c = 0; c < C; c++) {
			// cerr << rs[c] << ' ';

			if (rs[c] >= rs[f]) {	 
				s = f;
				f = c;
			}
		}
		// cerr << endl;

		// cerr << "C = " << C << "\tV = " << V << endl;
		if (rs[f] > (V / 2))
			cout << f << " 1" << endl;

		else {
			rs[f] = rs[s] = 0;

			for (v = 0; v < V; v++) {
				for (c = 0; (ps[v][c] != f) && (ps[v][c] != s); c++);
				rs[ ps[v][c] ]++;
			}
			
			if (rs[f] > rs[s])
				cout << f + 1 << " 2" << endl;
			else
				cout << s + 1 << " 2" << endl;

			// cerr << "f(" << f << "): " << rs[f] << "\ts(" << s << "): " << rs[s] << endl;
		}
		// cerr << "First: " << f + 1 << endl;
		// cerr << "Second: " << s + 1 << endl;
	}

	return 0;
}
