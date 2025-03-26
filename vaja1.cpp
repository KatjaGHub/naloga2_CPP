#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool Branje_Stevil(vector<int>& vec, const char s[]) {
    ifstream input(s);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        vec.push_back(st);
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void Izpis_Stevil(int* polje, unsigned int velikost) {
    ofstream output("out.txt");

    for (int i = 0; i < velikost; i++)
        output << polje[i] << ' ';
}

void CountingSort(vector<int>& A) {
    if (A.empty()) return;

    int max_val = *max_element(A.begin(), A.end());
    int min_val = *min_element(A.begin(), A.end());
    int range = max_val - min_val + 1;

    vector<int> C(range, 0);
    vector<int> B(A.size());

    for (int num : A) {
        C[num - min_val]++;
    }

    for (size_t i = 1; i < C.size(); i++) {
        C[i] += C[i - 1];
    }

    for (int i = A.size() - 1; i >= 0; i--) {
        B[C[A[i] - min_val] - 1] = A[i];
        C[A[i] - min_val]--;
    }

    A = B;
}

void RomanSort(vector<int>& A) {
    if (A.empty()) return;

    int max_val = *max_element(A.begin(), A.end());
    int min_val = *min_element(A.begin(), A.end());
    int range = max_val - min_val + 1;

    vector<int> C(range, 0);
    vector<int> B;

    for (int num : A) {
        C[num - min_val]++;
    }

    for (int i = 0; i < range; i++) {
        for (int j = 0; j < C[i]; j++) {
            B.push_back(i + min_val);
        }
    }

    A = B;
}

int main(int argc, const char* argv[]) {
    vector<int> A;

    if (argc < 3) return 0;
    if (!Branje_Stevil(A, argv[2])) return 0;

    if (argv[1][0] == '0') {
        CountingSort(A);
    }
    else {
        RomanSort(A);
    }
    Izpis_Stevil(&A[0], A.size());

    return 0;
}
