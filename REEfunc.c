#include <stdio.h>
#include <stdlib.h> 
#include "REE.h"
// you can find more info about each function in the "REE.h" file

int stackPush(struct NFAstack **top, int startS, int acceptS)  {    
    struct NFAstack *newbie;
    
    // allocating memory for new stack entry
    newbie = (struct NFAstack *)malloc(sizeof(struct NFAstack));
    if(!newbie) {
		printf("no space to allocate memory");
        return 0;
    }
    
    // set values we're storing in the new entry
    newbie->startState = startS;
	newbie->acceptState = acceptS;
	newbie->list = NULL;
	
    // put this node at the start of the list
    newbie->next = *top;
	*top = newbie;
    return 1;
}


int stackPop(struct NFAstack **top) {
    struct NFAstack *next;
	
    if(!(*top)) {
        // no values in stack
        printf("nothing in stack to pop\n");
        return 0;
    }
	
	// change top of the stack
    next = (*top)->next;
    free(*top);
    
	if (next != NULL) {
    	*top = next;
    } else {
    	*top = NULL;
    }
	
    return 1;
}

int addToList(struct NFAstack *stack, int fState, char tType, int tState) {
	struct transition *newlist;
	
	// allocating memory for new list entry
	newlist = (struct transition *)malloc(sizeof(struct transition));
	
	if(!newlist) {
		printf("no space to allocate memory");
        return 0;
    }
    struct transition *L = stack->list;
	
	// set values we're storing in the new entry
	newlist->fromState = fState;
	newlist->transitionType = tType;
	newlist->toState = tState;
	newlist->next = NULL;
	
	// find the end of the list...
	if (L != NULL) {
		while (L->next != NULL) {
			if (L == L->next) {
				break;
			}
			L = L->next;
		}
		// ...then append the new entry
		L->next = newlist;
	} else {
		// ...then append the new entry
		stack->list = newlist;
	}

	return 1;
}

void freeStructs(struct NFAstack **top) {
	// go through every stack, freeing it after freeing it's list
	if ((*top) != NULL) {
		if ((*top)->next != NULL) {
			freeStructs(&((*top)->next));
		}
		freeList((*top)->list);
		free((*top));
	}
}

void freeList(struct transition *list) {
	// go through the list, freeing each entry
	if (list != NULL) {
		freeList(list->next);
		free(list);
	}
}

int getLastStateStruct(struct NFAstack **top) {
	struct NFAstack *T = *top;
	int max = 1;
	int a = 0;
	if (T == NULL) {
		return 1;
	} else {
		while (T != NULL) {
			a = getLastStateList(T->list);
			if (max < a) {
				max = a;
			} 
			T = T->next;

		}
		return max;
	}
}

int getLastStateList(struct transition *list) {
	struct transition *L = list;
	int max = 1;
	int a = 0;
	if (L == NULL) {
		return 1;
	} else {
		while (L != NULL) {
			a = L->toState;
			if (max < a) {
				max = a;
			}
			L = L->next;
		} 
		return max;
	}
}

void printStructs(struct NFAstack **top) {
	if ((*top) != NULL) {
		if ((*top)->next != NULL) {
			printStructs(&((*top)->next));
		}
		printList((*top)->list);
	}
}

void printList(struct transition *list) {
	if (list != NULL) {
		printf("(q%d, %c) -> q%d\n", list->fromState, list->transitionType, list->toState);
		printList(list->next);
	}
}

void printStack(struct NFAstack *stack) {
	if (stack != NULL) {
		printf("\nStart: q%d\nAccept: q%d\n", stack->startState, stack->acceptState);
	}
}





