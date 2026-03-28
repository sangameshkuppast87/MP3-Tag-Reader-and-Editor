#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"mp3_header.h"

//Function to validate the Command line arguments
int validate(int argc, char* argv[],char str[][10], int* index)
{
	int flag = 1;
	if(argc < 2 || argc > 5)					//Checks for count of CLA
		return 0;

	if(strcmp(argv[1], "--help") == 0)				//Checks for help token
	{
		help_menu();
		exit(0);
	}

	if(strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-v") != 0)		//Checks for view and edit token
		return 0;

	if(strcmp(argv[1], "-e") == 0)
	{
		if(argc < 5)
			flag = 0;

		if(argv[2] == NULL)
			return 0;
		
		int valid = 0;
		for(int i = 0; i < 6; i++)
		{
			if(strcmp(argv[2], str[i]) == 0)		//Checks for the correct tag token
			{
				valid = 1;
				*index = i;				//Getting the index of the tags to be edited
				break;
			}
		}

		if(valid == 0 || flag == 0)
			return 0;

		int len1 = strlen(argv[4]);
		if(strcmp((argv[4] + len1 - 4), ".mp3") != 0)
			return 0;
	}

	if(strcmp(argv[1], "-v") == 0)
	{
		if(argc < 3)
			return 0;
		int len2 = strlen(argv[2]);
		if(strcmp((argv[2] + len2 - 4), ".mp3") != 0)
			return 0;
	}

	return 1;
}


//Function to view the MP3 tags
void mp3_view(char* argv[])
{
	FILE* fptr = fopen(argv[2], "r");
	//Checking for presence of the file
	if(fptr == NULL)								
	{
		printf("File not found\n");
		exit(0);
	}

	//Reading the ID3 header
	char buffer[3];
	fread(buffer, sizeof(buffer), 1, fptr);
	buffer[3] = '\0';
	if((strcmp(buffer, "ID3")) == 0)
	{
		//Skipping the 7 bytes
		fseek(fptr ,7, SEEK_CUR);

		printf("+===========================================================================+\n");
		printf("|                       🎧 MP3 tag reader for ID3v2 🎧%-22s|\n","");
		printf("+===========================================================================+\n");

		int i = 6;
		//Running the loop 6 times to read the 6 tags
		while(i > 0)
		{
			//Reading the Frame header
			char tag[4];
			fread(tag, sizeof(tag), 1, fptr);
			tag[4] = '\0';

			//Reading the size
			int size;
			fread(&size, sizeof(int), 1, fptr);
			//Converting the size from big endian to little endian
			int new_size = convert(size);

			fseek(fptr, 3, SEEK_CUR);

			//Reading the content from header
			char content[new_size - 1];
			fread(content, sizeof(content), 1 ,fptr);
			content[new_size - 1] = '\0';

			//Comapring the tags with the 6 different tags and printing accordingly
			if (strcmp(tag, "TIT2") == 0)
				printf("|🎶 %-10s%-5s%-59s|\n","Title","➤", content);
			else if (strcmp(tag, "TPE1") == 0)
				printf("|🎤 %-10s%-5s%-59s|\n", "Artist", "➤", content);
			else if (strcmp(tag, "TALB") == 0)
				printf("|💿 %-10s%-5s%-59s|\n", "Album", "➤", content);
			else if (strcmp(tag, "TYER") == 0)
				printf("|📅 %-10s%-5s%-59s|\n", "Year", "➤", content);
			else if (strcmp(tag, "TCON") == 0)
				printf("|🎼 %-10s%-5s%-59s|\n", "Genre", "➤", content);
			else if (strcmp(tag, "COMM") == 0)
				printf("|📝 %-10s%-5s%-59s|\n", "Comment", "➤", content);
			i--;
		}
		fclose(fptr);
		printf("+===========================================================================+\n");

	}
	else
	{
		printf("It is not MP3 file\n");
		fclose(fptr);
		exit(0);
	}
}


//Function to convert the integer from Big endian to Little endain
int  convert(int size)
{
	unsigned char* ptr = (unsigned char*)&size;
	int s = sizeof(int);
	for(int i = 0; i  < s / 2; i++)
	{
		//Swaping the bytes
		char temp = ptr[i];
		ptr[i] = ptr[s - i - 1];
		ptr[s - i - 1] = temp;
	}
	return size;
}


//Function to print the help menu
void help_menu()
{
	
	printf("\n+================================================================================+\n");
	printf("|USAGE : ");
	printf("./a.out -e -t/-a/-A/-y/-c/-g 'new name' file.mp3%-24s|\n", "");
	printf("|%-8s./a.out -v%-62s|\n","","");
	printf("+================================================================================+\n");
	printf("|%-11sAllows to edit a tag%-49s|\n","-e","");
	printf("|%-11sModifies a Title tag%-49s|\n", "-t","");
	printf("|%-11sModifies a Artist tag%-48s|\n", "-a","");
	printf("|%-11sModifies a Album tag%-49s|\n", "-A","");
	printf("|%-11sModifies a Year tag%-50s|\n", "-y","");
	printf("|%-11sModifies a Comment tag%-47s|\n", "-c","");
	printf("|%-11sModifies a Genre tag%-49s|\n", "-g","");
	printf("|%-11sPrints version info%-50s|\n", "-v","");
	printf("+================================================================================+\n");
}
