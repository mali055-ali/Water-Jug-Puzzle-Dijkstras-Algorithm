#include "Jug.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::istreambuf_iterator;

int main() {
    string solution;

    // Test case 1
    Jug head1(3, 5, 4, 1, 2, 3, 4, 5, 6);
    if (head1.solve(solution) != 1) {
        cout << "Error 3" << endl;
    }
    cout << solution << endl << endl;

    // Test case 2
    Jug head2(3, 5, 4, 1, 1, 1, 1, 1, 2);
    if (head2.solve(solution) != 1) {
        cout << "Error 3" << endl;
    }
    cout << solution << endl;

    return 0;
}