Author: Faisal Burhan Abdu
Title: cellStartimes ftp daemon;

NOTE!

This section contains the main process that handles
a key role of fetching and establishing socket connection
to the remote server using ftp protocol.


PROGRAM EXECUTION FLOW:

STEP_1. create a background process.

STEP_2. establishing remote connection.

STEP_3. authenticate.

STEP_4. read local database for new available file(s).

STEP_5. send file to the remote server.

STEP_6. close connection.

STEP_7. sleep.

STEP_8. repeat STEP_2.

 
