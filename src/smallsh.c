#include "smallsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char* prompt = "Command> ";

static char inpbuf[MAXBUF];
static char tokbuf[2 * MAXBUF];
static char* ptr = inpbuf;
static char* tok = tokbuf;

int userin(char* prompt);
void procline(void);
int gettok(char** outptr);
int isarg(char c);
int runcommand(char* cline[], int where);

int main(void)
{
	while (userin(prompt) != EOF) {
		procline();
	}

	return 0;
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
	static char special[] = { ' ', '\t', '&', ';', '\n' };
	int n = sizeof special;
	for (int i = 0; i < n; i++) {
		if (c == special[i])
			return 0;
	}

	return 1;
}

int runcommand(char* cline[], int where)
{
	pid_t pid;
	int status;

	switch (pid = fork()) {
	case -1:
		perror("smallsh");
		return -1;

	case 0:
		execvp(cline[0], cline);
		perror(cline[0]);
		exit(1);
	}

	if (where == BACKGROUND) {
		printf("[processs id %d]\n", pid);
		return 0;
	}

	int ret;
	while ((ret = wait(&status)) != pid && ret != -1);
	return (ret == -1 ? -1 : status);
}