#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct process{
    char name;
    int run_time;
    int arrive_time;
    int start_time;
    int end_time;
    int first;
    int boosting;
    int tickets;
    int stride;
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
int gcd(int n1,int n2);
void input(Process *process,int n);
void FIFO(void);
void RR(void);
void MLFQ(void);
void Stride(void);
void Turnaround_time(Process *process,int n);
void Response_time(Process *process,int n);

int main(int argc, char* argv[])
{
    int number = 0;
    printf("1번 : FIFO \n2번 : RR\n3번 : MLFQ\n4번 : Stride\n");
    printf("숫자를 입력하시오 : ");
    scanf("%d",&number);
    
    if(number == 1){
        FIFO();
    }
    else if(number == 2){
        RR();
    }
    else if(number == 3){
        MLFQ();
    }
    else if(number == 4){
        Stride();
    }
    else{
        printf("잘못입력하셨습니다.");
    }
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

void input(Process *process,int n){
    int i;
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
    Process Metrics[n];
    input(process,n);
    for (i=0;i<n;i++){
        Enqueue(&queue,process[i]);
    }
    int time = 0,c=0;
    while(!IsEmpty(&queue)){
        Process run = Dequeue(&queue);
        while(time<run.arrive_time){
            time +=1;
            printf("X ");
        }
        run.start_time  = time;
        for(i=0;i<run.run_time;i++){
            time +=1;
            printf("%c ",run.name);
        }
        run.end_time = time;
        Metrics[c] = run;
        c+=1;
    }
    printf("\n");
    Turnaround_time(Metrics,n);
    Response_time(Metrics,n);
}

void RR(){
    int i,n,time_quantum;
    printf("프로세스의 개수를 입력하시오 : ");
    scanf("%d",&n);
    getchar();
    Queue queue;
    InitQueue(&queue);
    Process process[n];
    Process Metrix[n];
    input(process,n);
    printf("time qunatum을 입력하시오 : ");
    scanf("%d",&time_quantum);
    int time = 0;
    int fin_count = 0, c = 0;
    Process run;
    run.run_time =0;
    int visit[n];
    for (i=0;i<n;i++){
        visit[i] = 0;
        process[i].first = 0;
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
            if (run.first == 0){
                run.first = 1;
                run.start_time = time;
            }
            for (i = 0;i<time_quantum;i++){
                run.run_time -= 1;
                time +=1;
                printf("%c ",run.name);
                if(run.run_time==0){
                    run.end_time = time;
                    Metrix[c] = run;
                    c+=1;
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
    printf("\n");
    Turnaround_time(Metrix,n);
    Response_time(Metrix,n);
}

void MLFQ(){
    int i,n;
    printf("프로세스의 개수를 입력하시오 : ");
    scanf("%d",&n);
    getchar();
    Process process[n],Metrix[n];
    input(process,n);
    Queue queue[5];
    for(i=1;i<5;i++){
        InitQueue(&queue[i]);
    }
    int time_quantum[5],fin_count = 0,time = 0,visit[n],boosting_time,check_run=0,c=0;
    Process run;
    run.run_time =0;
    for(i=0;i<n;i++){
        visit[i] = 0;
        process[i].boosting = 0;
        process[i].first = 0;
    }
    for (i=1;i<=4;i++){
        printf("%d번째 queue의 time_quantum을 입력하시오 : ",i);
        scanf("%d",&time_quantum[i]);
    }
    printf("boosting 주기를 입력하시오 : ");
    scanf("%d",&boosting_time);
    while(fin_count != n){
        for (i=0;i<n;i++){
            if(process[i].arrive_time<=time&&visit[i]==0){
                Enqueue(&queue[1],process[i]);
                visit[i] =1;
            }
        }
        if(check_run==1){
            Enqueue(&queue[1],run);
            check_run = 0;
        }
        for(i=1;i<=4;i++){
            if(!IsEmpty(&queue[i])){
                run = Dequeue(&queue[i]);
                if (run.first == 0){
                    run.first = 1;
                    run.start_time = time;
                }
                for(int j=0;j<time_quantum[i];j++){
                    run.run_time -= 1;
                    time += 1;
                    printf("%c ",run.name);
                    if(run.run_time == 0){
                        run.end_time = time;
                        Metrix[c] = run;
                        c+=1;
                        fin_count += 1;
                        break;
                    }
                }
                if (run.run_time>0){
                    if(i <= 3){
                        for(int j=1;j<=4;j++){
                            if(!IsEmpty(&queue[j])){
                                Enqueue(&queue[i+1],run);
                                break;
                            }
                            else if(IsEmpty(&queue[j])&&j==4){
                                check_run = 1;
                            }
                        }
                    }
                    else{
                        run.boosting += 1;
                        if (run.boosting == boosting_time){
                            run.boosting = 0;
                            Enqueue(&queue[1],run);
                        }
                        else{
                            Enqueue(&queue[4],run);
                        }
                    }
                }
                break;
            }
            else if(IsEmpty(&queue[i])&&i==4){
                printf("X ");
                time += 1;
            }
        }
    }
    printf("\n");
    Turnaround_time(Metrix,n);
    Response_time(Metrix,n);
}

void Stride(){
    int i,n,num = 1;
    printf("프로세서의 개수를 입력하시오 : ");
    scanf("%d",&n);
    getchar();
    Process process[n];
    int pass_value[n];
    for(i = 0;i<n;i++){
        pass_value[i]=0;
    }
    for(i=0;i<n;i++){
        printf("프로세서의 이름을 입력하시오 : ");
        scanf("%c",&process[i].name);
        printf("프로세서의 티켓수를 입력하시오 : ");
        scanf("%d",&process[i].tickets);
        getchar();
    }
    for(i=0;i<n;i++){
        num *=process[i].tickets;
    }
    for(i=0;i<n;i++){
        process[i].stride = num/process[i].tickets;
    }
    while(1){
        int run = 0;
        for(i = 0;i<n;i++){
            if(pass_value[i] < pass_value[run]){
                run = i;
            }
        }
        printf("%c ",process[run].name);
        pass_value[run] += process[run].stride;
        int check = 0;
        for(i=0;i<n-1;i++){
            if(pass_value[i] == pass_value[i+1]){
                check +=1;
            }
            else{
                break;
            }
        }
        if (check == n-1){
            break;
        }
        check = 0;
    }
}

void Turnaround_time(Process *process,int n){
    int i;
    float turnaround_time = 0;
    for(i=0;i<n;i++){
        turnaround_time += process[i].end_time - process[i].arrive_time;
    }
    printf("turnaround_time : %f\n",turnaround_time/n);
}

void Response_time(Process *process,int n){
    int i;
    float response_time = 0;
    for(i=0;i<n;i++){
        response_time += process[i].start_time - process[i].arrive_time;
    }
    printf("response_time : %f\n",response_time/n);
}


