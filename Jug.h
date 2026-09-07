#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <queue>
#include <vector>
#include <string>
#include <limits>

using std::cout;
using std::endl;
using std::string;

// Using STL priority queue for efficient cost-based state selection
// Credit: https://en.cppreference.com/w/cpp/container/priority_queue

class State {
public:
    unsigned a, b, Ca, Cb;
    unsigned fillA, fillB, emptyA, emptyB, AtoB, BtoA;

    State() : a(0), b(0), Ca(0), Cb(0), fillA(0), fillB(0), emptyA(0), emptyB(0), AtoB(0), BtoA(0) {}
    State(unsigned a, unsigned b, unsigned Ca, unsigned Cb) : a(a), b(b), Ca(Ca), Cb(Cb) {}
};

class Jug {
public:
    Jug(int cA, int cB, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
    ~Jug();

    int solve(std::string &solution);

private:
    void buildGraph();
    unsigned state_number(unsigned a, unsigned b, unsigned Ca, unsigned Cb);

    int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
    std::vector<State> states;
    const unsigned inf = std::numeric_limits<unsigned>::max();
};