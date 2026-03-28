/*
----------------------------------------------------------------------------------------------------------------
|Name:		Sangamesh Kuppast                                                                              |
----------------------------------------------------------------------------------------------------------------
|Date: 		28/10/2025                                                                                     |
----------------------------------------------------------------------------------------------------------------
|Description:	"MP3 Tag Reader"                                                                               |
|		-> This project is about an MP3 tag reader.                                                    |
|		-> It can view the tags such as Artist name, Title/Song name, Album, Year, Content type        |
|		   and Comments.                                                                               |
|		-> It can edit all the above mentioned tags accordin to user input.                            |
----------------------------------------------------------------------------------------------------------------
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mp3_header.h"

int main(int argc, char* argv[])
{
	//Creating a string array to store the tokens and also track the token using it's index.
	int index;
	char str[6][10] = {"-t", "-a", "-A", "-y", "-g", "-c"};

	//Validating the Command line arguments
	if(validate(argc, argv, str, &index))
	{
		if(strcmp(argv[1], "-v") == 0)			//If true view the tags
			mp3_view(argv);
		else if(strcmp(argv[1], "-e") == 0)		//If true edit the tags
			mp3_edit(argv, index);
	}
	else
	{
		//Printing error messages
		printf("Error: ");
		for(int i = 0; i < argc; i++)
		{
			printf("%s ",argv[i]);
		}
		printf(": INVALID ARGUMENTS\n");
		printf("USAGE :\n");
		printf("To see help menu pass like: ./a.out --help\n");
		printf("To view please pass like: ./a.out -v mp3filename\n");
		printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c 'New name' mp3filename\n");
	}
}
