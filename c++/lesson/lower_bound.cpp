#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v{ 503, 87, 512, 61, 908, 170, 897, 275, 200, 426 };

    sort(v.begin(), v.end());

    auto begin = v.cbegin();
    auto end   = v.cend();

    int target = 200;

    auto pos = lower_bound(begin, end, target);

    if (pos == end) {
        cout << "Not Found: " <<  endl;
    } else if (*pos != target) {
        cout << "Not Found: " << *pos <<  endl;
    } else {
        cout << *pos << endl;
    }

    target = 404;

    pos = lower_bound(begin, end, target);

    if (pos == end) {
        cout << "Not Found: " <<  endl;
    } else if (*pos != target) {
        cout << "Not Found: " << *pos <<  endl;
    } else {
        cout << *pos << endl;
    }
}
