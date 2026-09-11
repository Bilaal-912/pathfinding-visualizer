#include <iostream>
#include <vector>

class Grid {
public:
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        cells = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    }

    void print() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                std::cout << cells[r][c] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    int rows, cols;
    std::vector<std::vector<int>> cells;
};

int main() {
    Grid grid(5, 5);
    grid.print();
    return 0;
}