#include <vector>
#include <map>
#include <queue>    
#include <deque>      
#include <string>

using namespace std;

vector<string> parse_CSV(string str1); 

/*
Takes in a vector of 1,0,-1 i.e. a ternary encoding
And returns the decimal value

Currently theres mistake here
*/
int ternary_to_decimal(vector<int> input );

vector<int> decimal_to_ternary(int decimal);

int check_result(char user_move, char comp_move);

int convert_queue_to_state(deque<int> my_state, int R);

void print_array(float arr[],int arr_len);

void print_array(int arr[],int arr_len);

void print_queue(deque<int> q);


void print_vector(vector<string> q);

void print_map(map < pair<int,int> , float> myMap);

int convert_user_input_to_num(string valid_input,char user_input);

/*
TO DO::
Takes in a distribution and draws a random variable from that distribution
@params: dist contains the number of transitions. Need not be integer.
Returns: A character number : 1[P],2[R],3[S]
*/	
int draw_sample(int trans_counts[],float prior_count);
	
int user_won(char user_move, char comp_move );

int computer_won(char user_move, char comp_move );

/*
Takes in a move and returns what beats the move
so, R -> S, S -> P, P-> R
*/
char beating_move(char exp_move);
	
	
/*
TO DO::
Takes in a distribution and draws a random variable from that distribution

@params: dist contains the number of transitions. Need not be integer.
Returns: A character : P,R,S
*/
char draw_from_dist(vector<float> dist);
	