#include "task.h"


UINT32 g_testTaskID01;
UINT32 g_testTaskID02;

static VOID TaskF01(VOID)
{
    int sum = 0;

    while (1){
        // printf("WangWeiZhao Task 1 Sum:%d\n",sum++);
        usleep(1000000);
    }
    
}
static UINT32 Create_Task1(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S task1 = { 0 };

    //初始化任务1，记录基本信息
    task1.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF01;
    task1.uwStackSize = TASK_STACK_SIZE_TEST;
    task1.pcName = "wangweizhaoTask1";
    task1.usTaskPrio = TASK_PRIO_TEST - 1;
    task1.uwResved = LOS_TASK_STATUS_DETACHED;

    //创建任务1，ID记为 ID01
    ret = LOS_TaskCreate(&g_testTaskID01, &task1);

    return LOS_OK;
}

static VOID TaskF02(VOID)
{
    int sum = 0;

    while (1){
        // printf("WangWeiZhao Task 2 Sum:%d\n",sum++);
        usleep(3000000);

        if (sum>=10){
            UINT32 task1Status;
            UINT32 ret = LOS_TaskStatusGet(g_testTaskID01,&task1Status);

            if(ret == LOS_OK){
                if (task1Status != OS_TASK_STATUS_EXIT){
                    LOS_TaskDelete(g_testTaskID01);
                }
            }
        }
    }
}

static UINT32 Create_Task2(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S task2 = { 0 };

    task2.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskF02;
    task2.uwStackSize = TASK_STACK_SIZE_TEST;
    task2.pcName = "WangWeiZhaoTask2";
    task2.usTaskPrio = TASK_PRIO_TEST - 2;
    task2.uwResved = LOS_TASK_STATUS_DETACHED;

    ret = LOS_TaskCreate(&g_testTaskID02,&task2);

    return LOS_OK;
}

VOID task_demo()
{
    Create_Task1();
    Create_Task2();
}



