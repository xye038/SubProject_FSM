#include "Xin.h"

static struct FSM_s *Head_FSM = NULL;

void Fsm_Create(FSM_t *fsm, uint8_t Event,
                uint8_t Current_System_State,
                void (*EventActFunc)(void *)
                )
{
   fsm->CurState = Current_System_State;
   fsm->eventActFun = EventActFunc;       //回调函数需用户自己实现
   fsm->event = Event;
   fsm->Next = Head_FSM;
   Head_FSM = fsm;
  }

void Fsm_Process(void)
{
  struct FSM_s *pass_fsm;
  for(pass_fsm = Head_FSM; pass_fsm != NULL; pass_fsm = pass_fsm->Next)
  {
    if((pass_fsm->CurState==System_State)&&(pass_fsm->event==Trigger_Event))
    {
      pass_fsm->eventActFun(NULL);
    }
  }
}

void FSM_INIT(void)
{
  /*
  Fsm_Create(&Main_CodeQ,Set_LongDown_Event,Main_State,MainState_SetLongDownEvent_Func);
  Fsm_Create(&MaxShow_CodeQ,Set_LongDown_Event,Max_Range_Show_State,MainState_SetLongDownEvent_Func);
 */
}


