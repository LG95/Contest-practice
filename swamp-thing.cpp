/*
	Swamp Things
	------------
	Status: judge error
	Original: http://acm.bnu.edu.cn/v3/problem_show.php?pid=2856

	Hugh F. Oh, in his never-ending quest to prove the existence of extraterrestrials, has gotten hold of a number of nighttime photographs taken by a research group that is examining glowing swamp gas. Hugh wants to see if any of the photos show, not swamp gas, but Little Grey Men in glowing suits. The photographs consist of bright dots appearing against a black background. Unfortunately, at the time the photos were taken, trains were traveling through the area (there is a train trestle over the swamp), and occasional lights from the train windows also appear in the photographs. Hugh, being a fastidious researcher, wants to eliminate these spots from the images. He can't tell from the photos exactly where the tracks are, or from what direction the photos were taken, but he knows that the tracks in that area are perfectly straight, so he's decided on the following approach: he will find the line with the maximum number of spots lying on it and, if there are four or more spots on the line, he will eliminate those points from his calculations, assuming that those are windows on the train. If two or more lines have the maximum number of points, Hugh will just randomly select one such set and delete it from the photo (he's not all that fastidious – after all, he believes in Little Grey Men). If there are fewer than four points lying along a common line, Hugh will assume that there is no train in the photograph and won't delete any points. Please write a program for him to process a set of photographs.

	Input
	There will be a series of test cases. Each test case is one photograph described by a line containing a positive integer n (<= 1000), the number of distinct spots in the photograph, followed by n lines containing the integer coordinates of the spots, one (x, y) pair per line. All coordinates are between 0 and 10000. The last photo description is followed by a line containing a zero, marking the end of the input. This line should not be processed.

	Output
	For each test case, output the photo number followed by the number of points eliminated from the photograph. Imitate the sample output below
*/

#include <cmath>
#include <iostream>
#include <vector>

struct Pair {
	long x, y;
	Pair(long x, long y) : x(x), y(y) {}
};

int main(int argc, char const *argv[]) {
	using namespace std;

	int c, k, n, removed;
	vector<double> ms;
	vector<Pair> ps;
	vector<int> os;
	double m, x, y;

	c = 1;
	do {
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			ps.push_back( Pair(x, y) );
		}

		k = 0;
		removed = 0;
		for (int i = 0; i < (n - 1); i++)
			for (int j = i + 1; j < n; j++) {
				x = ps[j].x - ps[i].x;
				y = ps[j].y - ps[i].y;

				if (x != 0)
					m = y / x;
				else
					m = INFINITY;

				x = ms.size();
				for (k = 0; (k < x) && (ms[k] != m); k++);
					
				if (k < x) {
					if (i == os[k])
						removed++;
					else
						os[k] = i;
				}

				else {
					ms.push_back(m);
					os.push_back(i);
				}
			}

		if (n > 0)
			cout << "Photo " << c++ << ": " << removed << " points eliminated" << endl;

		ms.clear();
		os.clear();
		ps.clear();
	} while (n > 0);

	return 0;
}
