#ifndef REE_H
#define REE_H

// struct used for stack
struct NFAstack {
	int startState;
	int acceptState;
	struct NFAstack *next;
	struct transition *list;
};

// struct used for lists
struct transition {
	int fromState;
	char transitionType;
	int toState;
	struct transition *next;
};

// push a struct onto the stack
// param: 
//		**top = pointer to the top of the stack pointer
//		startS = the value you want to set the start state of the new entry
//		acceptS = the value you want to set the accept state of the new entry
// returns: 1 if successfully pushed, or 0 if there is no space in memory 
int stackPush(struct NFAstack **top, int startS, int acceptS);

// pop a struct from the stack
// param: 
//		**top = pointer to the top of the stack pointer
// returns: 1 if successfully popped, or 0 if the stack is empty
int stackPop(struct NFAstack **top);

// append a new list struct entry to a stack's list
// param:
//		*stack = pointer to the stack with the list we care about
//		fState = the value you want to set the from state of the new entry
//		tType = the value you want to set the transition type of the new entry
//		fState = the value you want to set the to state of the new entry
// returns: 1 if successfully added, or 0 if there is no space in memory
int addToList(struct NFAstack *stack, int fState, char tType, int tState);

// both "freeStructs" and "freeList" are used together
// itterates recursively through the stack and their lists, freeing up memory
// param: 
//		**top = pointer to the top of the stack pointer
//		*list = pointer to the begging of a list
void freeStructs(struct NFAstack **top);
void freeList(struct transition *list);

// both "getLastStateStruct" and "getLastStateList" are used together
// itterates recursively through the stack and their lists, finding the largest
// state number
// param: 
//		**top = pointer to the top of the stack pointer
//		*list = pointer to the begging of a list
// returns: the largest state number
int getLastStateStruct(struct NFAstack **top);
int getLastStateList(struct transition *list);

// both "printStructs" and "printList" are used together
// itterates recursively through the stack and their lists, printing their data
// param: 
//		**top = pointer to the top of the stack pointer
//		*list = pointer to the begging of a list
void printStructs(struct NFAstack **top);
void printList(struct transition *list);

// prints the start state and accept state of a stack entry
// param: 
//		*stack = pointer to a stack pointer
void printStack(struct NFAstack *stack);

#endif
