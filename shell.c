//for help on using execvp():
//https://stackoverflow.com/questions/27541910/how-to-use-execvp

//current time adapted from:
//https://www.techiedelight.com/print-current-date-and-time-in-c/

//for help on using strtok()
//https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>
#include <sys/wait.h>


int main()
{

	//Welcome menu
	printf("Shell started. Enter a command ([cmd] [arg(s)]) or exit with 'stop'\n");

	//Variables
	pid_t pid;
	char* prompt;
	char* args[10];
	char* arg;

while(1)
{
	//Initialize time variables
	time_t now;
	time(&now);

	//extracting time without date from ctime
	char* time = ctime(&now) + 11;
        time[8] = '\0';

	//Input prompt
	printf("%s", time);
	prompt = readline("> ");
	add_history(prompt);

	//tokenizing
	arg = strtok(prompt, " ");
	args[0] = arg;

	int i = 1;
	while (arg != NULL) {
	arg = strtok(NULL, " ");
	args[i] = arg;
	i++;
	}
        args[i+1] = NULL;

	if (strcmp(prompt, "stop") == 0)
	{
		exit(0);
	}
	
	else {
		pid = fork();
		if (pid == 0) {
		execvp(args[0], args);
		printf("Invalid entry\n");
		}
		else {
		waitpid(pid, NULL, 0);
		}
	}
}
	return 0;
}
