// #include <fstream>
// #include "Map.h"

// int main() {
//     cout << "LOADING ARTIC MAP... " << endl;
//     Map *map = new Map(MapLoader::loadMap("../Debug/MapFiles/artic.map"));
//     map->validate();
// 	Territory *territory = new Territory();
// 	std::cout << territory->getOwner();
//     delete map;

//     cout << "LOADING INVALID MAP..." << endl;
//     map = new Map(MapLoader::loadMap("../Debug/MapFiles/DisconnectedMap.txt"));
//     map->validate();
//     delete map;

//     cout << "LOADING DISCONNECTED CONTINENT MAP..." << endl;
//     map = new Map(MapLoader::loadMap("../Debug/MapFiles/DisconnectedContinent.txt"));
//     map->validate();
//     delete map;

//     cout << "LOADING CANADA MAP..." << endl;
//     map = new Map(MapLoader::loadMap("../Debug/MapFiles/canada.map"));
//     map->validate();
//     delete map;

//     cout << "LOADING BALTIC MAP..." << endl;
//     map = new Map(MapLoader::loadMap("../Debug/MapFiles/sw_baltic.map"));
//     map->validate();
//     cout << "PRINTING BALTIC MAP (BY TERRITORY ID's)" << endl;
//     cout << *map << endl;
//     cout << "DELETING MAP..." << endl;
//     delete map;
//     return 0;
// }
// // 