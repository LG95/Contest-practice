/*
	Google is Feeling Lucky 
	-----------------------
	Status: accepted
	Original: http://acm.bnu.edu.cn/v3/problem_show.php?pid=20433

	Google is one of the most famous Internet search engines which hosts and develops a number of Internet-based services and products. On its search engine website, an interesting button 'I'm feeling lucky' attracts our eyes. This feature could allow the user skip the search result page and goes directly to the first ranked page. Amazing! It saves a lot of time.

	The question is, when one types some keywords and presses 'I'm feeling lucky' button, which web page will appear? Google does a lot and comes up with excellent approaches to deal with it. In this simplified problem, let us just consider that Google assigns every web page an integer-valued relevance. The most related page will be chosen. If there is a tie, all the pages with the highest relevance are possible to be chosen.

	Your task is simple, given 10 web pages and their relevance. Just pick out all the possible candidates which will be served to the user when 'I'm feeling lucky'.

	Input 
	The input contains multiple test cases. The number of test cases T is in the first line of the input file.

	For each test case, there are 10 lines, describing the web page and the relevance. Each line contains a character string without any blank characters denoting the URL of this web page and an integer Vi denoting the relevance of this web page. The length of the URL is between 1 and 100 inclusively. (1 <= i <= 100)

	Output 
	For each test case, output several lines which are the URLs of the web pages which are possible to be chosen. The order of the URLs is the same as the input. Please look at the sample output for further information of output format.
*/

#include <iostream>
#include <list>
#include <string>

#define K 10

using namespace std;

struct Pair {
	string url;
	int relevance;

	Pair(const string& s, int i) : url(s), relevance(i) {}
	bool operator<(const Pair& other) {
		return this->relevance > other.relevance;
	}
};

int main(int argc, char const *argv[]) {
	list<Pair> l;
	string name;
	int r, T;

	cin >> T;

	for (int t = 1; t <= T; t++) {
		for (int i = 0; i < K; i++) {
			cin >> name >> r;
			l.push_back( Pair(name, r) );
		}

		l.sort();

		cout << "Case #" << t << ':' << endl;
		for (list<Pair>::iterator i = l.begin(); (i != l.end()) && (i->relevance == l.front().relevance); i++)
			cout << i->url << endl;

		l.clear();
	}

	return 0;
}
