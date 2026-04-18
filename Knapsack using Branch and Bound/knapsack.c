#include <stdio.h>
#include <stdlib.h>
struct Item {
    int id; // Original index tracker
    int weight;
    int value;
    float v_w_ratio;
};
struct Node {
    int level;
    int profit;
    int weight;
    float bound;
    int contains[20]; // 1 if item is included, 0 otherwise
};
int compare(const void* a, const void* b) {
    struct Item* itemA = (struct Item*)a;
    struct Item* itemB = (struct Item*)b;
    if (itemB->v_w_ratio > itemA->v_w_ratio) return 1;
    if (itemB->v_w_ratio < itemA->v_w_ratio) return -1;
    return 0;
}
float calculateBound(struct Node u, int n, int W, struct Item items[]) {
    if (u.weight >= W) return 0;
    float profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;
    while ((j < n) && (totweight + items[j].weight <= W)) {
        totweight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }
    if (j < n)
        profit_bound += (W - totweight) * items[j].v_w_ratio;
    return profit_bound;
}
int main() {
    int n, W, i;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);
    struct Item items[n];
    for ( i = 0; i < n; i++) {
        items[i].id = i + 1;
        printf("Enter value and weight for item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
        items[i].v_w_ratio = (float)items[i].value / items[i].weight;
    }
    qsort(items, n, sizeof(struct Item), compare);
    struct Node Q[100];
    int head = 0, tail = 0;
    int best_path[n];
    int maxProfit = 0;
    struct Node u, v;
    v.level = -1;
    v.profit = v.weight = 0;
    for( i=0; i<n; i++) v.contains[i] = 0;
    v.bound = calculateBound(v, n, W, items);
    Q[tail++] = v;
    while (head < tail) {
        v = Q[head++];
        if (v.level == n - 1) continue;
        u.level = v.level + 1;
        // Path 1: Include item
        u.weight = v.weight + items[u.level].weight;
        u.profit = v.profit + items[u.level].value;
        for( i=0; i<n; i++) u.contains[i] = v.contains[i];
        u.contains[u.level] = 1;
        if (u.weight <= W && u.profit > maxProfit) {
            maxProfit = u.profit;
            for( i=0; i<n; i++) best_path[i] = u.contains[i];
        }
        u.bound = calculateBound(u, n, W, items);
        if (u.bound > maxProfit) Q[tail++] = u;
        // Path 2: Exclude item
        u.weight = v.weight;
        u.profit = v.profit;
        u.contains[u.level] = 0;
        u.bound = calculateBound(u, n, W, items);
        if (u.bound > maxProfit) Q[tail++] = u;
    }
    printf("\nMaximum profit: %d", maxProfit);
    printf("\nItems included (ID - Value - Weight): \n");
    for ( i = 0; i < n; i++) {
        if (best_path[i] == 1) {
            printf("Item %d - Val: %d, Wt: %d\n", items[i].id, items[i].value, items[i].weight);
        }
    }
    return 0;
}
