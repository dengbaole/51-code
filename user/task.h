#ifndef _TASK_H
#define _TASK_H
#include <REGX52.H>


int get_task_state(void);
void fsmTask(char ch);
void task_init(void);
void NixieTaskInit(void);


#endif // !_TASK_H
