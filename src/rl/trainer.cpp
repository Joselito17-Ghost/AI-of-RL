#include "trainer.h"
#include "../env/grid_env.h"
#include "qlearning.h"
#include <fstream>
#include <iostream>

Trainer::Trainer(GridEnv& e, QLearning& a)
    : env(e), agent(a) {}

void Trainer::train(int episodes) {
    for (int ep = 0; ep < episodes; ep++) {
        int s = env.reset();
        bool done = false;
        float totalReward = 0.0f;

        while (!done) {
            int a = agent.act(s);
            StepResult r = env.step(a);
            agent.update(s, a, r.reward, r.next_state);
            s = r.next_state;
            totalReward += r.reward;
            done = r.done;
        }

        rewards.push_back(totalReward);

        if (ep % 50 == 0)
            std::cout << "Episode " << ep
                      << " | Reward = " << totalReward << std::endl;
    }
}

void Trainer::saveRewardsCSV(const char* filename) {
    std::ofstream out(filename);
    out << "episode,reward\n";
    for (size_t i = 0; i < rewards.size(); i++)
        out << i << "," << rewards[i] << "\n";
}
