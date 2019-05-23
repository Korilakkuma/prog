#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v1;

    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    vector<int> v2(4);

    v2[0] = 2;
    v2[1] = 3;
    v2[2] = 5;
    v2[3] = 7;

    vector<int> v3{ 2, 3, 5, 7 };

    cout << (v1 == v2) << endl;
    cout << (v1 == v3) << endl;
}
