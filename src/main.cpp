#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stack>
#include<algorithm>
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
struct SearchResult {
    vector<pair<int,int>> visitedOrder;
    vector<pair<int,int>> path;
};
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

SearchResult bfs(Grid& grid) {
    pair<int,int> start = findCell(grid, 2);
    pair<int,int> end = findCell(grid, 3);

    vector<pair<int,int>> visitedOrder;
    vector<vector<bool>> visited(grid.getRows(), vector<bool>(grid.getCols(), false));
    vector<vector<pair<int,int>>> parent(grid.getRows(), vector<pair<int,int>>(grid.getCols(), {-1,-1}));
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
                parent[nr][nc] = current;
                q.push({nr, nc});
            }
        }
    }

    // reconstruct path by walking backwards from end
    vector<pair<int,int>> path;
    pair<int,int> step = end;
    while (step != make_pair(-1,-1)) {
        path.push_back(step);
        step = parent[step.first][step.second];
    }
    reverse(path.begin(), path.end());

    SearchResult result;
    result.visitedOrder = visitedOrder;
    result.path = path;
    return result;
}

SearchResult dfs(Grid& grid) {
    pair<int,int> start = findCell(grid, 2);
    pair<int,int> end = findCell(grid, 3);

    vector<pair<int,int>> visitedOrder;
    vector<vector<bool>> visited(grid.getRows(), vector<bool>(grid.getCols(), false));
    vector<vector<pair<int,int>>> parent(grid.getRows(), vector<pair<int,int>>(grid.getCols(), {-1,-1}));
    stack<pair<int,int>> s;

    s.push(start);
    visited[start.first][start.second] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!s.empty()) {
        pair<int,int> current = s.top();
        s.pop();
        visitedOrder.push_back(current);

        if (current == end) break;

        for (int i = 0; i < 4; i++) {
            int nr = current.first + dr[i];
            int nc = current.second + dc[i];

            if (nr >= 0 && nr < grid.getRows() && nc >= 0 && nc < grid.getCols()
                && !visited[nr][nc] && !grid.isWall(nr, nc)) {
                visited[nr][nc] = true;
                parent[nr][nc] = current;
                s.push({nr, nc});
            }
        }
    }

    vector<pair<int,int>> path;
    pair<int,int> step = end;
    while (step != make_pair(-1,-1)) {
        path.push_back(step);
        step = parent[step.first][step.second];
    }
    reverse(path.begin(), path.end());

    SearchResult result;
    result.visitedOrder = visitedOrder;
    result.path = path;
    return result;
}

int main() {
    Grid grid(5, 5);
    grid.setCell(0, 0, 2); // start
    grid.setCell(4, 4, 3); // end
    grid.setCell(2, 2, 1); // wall

    grid.print();

    SearchResult result = bfs(grid);

    cout << endl << "BFS visited order:" << endl;
    for (auto& p : result.visitedOrder) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    cout << "Shortest path:" << endl;
    for (auto& p : result.path) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
    SearchResult dfsResult = dfs(grid);

cout << endl << "DFS visited order:" << endl;
for (auto& p : dfsResult.visitedOrder) {
    cout << "(" << p.first << "," << p.second << ") ";
}
cout << endl;

cout << "DFS path:" << endl;
for (auto& p : dfsResult.path) {
    cout << "(" << p.first << "," << p.second << ") ";
}
cout << endl;
    return 0;
}