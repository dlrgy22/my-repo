/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H


/*
 * You need to Declare functions in  here
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct process{
    char name;
    int run_time;
    int arrive_time;
}Process;
typedef struct Node //노드 정의
{
    Process data;
    struct Node *next;
}Node;
typedef struct Queue //Queue 구조체 정의
{
    Node *front; //맨 앞(꺼낼 위치)
    Node *rear; //맨 뒤(보관할 위치)
    int count;//보관 개수
}Queue;
void InitQueue(Queue *queue);//큐 초기화
int IsEmpty(Queue *queue); //큐가 비었는지 확인
void Enqueue(Queue *queue, Process data); //큐에 보관
Process Dequeue(Queue *queue); //큐에서 꺼냄
void sort(Process *process,int n);
void FIFO();


#endif /* LAB1_HEADER_H*/



