#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max(x,y) ((x) > (y)  ? (x) : (y))
#define MAX_WORD_SZ 256

typedef struct Node {
	struct Node * child[2];
	char * key;
	int height;
}Node;

void destroy_tree(Node * t);
int get_height(Node * t);
char * search_val(Node * t, char * key, int (*compare)(const char * a, const char * b));

void adjust_height(Node * t);
void rotate(Node ** root, int d);
void rebalance(Node **t);
void insert(Node **t, char * key);
void print_in_order(Node * t);
void print_reverse_order(Node * t);
void check(Node * root);

Node * search_node(Node * t, char * key);
