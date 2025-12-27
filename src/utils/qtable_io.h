#pragma once
#include <vector>
#include <fstream>

inline void save_qtable(const std::vector<float>& Q, const char* path) {
    std::ofstream out(path, std::ios::binary);
    size_t size = Q.size();
    out.write((char*)&size, sizeof(size));
    out.write((char*)Q.data(), size * sizeof(float));
}

inline bool load_qtable(std::vector<float>& Q, const char* path) {
    std::ifstream in(path, std::ios::binary);
    if (!in.good()) return false;

    size_t size;
    in.read((char*)&size, sizeof(size));
    Q.resize(size);
    in.read((char*)Q.data(), size * sizeof(float));
    return true;
}
