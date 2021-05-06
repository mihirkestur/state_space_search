#include<stdio.h>
#include<stdlib.h>
#include "A3_header_PES1UG19CS272.h"
//Name: Mihir Madhusudan Kestur   SRN: PES1UG19CS272     Section: E     Semester: 4

//initialising values
void initialise_state(STATE *state_ptr, int vol_A, int vol_B, int vol_C){
    state_ptr->jug_A = vol_A;
    state_ptr->jug_B = vol_B;
    state_ptr->jug_C = vol_C;
    state_ptr->choice_of_move = 0;
}
//displays state transition
void display_state(const STATE* state_ptr){
    printf("%s\n", (state_ptr->choice_of_move == 0) ? "A B":
    (state_ptr->choice_of_move == 1) ? "A C":((state_ptr->choice_of_move == 2) ? "B A":
    ((state_ptr->choice_of_move == 3) ? "B C":((state_ptr->choice_of_move == 4) ? "C A": "C B"))));
}
//returns 1 or 0 indicating same state or not 
int are_same_state(const STATE *state_1, const STATE *state_2){
    return (state_1->jug_A == state_2->jug_A) && 
    (state_1->jug_B == state_2->jug_B) && (state_1->jug_C == state_2->jug_C);
}

//returns 1 or 0 indicating if it is a valid state or not
//volume filled in the jugs should be >= 0 and <= their capacity and = to the initial state net amount
int is_valid_state(const STATE *initial_state, const STATE *capacity_state, const STATE *state_to_check){
    return (initial_state->jug_A + initial_state->jug_B + initial_state->jug_C == state_to_check->jug_A + state_to_check->jug_B + state_to_check->jug_C) 
    && (state_to_check->jug_A >=0 && state_to_check->jug_B >=0 && state_to_check->jug_C >=0) && 
    (state_to_check->jug_A <= capacity_state->jug_A && state_to_check->jug_B <= capacity_state->jug_B && state_to_check->jug_C <= capacity_state->jug_C);
}

//initialises the list
void initialise_list(LIST *list){
    list->head = list->tail = NULL;
}

//dislpays the content of the list
void display_list(const LIST *list){
    NODE *traverse = list->head;
    while(traverse->next_node != NULL){
        display_state(&traverse->state);
        traverse = traverse->next_node;
    }
}

//returns 1 or 0 indicating if the state is repeated or not
int is_state_repeated(const LIST *list, const STATE *state_to_check){
    NODE *traverse = list->head;
    while(traverse != NULL){
        if(are_same_state(&traverse->state, state_to_check)){
            return 1;
        }
        traverse = traverse->next_node;
    }
    return 0;
}

//adds node at end of list
void add_node_at_end(LIST *list, const STATE *state_to_add){
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->state = *state_to_add;
    //if list is empty
    if(list->head == NULL){
        new_node->previous_node = list->tail;
        new_node->next_node = NULL;
        list->head = new_node;
        list->tail = new_node;
    }
    //if it is not empty
    else{
        new_node->previous_node = list->tail;
        new_node->next_node = NULL;
        list->tail->next_node = new_node;
        list->tail = new_node;
    }
}

//removes node at the end of the list
void remove_node_at_end(LIST *list){
    //if list is empty return
    if(list->head == NULL){
        return;
    }
    //if list has only 1 node
    else if(list->head == list->tail){
        NODE *delete_node = list->head;
        list->head = list->tail = NULL;
        free(delete_node);
    }
    //if there are more than two nodes
    else{
        NODE *delete_node = list->tail;
        list->tail = delete_node->previous_node;
        list->tail->next_node = NULL;
        free(delete_node);
    }
}

//6 functions representing the possible moves
void A_to_B(const STATE *capacity_state, const STATE *begin, STATE *end){
    int free_volume_B = capacity_state->jug_B - begin->jug_B;  //volume that is free in jug B
    //if available volume in B is less than or equal to volume filled in A
    if(free_volume_B <= begin->jug_A){           
        end->jug_B = begin->jug_B + free_volume_B;  //fill the end state of B to brim
        end->jug_A = begin->jug_A - free_volume_B;  //subtract the volume from A 
    }
    //else if volume filled in A is strictly less than available volume in B
    else{
        end->jug_B = begin->jug_B + begin->jug_A;   //jug A's content is added to jug B
        end->jug_A = 0;                             //final state of A becomes empty
    }
    //jug C content remains the same
    end->jug_C = begin->jug_C;
}
void A_to_C(const STATE *capacity_state, const STATE *begin, STATE *end){
    int free_volume_C = capacity_state->jug_C - begin->jug_C;  //volume that is free in jug C
    //if available volume in C is less than or equal to volume filled in A
    if(free_volume_C <= begin->jug_A){           
        end->jug_C = begin->jug_C + free_volume_C;  //fill the end state of C to brim
        end->jug_A = begin->jug_A - free_volume_C;  //subtract the volume from A 
    }
    //else if volume filled in A is strictly less than available volume in C
    else{
        end->jug_C = begin->jug_C + begin->jug_A;   //jug A's content is added to jug C
        end->jug_A = 0;                             //final state of A becomes empty
    }
    //jug B content remains the same
    end->jug_B = begin->jug_B;
}
void B_to_A(const STATE *capacity_state, const STATE *begin, STATE *end){
    int free_volume_A = capacity_state->jug_A - begin->jug_A;  //volume that is free in jug A
    //if available volume in A is less than or equal to volume filled in B
    if(free_volume_A <= begin->jug_B){           
        end->jug_A = begin->jug_A + free_volume_A;  //fill the end state of A to brim
        end->jug_B = begin->jug_B - free_volume_A;  //subtract the volume from B 
    }
    //else if volume filled in B is strictly less than available volume in A
    else{
        end->jug_A = begin->jug_A + begin->jug_B;   //jug B's content is added to jug A
        end->jug_B = 0;                             //final state of B becomes empty
    }
    //jug C content remains the same
    end->jug_C = begin->jug_C;
}
void B_to_C(const STATE *capacity_state, const STATE *begin, STATE *end){
    int free_volume_C = capacity_state->jug_C - begin->jug_C;  //volume that is free in jug C
    //if available volume in C is less than or equal to volume filled in B
    if(free_volume_C <= begin->jug_B){           
        end->jug_C = begin->jug_C + free_volume_C;  //fill the end state of C to brim
        end->jug_B = begin->jug_B - free_volume_C;  //subtract the volume from B
    }
    //else if volume filled in B is strictly less than available volume in C
    else{
        end->jug_C = begin->jug_C + begin->jug_B;   //jug B's content is added to jug C
        end->jug_B = 0;                             //final state of B becomes empty
    }
    //jug A content remains the same
    end->jug_A = begin->jug_A;
}
void C_to_A(const STATE *capacity_state, const STATE *begin, STATE *end){
    int free_volume_A = capacity_state->jug_A - begin->jug_A;  //volume that is free in jug A
    //if available volume in A is less than or equal to volume filled in C
    if(free_volume_A <= begin->jug_C){           
        end->jug_A = begin->jug_A + free_volume_A;  //fill the end state of A to brim
        end->jug_C = begin->jug_C - free_volume_A;  //subtract the volume from C 
    }
    //else if volume filled in C is strictly less than available volume in A
    else{
        end->jug_A = begin->jug_A + begin->jug_C;   //jug C's content is added to jug A
        end->jug_C = 0;                             //final state of C becomes empty
    }
    //jug B content remains the same
    end->jug_B = begin->jug_B;
}
void C_to_B(const STATE *capacity_state, const STATE *begin, STATE *end){
    int free_volume_B = capacity_state->jug_B - begin->jug_B;  //volume that is free in jug B
    //if available volume in B is less than or equal to volume filled in C
    if(free_volume_B <= begin->jug_C){           
        end->jug_B = begin->jug_B + free_volume_B;  //fill the end state of B to brim
        end->jug_C = begin->jug_C - free_volume_B;  //subtract the volume from C 
    }
    //else if volume filled in C is strictly less than available volume in B
    else{
        end->jug_B = begin->jug_B + begin->jug_C;   //jug C's content is added to jug B
        end->jug_C = 0;                             //final state of A becomes empty
    }
    //jug A content remains the same
    end->jug_A = begin->jug_A;
}