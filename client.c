#include<stdio.h>
#include<stdlib.h>
#include "header.h"
#define DEBUG 0

int main(){
	//this has the solution states 
    LIST state_transition_list;
    //initialising the list
    initialise_list(&state_transition_list);

    //total capacity of each jug
    int capacity_A, capacity_B, capacity_C;       
    //volume filled initially in each jug  
    int initital_state_A, initital_state_B, initital_state_C;
    //volume of final state desired
    int final_state_A, final_state_B, final_state_C;

    //taking inputs
    scanf("%d %d %d", &capacity_A, &capacity_B, &capacity_C);
    scanf("%d %d %d", &initital_state_A, &initital_state_B, &initital_state_C);
    scanf("%d %d %d", &final_state_A, &final_state_B, &final_state_C);

    //creating 3 states: start state, goal state and the capacity state
    STATE start_state, goal_state, capacity_state;
    initialise_state(&start_state, initital_state_A, initital_state_B, initital_state_C);
    initialise_state(&goal_state, final_state_A, final_state_B, final_state_C);
    initialise_state(&capacity_state, capacity_A, capacity_B, capacity_C);

    //the start state obtained is added to the list
    add_node_at_end(&state_transition_list, &start_state);
    
    if(DEBUG){
        //print input
        printf("The input is \n");
        printf("%d %d %d\n", capacity_A, capacity_B, capacity_C);
        printf("%d %d %d\n", initital_state_A, initital_state_B, initital_state_C);
        printf("%d %d %d\n", final_state_A, final_state_B, final_state_C);
        //check if start and end states are correct and see if list is working
        printf("start state: ");display_state(&start_state);
        printf("\n goal state: ");display_state(&goal_state);
        printf("\n");
        display_list(&state_transition_list);
    }

    //this is an array of pointers to functions (possible moves, in the order expected) 
    void (*move[])(const STATE *capacity_state, const STATE *begin, STATE *end) = {
        A_to_B,
        A_to_C,
        B_to_A,
        B_to_C,
        C_to_A,
        C_to_B
    };

    int solution_count = 0; //holds the number of solutions
    int move_choice;        //value indicating the transition function from the array

    STATE *new_state = (STATE *)malloc(sizeof(STATE)); //new state to perform transitions
    
    //state space search logic
    //run loop until all possible solutions are obtained
	while(state_transition_list.head != NULL){
        //note the choice of move for a particular state
		move_choice = state_transition_list.tail->state.choice_of_move;
        //perform the transition on that state
		move[move_choice](&capacity_state, &state_transition_list.tail->state, new_state);
        if(DEBUG){
            printf("trying transition ");
            display_state(new_state);
        }
        //if the new state is not repeated and if it is a valid state then check if its a solution
		if(!is_state_repeated(&state_transition_list, new_state) && 
            is_valid_state(&start_state ,&capacity_state, new_state)){

            //add the state to the transition list
			add_node_at_end(&state_transition_list, new_state);
			//if it is the goal state then display the list and increment the solution count
            if(are_same_state(new_state, &goal_state)){
				display_list(&state_transition_list);
    			++solution_count;
    			printf("\n");
			}
		}
        //if it is repeated or not a valid state then transitions will not lead to goal state
		else{
            //remove the states
			while(state_transition_list.tail != NULL && ++state_transition_list.tail->state.choice_of_move == 6){
    			if(DEBUG){
                    printf("removing ");
                    display_state(&state_transition_list.tail->state);
                }
                remove_node_at_end(&state_transition_list);
			}
		}
	}
    //print the number of solutions
	printf("%d\n", solution_count);
}