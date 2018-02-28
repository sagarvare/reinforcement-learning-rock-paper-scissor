#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <map>
#include <fstream>
#include <random>
#include <queue>    
#include <deque>      
#include <string>
#include <iterator>
#include <sstream>
#include "helper.h"

using namespace std;

typedef pair<int, int> Key; //pair


int main(){
	int R = 3;//Number of steps back you want to remember
	int tot_states = pow(3,R); //Note, the total states will increase if comps states are included
	int initialize_from_previous = 1;
	string filename_previous = "filename.txt";
	string filename_logs = "game_play.log";

	// char valid_input[] = {'R','P','S','E'};
	string valid_input = "EPRS";

	//valid game play input: PRS
	string valid_move = "PRS";


	// typedef pair<int, int> Key;
	map < pair<int,int> , float> graph_state; //Check syntax for mapping from pair to a single transition number
	vector<int> out2 = decimal_to_ternary(101);
	int break_flag = 0;
	int old_state, new_state;//These contain the state numbers
	int counter = 0;//Number of moves played

	deque<int>  state_queue; //Contains the current state , i.e. last R moves
	char user_input;
	//Maybe add an option of initializing the 
	// graph from an earlier saved graph if available
	
	if (initialize_from_previous == 1){
		//Start My graph from the previous
		//Read the input?? Figure out how to save a map to and from the filename.txt
		//Use this to check it out
		cout << "Initialization from stored logs **NOT SUPPORTED** .This is just a tester inplace. I will add initializing logic later on.";

		//Go through the files and initialize the state_vector and the graph state appropriately.
		//Also make sure that the counter is also set appropriately
		string line;
		ifstream gameFile (filename_logs);
		if (gameFile.is_open() ) {
			while (getline(gameFile,line) ){
				string move; //Move is the read in 
				vector<string> results;
				results = parse_CSV(line);
				for (vector<string>::iterator i = results.begin(); i != results.end(); ++i){
					string move = *i;
					size_t found = valid_move.find(move);
					if (found!=string::npos && move != ""){
						//Add things to state_queue and make the game graph
						cout << "\n\ngoing to add:" << move;
						if (counter < R){
							int num_user_input = convert_user_input_to_num(valid_input, move[0]);
							state_queue.push_back(num_user_input);
						}else{ //There are more than R number of moves already done
							old_state = convert_queue_to_state(state_queue,R);
							int num_user_input = convert_user_input_to_num(valid_input, move[0]);
							state_queue.push_back(num_user_input); 
							state_queue.pop_front();
							new_state = convert_queue_to_state(state_queue,R);

							//Update the current graph
							if (graph_state.count(make_pair(old_state,new_state)) == 0){//Check syntax
								//This is a state that has not been seen before
								graph_state[make_pair(old_state,new_state)] = 1; //Check syntax
							}else{
								//This key is present
								graph_state[make_pair(old_state,new_state)]= 1 + graph_state[make_pair(old_state,new_state)]; //Check syntax
							}
						}
						counter++;

  					}
				}

				cout << "\n\n";
			}
			gameFile.close();
		}
		else{
			cout << "Unable to  open the FIle\n\n";
		}
	}


	
	//For generating random numbers
    mt19937 rng;
    rng.seed(random_device()());
    std::uniform_int_distribution<mt19937::result_type> dist6(1,3); // distribution in range [1, 6]

	//Open a file for logging all the users moves
	string file_name = "game_play.log";
	ofstream outfile;
	outfile.open(file_name, ios_base::app);

	//Open a file for logging all the computers moves
	string file_name_computer = "game_play_computer.log";
	ofstream outfile_computer;
	outfile_computer.open(file_name_computer, ios_base::app);

	//Open a file for logging the W/L numbers
	string file_name_WL = "game_WL_numbers.log";
	ofstream outfile_WL;
	outfile_WL.open(file_name_WL, ios_base::app);

	if (initialize_from_previous ==0){
	}
	int AI_loss = 0;
	int AI_wins = 0;
	int AI_draws = 0;



	while(break_flag == 0){
		cout << "\nEnter what you wanna play : R,P,S";
		cin >> user_input;

		// if (find(valid_input.begin(), valid_input.end(), user_input) != valid_input.end() ){
		if (valid_input.find(user_input) != string::npos){
			//Element part of valid input
			if (user_input == 'E'){
				//User wants to end the game
				cout << "\n\nThanks for playing";

				//Write the W/L numbers to logs
				outfile_WL << "wins:" << AI_wins<<"\n";
				outfile_WL << "draws:" << AI_draws <<"\n";
				outfile_WL << "loss:" << AI_loss << "\n";

				break_flag = 1;
				break;
			}
			outfile << user_input << ",";
			int num_user_input = convert_user_input_to_num(valid_input, user_input);
			//Else continue with normal game
			//Log the play, computer plays something, log the graph state and log the result
			

			//The first R moves are random
			if (counter < R){
				cout << "\n\n\n--------------------------------------ENTERING THE RANDOM PHASE!\n\n\n";
				//Computer plays something randomly
				char comp_move = valid_input[dist6(rng)];
				outfile_computer << comp_move << ",";

			    cout << "--------------------------------------------The computer played:" << comp_move << endl;

			    int result = check_result(num_user_input,comp_move);
				//Add the move to the queue
				state_queue.push_back(num_user_input);


				//Update who won
				if (user_won(user_input, comp_move) == 1 ){
					AI_loss ++;

				}else if (computer_won(user_input, comp_move) == 1){
					AI_wins ++;

				}else{
					AI_draws ++;
				}





			}else{
				// Implement a queue for appending the moves 
				// i.e. keep popping oldest and add the latest
				// all the states from the queue --> state transition --> update graph
				old_state = convert_queue_to_state(state_queue,R);
				// state_queue.push_back(num_user_input);
				// state_queue.pop_front();

				//currently old_state=new_state is NOT wrong
				//Because of an old bug that I corrected horribly
				//Now the bug is gone, but I am left with horrible code

				new_state = convert_queue_to_state(state_queue,R); 


				//Draw a random element from the graph before updating
				string possible_inputs = "PRS";
				int transition_counts[3];//Counts the previously seen transitions

				for (int char_temp = 0;char_temp<= 2;++char_temp){
					// Somehow temporarily append a number to a queue and then remove it
					// TO DO - Add some logic here
					deque<int> temp_queue(state_queue);//Assume temp_queue holds this 
					temp_queue.pop_back();
					// int num_char_temp = convert_user_input_to_num(valid_input, valid_input[char_temp+ 1]);
					temp_queue.push_back(char_temp);
					int possible_new_state;
					possible_new_state = convert_queue_to_state(temp_queue,R);
					transition_counts[char_temp] = graph_state[make_pair(old_state,possible_new_state)];
				}

				//transition counts holds the three transitions
				//Draw a random sample based on these probabilities of transition
				//Maybe just simply draw a random uniform and then use cdf concept
				float prior_count = 0.5;
				cout << "\n\n";
				for (int it =0;it<3;it++){
					cout << "\nCounts for playing the next one as:" << valid_input[it+ 1] << " is:" << transition_counts[it];
				}
				int int_comp_move= draw_sample(transition_counts,prior_count);
				//int_comp_move stores the computers move in integer value
				char exp_move = valid_input[int_comp_move];
				char comp_move = beating_move(exp_move);
				cout << "\n\n----------------------------------Computer played:"<< comp_move << "\n";
				//Update the state queue to keep track of this

				//print the old state and the new state
				state_queue.push_back(num_user_input);
				state_queue.pop_front();

				//Update the new state
				new_state = convert_queue_to_state(state_queue,R); 


				//Log the comp_move? Maybe......No harm right? Useless data but still...Debugging purposes?
				outfile_computer << comp_move << ",";

				//Update the current graph
				if (graph_state.count(make_pair(old_state,new_state)) == 0){//Check syntax
					//This is a state that has not been seen before
					graph_state[make_pair(old_state,new_state)] = 1; //Check syntax
				}else{
					//This key is present
					graph_state[make_pair(old_state,new_state)]= 1 + graph_state[make_pair(old_state,new_state)]; //Check syntax
				}

				//Update who won
				if (user_won(user_input, comp_move) ){
					AI_loss ++;

				}else if (computer_won(user_input, comp_move) ){
					AI_wins ++;

				}else{
					AI_draws ++;
				}



			}
			counter++;




			//Write the input to user game data





			//After every 100 data inputs, 
			//Save current graph 






			//If in the playing mode, pick an action based on the graph






			//Note down the result and keep doing statistical analysis






		}else{
			//Element not part of valid input
			cout << "Please enter a valid move";

		}
		// break_flag = 1;
	}
	return 0; 
}