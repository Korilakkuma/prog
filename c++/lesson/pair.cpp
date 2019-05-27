#include <iostream>
#include <utility>

using namespace std;

int main() {
    auto rilakkuma = make_pair("Rilakkuma", 168);
    // pair<string, int> rilakkuma("Rilakkuma", 168);

    cout << rilakkuma.first << endl;
    cout << rilakkuma.second << endl;
}
