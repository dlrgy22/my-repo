/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
*
*/
#include "lab1_sched_types.h"

/*
 * you need to implement scheduler simlator test code.
 *
 */

int main(void)
{
    int i,n;
    printf("프로세스의 개수를 입력하시오 : ");
    scanf("%d",&n);
    getchar();
    Process process[n];
    for (i=0;i<n;i++){
        printf("프로세스 이름 : ");
        scanf("%c",&process[i].name);
        getchar();
        printf("프로세스 도착시간 : ");
        scanf("%d",&process[i].arrive_time);
        printf("프로세스 실행시간 : ");
        scanf("%d",&process[i].run_time);
        getchar();
    }
    sort(process,n);
    FIFO(process,n);
}

