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

using namespace std;

int ternary_to_decimal(vector<int> input ){
	/*
	Takes in a vector of 1,0,-1 i.e. a ternary encoding
	And returns the decimal value

	Currently theres mistake here
	*/

	int out = 0;
	while(!input.empty()){
		int temp = input.back();
		cout << "Just testing \n";
		input.pop_back();
		out = out + temp*pow(3,(input.size()));
		cout << "\nTemp is:" << temp ;
		cout << "\n The input size is:" << input.size();
	}
	return out;
}

vector<int> decimal_to_ternary(int decimal){
	vector<int> ternary;
	while (decimal>2){
		div_t val;
		val = div(decimal,3);
		ternary.push_back(val.rem);
		decimal = val.quot;
	}
	ternary.push_back(decimal);
	return ternary;
}


int check_result(char user_move, char comp_move){
	//Basic computer game 
	if ((user_move == 'R' && comp_move == 'S') || (user_move == 'S' && comp_move == 'P') || (user_move == 'P' && comp_move == 'R')){
		return -1;
	}
	if ((user_move == 'S' && comp_move == 'R') || (user_move == 'P' && comp_move == 'S') || (user_move == 'R' && comp_move == 'P')){
		return 1;
	}
	return 0; 
}

int convert_queue_to_state(deque<int> my_state, int R){
	//Go through all the queues elements - should be exactly R
	int out = 0;
	int temp;
	for (int i =0;i< R; i++){
		//Check the top element and pop it
		temp = my_state.front() ; //Check this syntax
		my_state.pop_front();
		out = out + temp * pow(3,i);
	}
	return out;
}

void print_array(float arr[],int arr_len){
	/*Prints the array*/
	for (auto it = arr ;it != arr + arr_len; it++){
		cout << "\n" << *it;
	}
}
void print_array(int arr[],int arr_len){
	/*Prints the array*/
	for (auto it = arr ;it != arr + arr_len; it++){
		cout << "\n" << *it;
	}
}


void print_queue(deque<int> q)
{
  while (!q.empty())
  {
    cout << q.front() << " ";
    q.pop_front();
  }
  cout << endl;
}

void print_map(map < pair<int,int> , float> myMap)
{
	for(map < pair<int,int> , float>::const_iterator it = myMap.begin();it != myMap.end(); ++it){
	    cout << it->first.first << " ," << it->first.second << " " << it->second << "\n";
	}
}

int convert_user_input_to_num(string valid_input,char user_input){
	int break_flag = 0;
	for(int i=0;i<valid_input.length();i++){
		if (valid_input[i] == user_input){
			break_flag = 1;
			return i-1;// -1 because I need the output as 0,1,2 for P,R,S
		}
	}
	cout << "User input bad!!! Terminating\n\n\n\n";
	return -1;
}

int draw_sample(int trans_counts[],float prior_count){
	/*
	TO DO::
	Takes in a distribution and draws a random variable from that distribution
	
	@params: dist contains the number of transitions. Need not be integer.
	Returns: A character number : 1[P],2[R],3[S]
	*/
	int trans_counts_len = 1+(sizeof(trans_counts)/sizeof(*trans_counts));
	float summed_trans[trans_counts_len+1];
	summed_trans[0] = 0;
 	for (int i=0;i<trans_counts_len;i++){
		summed_trans[i+1] = summed_trans[i] + trans_counts[i] + prior_count;
	}

	//Test the computed
	// print_array(summed_trans,trans_counts_len + 1);
	// print_array(trans_counts,trans_counts_len);
	//Generate a random number
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0,1);

	float rand_number = dis(gen);
	rand_number = rand_number * summed_trans[trans_counts_len];
	//Get the lower bound of the nearest element
	int pos = lower_bound(summed_trans,summed_trans+ trans_counts_len + 1,rand_number) - summed_trans;

	return pos;


}

int user_won(char user_move, char comp_move ){
	if (user_move == 'R' && comp_move =='S'){
		return 1;
	}

	else if (user_move == 'P' && comp_move =='R'){
		return 1;
	}

	else if (user_move == 'S' && comp_move =='P'){
		return 1;
	}

	else{
		return 0;
	}

}

int computer_won(char user_move, char comp_move ){
	if (user_move == 'P' && comp_move =='S'){
		return 1;
	}

	else if (user_move == 'S' && comp_move =='R'){
		return 1;
	}

	else if (user_move == 'R' && comp_move =='P'){
		return 1;
	}

	else{
		return 0;
	}

}
char beating_move(char exp_move){
	/*
	Takes in a move and returns what beats the move
	so, R -> S, S -> P, P-> R
	*/
	if (exp_move == 'R'){
		return 'P';
	}
	else if (exp_move == 'S'){
		return 'R';
	}else{
		return 'S';
	}
}

char draw_from_dist(vector<float> dist){
	/*
	TO DO::
	Takes in a distribution and draws a random variable from that distribution
	
	@params: dist contains the number of transitions. Need not be integer.
	Returns: A character : P,R,S
	*/
	char out = 'E';
	return out;
}

typedef pair<int, int> Key; //pair


int main(){
	int R = 3;//Number of steps back you want to remember
	int tot_states = pow(3,R); //Note, the total states will increase if comps states are included
	int initialize_from_previous = 0;
	string filename_previous = "filename.txt";

	// typedef pair<int, int> Key;
	map < pair<int,int> , float> graph_state; //Check syntax for mapping from pair to a single transition number
	vector<int> out2 = decimal_to_ternary(101);
	int break_flag = 0;

	deque<int>  state_queue; //Contains the current state , i.e. last R moves
	char user_input;
	//Maybe add an option of initializing the 
	// graph from an earlier saved graph if available
	
	if (initialize_from_previous == 1){
		//Start My graph from the previous
		//Read the input?? Figure out how to save a map to and from the filename.txt
		//Use this to check it out
		cout << "Initialization from stored logs **NOT SUPPORTED** .This is just a tester inplace. I will add initializing logic later on.";
	}

	// char valid_input[] = {'R','P','S','E'};
	string valid_input = "EPRS";

	
	//For generating random numbers
    mt19937 rng;
    rng.seed(random_device()());
    std::uniform_int_distribution<mt19937::result_type> dist6(1,3); // distribution in range [1, 6]



	int counter = 0;//Number of moves played

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

	int old_state, new_state;//These contain the state numbers
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
				//Computer plays something randomly
				char comp_move = valid_input[dist6(rng)];
				outfile_computer << comp_move << ",";

			    cout << "The computer played:" << comp_move << endl;

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
				// print_queue(new_state);


				//Draw a random element from the graph before updating
				string possible_inputs = "PRS";
				int transition_counts[3];//Counts the previously seen transitions

				for (int char_temp = 0;char_temp<= 2;++char_temp){
					// Somehow temporarily append a number to a queue and then remove it
					// TO DO - Add some logic here
					deque<int> temp_queue(state_queue);//Assume temp_queue holds this 
					cout<< "print temp queue";
					print_queue(state_queue);
					temp_queue.pop_back();
					// int num_char_temp = convert_user_input_to_num(valid_input, valid_input[char_temp+ 1]);
					temp_queue.push_back(char_temp);
					int possible_new_state;
					cout << "possible next queue";
					print_queue(temp_queue);
					possible_new_state = convert_queue_to_state(temp_queue,R);
					cout << "next state" << possible_new_state << endl;
					transition_counts[char_temp] = graph_state[make_pair(old_state,possible_new_state)];
					cout << "transition count for this is:" << transition_counts[char_temp];

				}

				//transition counts holds the three transitions
				//Draw a random sample based on these probabilities of transition
				//Maybe just simply draw a random uniform and then use cdf concept
				float prior_count = 0.5;
				for (int it =0;it<3;it++){
					cout << "Counts for playing the next one as:" << valid_input[it+ 1] << " is:" << transition_counts[it] <<"\n";
				}
				int int_comp_move= draw_sample(transition_counts,prior_count);
				//int_comp_move stores the computers move in integer value
				char exp_move = valid_input[int_comp_move];
				char comp_move = beating_move(exp_move);
				cout << "Computer played:"<< comp_move << "\n";
				cout << "This is the mod version";
				//Update the state queue to keep track of this

				//print the old state and the new state
				print_queue(state_queue);
				cout << "old_state" <<old_state<< endl;
				state_queue.push_back(num_user_input);
				state_queue.pop_front();

				//Update the new state
				new_state = convert_queue_to_state(state_queue,R); 
				cout << "new_state" << new_state << endl;


				//Log the comp_move? Maybe......No harm right? Useless data but still...Debugging purposes?
				outfile_computer << comp_move << ",";

				//Update the current graph
				if (graph_state.count(make_pair(old_state,new_state)) == 0){//Check syntax
					//This is a state that has not been seen before
					cout <<"old:" << old_state <<"   new_state:" << new_state <<endl;
					graph_state[make_pair(old_state,new_state)] = 1; //Check syntax
				}else{
					//This key is present
					cout <<"old:" << old_state <<"   new_state:" << new_state <<endl;
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