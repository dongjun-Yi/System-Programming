#ifndef _SMALLSH_H_
#define _SMALLSH_H_

#define	EOL 		1		// 줄의 끝
#define ARG 		2		// 정상적인 인수
#define AMPERSAND 	3		// &
#define SEMICOLON 	4		// ;

#define MAXARG 		512		// 명령인수의 최대수
#define MAXBUF 		512		// 명령 입력행의 최대 길이

#define FOREGROUND 	0
#define BACKGROUND 	1
#define TRUE 1
#define FALSE 0
#define MAXPATHLEN 100

#define REDIRECTION_INPUT 5
#define REDIRECTION_OUTPUT 6
#define REDIRECTION_PIPE 7

#endif