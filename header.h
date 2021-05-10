//represents the structure of state of the jugs
typedef struct state_of_jugs{
    int choice_of_move; //indicates which of the 6 moves is to be performed
    int jug_A;          //volume filled in jug A
    int jug_B;          //volume filled in jug B
    int jug_C;          //volume filled in jug C
}STATE;

//structure of the node 
typedef struct node_in_list{
    struct node_in_list *previous_node;
    struct node_in_list *next_node;
    STATE state;
}NODE;

//structure if the doubly linked list
typedef struct doubly_linked_list{
    NODE *head;
    NODE *tail;
}LIST;

//six possible moves (in order that is mentioned in the requirements)
void A_to_B(const STATE *, const STATE *, STATE *);
void A_to_C(const STATE *, const STATE *, STATE *);
void B_to_A(const STATE *, const STATE *, STATE *);
void B_to_C(const STATE *, const STATE *, STATE *);
void C_to_A(const STATE *, const STATE *, STATE *);
void C_to_B(const STATE *, const STATE *, STATE *);

//utility for states
void initialise_state(STATE *, int, int, int);//initialises each state
void display_state(const STATE *);//displays the state
int are_same_state(const STATE *, const STATE *);//returns 1 or 0 indicating same state or not 
int is_valid_state(const STATE *, const STATE *, const STATE *);//returns 1 or 0 indicating if it is a valid state or not
//utility for lists
void initialise_list(LIST *);//initialises the list
void display_list(const LIST *);//dislpays the content of the list
int is_state_repeated(const LIST *, const STATE *);//returns 1 or 0 indicating if the state is repeated or not
void add_node_at_end(LIST *, const STATE *);//adds node at end of list
void remove_node_at_end(LIST *);//removes node at the end of the list