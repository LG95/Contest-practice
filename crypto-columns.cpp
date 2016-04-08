/*
	Crypto Columns
	--------------
	Status: judge error
	Original: http://acm.bnu.edu.cn/v3/problem_show.php?pid=1736

	The columnar encryption scheme scrambles the letters in a message (or plain text) using a keyword as illustrated in the following example: Suppose BATBOY is the keyword and our message is MEET ME BY THE OLD OAK TREE. Since the keyword has 6 letters, we write the message (ignoring spacing and punctuation) in a grid with 6 columns, padding with random extra letters as needed:
		MEETME
		BYTHEO
		LDOAKT
		REENTH

	Here, we've padded the message with NTH. Now the message is printed out by columns, but the columns are printed in the order determined by the letters in the keyword. Since A is the letter of the keyword that comes first in the alphabet, column 2 is printed first. The next letter, B, occurs twice. In the case of a tie like this we print the columns leftmost first, so we print column 1, then column 4. This continues, printing the remaining columns in order 5, 3 and finally 6. So, the order the columns of the grid are printed would be 2, 1, 4, 5, 3, 6, in this case. This output is called the cipher text, which in this example would be EYDEMBLRTHANMEKTETOEEOTH. Your job will be to recover the plaintext when given the keyword and the cipher text.

	Input
	There will be multiple input sets. Each set will be 2 input lines. The first input line will hold the keyword, which will be no longer than 10 characters and will consist of all uppercase letters. The second line will be the cipher text, which will be no longer than 100 characters and will consist of all uppercase letters. The keyword THEEND indicates end of input, in which case there will be no cipher text to follow.

	Output
	For each input set, output one line that contains the plain text (with any characters that were added for padding). This line should contain no spacing and should be all uppercase letters.
*/

#include <iostream>
#include <list>
#include <string>

#define LAST "THEEND"

struct Pair {
	char letter;
	int index;
	Pair(char c, int i) : letter(c), index(i) {}
	bool operator<(const Pair& other) { return this->letter < other.letter; }
};

int main(int argc, char const *argv[]) {
	using namespace std;

	char matrix[10][100];
	string key, ciphered;
	string::iterator p;
	list<Pair> l;
	int k, n;

	do {
		cin >> key;

		if (key != LAST) {
			cin >> ciphered;

			n = key.length();
			for (int i = 0; i < n; i++)
				l.push_back( Pair(key[i], i) );

			l.sort();
			p = ciphered.begin();
			k = ciphered.length() / n;
			// cerr << "n = " << n << "\tk = " << k << endl;
			for (list<Pair>::iterator i = l.begin(); i != l.end(); ++i) {
				// cerr << i->index + 1 << ' ';
				for (int j = 0; j < k; j++) {
					matrix[j][i->index] = *p++;
					// cerr << matrix[j][i->index];
				}
				// cerr << endl;
			}
			// cerr << endl;

			for (int i = 0; i < k; i++) {
				for (int j = 0; j < n; j++)
					cout << matrix[i][j];
				// cerr << endl;
			}
			cout << endl;

			l.clear();
		}
	} while (key != LAST);

	return 0;
}
