/*//MAIN METHOD FOR TESTING
#include "Orders.h"
#include "../Part 2/Player.h"

int main(){
    Player *p1 = new Player("Cristina Yang");
    Player *p2 = new Player("Owen Hunt");
    //PLACEHOLDER FOR NEUTRAL PLAYER
    Player *neutral = new Player("NEUTRAL");
    Map *map = new Map(MapLoader::loadMap("../Debug/MapFiles/artic.map"));
    Deck *deck = new Deck();

    p1->addTerritory(map->getTerritories());
    p1->addTerritory(map->getTerritories()+1);
    p2->addTerritory(map->getTerritories()+2);
    p2->addTerritory(map->getTerritories()+3);

    cout<<*map->getTerritories()<<endl;
    cout<<*(map->getTerritories()+1)<<endl;
    cout<<*(map->getTerritories()+2)<<endl;
    cout<<*(map->getTerritories()+3)<<endl;
    Deck *deck1 =new Deck();

    p1->setArmies(10);

    //DEPLOY ORDER
    cout<<"\nOWEN(P2) DEPLOYS ON A TERRITORY HE DOESN'T OWN\n";
    Deploy* deploy = new Deploy(p2,map->getTerritories(),2);
    deploy->execute();
    cout<<"\nOWEN(P2) DEPLOYS ON A TERRITORY HE OWNS MORE ARMIES THAN HE HAS\n";
    Deploy* deploy1 = new Deploy(p2,map->getTerritories()+2,4);
    deploy1->execute();
    cout<<"\nCRISTINA(P1) DEPLOYS ON A TERRITORY SHE OWNS WITH ARMIES SHE HAS\n";
    Deploy* deploy2 = new Deploy(p1,map->getTerritories(),4);
    deploy2->execute();

    //ADVANCE ORDER
    cout<<"\nCRISTINA(P1) ADVANCES HER TROOPS TO A TERRITORY THAT IS NOT ADJACENT TO HERS\n";
    Advance *advance = new Advance(p1,map->getTerritories(),map->getTerritories()+3,3,deck);
    advance->execute();
    cout<<"\nCRISTINA(P1) ADVANCES HER TROOPS TO A TERRITORY THAT IS ADJACENT TO HERS THAT SHE OWNS\n";
    Advance *advance1 = new Advance(p1,map->getTerritories(),map->getTerritories()+1,3,deck);
    advance1->execute();
    cout<<"\nCRISTINA(P1) ADVANCES HER TROOPS TO A TERRITORY THAT IS ADJACENT TO HERS THAT SHE DOESN'T OWN\n";
    Advance *advance2 = new Advance(p1,map->getTerritories(),map->getTerritories()+2,5,deck);
    advance2->execute();
    cout<<*(map->getTerritories()+2);
    cout<<"\nOWEN(P2) ADVANCES HIS TROOPS TO A TERRITORY THAT IS ADJACENT TO HIS THAT HE OWNS\n";
    Deploy* deploy3 = new Deploy(p2,map->getTerritories()+3,2);
    deploy3->execute();
    (map->getTerritories()+1)->setNumberOfArmies(10);
    Advance *advance3 = new Advance(p2,map->getTerritories()+3,map->getTerritories()+1,2,deck);
    advance3->execute();
    cout<<"\nADVANCING AGAIN TO CHECK THAT A CARD IS ONLY WON ONCE IN A TURN \n";
    //A FLAG IN PLAYER, IT WILL BE TURNED OFF AFTER EACH TURN IN THE GAME LOOP
    p2->setArmies(5);
    Deploy* deploy4 = new Deploy(p1,map->getTerritories()+2,5);
    deploy4->execute();
    p1->removeTerritory(map->getTerritories());
    p2->addTerritory(map->getTerritories());
    Advance *advance4 = new Advance(p1,map->getTerritories()+2,map->getTerritories(),5,deck);

    //AIRLIFT ORDER
    cout<<"\nCRISTINA(P1) AIRLIFTS HER TROOPS TO A TERRITORY THAT SHE DOESN'T OWN\n";
    Airlift *airlift = new Airlift(p1,map->getTerritories()+2,map->getTerritories()+3,3);
    airlift->execute();
    cout<<"\nCRISTINA(P1) AIRLIFTS HER TROOPS TO A TERRITORY THAT SHE OWNS AND IS NOT ADJACENT TO HERS\n";
    Airlift *airlift1 = new Airlift(p1,map->getTerritories()+2,map->getTerritories()+1,3);
    airlift1->execute();

    //BOMB ORDER
    cout<<"\nCRISTINA(P1) BOMBS A TERRITORY THAT SHE OWNS\n";
    Bomb *bomb = new Bomb(p1,map->getTerritories()+2,map->getTerritories()+1);
    bomb->execute();
    cout<<"\nCRISTINA(P1) BOMBS A TERRITORY THAT SHE DOESN'T OWN BUT ISN'T ADJACENT TO HERS\n";
    Bomb *bomb1 = new Bomb(p1,map->getTerritories(),map->getTerritories()+3);
    bomb1->execute();
    cout<<"\nCRISTINA(P1) BOMBS A TERRITORY THAT SHE DOESN'T OWN AND IS ADJACENT TO HERS\n";
    Bomb *bomb2 = new Bomb(p1,map->getTerritories()+1,map->getTerritories()+3);
    (map->getTerritories()+3)->setNumberOfArmies(30);
    cout<<*(map->getTerritories()+3)<<"\tArmies: "<<(map->getTerritories()+3)->getNumberOfArmies()<<endl;
    bomb2->execute();
    cout<<*(map->getTerritories()+3)<<"\tArmies: "<<(map->getTerritories()+3)->getNumberOfArmies()<<endl;

    //BLOCKADE ORDER
    cout<<"\nOWEN(P2) BLOCKADES A TERRITORY THAT HE DOESN'T OWN\n";
    Blockade *blockade = new Blockade(p2, map->getTerritories()+1,neutral);
    blockade->execute();
    cout<<"\nOWEN(P2) BLOCKADES A TERRITORY THAT HE OWNS\n";
    Blockade *blockade1 = new Blockade(p2, map->getTerritories()+3,neutral);
    blockade1->execute();
    cout<<*(map->getTerritories()+3);

    //NEGOTIATE ORDER
    cout<<"\nOWEN(P2) NEGOTIATES WITH HIMSELF\n";
    Negotiate *negotiate = new Negotiate(p2,p2);
    negotiate->execute();
    cout<<"\nOWEN(P2) NEGOTIATES WITH CRISTINA(P1)\n";
    Negotiate *negotiate1 = new Negotiate(p2,p1);
    negotiate1->execute();
    cout<<"\nCRISTINA(P1) BOMBS OWEN\n";
    p2->addTerritory(map->getTerritories()+3);
    Bomb *bomb3 = new Bomb(p1,map->getTerritories()+1,map->getTerritories()+3);
    bomb3->execute();

}

*/
