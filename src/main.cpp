#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

class Grid {
public:
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        cells = vector<vector<int>>(rows, vector<int>(cols, 0));
    }

    void print() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                cout << cells[r][c] << " ";
            }
            cout << endl;
        }
    }
    int getCell(int r, int c) {
        return cells[r][c];
    }
    void setCell(int r, int c, int value) {
        cells[r][c] = value;
    }
    bool isWall(int r, int c) {
        return cells[r][c] == 1;
    }
    int getRows() { return rows; }
    int getCols() { return cols; }

private:
    int rows, cols;
    vector<vector<int>> cells;
};

// ---- everything below is OUTSIDE the Grid class ----

pair<int,int> findCell(Grid& grid, int target) {
    for (int r = 0; r < grid.getRows(); r++) {
        for (int c = 0; c < grid.getCols(); c++) {
            if (grid.getCell(r, c) == target) {
                return {r, c};
            }
        }
    }
    return {-1, -1};
}

vector<pair<int,int>> bfs(Grid& grid) {
    pair<int,int> start = findCell(grid, 2);
    pair<int,int> end = findCell(grid, 3);

    vector<pair<int,int>> visitedOrder;
    vector<vector<bool>> visited(grid.getRows(), vector<bool>(grid.getCols(), false));
    queue<pair<int,int>> q;

    q.push(start);
    visited[start.first][start.second] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pair<int,int> current = q.front();
        q.pop();
        visitedOrder.push_back(current);

        if (current == end) break;

        for (int i = 0; i < 4; i++) {
            int nr = current.first + dr[i];
            int nc = current.second + dc[i];

            if (nr >= 0 && nr < grid.getRows() && nc >= 0 && nc < grid.getCols()
                && !visited[nr][nc] && !grid.isWall(nr, nc)) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    return visitedOrder;
}

int main() {
    Grid grid(5, 5);
    grid.setCell(0, 0, 2); // start
    grid.setCell(4, 4, 3); // end
    grid.setCell(2, 2, 1); // wall

    grid.print();
    cout << endl << "BFS visited order:" << endl;

    vector<pair<int,int>> order = bfs(grid);
    for (auto& p : order) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    return 0;
}