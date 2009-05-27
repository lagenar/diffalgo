#include <vector>
#include <iostream>

using namespace std;

typedef pair<int,int> par_int ;
typedef vector<par_int> vector_pares;

void calcSubsecuencia(string orig, string dest, vector_pares & subsec)
{
    int k = 0;
	int j = 0;
	for (int i = 0; i < orig.length(); i++) {
		j=k;
		while(j < dest.length() && orig[i] != dest[j])
			j++;
		if (j < dest.length()) {
			subsec.push_back(par_int(i,j));
			k = j+1;
		}
	}
}

int main(int argc, char *argv[])
{
	vector_pares subsec;
	cout << string(argv[1]) << " " << string(argv[2]) << endl;
	calcSubsecuencia(string(argv[1]), string(argv[2]), subsec);
	for (int i = 0; i < subsec.size(); i++) {
		cout << subsec[i].first << " " << subsec[i].second << endl;
	}
	return 0;
}
