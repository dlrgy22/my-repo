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

void input(Process *process,int n){         //사용할 프로세스의 정보 입력
    int i;
    for (i=0;i<n;i++){
        printf("프로세스 이름 : ");
        scanf("%c",&process[i].name);
        getchar();                          //입력버퍼를 비운다
        printf("프로세스 도착시간 : ");
        scanf("%d",&process[i].arrive_time);
        printf("프로세스 실행시간 : ");
        scanf("%d",&process[i].run_time);
        getchar();
    }
    sort(process,n);                    //프로세스를 도착시간에 따라서 정렬
}

void sort(Process *process,int n){          //도착시간으로 정렬 bubble sort사용
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
    InitQueue(&queue);              //queue 초기화
    Process process[n];
    Process Metrics[n];             //Turn_arroundtime, Response_time을 구하기위하여 필요한 정보들을 저장
    input(process,n);               //프로세스 정보입력
    for (i=0;i<n;i++){
        Enqueue(&queue,process[i]);     //프로세스들을 Enqueue
    }
    int time = 0,c=0;                   //시간 초기화, Metrix 배열 에사용할 인덱스 초기화
    while(!IsEmpty(&queue)){            //queue가 Empty가 아닐때 까지 run
        Process run = Dequeue(&queue);  //제일 최근에 들어온것 Dequeue
        while(time<run.arrive_time){    //만약 도착시간이 현재 시간보다 이후라면 X를 출력
            time +=1;
            printf("X ");
        }
        run.start_time  = time;         //start_time을 현재시간으로 설정
        for(i=0;i<run.run_time;i++){    //run time만큼 프로세스 출력
            time +=1;
            printf("%c ",run.name);
        }
        run.end_time = time;        //process가 끝나면 end_time에 현재시간으로 설정
        Metrics[c] = run;           //Metrics 배열에 run 정보를 입력후 c+1
        c+=1;
    }
    printf("\n");
    Turnaround_time(Metrics,n);     //Turnarround_time 계산
    Response_time(Metrics,n);       //Response_time 계산
}

void RR(){
    int i,n,time_quantum;
    printf("프로세스의 개수를 입력하시오 : ");
    scanf("%d",&n);
    getchar();
    Queue queue;
    InitQueue(&queue);          //queue 초기화
    Process process[n];
    Process Metrix[n];
    input(process,n);           //프로세스 정보 입력
    printf("time qunatum을 입력하시오 : ");
    scanf("%d",&time_quantum);              //queue의 time_qunatum입력
    int time = 0;                           //시간초기화
    int fin_count = 0, c = 0;               //실행이끝난 프로세스의 개수를 count하는데 사용, Metrix배열 인덱스로 사용
    Process run;
    run.run_time =0;
    int visit[n];                           //실행한적이 있는가를 판단하는 배열
    for (i=0;i<n;i++){                      //visit 배열 초기화
        visit[i] = 0;
        process[i].first = 0;
    }
    while(fin_count != n){                  //모든 프로세스가 끝날때 까지 반복
        for(i=0;i<n;i++){
            if(process[i].arrive_time<=time&&visit[i]==0){          //새로들어온 프로세스가 있으면 먼저 enqueue
                Enqueue(&queue,process[i]);
                visit[i]=1;                                         //방문표시
            }
        }
        if (run.run_time != 0){                         //실행시간이 끝나지 않았으면 다시 enqueue
            Enqueue(&queue,run);
        }
        if(!IsEmpty(&queue)){                           //비어 있지 않을경우 실행
            run = Dequeue(&queue);
            if (run.first == 0){
                run.first = 1;
                run.start_time = time;                  //처음 실행될 경우 start_time에 현재시간
            }
            for (i = 0;i<time_quantum;i++){             //입력받은 time_quantum만큼 실행
                run.run_time -= 1;                      //한번 실행할때마다 run_time을 줄여 남아있는 시간을 표시
                time +=1;
                printf("%c ",run.name);                 //이름출력
                if(run.run_time==0){                    //실행이 끝났는지 확인
                    run.end_time = time;                //끝났으면 end_time에 현재시간 입력
                    Metrix[c] = run;                    //Metrix에 정보 입력
                    c+=1;
                    fin_count +=1;                      //프로세스가 끝났으므로 fin_count증가
                    break;
                }
            }
        }
        else{                                           //현재시간에 들어있는 프로세스가 없다면 x출력
            time +=1;
            printf("X ");
        }
    }
    printf("\n");
    Turnaround_time(Metrix,n);                          //Turnarround_time 과 Response_time 출력
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
        InitQueue(&queue[i]);                               //queue초기화
    }
    int time_quantum[5],fin_count = 0,time = 0,visit[n],boosting_time,check_run=0,c=0;      //boosting_time : 부스팅 주기, check_run : 나머지 큐가 비었을때 사용되는 큐의 우선순위를 높여주는대 사용
    Process run;
    run.run_time =0;
    for(i=0;i<n;i++){               //초기화
        visit[i] = 0;
        process[i].boosting = 0;
        process[i].first = 0;
    }
    for (i=1;i<=4;i++){                     //time_quantum입력
        printf("%d번째 queue의 time_quantum을 입력하시오 : ",i);
        scanf("%d",&time_quantum[i]);
    }
    printf("boosting 주기를 입력하시오 : ");                //부스팅 주기 입력
    scanf("%d",&boosting_time);
    while(fin_count != n){                              //모든 프로세스가 끝나기 전까지 반복
        for (i=0;i<n;i++){
            if(process[i].arrive_time<=time&&visit[i]==0){              //처음 실행되는 프로세스 있는지 확인후 먼저 enqueue
                Enqueue(&queue[1],process[i]);
                visit[i] =1;                                            //방문확인
            }
        }
        if(check_run==1){
            Enqueue(&queue[1],run);
            check_run = 0;
        }
        for(i=1;i<=4;i++){
            if(!IsEmpty(&queue[i])){                                    //queue에 프로세스가 있는지 확인 있으면 실행
                run = Dequeue(&queue[i]);
                if (run.first == 0){                                    //한번도 실행된적이 없는 프로세스면 start_time에 현재시간 입력
                    run.first = 1;
                    run.start_time = time;
                }
                for(int j=0;j<time_quantum[i];j++){                     //해당큐의 time_quantum만큼 실행
                    run.run_time -= 1;
                    time += 1;
                    printf("%c ",run.name);
                    if(run.run_time == 0){                              //실행중에 프로세스실행이 모두 완료되면 break
                        run.end_time = time;                            //실행시간이 모두 종료되면 end_time에 현재시간 입력
                        Metrix[c] = run;                                //Metrix배열에 정보 입력
                        c+=1;                                           //인덱스 증가
                        fin_count += 1;                                 //하나가 종료됬으므로 fin_count 증가
                        break;
                    }
                }
                if (run.run_time>0){                                    //아직 실행해야할 시간이 남았을경우
                    if(i <= 3){                                         //맨 밑의 큐가 아닐경우
                        for(int j=1;j<=4;j++){
                            if(!IsEmpty(&queue[j])){                    //큐에 다른 프로세스가 없을경우 enqueue후 break
                                Enqueue(&queue[i+1],run);               //한칸 아래 큐에 enqueue
                                break;
                            }
                            else if(IsEmpty(&queue[j])&&j==4){          //다른 프로세스가 있을경우 check_run을 1로 설정
                                check_run = 1;
                            }
                        }
                    }
                    else{                                               //맨 밑의큐일경우
                        run.boosting += 1;                              //boosting 시간 +1
                        if (run.boosting == boosting_time){             //만약 설정한 부스팅 주기와 크기가 같아진다면 최상위 큐에 enqueue
                            run.boosting = 0;
                            Enqueue(&queue[1],run);
                        }
                        else{                                           //아직 부스팅주기보다 작을경우 맨 밑의큐에 유지
                            Enqueue(&queue[4],run);
                        }
                    }
                }
                break;                                                  //한 프로세스를 실행시킨후 break
            }
            else if(IsEmpty(&queue[i])&&i==4){                          //맨 마지막까지 모든 큐가 비어있으면 X출력
                printf("X ");
                time += 1;
            }
        }
    }
    printf("\n");
    Turnaround_time(Metrix,n);                                          //Turnaround_time,Response_time 출력
    Response_time(Metrix,n);
}

void Stride(){
    int i,n,num = 1;
    printf("프로세서의 개수를 입력하시오 : ");
    scanf("%d",&n);
    getchar();
    Process process[n];
    int pass_value[n];                                                  //pass_value 설정
    for(i = 0;i<n;i++){
        pass_value[i]=0;
    }
    for(i=0;i<n;i++){                                                   //프로세스 정보 입력
        printf("프로세서의 이름을 입력하시오 : ");
        scanf("%c",&process[i].name);
        printf("프로세서의 티켓수를 입력하시오 : ");
        scanf("%d",&process[i].tickets);
        getchar();
    }
    for(i=0;i<n;i++){                                                   //num에 모든 프로세스의 티켓값을 곱한다
        num *=process[i].tickets;
    }
    for(i=0;i<n;i++){
        process[i].stride = num/process[i].tickets;                     //각 stride에 num의 값을 프로세스로 나눈값을 넣어준다
    }
    while(1){
        int run = 0;
        for(i = 0;i<n;i++){
            if(pass_value[i] < pass_value[run]){                        //모든 프로세스중에 가장 작은 pass_value값을 가지는 프로세스를 찾는다
                run = i;
            }
        }
        printf("%c ",process[run].name);                                //가장 작은 pass_value값을 가지는 프로세스 이름 출력
        pass_value[run] += process[run].stride;                         //pass_value에 해당 프로세스의 stride 값을 더해준다
        int check = 0;                                                  //check 초기화
        for(i=0;i<n-1;i++){                                             //모든 프로세스를 돌아다니면서 pass_value값 확인
            if(pass_value[i] == pass_value[i+1]){                       //다음프로세스와 같을경우 다음프로세스확인
                check +=1;
            }
            else{                                                       //다음 프로세스와 다를경우 바로 break
                break;
            }
        }
        if (check == n-1){                                              //만약 모든 pass_value가 같을경우 한 주기가 끝난것 이므로 break
            break;
        }
        check = 0;
    }
}

void Turnaround_time(Process *process,int n){                           //Turnarround_time 계산
    int i;
    float turnaround_time = 0;
    for(i=0;i<n;i++){                                                   //각 프로세스의 end_time에서 arrive_time을 빼준것을 누적
        turnaround_time += process[i].end_time - process[i].arrive_time;
    }
    printf("turnaround_time : %f\n",turnaround_time/n);                 //누적된 값을 프로세스의 개수로 나누어 출력
}

void Response_time(Process *process,int n){                             //Response_time 계산
    int i;
    float response_time = 0;
    for(i=0;i<n;i++){                                                   //각 프로세스의 start_time에서 arrive_time을 빼준것을 누적
        response_time += process[i].start_time - process[i].arrive_time;
    }
    printf("response_time : %f\n",response_time/n);                     //누적된 값을 프로세스의 개수로 나누어 출력
}



/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler. 
 */


