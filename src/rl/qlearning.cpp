// Q-learning core training loop
#include "qlearning.h"
#include <cstdlib>
#include <algorithm>

QLearning::QLearning(int s, int a)
    : n_states(s), n_actions(a), Q(s * a, 0.0f) {}

int QLearning::act(int state) {
    if ((rand() % 100) < 10)
        return rand() % n_actions;

    int best = 0;
    for (int a = 1; a < n_actions; a++) {
        if (Q[state * n_actions + a] > Q[state * n_actions + best])
            best = a;
    }
    return best;
}

void QLearning::update(int s, int a, float r, int s2) {
    float maxQ = Q[s2 * n_actions];
    for (int i = 1; i < n_actions; i++)
        maxQ = std::max(maxQ, Q[s2 * n_actions + i]);

    Q[s * n_actions + a] += alpha * (r + gamma * maxQ - Q[s * n_actions + a]);
}
