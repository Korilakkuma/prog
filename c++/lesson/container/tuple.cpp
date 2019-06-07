#include <iostream>
#include <utility>

using namespace std;

int main() {
    auto rilakkuma = make_tuple("Rilakkuma", 2003, 9, 0);
    // tuple<string, int, int, int> rilakkuma("Rilakkuma", 2003, 9, 0);

    cout << get<0>(rilakkuma) << endl;
    cout << get<1>(rilakkuma) << endl;
    cout << get<2>(rilakkuma) << endl;
    cout << get<3>(rilakkuma) << endl;
}
