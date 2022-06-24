#include "event_demo.h"

EVENT_CB_S g_pevent1;
EVENT_CB_S g_pevent2;
extern EVENT_CB_S g_pevent;
UINT32 g_testCount1;
UINT32 g_testCount2;
UINT32 g_EventTest_TaskID1;
UINT32 g_EventTest_TaskID2;

static void TaskF01()
{
   UINT32 ret;
   g_testCount1++;
   printf("\n++++++++++++TaskF01, before event (AND) read, the g_testCount1 = %d. \n", g_testCount1);
   ret = LOS_EventRead(&g_pevent1, 0x11, LOS_WAITMODE_AND, LOS_WAIT_FOREVER);
   g_testCount1++;
   printf("\n++++++++++++TaskF01:after event (AND) read, the g testCount1 = %d. \n", g_testCount1);
   LOS_EventClear(&g_pevent1, 0x11);
   printf("\n++++++++++++TaskF01,before event (OR) read, the q testCount1 = %d. \n", g_testCount1);
   ret = LOS_EventRead(&g_pevent1, 0x11, LOS_WAITMODE_OR, LOS_WAIT_FOREVER);
   g_testCount1++;
   printf("\n++++++++++++TaskF01:after event (OR) read, the q_ testCount1 = %d. \n", g_testCount1);
EXIT:
   ret = LOS_TaskDelete(g_EventTest_TaskID1);
   return;
}

static VOID TaskF02()
{
   UINT32 ret;
   printf("\n++++++++++++TaskF02, before event read, the g_testCount2 is %d \n", g_testCount2);
   printf("\n++++++++++++TaskF02: reading the event (0x11) ...wait for 100 time cycles... \n");
   ret = LOS_EventRead(&g_pevent2, 0x11, LOS_WAITMODE_AND, 100); // 100，读事件倒计时周期。
   printf("\n++++++++++++TaskF02: has read the event, going to do the g_testcount++...\n");
   g_testCount2++;
   printf("\n++++++++++++TaskF02: after the event reading, the g_testCount2 is %d \n", g_testCount2);
   printf("\n++++++++++++TaskF02: waiting to read the event (0x4) ...wait forever...\n");
   ret = LOS_EventRead(&g_pevent2, 0x4, LOS_WAITMODE_AND, LOS_WAIT_FOREVER); //读不到相应的消息就永远等待
   //如果Qx4不到来,任务一直等到。下面的自加操作和打印语句都不会被执行
   g_testCount2++;
   printf("\n++++++++++++TaskF02:after the event reading (0x4), the g testCount2 is %d \n", g_testCount2);
EXIT:
   LOS_TaskDelete(g_EventTest_TaskID2);
   printf("\n++++++++++++TaskF02:deleted!\n");
}

void event_demo()
{
   UINT32 ret;
   printf("\n++++++++++++EventTest001: event CB1 init begins. \n");
   g_pevent1.uwEventID = 0x0;
   ret = LOS_EventInit(&g_pevent1);
   if (ret == LOS_OK)
   {
      printf("\n++++++++++++EventTest001: event CB1 init finished. \n");
   }
   TSK_INIT_PARAM_S task1;
   (void)memset_s(&task1, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
   task1.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF01;
   task1.pcName = "EventTsk1";
   task1.uwStackSize = TASK_STACK_SIZE_TEST;
   task1.usTaskPrio = TASK_PRIO_TEST - 2;
   task1.uwResved = LOS_TASK_STATUS_DETACHED;
   ret = LOS_TaskCreate(&g_EventTest_TaskID1, &task1);
   if (ret == LOS_OK)
      printf("\n++++++++++++TaskF01 Task: Created. \n");
   else
      return ret;
   g_testCount1 = 0;

   printf("\n++++++++++++EventTest001: write event (AND) 0x10...\n");
   ret = LOS_EventWrite(&g_pevent1, 0x10);
   LOS_TaskDelay(10);
   printf("\n++++++++++++EventTest001: write event (AND) 0x01...\n");
   ret = LOS_EventWrite(&g_pevent1, 0x01);
   LOS_TaskDelay(10);
   // Send another event of 0x1 or 0x10
   printf("\n++++++++++++EventTest001: write event (OR) 0x01...\n");
   ret = LOS_EventWrite(&g_pevent1, 0x01);
   LOS_TaskDelay(10);
   // Clear up here
   ret = LOS_EventDestroy(&g_pevent1);
   // ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
}

void event_demo1()
{
   UINT32 ret;
   TSK_INIT_PARAM_S task2;
   (void)memset_s(&task2, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
   task2.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF02;
   task2.pcName = "EventTsk2";
   task2.uwStackSize = TASK_STACK_SIZE_TEST;
   task2.usTaskPrio = TASK_PRIO_TEST - 2;
   task2.uwResved = LOS_TASK_STATUS_DETACHED;
   ret = LOS_TaskCreate(&g_EventTest_TaskID2, &task2);
   if (ret == LOS_OK)
      printf("\n++++++++++++TaskF02 Task: Created\n");
   g_testCount2 = 0;
   g_pevent2.uwEventID = 0x0;
   LOS_EventInit(&g_pevent2);
   printf("\n++++++++++++EventTest002-event CB2 init\n");
   LOS_TaskDelay(10);
   LOS_EventWrite(&g_pevent2, 0x2);
   printf("\n++++++++++++EventTest002,write (0x2) to event, the current uwEventID = %u. \n", g_pevent2.uwEventID);
   LOS_TaskDelay(10); // 10, set delay time.
   LOS_EventWrite(&g_pevent2, 0x11);
   printf("\n++++++++++++EventTest002,write (0x11) to event, the current uwEventID = %u.\n", g_pevent2.uwEventID);
   LOS_TaskDelay(10); // 10, set delay time.
   LOS_EventClear(&g_pevent2, 0xffff);
   printf("\n++++++++++++EventTest002, clear all events with oxffff. the current uwEventID = %u. \n", g_pevent2.uwEventID);
   ret = LOS_EventDestroy(&g_pevent2);
   // ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
   ret = LOS_TaskDelete(g_EventTest_TaskID2);
   // ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
   printf("\n++++++++++++EventTest_TaskID2: deleted. \n");
   return;
}
