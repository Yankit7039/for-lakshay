const fs = require('fs');

function parseInput() {
  const data = fs.readFileSync(0, 'utf8').trimEnd();
  if (!data) {
    return null;
  }
  const lines = data.split(/\r?\n/).map((line) => line.trim());
  if (lines.length === 0) {
    return null;
  }

  const headerParts = lines[0].split(/\s+/);
  if (headerParts.length < 2) {
    throw new Error('Invalid input: expected grid size and target word on first line');
  }

  const n = Number(headerParts[0]);
  const word = headerParts[1];

  if (!Number.isInteger(n) || n <= 0) {
    throw new Error('Invalid grid size');
  }
  if (!word) {
    throw new Error('Target word is empty');
  }

  if (lines.length - 1 < n) {
    throw new Error('Insufficient grid rows provided');
  }

  const grid = [];
  for (let i = 0; i < n; i += 1) {
    const row = lines[i + 1];
    if (row.length !== n) {
      throw new Error(`Grid row ${i + 1} must contain exactly ${n} characters`);
    }
    grid.push(row);
  }

  return { n, word, grid };
}

function findWord({ n, word, grid }) {
  const wordLower = word.toLowerCase();
  const gridLower = grid.map((row) => row.toLowerCase());
  const visited = Array.from({ length: n }, () => Array(n).fill(false));
  const dirs = [
    [1, 0],
    [-1, 0],
    [0, 1],
    [0, -1],
  ];

  function dfs(r, c, idx, path) {
    if (gridLower[r][c] !== wordLower[idx]) {
      return null;
    }

    path.push([r, c]);
    visited[r][c] = true;

    if (idx === wordLower.length - 1) {
      return path.slice();
    }

    for (const [dr, dc] of dirs) {
      const nr = r + dr;
      const nc = c + dc;
      if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
        continue;
      }
      if (visited[nr][nc]) {
        continue;
      }
      if (gridLower[nr][nc] !== wordLower[idx + 1]) {
        continue;
      }
      const result = dfs(nr, nc, idx + 1, path);
      if (result) {
        return result;
      }
    }

    visited[r][c] = false;
    path.pop();
    return null;
  }

  for (let r = 0; r < n; r += 1) {
    for (let c = 0; c < n; c += 1) {
      if (gridLower[r][c] !== wordLower[0]) {
        continue;
      }
      const path = [];
      const result = dfs(r, c, 0, path);
      if (result) {
        return result.map(([row, col]) => `${row + 1}${col + 1}`).join('');
      }
    }
  }

  return null;
}

function main() {
  const parsed = parseInput();
  if (!parsed) {
    return;
  }
  const path = findWord(parsed);
  if (path) {
    console.log(`yes ${path}`);
  } else {
    console.log('no');
  }
}

main();
