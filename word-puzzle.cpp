#include <bits/stdc++.h>

struct InputData {
    int n{};
    std::string word;
    std::vector<std::string> grid;
    bool valid{false};
};

InputData parseInput(std::istream &in) {
    InputData data;
    if (!(in >> data.n >> data.word)) {
        return data;
    }
    if (data.n <= 0) {
        return data;
    }
    data.grid.reserve(data.n);
    for (int i = 0; i < data.n; ++i) {
        std::string row;
        if (!(in >> row) || static_cast<int>(row.size()) != data.n) {
            return data;
        }
        data.grid.push_back(row);
    }
    data.valid = true;
    return data;
}

bool dfs(int r, int c, int idx,
         const std::vector<std::string> &grid,
         const std::string &word,
         std::vector<std::vector<bool>> &visited,
         std::vector<std::pair<int, int>> &path) {
    if (grid[r][c] != word[idx]) {
        return false;
    }

    visited[r][c] = true;
    path.emplace_back(r, c);

    if (idx == static_cast<int>(word.size()) - 1) {
        return true;
    }

    constexpr int dr[4] = {1, -1, 0, 0};
    constexpr int dc[4] = {0, 0, 1, -1};

    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= static_cast<int>(grid.size()) || nc < 0 || nc >= static_cast<int>(grid.size())) {
            continue;
        }
        if (visited[nr][nc]) {
            continue;
        }
        if (grid[nr][nc] != word[idx + 1]) {
            continue;
        }
        if (dfs(nr, nc, idx + 1, grid, word, visited, path)) {
            return true;
        }
    }

    visited[r][c] = false;
    path.pop_back();
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    InputData data = parseInput(std::cin);
    if (!data.valid) {
        return 0;
    }

    std::vector<std::string> gridLower = data.grid;
    for (auto &row : gridLower) {
        for (auto &ch : row) {
            ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }

    std::string wordLower = data.word;
    for (auto &ch : wordLower) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    std::vector<std::vector<bool>> visited(data.n, std::vector<bool>(data.n, false));
    std::vector<std::pair<int, int>> path;

    for (int r = 0; r < data.n; ++r) {
        for (int c = 0; c < data.n; ++c) {
            if (gridLower[r][c] != wordLower.front()) {
                continue;
            }
            for (auto &row : visited) {
                std::fill(row.begin(), row.end(), false);
            }
            path.clear();
            if (dfs(r, c, 0, gridLower, wordLower, visited, path)) {
                std::string coords;
                for (const auto &[row, col] : path) {
                    coords += std::to_string(row + 1);
                    coords += std::to_string(col + 1);
                }
                std::cout << "yes " << coords << '\n';
                return 0;
            }
        }
    }

    std::cout << "no\n";
    return 0;
}
