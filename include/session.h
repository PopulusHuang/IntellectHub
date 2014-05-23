#ifndef _SESSION_H_
#define _SESSION_H_
#define SESSION_SIZE 20
#define SESSION_TIMEOUT 60*60  /* 60 minutes */ 
#define TIME_SIZE 20
int ssesion_start();
int session_check(char *session_id);
int session_destory(char *session_id);
#endif
