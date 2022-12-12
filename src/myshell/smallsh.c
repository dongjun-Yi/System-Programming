#include "smallsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


char* prompt = "Command> ";

static char inpbuf[MAXBUF];
static char tokbuf[2 * MAXBUF];
static char* ptr = inpbuf;
static char* tok = tokbuf;

int userin(char* prompt);
void procline(void);
int gettok(char** outptr);
int isarg(char c);
void runcommand(char* cline[], int where);
void sig_ignore(int);
int internal_command(char* cline[]);
void external_command(char* cline[], int where);

int main(void)
{
	signal(SIGINT, sig_ignore);
	while (userin(prompt) != EOF) {
		procline();
	}

	return 0;
}

void sig_ignore(int){
	printf("\n%s", prompt);
	fflush(stdout);
}

int userin(char* p)
{
	printf("%s", p);

	int c;
	int count = 0;

	ptr = inpbuf;
	tok = tokbuf;

	while (1) {
		if ((c = getchar()) == EOF)
			return EOF;

		if (count < MAXBUF)
			inpbuf[count++] = c;

		if (c == '\n' && count < MAXBUF) {
			inpbuf[count] = '\0';

			return count;
		}

		if (c == '\n') {
			printf( "smallsh: input line too long \n" );
			count = 0;
			printf("%s", p);
		}
	}
}

void procline(void)
{
	char* arg[MAXARG + 1];
	int toktype;
	int narg;
	int type;

	narg = 0;

	while (1) {
		switch (toktype = gettok(&arg[narg])) {
		case REDIRECTION_INPUT:
		case REDIRECTION_OUTPUT:
		case REDIRECTION_PIPE:
		case ARG:
			if (narg < MAXARG)
				narg++;
			break;

		case EOL:
		case SEMICOLON:
		case AMPERSAND:
			if (toktype == AMPERSAND)
				type = BACKGROUND;
		   	else
				type = FOREGROUND;

			if (narg != 0) {
				arg[narg] = NULL;
				runcommand(arg, type);
			}

			if (toktype == EOL)
				return;

			narg = 0;
			break;
		}
	}
}

int gettok(char** outptr)
{
	int type;

	*outptr = tok;

	while (*ptr == ' ' || *ptr == '\t')
		ptr++;

	*tok++ = *ptr;

	switch (*ptr++) {
	case '\n':
		type = EOL;
		break;

	case '&':
		type = AMPERSAND;
		break;

	case ';':
		type = SEMICOLON;
		break;
	case '<':
		type=REDIRECTION_INPUT;
		break;
	case '>':
		type=REDIRECTION_OUTPUT;
		break;
	case '|':
		type=REDIRECTION_PIPE;
		break;

	default:
		type = ARG;
		while (isarg(*ptr))
			*tok++ = *ptr++;
	 }

	*tok++ = '\0';

	return type;
}

int isarg(char c)
{
	static char special[] = { ' ', '\t', '&', ';', '\n', '<', '>', '|' };
	int n = sizeof special;
	for (int i = 0; i < n; i++) {
		if (c == special[i])
			return 0;
	}

	return 1;
}

int join(char* cmd1[], char* cmd2[]){
	int status;
	switch(fork()){
		case -1:
			perror("fork");
			exit(-1);
		case 0:
			break;
		
		default:
			wait(&status);
			return status;
	}
	int fd[2];
	pipe(fd);
	
	switch(fork()){
		case -1:
			perror("fork");
			exit(-1);
		case 0:
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			
			execvp(cmd1[0], cmd1);
			perror("pipe");
			exit(-1);
		
		default:
			dup2(fd[0], 0);
			
			close(fd[0]);
			close(fd[1]);
			
			execvp(cmd2[0], cmd2);
			perror("pipe");
			exit(-1);
	}
}

int redirection_check(char* cline[]){
	for(int i=0; cline[i] != NULL; i++){
		if(!strcmp("<", cline[i])){
			cline[i] = NULL;
			int fd = open(cline[i+1], O_RDONLY, 0644);
			dup2(fd,0);
			close(fd);
			return TRUE;
		}
		
		if(!strcmp(">", cline[i])){
			cline[i] = NULL;
			int fd = open(cline[i+1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			dup2(fd,1);
			close(fd);
			return TRUE;
		}
		
		if(!strcmp("|", cline[i])){
			cline[i] = NULL;
			join(&cline[0], &cline[i+1]);
			return FALSE;
		}
	}
	return TRUE;
}

void standard_io(void){
	close(0);
	close(1);
	open("/dev/tty", O_RDONLY);
	open("/dev/tty", O_WRONLY);
}

void runcommand(char* cline[], int where)
{
	if(!internal_command(cline)){
		if(redirection_check(cline)){
			external_command(cline, where);
			standard_io();
		}
	}
}

void change_directory(char* dest){
	char buf[MAXPATHLEN];
	
	if(dest == NULL){
		strcpy(buf, (char *) getenv("HOME"));
	}else{
		if(chdir(dest)<0)
			perror(dest);
	}
}

int internal_command(char* cline[]){
	if(!strcmp(cline[0], "cd")){
		change_directory(cline[1]);
		return TRUE;
	}else if(!strcmp(cline[0], "exit")){
		exit(0);
	}
	return FALSE;
}



void external_command(char* cline[], int where)
{
	
	pid_t pid;
	int status;

	switch (pid = fork()) {
	case -1:
		perror("smallsh");
		exit(0);

	case 0:
		execvp(cline[0], cline);
		perror(cline[0]);
		exit(1);
	}

	if (where == BACKGROUND) {
		printf("[processs id %d]\n", pid);
		return;
	}
	waitpid(pid, &status,0);
}