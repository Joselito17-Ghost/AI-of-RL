#pragma once

float train_qlearning(bool headless, int episodes);

// Sauvegarde / chargement Q-table
void save_agent_qtable(const char* path);
bool load_agent_qtable(const char* path);
