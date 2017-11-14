#ifndef CLIENTPUSH_H
#define CLIENTPUSH_H

#include <string.h>

#define UFTP_USERNAME "USER"
#define UFTP_PASSWORD "PASS"
#define UFTP_EXIT_CONNECTION "QUIT"
#define UFTP_CHANGE_WORKING_DIRECTORY "CWD /\n"     
#define UFTP_CHANGE_TO_PARENT_DIRECTORY "CDUP"
#define UFTP_DELETE_FILE "DELE"    
#define UFTP_AUTHENTICATION "AUTH*"   
#define UFTP_CLEAR_COMMAND_CHANNEL "CCC*"    
#define UFTP_APPEND "APPE"      
#define UFTP_ABORT_FILE_TRANSFER "ABOR"    
#define UFTP_RETURN_FILE_LIST "MLST"    
#define UFTP_VERBS_USERNAME  "USER"
#define UFTP_VERBS_PASSWORD  "PASS"    
#define UFTP_SEND_FILE "STOR"
#define UFTP_GET_FILE "RETR"
#define UFTP_FILE_TYPE "TYPE"
#define UFTP_PASIVE_MODE "PASV\n"

/*
 *@Author : Faisal Burhan abdu.
 *@Version : 1.1.0v
 *@Date : 26 | OCT | 2017
 *@File: header file
 */

  
  //declare user specific data types  
  typedef enum { false, true } Boolean;
  typedef char* String;

  struct loger{
     const char scon[20];
     char conErrMsg[64];
  };


     

  
/**
  *Initiate and establishe (TCP/IP) Socket connection to the remote server.
  *@param file, for storing connection logs, 
  */
  void createConn(int Socket, const char *addr, int port, FILE *file);
/**
  *handles authentication procedures to the remote server.
  *@param socket  for storing a socket descriptor
  *@param userName for storing user name or authetication ID 
  *@param password for storing user password in string value
  *@param file for logging connection process. 
  */
  int authProcedure(int Socket, String userName, String password);
/**
  *Initiates passive mode for data transfer.
  *@param socket  for storing a socket descriptor
  *@param arg for storing a pasive command in a string form.
  *@param file for logging connection process. 
  */
  int pasiveMode(int Socket, String cmd);
/**
  *below is a variadic fucntion that takes a variable number of arguments
  *to be passed into the function's main body for processing.
  *@param socket  for storing a socket descriptor
  *@param fmt for storing a formatted word that to be sent as command to remote server.
  *@param file for logging connection process. 
  */
  int send_str(int socket, const char *fmt, ...);
/**
  *process and sends file to a the remote server
  *@param socket  for storing a socket descriptor
  *@param file for holding a content file to be sent / received from a remote server. 
  */
  int send_file(int socket, FILE *f);
/**
  *close open connection to a specified server
  *@param socket  for storing a socket descriptor
  *@param file for logging connection process. 
  */  
  int clearCon(int socket);

#endif //CLIENTPUS_H