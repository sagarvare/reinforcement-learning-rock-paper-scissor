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


vector<string> parse_CSV(string str1) {
	stringstream ss(str1);
	vector<string> result;

    string i;
	while( ss.good() )
	{
		string substr;
		getline( ss, substr, ',' );
		result.push_back( substr );
	}
    return result;
}

int ternary_to_decimal(vector<int> input ){
	/*
	Takes in a vector of 1,0,-1 i.e. a ternary encoding
	And returns the decimal value

	Currently theres mistake here
	*/

	int out = 0;
	while(!input.empty()){
		int temp = input.back();
		input.pop_back();
		out = out + temp*pow(3,(input.size()));
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


void print_vector(vector<string> q)
{
  for (vector<string>::iterator i = q.begin(); i != q.end(); ++i)
    cout << *i << '\n';
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
