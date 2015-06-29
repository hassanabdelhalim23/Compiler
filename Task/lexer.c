#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_types.h"

#define TOKEN_LENGTH 40
#define SHIFT 4
#define SIZE 1000

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyleng;

static int hash (char *key);
void insert(char *name, int length, int line_number, int type);
void display_symbol_table();

// // // // // // // // // // // // 

typedef struct LinkedList { 
     int line_number;
     struct LinkedList * next;
     int type;
} *LinkedList;

typedef struct HashLinkedList { 
     char token_value[TOKEN_LENGTH];
     LinkedList lines;
     int token_type;
     struct HashLinkedList *next;
} *Node;


static Node symbol_table[SIZE];
// // // // // // // // // // // // 

// char *data_types[] = {NULL, "Code for VOID", "Code for int", "Code for float", "Code for WHILE", "Code for IF", "Code for (",
// 					"Code for )", "Code for {", "Code for }", "ptr to symbol table entry for ", "ptr to integer table entry for ",
// 					"ptr to float table entry for ", "Code for =", "Code for ==", "Code for >", "Code for >=", "Code for <",
// 					"Code for <=", "Code for -", "Code for +", "Code for *", "Code for /", "Code for //"};

int main(void) {
	int token, number_of_tokens = 0, line_number, length = 0;
	char *text;

	printf("\t-----------\t\t-----------\t\t------\n");
	printf("\tToken Class\t\tToken Value\t\tLength\n");
	printf("\t-----------\t\t-----------\t\t------\n");

	token = yylex(); 	// Returns the value returned from the lex file of the certain RegExp matched
					  	// for example returns '3' if the keyword 'float' was matched
	while(token) {
		if(token != COMMENT) {
			line_number = yylineno;
			length = yyleng;
			text = yytext;
			if(token == INT_VAL) {
				insert(text, length, line_number, INT_VAL);
			}
			if(token == FLOAT_VAL) {
				insert(text, length, line_number, FLOAT_VAL);
			}
			printf("%d\t%d\t\t\t%s\t\t\t%d\n", line_number, token, text, length);
			number_of_tokens++;
		}
		token = yylex();
	}
	printf("Number of Tokens: %d\n", number_of_tokens);
	display_symbol_table();
	return 0;
}

static int hash (char *key) {
	int temp = 0;
	int i = 0;
	while (key[i] != '\0') { 
		temp = ((temp << SHIFT) + key[i]) % SIZE;
		++i;
	}
	return temp;
}

void insert(char *name, int length, int line_number, int type) { 
	int h = hash(name);
	Node node =  symbol_table[h];
	while ((node != NULL) && (strcmp(name,node->token_value) != 0))
		node = node->next;
	if (node == NULL) { 
		node = (Node) malloc(sizeof(struct HashLinkedList));
		strncpy(node->token_value, name, length);
		node->token_type = type;
		node->lines = (LinkedList) malloc(sizeof(struct LinkedList));
		node->lines->line_number = line_number;
		node->lines->next = NULL;
		node->next = symbol_table[h];
		symbol_table[h] = node; 
	} else { 
		LinkedList linked_list = node->lines;
		while (linked_list->next != NULL) 
			linked_list = linked_list->next;
		linked_list->next = (LinkedList) malloc(sizeof(struct LinkedList));
		linked_list->next->line_number = line_number;
		linked_list->next->next = NULL;
	}
}


void display_symbol_table() {
	printf("\n\n\n\t\t\tSymbol Table Entries\n\n");
	int i;
	printf("\t-----------\t\t-----------\t\t-----------\n");
	printf("\tToken Class\t\tToken Value\t\tLine Number\n");
	printf("\t-----------\t\t-----------\t\t-----------\n");
	for (i=0; i < SIZE; ++i) { 
		if (symbol_table[i] != NULL) { 
			Node node = symbol_table[i];
	  		while (node != NULL) { 
	  			if (node->token_type == INT_VAL)
			      	printf("\t%d\t", INT_VAL);
			    if (node->token_type == FLOAT_VAL)
			    	printf("\t%d\t", FLOAT_VAL);
	  			LinkedList ll = node->lines;
			    printf("\t\t%s\t\t\t",node->token_value);	    		
			    while (ll != NULL) { 
			    	printf("%d\n",ll->line_number);
					ll = ll->next;
			    }
			    printf("\n");
		    	node = node->next;
			}
		}
	}
} 