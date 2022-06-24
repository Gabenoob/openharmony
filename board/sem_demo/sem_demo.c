#include "sem_demo.h"

UINT16 semCount = 2;
TSK_INIT_PARAM_S task1;
TSK_INIT_PARAM_S task2;

static VOID TaskF01(void)
{
    UINT32 ret;
    printf("\n++++++++++wangweizhaoTaskF01 (1) :before sem pend success,Count = %d,it should be 2\n", Count);
    ret = LOS_SemPend(g_semTest1, LOS_WAIT_FOREVER);
    Count++;
    ret = LOS_SemPost(g_semTest1);
    printf("\n++++++++++wangweizhaoTaskF01 (2):after sem post success,Count = %d,it should be 3\n", Count);
}

static VOID TaskF02(void)
{
    UINT32 ret;

    Count++;
    printf("\n++++++++++wangweizhaoTaskF02 (1) :before sem pend success,Count = %d,it should be 1\n", Count);
    ret = LOS_SemPend(g_semTest1, LOS_WAIT_FOREVER);
    Count++;
    printf("\n++++++++++wangweizhaoTaskF02 (2) :after sem pend success,Count = %d,it should be 2\n", Count);
    printf("\n++++++++++wangweizhaoTaskF02 (3) :hold sem for 50 ticks,task1 should be scheduled\n");
    LOS_TaskDelay(50);
    printf("\n++++++++++wangweizhaoTaskF02 (4) :sem post,in the next 50 ticks task1 should be continued\n");
    ret = LOS_SemPost(g_semTest1);
    LOS_TaskDelay(10);
    Count++;
    printf("\n++++++++++wangweizhaoTaskF02 (5):after sem post check,Count = %d,it should be 4\n", Count);
}

VOID Sem_Demo(VOID)
{
    UINT32 ret;
    ret = LOS_SemCreate(semCount, &g_semTest1);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao SemDemo : sem created ok with handler 0x%x\n", Count);
    }

    LOS_TaskLock();
    task1.pcName = "VSemB2_1";
    task1.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF01;
    task1.usTaskPrio = TASK_PRIO_TEST;
    task1.uwStackSize = 0x900;
    task1.uwResved = 0;

    ret = LOS_TaskCreate(&g_testTaskID01, &task1);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Sem Demo:testTask1 created ok with ID 0x%d\n", g_testTaskID01);
    }

    task2.pcName = "VSemB2_2";
    task2.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF02;
    task2.usTaskPrio = TASK_PRIO_TEST-2;
    task2.uwStackSize = 0x900;
    task2.uwResved = 0;

    ret = LOS_TaskCreate(&g_testTaskID02, &task2);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Sem Demo:testTask2 created ok with ID 0x%d\n", g_testTaskID02);
    }
    LOS_TaskUnlock();

    printf("\n++++++++++wangweizhao Sem Demo:Sem_demo will delay for 90 ticks\n");
    LOS_TaskDelay(90);

    printf("\n++++++++++wangweizhao Sem Demo:after 90 ticks ,the final Count = %d\n", Count);
    ret = LOS_SemDelete(g_semTest1);
    if (ret == LOS_OK)
    {
        printf("\n++++++++++wangweizhao Sem Demo:g_semTest1 deleted ok\n");
    }

    return ;
}
