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
    InitQueue(&queue);
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



/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler. 
 */


