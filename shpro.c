/*
 ============================================================================
 Name        : shpro.c
 Author      : mahendra pratap singh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <unistd.h>
#include "time.h"
#include <fcntl.h>
#include "list.h"

#define M 100
#define N 100


int nshell=0;





void callcopy(char incmdparts[M][N])
{
	int ret =0;
	ret = fork();
	if(ret == 0){
		char cmd1[1000],cmd2[1000],cmd3[1000];
		char buff[500];
		getcwd(buff,sizeof(buff));
		puts(buff);
		memset(cmd1,0,sizeof(cmd1));
		memset(cmd2,0,sizeof(cmd2));
		memset(cmd3,0,sizeof(cmd3));
		sprintf(cmd1,"%s/%s",buff,incmdparts[0]);
		sprintf(cmd2,"%s",incmdparts[1]);
		sprintf(cmd3,"%s",incmdparts[2]);
		int ret = execlp(cmd1,cmd1,cmd2,cmd3,NULL);
		if(ret == -1){
			perror("\nOur path not found !!! ");

			struct node *ptr = head;

			while(ptr != NULL) {
				char bufff[1000];
				memset(buff,0,1000);
				sprintf(buff,"%s/%s",ptr->data,incmdparts[0]);
				int ret1 = execlp(cmd1,cmd1,cmd2,cmd3,NULL);
				sleep(1);
				if(ret1 != -1)
				{
					break;
				}
				ptr = ptr->next;
			}


		}else {
			printf("exec successfull");
		}
	}else{
		puts("\nparent process\n");
		wait(NULL);
	}

	return;
}
void callcreatefile(char incmdparts[M][N])
{
	double time = 0;
	clock_t begin = clock();
	int cmd = atoi(incmdparts[1]);
	char fileName[100] = {0};
	char BUFF[1024]; // 1KB
	int Count = 0;
	switch(cmd)
	{
	case 1:

		Count = 1024;

		break;
	case 2:

		Count = 1024*10;
		break;
	case 3:

		Count = 1024*100;
		break;
	default:
		printf(" Invalid option");
		return;

	}

	int des =  open(incmdparts[2], O_CREAT | O_WRONLY | O_EXCL , 0700);
	if(des == -1){
		perror("Returned error");
		return;
	}

	for(int i = 0 ; i<Count; i++)
	{

		if(sizeof(BUFF) != write(des, BUFF, sizeof(BUFF)))
		{
			perror("Write error");
			return;
			break;
		}

	}

	close(des);
	clock_t end = clock();
	time = (double)(end-begin)/CLOCKS_PER_SEC;
	printf(" File created succesfully and time taken = %lf second",time);

	return;
}
void callcd(char incmdparts[M][N])
{

	int ret = chdir(incmdparts[1]);
	if(ret == -1){
		perror("\nerror : ");
	}

	return;
}
void callpwd()
{
	char buff[500];
	memset(buff,0,sizeof(buff));
	getcwd(buff,sizeof(buff));
	puts(buff);

	return;
}


void callpushd(char incmdparts[M][N])
{

	push(incmdparts[1]);

	int ret = chdir(incmdparts[1]);
	if(ret == -1){
		perror("\nerror : ");
	}


	return;
}

void callpopd()
{
	char buff[500];
	memset(buff,0,sizeof(buff));
	getcwd(buff,sizeof(buff));

	popTop();

	return;
}

void callpath(char incmdparts[M][N])
{

	if(strcmp("+",incmdparts[1])==0){
		push(incmdparts[2]);
	}else if(strcmp("-",incmdparts[1])==0){
		popKey(incmdparts[2]);

	}else
	{
		if(!isEmpty())
			printList();
		else
			puts("\nNo directory in the path\n");

	}

	return;
}


int mymain(int argc, char *argv[]) {
	printf("\033[2J\033[0;0H");
	printf("--------------------- DUMMY SHELL OS ELL 783 GROUP 6----------------------\n");

	int maxcmds=9;
	char * cmdlist[]={
			"cd",
			"copy",
			"path",
			"pushd",
			"popd",
			"newshell",
			"exit",
			"pwd",
			"createfile"};



	while(1){
		char incmd[1000];
		char incmdparts[M][N];
		memset(incmd,0,sizeof(incmd));
		memset(incmdparts,0,sizeof(incmdparts));
		printf("\n$");
		fflush(stdin);
		gets(incmd);
		char * token=NULL, *saveptr1=NULL, *str1=incmd;
		int count=0;
		for (count = 0 ; ; count++, str1 = NULL) {
			token = strtok_r(str1,(char *)" ", &saveptr1);
			if (token == NULL){

				break;
			}
			strcpy(incmdparts[count],token);
		}


		int cmdfound=-1;
		for(int i=0;i<maxcmds;i++){
			if(strcmp(incmdparts[0],cmdlist[i])==0){
				cmdfound=i;
				break;
			}
		}

		switch(cmdfound){
		case 0://cd
			callcd(incmdparts);
			break;
		case 1://copy
			callcopy(incmdparts);
			break;
		case 2://path
			callpath(incmdparts);
			break;
		case 3://pushd
			callpushd(incmdparts);
			break;
		case 4://popd
			callpopd();
			break;
		case 5://newshell
			//callnewshell();
			nshell++;
			mymain(argc,argv);
			break;
		case 6://exit
			puts("\n Exit Shell\n");
			if(nshell==0){
				exit(0);
			} else{
				nshell--;
			}
			break;
		case 7://pwd
			callpwd();
			break;
		case 8://pwd
			callcreatefile(incmdparts);
			break;
		default:
		{
			int ret = 0;
			char buffer[1000];
			memset(buffer,0,sizeof(buffer));
			if(find("/bin") != NULL){
				sprintf(buffer,"/bin/%s",incmdparts[0]);
				ret = fork();
				if(ret ==0){
					execlp(buffer,buffer,NULL);
				}else{
					wait(NULL);
				}
			}
			else

				puts("Invalid command");
		}
		}
	}

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {

	mymain(argc, argv);
}
