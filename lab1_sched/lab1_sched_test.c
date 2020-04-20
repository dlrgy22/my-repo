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
    int number;
    printf("1번 : FIFO \n2번 : RR\n3번 : MLFQ\n4번 : Stride\n");        //방법 선택
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

