#pragma once

typedef struct Node{
	char digit;
	struct Node *next_node;
    struct Node *prev_node;
}Node;
typedef struct Bignumber{
	Node *head;
	Node *tail;
	int size;
}Bignumber;

Node *new_Node(char c);
Bignumber *new_Number();
void add_to_b(Bignumber **head_ref, char c);
void add_to_e(Bignumber **tail_ref, char c);
Bignumber *get_number(char c);
void print_number(Bignumber *number);
void free_list(Bignumber *list);
void swap(Bignumber **f, Bignumber **s);
void free_node(Node **cur);