#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "REE.h"

int main() {
	// declaring variables:
	// *stack is the pointer to the top of the stack
	struct NFAstack *stack = NULL;

	struct NFAstack *nFA = NULL;
	struct transition *T1 = NULL;
	struct transition *T2 = NULL;
	
	char FA[100];
	int c = 0;
	
	int i = 0;
	int j = 0;
	
	char acceptedInput[8] = "abcdeE*|";
	
	// get input from the user
	printf("Enter regular expression:\n");
	scanf("%s", FA);
	
	while (c < strlen(FA)) {
		// checks if user input is valid (if not, close the program)
		if (strlen(strchr(acceptedInput, FA[c])) <= 1) {
			printf("not valid regular expression\n");
			if (stack != NULL) {
				freeStructs(&stack);
			}
			exit(0);
		} else {
			
			switch (FA[c]) {
				
				// Concatination does not work given how I set up the transition list
				/*
				case '&':
					//push(NFA that accepts the concatenation of L(nFA1) followed by L(nFA2));
					T1 = stack->list;
					stackPop(&stack);
					
					T2 = stack->list;
					stackPop(&stack);
					
					stackPush(&stack, 0, 0);
					i = getLastStateStruct(&stack);
					
					while (T1 != NULL) {
						addToList(stack, i+(T1->fromState), T1->transitionType, i+(T1->toState));
						T1 = T1->next;
					}
					
					j = getLastStateStruct(&stack);
					
					while (T2 != NULL) {
						addToList(stack, j+(T2->fromState), T2->transitionType, j+(T2->toState));
						T2 = T2->next;
					}
					
					stack->startState = i;
					stack->acceptState = j;
					break;
				*/
				
				// Union case
				case '|':
					//push(NFA that accepts L(nFA1) | L(nFA2));
					if (stack == NULL) {
						printf("not valid regular expression\n");
						if (stack != NULL) {
						freeStructs(&stack);
						}
						exit(0);
					}
					
					T1 = stack->list;
					stackPop(&stack);
					
					if (stack == NULL) {
						printf("not valid regular expression\n");
						if (stack != NULL) {
						freeStructs(&stack);
						}
						exit(0);
					}
					
					T2 = stack->list;
					stackPop(&stack);
					
					stackPush(&stack, 0, 0);
					i = getLastStateStruct(&stack);
					addToList(stack, i, 'E', i+1);
					
					while (T1 != NULL) {
						addToList(stack, i+(T1->fromState)-1, T1->transitionType, i+(T1->toState)-1);
						T1 = T1->next;
					}
					
					j = getLastStateStruct(&stack);
					addToList(stack, j, 'E', j+1);
					addToList(stack, i, 'E', j+2);
					
					while (T2 != NULL) {
						addToList(stack, j+1+(T2->fromState), T2->transitionType, j+1+(T2->toState));
						T2 = T2->next;
					}
					addToList(stack, getLastStateStruct(&stack), 'E', j+1);
					
					stack->startState = i;
					stack->acceptState = j+1;
					break;
				
				// Kleene star case
				case '*':
					//push(NFA that accepts L(nFA) start);
					if (stack == NULL) {
						printf("not valid regular expression\n");
						if (stack != NULL) {
						freeStructs(&stack);
						}
						exit(0);
					}
					
					T1 = stack->list;
					stackPop(&stack);
					
					stackPush(&stack, 0, 0);
					
					i = getLastStateStruct(&stack);
					
					addToList(stack, i, 'E', i+1);

					while (T1 != NULL) {
						addToList(stack, i+(T1->fromState), T1->transitionType, i+(T1->toState));
						T1 = T1->next;
					}
					
					j = getLastStateStruct(&stack);
					addToList(stack, j, 'E', i+1);
					stack->startState = i;
					stack->acceptState = i+1;
					
					break;
					
				default:
					//push(NFA that accepts a single character c);
					i = getLastStateStruct(&stack);
					stackPush(&stack, i, i+1);
					addToList(stack, i, FA[c], i+1);
					break;
			}
		}
		//printStack(stack);
		//printStructs(&stack);
		c++;
	}
	
	// find largest accept state (which would be the accept state of the RE)
	nFA = stack;
	int max = nFA->acceptState;
	while (nFA->next != NULL) {
		if (max < nFA->acceptState) {
			max = nFA->acceptState;
		}
		nFA = nFA->next;
	}
	// print NFA
	printf("\nStart: q%d\nAccept: q%d\n", nFA->startState, max);
	printStructs(&stack);
	// clean up memory
	freeStructs(&stack); 
}

