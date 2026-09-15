let startCell = null;
let endCell = null;
let isMouseDown = false;

document.addEventListener("mousedown", () => isMouseDown = true);
document.addEventListener("mouseup", () => isMouseDown = false);

const ROWS = 15;
const COLS = 25;
const gridContainer = document.getElementById("grid");

for (let r = 0; r < ROWS; r++) {
    for (let c = 0; c < COLS; c++) {
        const cell = document.createElement("div");
        cell.classList.add("cell");
        cell.dataset.row = r;
        cell.dataset.col = c;

        cell.addEventListener("click", () => handleClick(cell));
        cell.addEventListener("mouseenter", () => {
            if (isMouseDown && startCell && endCell && cell !== startCell && cell !== endCell) {
                cell.classList.add("wall");
            }
        });

        gridContainer.appendChild(cell);
    }
}

function handleClick(cell) {
    if (!startCell) {
        startCell = cell;
        cell.classList.add("start");
    } else if (!endCell && cell !== startCell) {
        endCell = cell;
        cell.classList.add("end");
    } else if (cell !== startCell && cell !== endCell) {
        cell.classList.toggle("wall");
    }
}
document.getElementById("resetBtn").addEventListener("click", () => {
    document.querySelectorAll(".cell").forEach(cell => {
        cell.classList.remove("start", "end", "wall", "visited", "path");
    });
    startCell = null;
    endCell = null;
});
function buildGridData() {
    const grid = [];
    for (let r = 0; r < ROWS; r++) {
        const row = [];
        for (let c = 0; c < COLS; c++) {
            const cell = document.querySelector(`[data-row='${r}'][data-col='${c}']`);
            row.push(cell.classList.contains("wall") ? 1 : 0);
        }
        grid.push(row);
    }
    return grid;
}
function bfs(grid, start, end) {
    const visitedOrder = [];
    const visited = Array.from({length: ROWS}, () => Array(COLS).fill(false));
    const parent = Array.from({length: ROWS}, () => Array(COLS).fill(null));
    const queue = [start];
    visited[start[0]][start[1]] = true;

    const dr = [-1, 1, 0, 0];
    const dc = [0, 0, -1, 1];

    while (queue.length > 0) {
        const current = queue.shift();
        visitedOrder.push(current);

        if (current[0] === end[0] && current[1] === end[1]) break;

        for (let i = 0; i < 4; i++) {
            const nr = current[0] + dr[i];
            const nc = current[1] + dc[i];

            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS
                && !visited[nr][nc] && grid[nr][nc] !== 1) {
                visited[nr][nc] = true;
                parent[nr][nc] = current;
                queue.push([nr, nc]);
            }
        }
    }

    const path = [];
    let step = end;
    while (step) {
        path.push(step);
        step = parent[step[0]][step[1]];
    }
    path.reverse();

    return { visitedOrder, path };
}
document.getElementById("runBtn").addEventListener("click", () => {
    if (!startCell || !endCell) {
        alert("Please set a start and end point first.");
        return;
    }

    // clear any previous visited/path styling before re-running
    document.querySelectorAll(".cell").forEach(cell => {
        cell.classList.remove("visited", "path");
    });

    const grid = buildGridData();
    const start = [parseInt(startCell.dataset.row), parseInt(startCell.dataset.col)];
    const end = [parseInt(endCell.dataset.row), parseInt(endCell.dataset.col)];

    const result = bfs(grid, start, end);
    animate(result.visitedOrder, result.path);
});
function animate(visitedOrder, path) {
    visitedOrder.forEach((cell, i) => {
        setTimeout(() => {
            const el = document.querySelector(`[data-row='${cell[0]}'][data-col='${cell[1]}']`);
            if (el && !el.classList.contains("start") && !el.classList.contains("end")) {
                el.classList.add("visited");
            }
        }, 15 * i);
    });

    setTimeout(() => {
        path.forEach((cell, i) => {
            setTimeout(() => {
                const el = document.querySelector(`[data-row='${cell[0]}'][data-col='${cell[1]}']`);
                if (el && !el.classList.contains("start") && !el.classList.contains("end")) {
                    el.classList.add("path");
                }
            }, 30 * i);
        });
    }, 15 * visitedOrder.length);
}