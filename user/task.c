#include "task.h"
#include "nixie.h"
#include "separate_button.h"
#include "matrixkey.h"
#include "uart.h"
#include "delay.h"
#include "beep.h"

extern unsigned char KeyNum;
extern unsigned char button;
static void MyTask(char ch);
static void NixieTask(void);

typedef enum
{
	STATE_IDLE, 									//����״̬
	STATE_NIXIE,									//�ϴ�����״̬
	STATE_MATRIXKEY, 								//��������״̬
	STATE_MUSIC,									//ע��״̬
	STATE_MATCH,									//ƥ��״̬
	STATE_DELETE,									//ɾ��״̬
	STATE_STANDBY,
	STATE_WRITEFLASH,
	STATE_USBKEY,
	STATE_USER_TEST,
	STATE_ENROLL_NOCHECK_FINGER,
	STATE_MAX
} _FsmState; 

typedef enum
{
	NIXIE_STATE_IDLE,
	NIXIE_STATE_WORK,
	NIXIE_STATE_END,
	NIXIE_STATE_MAX
}_NixieState;





_FsmState get_state;
_NixieState get_Nixie_state;

int get_task_state(void)
{
	return get_state;
}




void fsmTask(char ch)
{
	MyTask(ch);
}
void task_init(void)
{
	get_state = STATE_IDLE;
	get_Nixie_state = NIXIE_STATE_IDLE;
}

static void MyTask(char ch)
{
    switch(get_state)
    {
        case STATE_IDLE:
			if(button == 4)
			{
				get_state = STATE_MUSIC;
			}
        	break;
        case STATE_NIXIE:
			NixieTask();
        	break;
		case STATE_MATRIXKEY:
			break;
		case STATE_MUSIC:

			break;
        default:
       		break;
    }

}


void NixieTaskInit(void)
{
	get_Nixie_state = NIXIE_STATE_IDLE;
}

static void NixieTask(void)
{
	switch(get_Nixie_state)
	{
		case NIXIE_STATE_IDLE:
		if(KEY1==0)
		{
			get_Nixie_state = NIXIE_STATE_WORK;
		}
		Nixie(1,2);
		break;
		case NIXIE_STATE_WORK:
		Nixie(1,1);
		if(KEY2==0)
		{
			
			get_Nixie_state = NIXIE_STATE_IDLE;
		}
		break;
		case NIXIE_STATE_END:
		get_state=STATE_IDLE;
		break;
	}

} 

