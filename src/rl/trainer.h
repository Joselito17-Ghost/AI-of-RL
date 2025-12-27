#pragma once
#include <vector>

class GridEnv;
class QLearning;

class Trainer {
public:
    Trainer(GridEnv& env, QLearning& agent);
    void train(int episodes);
    void saveRewardsCSV(const char* filename);

private:
    GridEnv& env;
    QLearning& agent;
    std::vector<float> rewards;
};
