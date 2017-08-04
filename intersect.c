#include <sys/stat.h>
#include "avlIntersect.h"

void usage(const char * input);
FILE * check_file(char * input);
int check_file_size(const char * filename);
int compare_words(const char * a, const char * b);

void find_smallest_file(int argc, char **argv)
{
	int size = MAX_WORD_SZ, file_size;
	int index = 1;
	for (int x = 1; x < argc; x++)
	{
		//USING THE STAT STRUCT
		if ( size > (file_size = check_file_size(argv[x]) ) )
		{
			index = x;
		}
	}
	char * temp;
	if ( index != 1)
	{
		temp = argv[1];
		argv[1] = argv[index];
		argv[index] = temp;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
		usage(argv[0]);
	
	//FIND SMALLEST FILE AND SWAP WITH argv([1])
	
	find_smallest_file(argc, argv);
	//Initialize the tree array
	Node *root [argc - 1];
	for ( int x = 0; x < (argc - 1); x++)
	{
		root[x] = NULL;
	}
	
	
	char *match, word [MAX_WORD_SZ];
	int n, file_num = 0;
	//Files start with 1 
	for (int file = 1; file < argc; file++)
	{
		printf("\nOpening file: %s \n", argv[file]);
		FILE * input = check_file(argv[file]);

		while ( (n = fscanf(input, "%256s", word)) != EOF ) 
		{
			if (file == 1)
			{
				//Fill the first BST with the words of the first file
				insert(&root[file_num], word);
			}
			else
			{
				//Fill the second BST with matching words from the previous BST.
				match = search_val(root[file - 2], word, compare_words);
				if (match)
				{
					insert(&root[file - 1], match);
				}
			}
		}
	
		//IF statement to destroy tree if
		//printf("\nend of file: [%d][%d]\n", file, argc);
		fclose(input);
		file_num++;
	}
	
	printf("\nLETS PRINT FINAL BST\n\n");
	print_in_order(root[file_num - 1]);
	if ( !root[file_num - 1])
		printf("There are no matching words in these files!");
	printf("\n");
	
	//DESTROY / FREE The previously used trees!!!
	for ( int x = 0; x < argc - 1; x++)
	{
		destroy_tree(root[x]);
	}
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

FILE * check_file( char * filename)
{
	FILE * input = fopen(filename, "r");
	
	//printf("checking to open file\n");
	if( input )
		return input;
	else
		return NULL;
}

void usage(const char * input)
{
	fprintf(stderr, "usage error: %s [filename][...] \n", input);
	exit(1);
}

int  check_file_size(const char * filename)
{
	//GET THE SIZE OF THE FILE AND EXIT IF == 0
	struct stat *buff;
	int file_size;
	buff = malloc(sizeof(struct stat));
	
	stat(filename, buff);
	if ((file_size = buff->st_size) == 0)
	{
		printf("The file %s is unreadable or empty\n", filename);
		free(buff);
		usage(filename);
	}
	free(buff);
	
	return file_size;
}
