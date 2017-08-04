#include "avlIntersect.h"

void destroy_tree(Node * t)
{
	if (t != NULL)
	{
		destroy_tree(t->child[0]);
		destroy_tree(t->child[1]);
		free(t->key);
		free(t);
	}
}

int get_height(Node * t)
{
	if (t != NULL)
	{
		return t->height;
	}
	else
	{
		return 0;
	}
}

char * search_val(Node * t, char * key, int (*compare)(const char * a, const char * b))
{
	//This function takes a root node, and a key word to search for.
	//Returns the word that was succesfully matched, else it returns nothing.
	
	if ( t == NULL)
	{	//Reached end of search -- Not in the tree;
		return NULL;
	}	
	
	//If there are leaf nodes remaining to search.
	int order = compare(key, t->key);
	
	//If compare function returns as equal (-1)
	if ( order < 0)
	{
		//printf("return: %s\n", key);
		return t->key; //return the char * ???
	}
	//Else the compare function returns either greater than (1) or less than (0).
	else 
	{
		return search_val(t->child[order], key, compare);
	}
}

void adjust_height(Node * t)
{
	//Double check and adjust
	if(t != NULL)
		t->height = 1 + Max(get_height(t->child[0]), get_height(t->child[1]));
}

void rotate(Node ** root, int d)
{
	Node * oldRoot;
	Node * newRoot;
	Node * oldMiddle;
	
	oldRoot = *root;
	newRoot = oldRoot->child[d];
	oldMiddle = newRoot->child[!d];
	
	oldRoot ->child[d] = oldMiddle;
	newRoot->child[!d] = oldRoot; 
	*root = newRoot;
	
	//Adjust heights after rotation
	adjust_height((*root)->child[!d]); 	//old
	adjust_height(*root);				//new
}

void rebalance(Node **t)
{
	int d;
	
	if (*t != NULL)
	{
		for (d = 0; d < 2; d++)
		{
			if (get_height((*t)->child[d]) > get_height((*t)->child[!d]) + 1)
			{
				if( get_height((*t)->child[d]) > get_height((*t)->child[!d]))
				{
					rotate(t, d);
				}
				else
				{
					rotate(&(*t)->child[d], !d);
					rotate(t, d);
				}
				
				return;
			}
		}
		adjust_height(*t);
	}
}

void insert(Node **t, char * key)
{
	if (*t == NULL)
	{
		//printf("here making new BST node\n");
		*t = malloc(sizeof(struct Node));
		if (t == NULL)
		{
			fprintf(stderr, "Memory error\n");
			return;
		}
		
		(*t)->child[0] = NULL;
		(*t)->child[1] = NULL;
		
		//Insert the word into a new BST.
		(*t)->key = malloc(MAX_WORD_SZ);
		strcpy((*t)->key, key);
		(*t)->height = 1;
		
		return;
	}
	else if ( (strcasecmp(key, (*t)->key))  == 0)
	{
		return;
	}
	else
	{
		insert(&(*t)->child[strcasecmp(key, (*t)->key) > 0 ? 1: 0], key);
		rebalance(t);
		return;
	}
}

void print_in_order(Node * t)
{
	if ( t != NULL)
	{ 	
		print_in_order(t->child[0]);
		printf("[%s]\n", t->key);
		print_in_order(t->child[1]);
	}
}

void print_reverse_order(Node * t)
{
	if ( t != NULL)
	{
		print_reverse_order(t->child[1]);
		printf("[%s]\n", t->key);
		print_reverse_order(t->child[0]);
	}
}

void check(Node * root)
{
	int i;
	if ( root != NULL)
	{
		for ( i = 0; i < 2; i++)
		{
			check(root->child[i]);
		}
		root->height == 1 + Max(get_height(root->child[0]), get_height(root->child[1]));
	}
}

