/*
	Equivalent Boolean Expressions
	------------------------------
	This implementation uses stack based evaluation of expressions, which are strings converted into postfix notation.
	Status: runtime error
	Original: http://acm.bnu.edu.cn/v3/problem_show.php?pid=13243

	In this problem you are given some Boolean expressions, you can evaluate them and find whether they return true or false. A Boolean expression consists of three basic operators, and (&), or (|) or not (!). '&' and '|' are binary operators, where '!' is a unary operator. '&' returns true if and only if both of its operands are true, '|' returns true if any of its operands is true. '!' negates the operand, that means it makes true to false and vice versa. The grammar is given below:
	
		Expression => Term | Expression '|' Term
		Term => Factor | Term '&' Factor
		Factor => Sub | '!' Factor
		Sub => Variable | '(' Expression ')'
		Variable => 'a' | 'b' | ... | 'j'
		Table 1: Grammar in EBNF

	And Boolean variables can be true or false. In this problem, you are given two Boolean expressions, your task is to find whether they are equivalent or not. Two Boolean expressions are said equivalent if they produce same results in all situations. That means if we change the value of the variables, the expressions produce same results.

	Input
	Input starts with an integer T (≤ 100), denoting the number of test cases.
	Each case contains two lines. In each line there will be a non-empty string representing a Boolean expression which follows the grammar described above. The strings will not contain any white spaces and the length will be less than 101.

	Output
	For each case, print the case number and 'Equivalent' if the expressions are equivalent; or 'Not Equivalent' if they are not. Be careful about spelling and case sEnSitiVity.
*/

#include <iostream>
#include <vector>

// #define DEBUG
#define SIZE 26

using namespace std;

bool check_equivalence(const string& exp1, const string& exp2);
void convert_expression(string& s);
void reset_vars();

int main(int argc, char const *argv[]) {
	string in1, in2;
	int n;

	cin >> n;

	for (int i = 0; i < n; i++) {
		reset_vars();
		
		cin >> in1;
		cin >> in2;

		#ifdef DEBUG
			cerr << in1 << ':';
			cerr << in2 << '\t';
		#endif

		convert_expression(in1);
		convert_expression(in2);

		#ifdef DEBUG
			cerr << in1 << ':';
			cerr << in2 << endl;
		#endif

		cout << "Case " << i + 1 << ':' << (check_equivalence(in1, in2) ? " " : " Not ") << "Equivalent" << endl;
	}

	return 0;
}

int precedence(char op) {
	switch (op) {
		case '(':
			return 4;
		case '!':
			return 3;
		case '&':
			return 2;
		case '|':
			return 1;
		default:
			return 0;
	}
}

int v;
short var_indxs[SIZE];

void convert_expression(string& s) {
	const int N = s.length();
	vector<char> stack;
	int write = 0;
	char c, temp;
	int aux;

	for (int read = 0; read < N; read++) {
		c = s[read];

		if ( (c >= 'a') && (c <= 'z') ) {
			s[write++] = c;
			aux = c - 'a';

			if (var_indxs[aux] < 0)
				var_indxs[aux] = v++; 
		}

		else if (c != ')') {
		 	if ( !stack.empty() ) {
				temp = stack.back();

		 		if (precedence(c) <= precedence(temp)) {
			 		stack.pop_back();

					if (temp != '(')
						s[write++] = temp;
				}
		 	}
				
			stack.push_back(c);
		}
	}

	while ( !stack.empty() ) {
		temp = stack.back();
		stack.pop_back();

		if (temp != '(')
			s[write++] = temp;
	}

	s.resize(write);
}

void reset_vars() {
	for (int i = 0; i < SIZE; i++)
		var_indxs[i] = -1;
	v = 0;
}

bool vars[SIZE];

bool evaluate(const string& exp) {
	const int N = exp.length();
	vector<bool> stack;
	bool temp1, temp2;
	char c;

	for (int read = 0; read < N; read++) {
		c = exp[read];

		if ( (c >= 'a') && (c <= 'z') )
			stack.push_back(vars[ var_indxs[c - 'a'] ]);

		else
			switch (c) {
				case '!':
					temp1 = stack.back();
					stack.pop_back();
					stack.push_back(!temp1);
					break;
				case '&':
					temp1 = stack.back();
					stack.pop_back();
					temp2 = stack.back();
					stack.pop_back();
					stack.push_back(temp1 && temp2);
					break;
				case '|':
					temp1 = stack.back();
					stack.pop_back();
					temp2 = stack.back();
					stack.pop_back();
					stack.push_back(temp1 || temp2);
					break;
			}

		#ifdef DEBUG
			cerr << read + 1 <<  " - Stack =";
			for(unsigned i = 0; i < stack.size(); i++)
				cerr << ' ' << stack[i];
			cerr << endl;
		#endif
	}

	return stack.back();
}

bool evaluate_all(const string& exp1, const string& exp2, int i) {
	if (i == v) {
		#ifdef DEBUG
			bool r1 = evaluate(exp1);
			bool r2 = evaluate(exp2);

			for (int j = 0; j < SIZE; j++)
				if (var_indxs[j] >= 0)
					cerr << char(j + 'a') << '=' << vars[ var_indxs[j] ] << '\t';
			cerr << "|\t" << r1 << '\t' << r2 << endl;

			return r1 == r2;
		#endif

		return evaluate(exp1) == evaluate(exp2);
	}

	else {
		vars[i] = false;
		if ( !evaluate_all(exp1, exp2, i + 1) )
			return false;

		vars[i] = true;
		return evaluate_all(exp1, exp2, i + 1);
	}
}

bool check_equivalence(const string& exp1, const string& exp2) {
	return evaluate_all(exp1, exp2, 0);
}
