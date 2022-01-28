#include "Map.h"
int main() {
    Edge edges[] = {{1,2}, {0,1}, {2,4}, {3,4}, {4,3}, {5,6}, {6,1}, {7,6},{6,7}, {7,8}, {8,7}, {8,1}};
    int N = 9;
    auto *territories = new Territory[N];
    for (int i = 0; i < N; i++) {
        territories[i].setId(i);
        territories[i].setName("TEST NAME ");
    }
    int e = sizeof(edges)/sizeof(edges[0]);
    Map map(edges, territories, N, e);
    map.printMap();

    Continent europe = *new Continent(1, "Europe", 4, "Green");
    int ids[] = {1, 2, 3};
    europe.addTerritories(ids, 3, map.head);
    cout << "PRINTING EUROPE'S TERRITORIES..." << endl;
    for (int i = 0; i < 3; i++) {
        cout << europe.getTerritory(i) << endl;
    }
    if (!map.isConnected()) {
        cout << "MAP IS NOT CONNECTED";
    }
    else {
        cout<< "MAP IS CONNECTED";
    }

    return 0;
}
