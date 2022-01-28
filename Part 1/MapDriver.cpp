#include "Map.h"
int main() {
    Edge edges[] = {{1,2}, {0,1}, {2,4}, {3,2}, {4,2}, {5,1}, {6,1}, {7,6},{6,7}, {7,8}, {8,7}, {8,1}};
    int N = 9;
    Territory *territories = new Territory[N];
    for (int i = 0; i < N; i++) {
        territories[i].setId(i);
        territories[i].setName("TEST NAME ");
    }
    int e = sizeof(edges)/sizeof(edges[0]);
    Map map(edges, territories, N, e);
    map.printMap();
    return 0;
}
