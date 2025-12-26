// Grid Environment implementation
#include "grid_env.h"

GridEnv::GridEnv(int w, int h) : width(w), height(h) {
    reset();
}

int GridEnv::reset() {
    x = 0;
    y = 0;
    return state();
}

int GridEnv::state() const {
    return y * width + x;
}

StepResult GridEnv::step(int action) {
    if (action == 0 && y > 0) y--;
    if (action == 1 && y < height - 1) y++;
    if (action == 2 && x > 0) x--;
    if (action == 3 && x < width - 1) x++;

    StepResult r;
    r.next_state = state();
    r.reward = (x == width - 1 && y == height - 1) ? 1.0f : -0.01f;
    r.done = (x == width - 1 && y == height - 1);
    return r;
}
