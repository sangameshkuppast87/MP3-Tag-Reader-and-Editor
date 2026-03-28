#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "mp3_header.h"

//Function to edit the tags of the MP3 file
void mp3_edit(char* argv[], int index)
{
        FILE* fptr = fopen("temp.mp3", "w");
        FILE* qptr = fopen(argv[4], "r");

	if(fptr != NULL && qptr != NULL)
	{
		//Reading and copying the 10 bytes of header content
		char header[10];
		fread(header, sizeof(header), 1, qptr);
		fwrite(header, sizeof(header), 1, fptr);

		//Creating the string array to compare the frame tags according to the index
		char tags[6][5] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
		
		char *tag_names[]  = { "Title", "Artist", "Album", "Year", "Genre", "Comment" };

		printf("+==========================================================================+\n");
		printf("|%-28sSelect Edit Option%-28s|\n", "", "");
		printf("+==========================================================================+\n");
		printf("|%-24sSelect %s Change Option%-24s|\n", "", tag_names[index], "");
		printf("+==========================================================================+\n");
		printf("|%-23s%10s ➤  %-20s%-17s|\n", "", tag_names[index], argv[3], "");
		printf("+==========================================================================+\n");

		int flag = 0;
		//Running the loop for 6 times to deal with the 6 tags
		for(int i = 0; i < 6; i++)
		{
			char tag[5];
			fread(tag, 4, 1, qptr);
			tag[4] = '\0';
			//If the user entered tag matches with the string array edit the respective tag
			if(strcmp(tag, tags[index]) == 0 && flag == 0)
			{
				//Writing the Frame header to the temporary file
				fwrite(tag, 4, 1, fptr);

				int size1;
				//Reading the size from original file
				fread(&size1, sizeof(int), 1, qptr);
				int new_size = convert(size1);

				int size2 = strlen(argv[3]) + 1;
				//Converting from little endian to big endian
				int new_size2 = convert(size2);
				//Writing the new size to temporary file
				fwrite(&new_size2, sizeof(new_size2), 1, fptr);
				fseek(fptr, 3, SEEK_CUR);

				//Writing the edited tag content to file
				fwrite(argv[3], size2 - 1, 1, fptr);
				//Skipping the size + flag bytes in the original file
				fseek(qptr, new_size + 2, SEEK_CUR);
				flag = 1;
			}
			else
			{
				//Writing the Frame header to the temporary file
				fwrite(tag, 4, 1, fptr);

				//Reading the size from original file and writing the size to temporary file
				int size;
				fread(&size, sizeof(int), 1, qptr);
				fwrite(&size, sizeof(int), 1, fptr);
				int new_size = convert(size);

				fseek(fptr, 3, SEEK_CUR);
				fseek(qptr, 3, SEEK_CUR);

				//Reading tag content from original file and writing it to temporary file
				char content[new_size - 1];
				fread(content, sizeof(content), 1 ,qptr);
				fwrite(content, sizeof(content), 1 ,fptr);
			}
		}

		//Copying the rest of the file content
		int ch;
		while((ch = fgetc(qptr)) != EOF)
		{
			fputc(ch,fptr);
		}

		fclose(fptr);
		fclose(qptr);

		char old_file_name[strlen(argv[4])];
		//Copying the original file name string
		strcpy(old_file_name, argv[4]);

		//Deleting the original file
		remove(argv[4]);


		//Renaming the temporary file as original file
		rename("temp.mp3", argv[4]);
		
		printf("|%-23s%s Changed Successfully! 🚀 %-20s|\n", "", tag_names[index], "");
		printf("+==========================================================================+\n");
	}
	else
	{
		printf("File not found\n");
	}

}
