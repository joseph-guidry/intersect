#include "avlIntersect.h"


void usage(char * input);
FILE * check_file(char * input);
int compare_words(const char * a, const char * b);

int main(int argc, char **argv)
{
	if (argc < 2)
		usage(argv[0]);
	
	//Initialize the tree array
	
	Node *root [argc - 1];
	for ( int x = 0; x < (argc - 1); x++)
	{
		root[x] = NULL;
	}
	
	//OLD STUFF
	//Node *root = NULL;
	
	char *match, word [40];
	int n;
	//Files start with 1 
	for (int file = 1; file < argc; file++)
	{
		printf("\nOpening file: %s \n", argv[file]);
		FILE * input = check_file(argv[file]);

		while ( (n = fscanf(input, "%s", word)) != EOF ) 
		{
			//printf("key: [%s]|root -> key: [%s]\n", word, root == NULL ? "nothing" : root->key);
			//FUNCTION TO TRIM PUNCUATION OFF
			if (file == 1)
			{//Fill the first BST with the words of the first file
				insert(&root[0], word);
				
				//printf("LETS PRINT THE 1st BST\n");
				//print_in_order(root[0]);
				//printf("\n");
			}
			else
			{
				//printf("\nword: [%s]\n", word);
				match = search_val(root[0], word, compare_words);
				//printf("match: [%s]\n\n", match);
				if (match)
				{
					insert(&root[1], match);
				}
			}
			//printf("here (*t)-> key: [%s]\n", root->key );
		}
	
		fclose(input);
		//printf("LETS PRINT THE BST\n");
		//print_in_order(root[1]);
		//printf("\n");
		
	}
	printf("\nLETS PRINT FINAL BST\n");
	print_in_order(root[1]);
	printf("\n");
	
}

int compare_words(const char * a, const char * b)
{
	int value = strcasecmp(a, b);
	//Return negative (-1) to indicate a match
	if ( !value )
		return -1;
	else if ( value > 0)
		return 1;
	else
		return 0;
}	

void usage(char * input)
{
	fprintf(stderr, "usage error: %s [filename] \n", input);
	exit(1);
}


FILE * check_file( char * filename)
{
	FILE * input = fopen(filename, "r");
	//GET THE SIZE OF THE FILE AND EXIT IF == 0
	//USING THE STAT STRUCT
	/*
		printf("The file %s is unreadable or empty\n", filename);
		usage(filename);
		
	*/
	printf("checking to open file\n");
	if( input )
		return input;
	else
		return NULL;
}


