#include "shell.h"
extern void event_demo();
extern void event_demo1();
extern void Sem_Demo();
extern void Mux_Demo();
extern void Queue_Demo();
extern void mem_demo();
extern void Answer4_Demo();
UINT32 myShellCmd_event(UINT32 argc, const CHAR **argv)
{
    (void)argc;
    (void)argv;
    printf("This is event demo launch command.\n");
    event_demo();
    event_demo1();
    return 0;
}

UINT32 Shell_cmd_mem(UINT32 argc, const CHAR **argv)
{
    (void)argc;
    (void)argv;
    printf("This is mem demo launch command.\n");
    Mem_Demo();
    return 0;
}

UINT32 Shell_cmd_semphore(UINT32 argc, const CHAR **argv)
{
    (void)argc;
    (void)argv;
    printf("This is sem demo launch command.\n");
    Sem_Demo();
    return 0;
}
UINT32 Shell_cmd_MUX(UINT32 argc, const CHAR **argv)
{
    (void)argc;
    (void)argv;
    printf("This is mutex demo launch command.\n");
    Mutex_Demo();
    return 0;
}

UINT32 Shell_cmd_Queue(UINT32 argc, const CHAR **argv)
{
    (void)argc;
    (void)argv;
    printf("This is queue demo launch command.\n");
    Queue_Demo();
    return 0;
}

UINT32 Shell_cmd_Answer4(UINT32 argc, const CHAR **argv)
{
    (void)argc;
    (void)argv;
    printf("This is Answer4_Demo launch command.\n");
    Answer4_Demo();
    return 0;
}

void regMyShellCmd(void)
{
    osCmdReg(CMD_TYPE_STD, "event_demo", 0, myShellCmd_event);
    osCmdReg(CMD_TYPE_STD, "sem_demo", 0, Shell_cmd_semphore);
    osCmdReg(CMD_TYPE_STD, "mutex_demo", 0, Shell_cmd_MUX);
    osCmdReg(CMD_TYPE_STD, "queue_demo", 0, Shell_cmd_Queue);
    osCmdReg(CMD_TYPE_STD, "mem_demo", 0, Shell_cmd_mem);
    osCmdReg(CMD_TYPE_STD, "Answer4_Demo", 0, Shell_cmd_Answer4);
}