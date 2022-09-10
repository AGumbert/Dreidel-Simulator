

#include <iostream>
#include <stdlib.h> 
#include <time.h>

using namespace std;

int dreidel_rolls(int num_players, int starting_gelt);
double average_dreidel_rolls(int num_players, int starting_gelt);
double average_dreidel_rolls(int num_players, int starting_gelt, 
                                                        int num_tries);

int main(){
  
    srand(time(0));
    
    //gets the number of players from the user
    cout << "Enter the number of players you want to test (2-10): ";
    int num_players;
    cin >> num_players;
    
      
    cout << "\nAverage number of dreidel rolls for " << num_players 
              << " players with 0-50 starting gelt:\n";
              
              
    //tests 0-50 starting gelt for given number of players
    //takes average number of rolls for 1000 games
    for(int i = 0; i<= 50; i++){
            cout << "    " << i << " starting gelt average number of rolls: "
                 << average_dreidel_rolls(num_players, i, 1000) << "\n"; 
    }
    
    cout << "\n";
    
    //cout << "\n" << num_players << " players each starting with " 
    //     << starting_gelt << " gelt.\nGame completed in " << num_rounds  
    //     << " rounds and " << num_dreidel_rolls << " dreidel rolls.\n\n"; 
         
}

//function that determines average number of rolls 
//needed for given number of players (num_players),
//given number of starting gelt (starting_gelt), averaged 
//across num_tries games
double average_dreidel_rolls(int num_players, int starting_gelt, 
                                                        int num_tries){
  
    int total_rolls = 0;
    for(int i = 0; i < num_tries; i++){
        total_rolls += dreidel_rolls(num_players, starting_gelt);
    }
    return (double) total_rolls * 1.0 / num_tries; 
}

//plays one game of dreidel with num_players players 
//and starting_gelt starting gelt
int dreidel_rolls(int num_players, int starting_gelt){

    //sets up the game, gives each player 
    //the starting gelt
    int players_gelt[num_players];
    
    for(int i = 0; i < num_players; i++){
        players_gelt[i] = starting_gelt; 
    }
    
    //initializes variables of game
    int curr_player = 0; 
    
    int pot_gelt = 0; 
    
    int num_rounds = 1;
    
    int num_dreidel_rolls = 0; 
    
    
    while(true){
        
        //group contributions to pot 
        if(pot_gelt <= 1 or curr_player == 0){
          
            for(int i = 0; i < num_players; i++){
                if(players_gelt[i] > 0){
                    players_gelt[i]--;
                    pot_gelt++;
                } 
            }
        }
        
        //check for endgame 
        int remaining_players = 0;
        for(int i = 0; i < num_players; i++){
            if(players_gelt[i] > 0){
                remaining_players++;
            }
        }
        if(remaining_players <= 1){
            return num_dreidel_rolls;  
        }
        
        //dreidel roll 
        if(players_gelt[curr_player] > 0){
          
            int dreidel_roll = rand() % 4;
            num_dreidel_rolls++; 
            
            //gimel
            if(dreidel_roll == 1){
              
                players_gelt[curr_player] += pot_gelt; 
                pot_gelt = 0; 
                
            //hay
            }else if(dreidel_roll == 2){
              
                players_gelt[curr_player] += ((pot_gelt / 2) + pot_gelt % 2);
                pot_gelt -= ((pot_gelt / 2) + pot_gelt % 2);
            
            //shin
            }else if(dreidel_roll == 3){
              
                players_gelt[curr_player]--;
                pot_gelt++; 
            }
        }
        
        
        //check for endgame 
        remaining_players = 0;
        for(int i = 0; i < num_players; i++){
            if(players_gelt[i] > 0){
                remaining_players++;
            }
        }
        if(remaining_players <= 1){
            return num_dreidel_rolls;  
        }
        
        //turn taking 
        if(curr_player == num_players - 1){
            curr_player = 0;
            num_rounds++; 
        }else{
            curr_player++;
        }
    }
}




