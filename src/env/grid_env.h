// Grid Environment header
#pragma once

struct StepResult {
    int next_state;
    float reward;
    bool done;
};

class GridEnv {
public:
    GridEnv(int w = 5, int h = 5);
    int reset();
    StepResult step(int action);
    int state() const;

private:
    int width, height;
    int x, y;
};
