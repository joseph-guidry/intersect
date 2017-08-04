#include <assert.h>
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
	//printf("here | t = NULL %c \n", t != NULL ? 'T':'F');
	//printf("key: %s\nt->key: %s\n", key, t->key);
	
	
	
	if ( t == NULL)
	{	//REached end of search -- Not in the tree;
		//printf("t = NULL\n");
		return NULL;
	}	
	//printf("\nword: [%s]\n", key);
	//printf("match: [%s]\n\n", t->key);
	int order = compare(key, t->key);
	//printf("order = %d \n", order);
	if ( order < 0)
	{
		//printf("return: %s\n", key);
		return t->key; //return the char * ???
	}
	else 
	{
		//printf("return: t->key = %s| key = %s\n", t->key, key);
		//If the strcasecmp returns a positive number.
		return search_val(t->child[order], key, compare);
	}
}

Node * search_node(Node * t, char * key)
{
		int order = strcasecmp(key, t->key);
		if (!order)
		{
			return t;
		}
		else if (order > 0) //Use the compare function
		{
			search_node(t->child[0], key);
		}
		else if (order < 0)
		{
			search_node(t->child[1], key);
		}
		else
			return NULL;
}


void adjust_height(Node * t)
{
	//Double check and adjust
	if(t != NULL)
		t->height = 1 + Max(get_height(t->child[0]), get_height(t->child[1]));
		
	/* 
	OLD STUFF
	if(t != NULL);
	
	t->height = 1 + Max(get_height(t->child[0]), get_height(t->child[1]));
	*/
	
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
		/* 
		OLD STUFF
		assert(*t); //Assumes malloc worked. -> insert appropriate checks
		*/
		(*t)->child[0] = NULL;
		(*t)->child[1] = NULL;
		
		
		(*t)->key = malloc(MAX_WORD_SZ);
		strcpy((*t)->key, key);
		//printf("The inserted word is [%s]\n", (*t)->key);
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
		printf("%s ", t->key);
		print_in_order(t->child[1]);
	}
}

void print_reverse_order(Node * t)
{
	if ( t != NULL)
	{
		print_reverse_order(t->child[1]);
		printf("%s ", t->key);
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
		assert(root->height == 1 + Max(get_height(root->child[0]), get_height(root->child[1])));
	}
}

