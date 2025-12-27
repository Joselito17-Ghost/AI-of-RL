#include "trainer.h"
#include "qlearning.h"
#include "env/grid_env.h"
#include "utils/qtable_io.h"

// Agent global (géré par le trainer)
static QLearning agent(25, 4);

float train_qlearning(bool, int episodes) {
    GridEnv env(5, 5);
    float total_reward = 0.0f;

    for (int ep = 0; ep < episodes; ep++) {
        int s = env.reset();
        bool done = false;
        float episode_reward = 0.0f;

        while (!done) {
            int a = agent.act(s);
            StepResult r = env.step(a);
            agent.update(s, a, r.reward, r.next_state);
            s = r.next_state;
            episode_reward += r.reward;
            done = r.done;
        }

        total_reward += episode_reward;
    }

    return total_reward / episodes;
}

// -------- Q-TABLE IO --------

void save_agent_qtable(const char* path) {
    save_qtable(agent.table(), path);
}

bool load_agent_qtable(const char* path) {
    return load_qtable(agent.table_mut(), path);
}
