#include <iostream>
#include <random>
using namespace std; 

class Player{ // Player Class and Stats
    public:
        int health = 50;
        int attack = 10;
        int score = 0;
        int no_of_attackpotion = 0;
        int no_of_healthpotion = 0;

};
class Enemy{ //Enemy Class and Stats 
    public:
    string name;
    int health;
    int attack;
    int score_worth;
    Enemy(string name, int health, int attack, int score_worth)
        : name(name), health(health), attack(attack), score_worth(score_worth){
            cout << "\n"<< name <<" : \n"
                 << "Health : " << health << "\n"
                 << "Attack : " << attack << endl;

        }
        
};
//Function Prototypes
void GenerateRoom(Player& player_ob, mt19937& gen, uniform_int_distribution<int> dist); //Randomly chooses the next room on exploring
void EnemySpawn(int id, Player& ply_ob); //Creates Enemy Object
void Battle(Player& player_object, Enemy& enem_ob); //Controls Fight Sequences

int main(){ 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);//Random number from 1-100 which decides our room
    Player player;
    int choice;
    bool notQuit = true;
    
    cout << "===============================\n"
         << "--------DUNGEON CRAWLER--------\n"
         << "===============================\n";
    while (notQuit){
        if(player.health <0.1){
            int choiceafterdeath;
            cout << "Play Again or Quit Game?\n"
                         << "1. PLAY AGAIN\n"
                         << "2. QUIT" << endl;
            cin >> choiceafterdeath;
            switch (choiceafterdeath){
                case 1:
                    notQuit=true;
                    player.health = 50;
                    player.attack = 10;
                    player.score = 0;
                    player.no_of_attackpotion = 0;
                    player.no_of_healthpotion = 0;
                    break;
                case 2:
                    notQuit = false;
                    break;
            }
        }
        else{
            cout << "\nChoose your option\n"
         << "1. Explore\n"
         << "2. Stats\n"
         << "3. Open Potion Bag\n"
         << "4. Quit" << endl;
        cin >> choice;
        switch(choice){
            case 1:
                cout << "\nYou entered a new room \n";
                GenerateRoom(player, gen, dist);
                break;
            case 2:
                cout << "\nPlayer Stats: \n"
                 << "Health : " << player.health << "\n"
                 << "Attack Power : " << player.attack << "\n"
                 << "Score : " << player.score << "\n";
                break;
            case 3:
                int potionchoice;
                cout << "\nPotion Bag :\n"
                     << "\t Health Potions : " << player.no_of_healthpotion << "\n"
                     << "\t Attack Potions : " << player.no_of_attackpotion << "\n \n"
                     << "Use Potion?\n"
                     << "\t1. Use Health Potion\n"
                     << "\t2. Use Attack Potion\n"
                     << "\t3. Close Potion Bag" << endl;
                cin >> potionchoice;
                switch (potionchoice){
                    case 1:
                        if(player.no_of_healthpotion > 0){
                            player.no_of_healthpotion -=1;
                            player.health += 20;
                            cout << "\nYour Health has increased by 20!" << endl;
                            
                        }
                        else{
                            cout << "\nYou don't have any Health Potions!"<<endl;
                        }
                        break;
                    case 2:
                        if(player.no_of_attackpotion > 0){
                            player.no_of_attackpotion -=1;
                            player.attack += 10;
                            cout << "\nYour Attack Power has increased by 10!" << endl;
                            
                        }
                        else{
                            cout << "\nYou don't have any Attack Potions!"<<endl;
                        }

                        break;
                    case 3:
                        break;
                    default:
                        cout << "\nInvalid Input!" << endl;
                        break;
                }
                cout << "\nYou close your Potion Bag" << endl;
                break;
            case 4:
                notQuit = false;
                break;
            default:
                cout << "Invalid Input\n";
        }
        
        }
    }
}
void EnemySpawn(int id, Player& ply_ob){
    if (id <= 40){
        cout << "A Goblin Appears with a Crackling Laugh!\n";
        Enemy goblin("Goblin", 10 + (4 * (ply_ob.score/5)), 2 + (2 * (ply_ob.score/5)), 1);
        Battle(ply_ob, goblin);
    }
    else if (id <= 60){
        cout << "A Zombie Marches towards you with a Ghastly Moan!\n";
        Enemy zombie("Zombie", 25+(2*(ply_ob.score/5)), 7+(2*(ply_ob.score/5)), 2);
        Battle(ply_ob, zombie);
    }     
    else{
        cout << "A Mummy Approaches from the Shadows!\n";
        Enemy mummy("Mummy", 15+(2*(ply_ob.score/5)), 10+(2*(ply_ob.score/5)), 3);
        Battle(ply_ob, mummy);
    } 
}
void Battle(Player& player_object, Enemy& enem_ob){
    bool is_fighting = true;
    int battle_choice;
    while(is_fighting){
        cout << "\n---FIGHT MENU---\n" 
        << "1. Attack\n"  
        << "2. Player Stats\n" 
        << "3. Enemy Stats\n"
        << "4. Flee" << endl;
        cin >> battle_choice;
        switch(battle_choice){
            case 1:
                enem_ob.health -= player_object.attack;  // Player deals damage to Enemy
                cout << "You have attacked " << enem_ob.name << " for " << player_object.attack << " damage!" << endl;
                if(enem_ob.health <= 0){
                    player_object.score += enem_ob.score_worth;
                    cout << enem_ob.name << " has fallen!\n"
                         << "You have been awarded " << enem_ob.score_worth << " score!" << endl;
                    is_fighting=false;
                    break;
                }
                player_object.health -= enem_ob.attack; // Enemy deals damage to Player
                cout << "The " << enem_ob.name << " attacks you for " << enem_ob.attack << "!" << endl;
                if(player_object.health < 0.1){
                    cout <<"+++===========================+++\n"
                         << "You Died to a " << enem_ob.name <<"\n"
                         <<"+++===========================+++\n";
                    is_fighting =false;
                    
                    
                }
                break;
            case 2:
                cout << "Player Stats: \n"
                 << "Health : " << player_object.health << "\n"
                 << "Attack Power : " << player_object.attack << "\n"
                 << "Score : " << player_object.score << "\n";
                break;
            case 3:
                cout << enem_ob.name <<"'s Stats: \n"
                 << "Health : " << enem_ob.health << "\n"
                 << "Attack Power : " << enem_ob.attack << "\n";
                break;
            case 4:
                cout << "You have fled from a " << enem_ob.name << endl;
                player_object.score -= 1;
                is_fighting =false;
                break;
        }
    }
}

void GenerateRoom(Player& player_ob, mt19937& gen, uniform_int_distribution<int> dist){
    int room_id = dist(gen);
    if (room_id <= 60) { 
        cout << "Enemy Spotted \n"; // 60% chance of an enemy room
        EnemySpawn(room_id, player_ob);
    }
    else if (room_id <= 80) {  
        cout << "You find a Health Potion \n"; // 20% chance of getting a Health potion
        player_ob.no_of_healthpotion +=1;
    }
    else if (room_id <= 90) {  
        cout << "You find a Attack Potion \n"; // 10% chance of getting a Attack potion
        player_ob.no_of_attackpotion +=1;
    }   
    else {
        cout << "Empty Room \n"; // 10% chance of a empty room
    }

}
