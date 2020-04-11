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
    int i;
    Queue queue;
 
    InitQueue(&queue);//큐 초기화
    for (i = 1; i <= 5; i++)//1~5까지 큐에 보관
    {
        Process pro;
        scanf("%c",&pro.name);
        scanf("%d",&pro.time);
        getchar();
        Enqueue(&queue,pro);
        //Enqueue(&queue, i);
    }
    while (!IsEmpty(&queue))//큐가 비어있지 않다면 반복
    {
        Process pro;
        pro = Dequeue(&queue);
        printf("%c %d\n",pro.name,pro.time);
        //printf("%d ", Dequeue(&queue));//큐에서 꺼내온 값 출력
    }
    printf("\n");
    return 0;
}

