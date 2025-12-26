// Q-learning interface
#pragma once
#include <vector>

class QLearning {
public:
    QLearning(int states, int actions);
    int act(int state);
    void update(int s, int a, float r, int s2);

private:
    int n_states, n_actions;
    float alpha = 0.1f;
    float gamma = 0.99f;
    std::vector<float> Q;
};
