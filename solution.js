'use strict';

const fs = require('fs');

const input = fs.readFileSync(0, 'utf8').trim().split(/\s+/);
let idx = 0;
const next = () => input[idx++];

const n = Number(next());
const T = Number(next());
const SCALE = 100;
const maxLoss = Math.round(T * SCALE);

const layers = [];
for (let i = 0; i < n; i++) {
  const k = Number(next());
  const options = [];
  for (let j = 0; j < k; j++) {
    next(); // bit-width label, e.g. 8bit / 16bit
    const loss = Math.round(Number(next()) * SCALE);
    const mem = Number(next());
    options.push({ loss, mem });
  }
  layers.push(options);
}

let dp = new Array(maxLoss + 1).fill(Infinity);
dp[0] = 0;

for (const options of layers) {
  const ndp = new Array(maxLoss + 1).fill(Infinity);
  for (let loss = 0; loss <= maxLoss; loss++) {
    if (dp[loss] === Infinity) continue;
    for (const opt of options) {
      const newLoss = loss + opt.loss;
      if (newLoss > maxLoss) continue;
      const newMem = dp[loss] + opt.mem;
      if (newMem < ndp[newLoss]) ndp[newLoss] = newMem;
    }
  }
  dp = ndp;
}

let ans = Infinity;
for (let loss = 0; loss <= maxLoss; loss++) {
  if (dp[loss] < ans) ans = dp[loss];
}

console.log(ans.toFixed(2));
