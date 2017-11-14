/* INCLUDE STD HEADERS HERE */
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h> //for open
#include <unistd.h> //for close
#include <stdarg.h>
#include <sys/stat.h>
#include <errno.h>
#include <syslog.h>
#include <time.h>
/*INCLUDE USER DEFINED HEADERS HERE*/
#include "clientPush.h"

/*
 *@Author : Faisal Burhan abdu.
 *@Version : 1.1.0v
 *@Date : 26 | OCT | 2017
 *File : application.c 
 */

//Initialize globals.
char _userName[] = "USER kickoffc\n";
char _passWord[] = "PASS Africamoja7124\n";
char _PASIVE[] = "PASV\n";
char _changeDir[] = "CWD/\n";
const int _SIZE = 1023;
const int port = 21;
const char address[] = "67.225.129.56";
char buffer[1023];
FILE *logFile, *dsLog, *contentFile;  //ds: short for daemon system log
struct sockaddr_in sa;
struct logMessage *logIn;
int res;
int SocketFD;
int i = 0;
char command[256];


//START OF MAIN
int main(void) {
    //open daemon system logs file.
    dsLog = fopen("/root/Cellulant/Project2/UpdateStimesPrototype/controller/daemonAngel.log","a+");
    //process ID and Session ID
    pid_t pid, sid;      
    //Fork off the parent process
    pid = fork();
    if (pid < 0)
    {
      syslog (LOG_NOTICE, "error forking off the parent process failed...");
      fputs("error forking off the parent process failed...\n", dsLog);
      exit(EXIT_FAILURE);
    }syslog (LOG_NOTICE, "forking a parent process...");
      fputs("forking off the parent process...\n", dsLog);
    /* If we got a good PID, then
     * we can exit the parent process. 
     */
    if (pid > 0)
    {
      syslog (LOG_NOTICE, "error exiting the parent process...");
      fputs("error exiting the parent process...\n", dsLog);
      exit(EXIT_SUCCESS);
    }syslog (LOG_NOTICE, "exiting the parent process...");
      fputs("successfully exiting the parent process...\n", dsLog);
    /* Change the file mode mask */
    umask(0); 
    /* Open any logs here */  
    syslog (LOG_NOTICE, "changing the file mode mask...");
      fputs("changing the file mode mask...\n", dsLog);                  
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0)
    {
      /* Log the failure */
      syslog (LOG_NOTICE, "error creating a new SID for the child process...");
      fputs("error creating a new SID for the child process...\n", dsLog);
      exit(EXIT_FAILURE);
    }syslog (LOG_NOTICE, "creating a new SID for the child process...");
      fputs("creating a new SID for the child process...\n", dsLog);  
    //Change the current working directory 
    if ((chdir("/")) < 0)
    {
      /* Log the failure */
      syslog (LOG_NOTICE, "failed to change the current working directory...");
      fputs("failed to change the current working directory...\n", dsLog);
      exit(EXIT_FAILURE);
    }syslog (LOG_NOTICE, "changing the current working directory...");
      fputs("changing the current working directory...\n", dsLog);
    //Close out the standard logFile descriptors
    syslog(LOG_NOTICE,"entering main code...");
      fputs("entering main code...\n", dsLog);
    fclose(dsLog);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    closelog();
    //Daemon-specific initialization goes here   
    //Enter the DARKHOLE where time is... 
    while (1)
    {
      //Do some task here ...
      time_t rawtime;
      struct tm * timeinfo;
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      //open content file to read  in b_mode 
      contentFile = fopen("/root/Cellulant/Project2/UpdateStimesPrototype/controller/ffiletest.txt", "rb");
      //open log file
      logFile = fopen("/root/Cellulant/Project2/UpdateStimesPrototype/controller/daemonAngel.log","a+");
      //write a time stamp to the log file.
      fputs(asctime (timeinfo),logFile);
      //call for socket conection procedure 
      createConn(SocketFD,address,port,logFile);
      /*
       * initiating authentication to remote server
       * Note: 
       * In order to successfully login to the remote server,
       * socket descriptor, userName and password must be provided in the function's main logics.
       */
      if(authProcedure(SocketFD,_userName,_passWord)){ fputs("logging in to remote ftp server...\n",logFile); } 
      //change connection mode to pasive 
      if(pasiveMode(SocketFD,_PASIVE)){ fputs("turning on pasive mode...\n",logFile); }
       //initiate file transfer
       //catch some info. 
       if(send_file(SocketFD, contentFile)){ fputs("transfering file...\n",logFile); }                      
      // //exit remote connection
      if(clearCon(SocketFD)){ fputs("exiting remote connection...\n", logFile); }
      //safely close all open I/Os pipes.
      fclose(logFile);
      shutdown(SocketFD, SHUT_RDWR);
      close(SocketFD);
      // wait for n amount of seconds
      sleep(120);
    } 
   // Exit code 
   exit(EXIT_SUCCESS);
}  // END OF MAIN 

/* BEGIN: 
 * write user defined (functions) below 
 */

void createConn(int Socket,const char *addr, int port,FILE *file)
{
  Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  (Socket < 0)? fputs("Error creating socket to remote ftp server...\n",file): fputs("creating socket to remote ftp server...\n",file);
  memset(&sa, 0, sizeof sa);
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  res = inet_pton(AF_INET, addr, &sa.sin_addr);
  (connect(Socket, (struct sockaddr *)&sa, sizeof sa) == -1)? fputs("connection to remote server failed...\n",file) : fputs("connection to remote server established...\n",file);
}


int authProcedure(int Socket, String userName, String password)
{
  int push;
  if (Socket != -1)
  {
    bzero(buffer,_SIZE);
    push = write(Socket,buffer,strlen(strcpy(buffer,userName)));
    bzero(buffer,_SIZE);
    push = write(Socket,buffer,strlen(strcpy(buffer,password)));
  }
  return push;

}

int pasiveMode(int Socket, String cmd)
{ int pasive;
  if (Socket != -1)
  {
    bzero(buffer,_SIZE);
    pasive = write(Socket,buffer,strlen(strcpy(buffer,cmd)));
  }
  return pasive;
}

int send_str(int socket, const char* fmt, ...) {
    va_list args;
    char msgbuf[_SIZE];
    va_start(args, fmt);
    vsnprintf(msgbuf, sizeof(msgbuf), fmt, args);
    va_end(args);
    return send(socket, msgbuf, strlen(msgbuf), 0);
}

int send_file(int socket, FILE *f){
  char filebuf[_SIZE+1];
  int n, ret = 0;

  if (SocketFD != -1)
  {
    /* code */
    //change dir
  write(socket,buffer,strlen(strcpy(buffer,_changeDir)));
  while ((n=fread(filebuf, 1, _SIZE, f)) > 0)
  {
    int st = send(socket, filebuf, n, 0);
      if (st < 0)
      {
        //err(1, "send logFile error, errno = %d, %s", errno, strerror(errno));
        ret = -1;
        break;
      } else {
        filebuf[n] = 0;
        //info(1, " %d bytes sent", st);
      }
    }
  }     
    return ret;
}

int clearCon(int socket)
{
  int push;
  if (socket != -1)
  {
    bzero(buffer,_SIZE);
    push = write(socket,buffer,strlen(strcpy(buffer,UFTP_EXIT_CONNECTION)));
  }
  return push;
}
