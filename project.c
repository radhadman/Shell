/*Linux manual pages were helpful in implementing the system calls*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include <time.h>
	
	char input[100]; //buffers for user input
	char input2[100];
	char input3[100];
	int size; //used in truncate option
	struct stat buf; //used for file attributes

	int main(int argc, char *argv[]) {
	
	printf("Input options:\n"); //user interface
	printf("\tEnter 'cd' to change directory\n");
	printf("\tEnter 'pwd' to display present working directory\n");
	printf("\tEnter 'ls' to display current directory contents\n");
	printf("\tEnter 'rm' to delete a file\n");
	printf("\tEnter 'rmdir' to delete a directory\n");
	printf("\tEnter 'mv' to move/rename a file\n");
	printf("\tEnter 'tr' to truncate a file\n");
	printf("\tEnter 'op' to open a file\n");
	printf("\tEnter 'ck' to examine a file's attributes\n");
	printf("\tEnter 'c' to cancel an entry\n");

	while(1) {
	char *buffer = readline("> ");
		add_history(buffer);
		if (strcmp(buffer, "ls") == 0)
			system("ls"); //lists contents
		else if (strcmp(buffer, "cd") == 0)
	{
			printf("Enter a directory:\n");
			scanf("%s", input);
			chdir(input); //changes directory
	}

		else if (strcmp(buffer, "pwd") == 0)
			system("pwd"); //present working directory


		else if (strcmp(buffer, "mv") == 0) //rename file
	{
		printf("Enter a file to rename:\n");
		scanf("%s", input);
			if (strcmp(input, "c") == 0)
		{
			continue;
		}
		printf("Enter a new location:\n");
		scanf("%s", input2);
		sprintf(input3, "mv %s %s", input, input2);
			if (strcmp(input2, "c") == 0)
		{
			continue;
		}
			else if (access(input, F_OK) != -1) //if file exists
		{
			system(input3);
			printf("File moved\n");
		}
			else
			printf("%s could not be found in that directory\n", input);
	}

		else if (strcmp(buffer, "rm") == 0) //delete file option
	{
		printf("Enter a file to delete:\n"); 
		scanf("%s", input);
			if (strcmp(input, "c") == 0)
		{
			continue;
		}
			else if (access(input, F_OK) != -1)
		{
			remove(input);
			printf("%s", input);
			printf(" was removed\n");
		}
			else
			printf("%s could not be found in that directory\n", input); //error message for file not found
	}

		else if (strcmp(buffer, "rmdir") == 0) //delete directory
	{
		printf("Enter a directory to delete (directory must be empty):\n");
		scanf("%s", input);
			if (strcmp(input, "c") == 0)
		{
			continue;
		}
			else 
		{
			rmdir(input);
				if (rmdir(input) == 0) //returns true if file is deleted
			{
				printf("Directory was deleted");
			}
				else 
				printf("There was an issue removing the directory\n");
		}

	}

		else if (strcmp(buffer, "tr") == 0) //truncate file
	{
		printf("Enter a file to truncate:\n");
		scanf("%s", input);
			if (strcmp(input, "c") == 0)
		{
			continue;
		}
			else if (access(input, F_OK) != -1)
		{
			printf("Enter a new length (in bytes) for the file (some data may be lost after truncation):\n");
			scanf("%d", &size);
			sprintf(input2, "truncate -s %d", size);
                        system(input2);
			printf("File truncated");
		}
			else
		{
			printf("%s could not be found in that directory\n", input);
		}
	}

		else if (strcmp(buffer, "op") == 0) //open file 
	{
		printf("Enter a file to open:\n");
		scanf("%s", input);
			if (strcmp(input, "c") == 0)
		{
			continue;
		}
			else if (access(input, F_OK) != -1)
		{
			open(input, O_RDWR | O_CREAT, S_IRWXU); //includes flags 
					//O_RDWR: read and write permissions
					// O_CREAT, creates file if not found
					// S_IRWXU, user has read/write and execute permissions
		}
	}

		else if (strcmp(buffer, "ck") == 0) //check file 
	{
		printf("Enter a file to check:\n");
		scanf("%s", input);
		stat(input, &buf);
			if (strcmp(input, "c") == 0)
		{
			continue;
		}
			else if (access(input, F_OK) != -1)
		{
			//different attributes
			printf("File device major ID: %d\n", major(buf.st_dev));
			printf("I-node number: %ju\n", buf.st_ino);
			printf("Protection: %d\n", buf.st_mode);
			printf("Number of hard links: %lu\n", buf.st_nlink);
			printf("User ID of owner: %d\n", buf.st_uid);
			printf("Group ID of owner: %d\n", buf.st_gid);
			printf("Minor device ID (if special file): %d\n", minor(buf.st_rdev));
			printf("Total size of file in bytes: %jd\n", buf.st_size);
			printf("Blocksize for file system I/O: %jd\n", buf.st_blksize);
			printf("Number of 512B blocks allocated: %zd\n", buf.st_blocks);
			printf("Time of last access: %s", ctime(&buf.st_atime));
			printf("Time of last modification: %s", ctime(&buf.st_mtime));
			printf("Time of last status change: %s", ctime(&buf.st_ctime));
		}
	}

		else if (strcmp(buffer, "c") == 0) //returns to prompt
	{
			continue;
	}

		else //invalid input
	{
		printf("That is not a valid entry\n");
	}
}
	return 0;
}
