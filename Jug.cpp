#include "Jug.h"
#include <queue>

unsigned Jug::state_number(unsigned a, unsigned b, unsigned Ca, unsigned Cb) {
    if (a > Ca or b > Cb) {
    throw std::runtime_error("domain error");
  }
  return a*(Cb+1)+b;
}


Jug::Jug(int cA, int cB, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : Ca(cA), Cb(cB), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {
    if (Ca <= 0 || Cb <= 0 || (N > cB) || N < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
        cout << "Invalid input values." << endl;
        return;
    }
    buildGraph();
}

Jug::~Jug() {}



void Jug::buildGraph() {
    states.resize((Ca + 1) * (Cb + 1));
    for (int a = 0; a <= Ca; ++a) {
        for (int b = 0; b <= Cb; ++b) {
            unsigned index = state_number(a, b, Ca, Cb);
            states[index] = State(a, b, Ca, Cb);

            states[index].fillA = state_number(Ca, b, Ca, Cb);
            states[index].fillB = state_number(a, Cb, Ca, Cb);
            states[index].emptyA = state_number(0, b, Ca, Cb);
            states[index].emptyB = state_number(a, 0, Ca, Cb);

            int pourAB = std::min(a, Cb - b);
            states[index].AtoB = state_number(a - pourAB, b + pourAB, Ca, Cb);

            int pourBA = std::min(b, Ca - a);
            states[index].BtoA = state_number(a + pourBA, b - pourBA, Ca, Cb);
        }
    }
}


int Jug::solve(string &solution) {
    if (Ca <= 0 || Cb <= 0 || N <= 0 || N > Cb || Ca > Cb || Cb > 1000 ||
        cfA <= 0 || cfB <= 0 || ceA <= 0 || ceB <= 0 || cpAB <= 0 || cpBA <= 0) {
        solution.clear();
        return -1;
    }

    // priority queue for dijs algo
    using StatePair = std::pair<unsigned, unsigned>;  // {cost, state_index}
    std::priority_queue<StatePair, std::vector<StatePair>, std::greater<StatePair>> pq;
    
    // cost table 
    std::vector<unsigned> cost(states.size(), inf);
    // previous state
    std::vector<unsigned> previous(states.size(), -1);
    // steps taken to reach each state
    std::vector<std::string> steps(states.size(), "");

    // start from the initial state (0,0)
    unsigned start = state_number(0, 0, Ca, Cb);
    cost[start] = 0;
    pq.push({0, start});

    // implement dijs algo
    while (!pq.empty()) {
        unsigned current = pq.top().second;   // the state with the lowest cost
        unsigned currentCost = pq.top().first;
        pq.pop();

        // state where jug b has N liters
        if (states[current].b == static_cast<unsigned>(N)) {
            solution.clear();
            unsigned totalCost = cost[current];
            std::vector<string> path;

            // path from end state to start state
            while (current != start) {
                path.push_back(steps[current]);
                current = previous[current];
            }
            std::reverse(path.begin(), path.end());  // reverse to get correct order

            // solution string
            for (const string &step : path) {
                solution += step + "\n";
            }
            solution += "success " + std::to_string(totalCost);
            return 1;
        }

        // possible transitions
        std::vector<std::pair<unsigned, string>> neighbors = {
            {states[current].fillA, "fill A"},
            {states[current].fillB, "fill B"},
            {states[current].emptyA, "empty A"},
            {states[current].emptyB, "empty B"},
            {states[current].AtoB, "pour A B"},
            {states[current].BtoA, "pour B A"}
        };

        // costs for each action
        std::vector<unsigned> costs = {
            static_cast<unsigned>(cfA),
            static_cast<unsigned>(cfB),
            static_cast<unsigned>(ceA),
            static_cast<unsigned>(ceB),
            static_cast<unsigned>(cpAB),
            static_cast<unsigned>(cpBA)
        };

        // look at neighbors and update costs if a shorter path is found
        for (size_t i = 0; i < neighbors.size(); ++i) {
            unsigned next = neighbors[i].first;
            unsigned newCost = currentCost + costs[i];

            // if we found a cheaper path to `next`, update the path and push to queue
            if (newCost < cost[next]) {
                cost[next] = newCost;
                previous[next] = current;
                steps[next] = neighbors[i].second;
                pq.push({newCost, next});
            }
        }
    }

    // no solution found, return 0
    solution.clear();
    return 0;
}