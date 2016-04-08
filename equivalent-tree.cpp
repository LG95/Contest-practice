/*
	Equivalent Boolean Expressions
	------------------------------
	This implementation uses tree based evaluation of expressions, which are trees designed according to the object oriented composite pattern.
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

#define SIZE 26

using namespace std;

class Tree {
public:
	virtual ~Tree() {}
	virtual bool evaluate() = 0;
};

bool check_equivalence(Tree *exp1, Tree *exp2);
Tree * create_tree(string& s);
void reset_vars();

int main(int argc, char const *argv[]) {
	Tree *t1, *t2;
	string in;
	int n;

	cin >> n;

	for (int i = 0; i < n; i++) {
		reset_vars();
		
		cin >> in;
		t1 = create_tree(in);

		cin >> in;
		t2 = create_tree(in);

		cout << "Case " << i + 1 << ':' << (check_equivalence(t1, t2) ? " " : " Not ") << "Equivalent" << endl;
		
		delete t1;
		delete t2;
	}

	return 0;
}

class AndNode : public Tree {
	Tree *l;
	Tree *r;

public:
	AndNode(Tree *left, Tree *right) {
		l = left;
		r = right;
	}

	virtual ~AndNode() {
		delete l;
		delete r;
	}

	virtual bool evaluate() {
		return l->evaluate() && r->evaluate();
	}
};

class OrNode : public Tree {
	Tree *l;
	Tree *r;

public:
	OrNode(Tree *left, Tree *right) {
		l = left;
		r = right;
	}

	virtual ~OrNode() {
		delete l;
		delete r;
	}

	virtual bool evaluate() {
		return l->evaluate() || r->evaluate();
	}
};

class NotNode : public Tree {
	Tree *t;

public:
	NotNode(Tree *subtree) {
		t = subtree;
	}

	virtual ~NotNode() {
		delete t;
	}

	virtual bool evaluate() {
		return !t->evaluate();
	}
};

class VariableLeaf : public Tree {
	bool *v;

public:
	VariableLeaf(bool *variable) {
		v = variable;
	}

	virtual bool evaluate() {
		return *v;
	}
};

int v;
bool vars[SIZE];

bool evaluate_all(Tree *exp1, Tree *exp2, int i) {
	if (i == v) {
		return exp1->evaluate() == exp2->evaluate();
	}

	else {
		vars[i] = false;
		if ( !evaluate_all(exp1, exp2, i + 1) )
			return false;

		vars[i] = true;
		return evaluate_all(exp1, exp2, i + 1);
	}
}

bool check_equivalence(Tree *exp1, Tree *exp2) {
	return evaluate_all(exp1, exp2, 0);
}

short var_indxs[SIZE];

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

Tree * create_tree(string& s) {
	const int N = s.length();
	vector<Tree *> stack1;
	vector<char> stack2;
	Tree *t1, *t2;
	char c, temp;
	int aux;

	for (int read = 0; read < N; read++) {
		c = s[read];

		if ( (c >= 'a') && (c <= 'z') ) {
			aux = c - 'a';

			if(var_indxs[aux] < 0)
				var_indxs[aux] = v++;

			stack1.push_back(new VariableLeaf(vars + var_indxs[aux]));
		}

		else if (c != ')') {
			if ( !stack2.empty() ) {
				temp = stack2.back();

			 	if (precedence(c) <= precedence(temp)) {
			 		stack2.pop_back();

					if (temp != '(')
						switch (temp) {
							case '!':
								t1 = stack1.back();
								stack1.pop_back();
								stack1.push_back(new NotNode(t1));
								break;
							case '&':
								t1 = stack1.back();
								stack1.pop_back();
								t2 = stack1.back();
								stack1.pop_back();
								stack1.push_back(new AndNode(t1, t2));
								break;
							case '|':
								t1 = stack1.back();
								stack1.pop_back();
								t2 = stack1.back();
								stack1.pop_back();
								stack1.push_back(new OrNode(t1, t2));
								break;
						}
			 	}
			}
				
			stack2.push_back(c);
		}
	}

	while ( !stack2.empty() ) {
		temp = stack2.back();
		stack2.pop_back();

		if (temp != '(')
			switch (temp) {
				case '!':
					t1 = stack1.back();
					stack1.pop_back();
					stack1.push_back(new NotNode(t1));
					break;
				case '&':
					t1 = stack1.back();
					stack1.pop_back();
					t2 = stack1.back();
					stack1.pop_back();
					stack1.push_back(new AndNode(t1, t2));
					break;
				case '|':
					t1 = stack1.back();
					stack1.pop_back();
					t2 = stack1.back();
					stack1.pop_back();
					stack1.push_back(new OrNode(t1, t2));
					break;
			}
	}

	return stack1.back();
}

void reset_vars() {
	for (int i = 0; i < SIZE; i++)
		var_indxs[i] = -1;
	v = 0;
}
