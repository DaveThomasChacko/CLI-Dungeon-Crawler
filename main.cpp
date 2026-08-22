#include <iostream>
#include <random>
using namespace std; 
//Function Prototypes


class Player{
    public:
        int health =100;
        int attack = 10;
        int score = 0;

};
class Enemy{
    public:
    string name;
    int health;
    int attack;
    int score_worth;
    Enemy(string name, int health, int attack, int score_worth)
        : name(name), health(health), attack(attack), score_worth(score_worth){}
        
};
void GenerateRoom(Player& player_ob);
void EnemySpawn(int id, Player& ply_ob);
void Battle(Player& player_object, Enemy& enem_ob);

int main(){
    Player player;
    int choice;
    bool notQuit = true;
    cout << "===============================\n"
         << "--------DUNGEON CRAWLER--------\n"
         << "===============================\n";
    while (notQuit){
        cout << "Choose your option\n"
         << "1. Explore\n"
         << "2. Stats\n"
         << "3. Open Potion Bag\n"
         << "4. Quit" << endl;
        cin >> choice;
        switch(choice){
            case 1:
                cout << "You entered a new room \n";
                GenerateRoom(player);
                break;
            case 2:
                cout << "Player Stats: \n"
                 << "Health : " << player.health << "\n"
                 << "Attack Power : " << player.attack << "\n"
                 << "Score : " << player.score << "\n";
                break;
            case 3:
                cout << "Potion Bag Shown!\n";
                break;
            case 4:
                notQuit = false;
                break;
            default:
                cout << "Invalid Input\n";
        }
    }
}
void EnemySpawn(int id, Player& ply_ob){
    if (id <= 40){
        cout << "A Goblin Appears with a Crackling Laugh!\n";
        Enemy goblin("Goblin", 10+(2*ply_ob.score), 5+(2*ply_ob.score), 1);
        Battle(ply_ob, goblin);
    }
    else if (id <= 60){
        cout << "A Zombie Marches towards you with a Ghastly Moan!\n";
        Enemy zombie("Zombie", 20+(2*ply_ob.score), 7+(2*ply_ob.score), 2);
        Battle(ply_ob, zombie);
    }     
    else{
        cout << "A Mummy Approaches from the Shadows!";
        Enemy mummy("Mummy", 12+(2*ply_ob.score), 10+(2*ply_ob.score), 3);
        Battle(ply_ob, mummy);
    } 
}
void Battle(Player& player_object, Enemy& enem_ob){
    bool is_fighting = true;
    int battle_choice;
    while(is_fighting){
        cout << "---FIGHT MENU---\n" 
        << "1. Attack\n" 
        << "2. Open Potion Bag\n" 
        << "3. Player Stats\n" 
        << "4. Enemy Stats\n"
        << "5. Flee" << endl;
        cin >> battle_choice;
        switch(battle_choice){
            case 1:
                enem_ob.health -= player_object.attack;  //Player deals damage to Enemy
                cout << "You have attacked " << enem_ob.name << " for " << player_object.attack << " damage!" << endl;
                if(enem_ob.health == 0){
                    player_object.score += enem_ob.score_worth;
                    cout << enem_ob.name << " has fallen!\n"
                         << "You have been awarded " << enem_ob.score_worth << " score!" << endl;
                    is_fighting=false;
                    break;
                }
                player_object.health -= enem_ob.attack; //Enemy deals damage to Player
                cout << "The " << enem_ob.name << " attacks you for " << enem_ob.attack << "!" << endl;
                break;
            case 2:
                break;
            case 3:
                cout << "Player Stats: \n"
                 << "Health : " << player_object.health << "\n"
                 << "Attack Power : " << player_object.attack << "\n"
                 << "Score : " << player_object.score << "\n";
                break;
            case 4:
                cout << enem_ob.name <<"'s Stats: \n"
                 << "Health : " << enem_ob.health << "\n"
                 << "Attack Power : " << enem_ob.attack << "\n";
                break;
        }
    }
}
void GenerateRoom(Player& player_ob){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);//Random number from 1-100 which decides our room
    int room_id = dist(gen);
    if (room_id <= 70) { 
        cout << "Enemy Spotted \n"; // 70% chance of an enemy room
        EnemySpawn(room_id, player_ob);
    }
    else if (room_id <= 90) {  
        cout << "Potion Get \n"; // 20% chance of getting a potion
    }   
    else {
        cout << "Empty Room \n"; // 10% chance of a empty room
    }

}
