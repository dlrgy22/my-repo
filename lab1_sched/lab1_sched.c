/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/

#include "lab1_sched_types.h"

void InitQueue(Queue *queue)
{
    queue->front = queue->rear = NULL; //front와 rear를 NULL로 설정
    queue->count = 0;//보관 개수를 0으로 설정
}
 
int IsEmpty(Queue *queue)
{
    return queue->count == 0;    //보관 개수가 0이면 빈 상태
}
 
void Enqueue(Queue *queue, Process data)
{
    Node *now = (Node *)malloc(sizeof(Node)); //노드 생성
    now->data = data;//데이터 설정
    now->next = NULL;
 
    if (IsEmpty(queue))//큐가 비어있을 때
    {
        queue->front = now;//맨 앞을 now로 설정
    }
    else//비어있지 않을 때
    {
        queue->rear->next = now;//맨 뒤의 다음을 now로 설정
    }
    queue->rear = now;//맨 뒤를 now로 설정
    queue->count++;//보관 개수를 1 증가
}
 
Process Dequeue(Queue *queue)
{
    Process re;
    Node *now;
    if (IsEmpty(queue))//큐가 비었을 때
    {
        return re;
    }
    now = queue->front;//맨 앞의 노드를 now에 기억
    re = now->data;//반환할 값은 now의 data로 설정
    queue->front = now->next;//맨 앞은 now의 다음 노드로 설정
    free(now);//now 소멸
    queue->count--;//보관 개수를 1 감소
    return re;
}

void sort(Process *process,int n){
    int i,j;
    Process tmp;
    for(i=n-1;i>0;i--){
        for(j=0;j<i;j++){
            if(process[j].arrive_time>process[j+1].arrive_time){
                tmp = process[j];
                process[j] = process[j+1];
                process[j+1] = tmp;
            }
        }
    }
}

void FIFO(){
    int i,n;
    printf("프로세스의 개수를 입력하시오 : ");
    scanf("%d",&n);
    getchar();
    Queue queue;
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
    for (i=0;i<n;i++){
        Enqueue(&queue,process[i]);
    }
    int time = 1;
    while(!IsEmpty(&queue)){
        Process run = Dequeue(&queue);
        while(time<run.arrive_time){
            time +=1;
            printf("X ");
        }
        for(i=0;i<run.run_time;i++){
            time +=1;
            printf("%c ",run.name);
        }
    }
}



/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler. 
 */


