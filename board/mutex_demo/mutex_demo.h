#ifndef IT_LOS_MUX_H
#define IT_LOS_MUX_H

#include "osTest.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

UINT32 g_mutexTest1;
extern UINT32 Count;
extern UINT32 g_testTaskID01;
extern UINT32 g_testTaskID02;

VOID Mutex_Demo(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _ItLosMuxH */