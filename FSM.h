#ifndef _FSM_H__
#define _FSM_H__

#include "Xin.h"

typedef struct FSM_s
{
  uint8_t event;               /*触发事件*/
  uint8_t CurState;            /*当前状态*/
  void (*eventActFun)(void *); /*动作函数*/
  uint8_t NextState;           /*跳转状态*/

  struct FSM_s *Next;
}FSM_t;

void Fsm_Create(FSM_t *fsm, uint8_t Event,
                uint8_t Current_System_State,
                void (*EventActFunc)(void *)
                )；
void Fsm_Process(void)；
#endif
