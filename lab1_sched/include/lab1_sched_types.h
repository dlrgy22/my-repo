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
typedef struct process{                     //프로세스 구조체
    char name;                              //이름
    int run_time;                           //총 실행시간
    int arrive_time;                        //프로세스 도착시간
    int start_time;                         //프로세스 시작시간
    int end_time;                           //프로세스가 끝나는 시간
    int first;                              //해당 프로세스가 처음 실행되는지 확인할때 사용
    int boosting;                           //부스팅주기와 비교하여 부스팅 실행여부 판단
    int tickets;                            //Stride 스케쥴링할때 프로세스에 줄 티켓값
    int stride;                             //프로세스의 stride값
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
void sort(Process *process,int n); //프로세스를 arrive_time순으로 정렬
void input(Process *process,int n); // 프로세스정보를 입력
void FIFO(void);                    //FIFO 스케쥴링
void RR(void);                      //라운드로빈 스케줄링
void MLFQ(void);                    //MLFQ 스케쥴링
void Stride(void);                  //Stride 스케쥴링
void Turnaround_time(Process *process,int n);   //Turnaround_time 스케쥴링
void Response_time(Process *process,int n);     //Response_time 스케쥴링

#endif /* LAB1_HEADER_H*/



