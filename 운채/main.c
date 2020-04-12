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
void FIFO(void);
void RR(void);
void MLFQ(void);

int main(void)
{
    //FIFO();
    RR();
}
 
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

void RR(){
    int i,n,time_quantum;
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
    printf("time qunatum을 입력하시오 : ");
    scanf("%d",&time_quantum);
    int time = 1;
    int fin_count = 0;
    Process run;
    run.run_time =0;
    int visit[n];
    for (i=0;i<n;i++){
        visit[i] = 0;
    }
    while(fin_count != n){
        for(i=0;i<n;i++){
            if(process[i].arrive_time<=time&&visit[i]==0){
                Enqueue(&queue,process[i]);
                visit[i]=1;
            }
        }
        if (run.run_time != 0){
            Enqueue(&queue,run);
        }
        if(!IsEmpty(&queue)){
            run = Dequeue(&queue);
            for (i = 0;i<time_quantum;i++){
                run.run_time -= 1;
                time +=1;
                printf("%c ",run.name);
                if(run.run_time==0){
                    fin_count +=1;
                    break;
                }
            }
        }
        else{
            time +=1;
            printf("X ");
        }
    }
}

void MLFQ(){
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
    Queue queue_1;
}
