#include <stdio.h>

#define MAXN 5005
#define MAXK 55
#define INF 9223372036854775807LL

int a[MAXN];
long long prefix[MAXN];
long long cost[MAXN][MAXN];
long long dp_prev[MAXN];
long long dp_cur[MAXN];

static long long range_sum(int l, int r) {
    if (l > r) {
        return 0;
    }
    return prefix[r + 1] - prefix[l];
}

static long long calc_cost(int l, int r) {
    int m = (l + r) / 2;
    long long rep = a[m];
    long long left = (long long)(m - l) * rep - range_sum(l, m - 1);
    long long right = range_sum(m + 1, r) - (long long)(r - m) * rep;
    return left + right;
}

static void compute_layer(int seg, int l, int r, int optL, int optR) {
    if (l > r) {
        return;
    }

    int mid = (l + r) >> 1;
    long long bestVal = INF;
    int bestP = optL;

    int start = optL;
    if (start < seg - 1) {
        start = seg - 1;
    }
    int end = optR;
    if (end > mid - 1) {
        end = mid - 1;
    }

    for (int p = start; p <= end; p++) {
        if (dp_prev[p] == INF) {
            continue;
        }
        long long val = dp_prev[p] + cost[p][mid - 1];
        if (val < bestVal) {
            bestVal = val;
            bestP = p;
        }
    }

    dp_cur[mid] = bestVal;
    compute_layer(seg, l, mid - 1, optL, bestP);
    compute_layer(seg, mid + 1, r, bestP, optR);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + a[i];
    }

    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            cost[l][r] = calc_cost(l, r);
        }
    }

    for (int j = 0; j <= n; j++) {
        dp_prev[j] = (j == 0) ? 0 : INF;
    }

    long long ans = INF;
    for (int seg = 1; seg <= k; seg++) {
        for (int j = 0; j <= n; j++) {
            dp_cur[j] = INF;
        }
        compute_layer(seg, 1, n, seg - 1, n - 1);
        if (dp_cur[n] < ans) {
            ans = dp_cur[n];
        }
        for (int j = 0; j <= n; j++) {
            dp_prev[j] = dp_cur[j];
        }
    }

    printf("%lld\n", ans);
    return 0;
}
