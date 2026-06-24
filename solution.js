const readline = require('readline');

// 创建输入接口
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

let input = []; // 用于存储所有输入

// 每行输入都会触发 'line' 事件
rl.on('line', (line) => {
    input.push(line);
});

// 输入结束后触发 'close' 事件
rl.on('close', () => {
    const lines = input.map((s) => s.trim()).filter((s) => s.length > 0);
    const first = lines[0].split(/\s+/);
    const L = parseInt(first[0], 10);
    const T = parseFloat(first[1]);

    const SCALE = 100;
    const maxLoss = Math.round(T * SCALE);

    const layers = [];
    for (let i = 1; i <= L; i++) {
        const parts = lines[i].split(/\s+/);
        const k = parseInt(parts[0], 10);
        const options = [];
        let idx = 1;
        for (let j = 0; j < k; j++) {
            idx++; // 跳过 bit 描述字符串，如 8bit
            const loss = Math.round(parseFloat(parts[idx++]) * SCALE);
            const mem = parseFloat(parts[idx++]);
            options.push({ loss, mem });
        }
        layers.push(options);
    }

    let dp = new Array(maxLoss + 1).fill(Infinity);
    dp[0] = 0;

    for (const options of layers) {
        const next = new Array(maxLoss + 1).fill(Infinity);
        for (let used = 0; used <= maxLoss; used++) {
            if (dp[used] === Infinity) continue;
            for (const opt of options) {
                const newUsed = used + opt.loss;
                if (newUsed > maxLoss) continue;
                const totalMem = dp[used] + opt.mem;
                if (totalMem < next[newUsed]) {
                    next[newUsed] = totalMem;
                }
            }
        }
        dp = next;
    }

    let ans = Infinity;
    for (let i = 0; i <= maxLoss; i++) {
        if (dp[i] < ans) ans = dp[i];
    }

    console.log(ans.toFixed(2));
});
