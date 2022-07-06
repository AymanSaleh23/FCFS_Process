/*
 * main.c
 *
 *  Created on: Mar 24, 2022
 *      Author: Ayman Saleh
 */

#include <stdio.h>
#include <stdlib.h>
#define OK 	0
#define NOK 1
#define NO_PROCESS_FOUND -1

#define MuximumProcesses 4

#pragma pack(1)

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef float  f32;

typedef struct {
	u16 BurstTime;
	u32 ArrivalTime;
	u32 StartTime;
	u32 WaitingTime;
}Process;

Process Ps[MuximumProcesses];
u16 TotalWaitingTime = 0;
u16 TotalServiesTime = 0;

u8 OS_u8CreateProcess 		(u16 Copy_u16BurstTime, u32 Copy_u32ArrivalTime);
u8 OS_u8CalculateWaitingTime(void);
u8 OS_u8StartSchedule 		(void);
u8 OS_u8CalculateAverageWaitingTime (Process * Copy_processConfig );


int main (void){
	printf("Maximum number of Processes:\t%d\n",MuximumProcesses);

	printf("%s \n", (OS_u8CreateProcess(8,0)==OK)?("Process Created"):("Invalid Parameters") );
	printf("%s \n", (OS_u8CreateProcess(4,1)==OK)?("Process Created"):("Invalid Parameters") );
	printf("%s \n", (OS_u8CreateProcess(9,2)==OK)?("Process Created"):("Invalid Parameters") );
	printf("%s \n", (OS_u8CreateProcess(5,3)==OK)?("Process Created"):("Invalid Parameters") );


	printf("##################################################\n");
	printf("Process ID \t Start Time \t Waiting Time\n");
	printf("##################################################\n");
	OS_u8CalculateWaitingTime();
	return 0;
}

u8 OS_u8CreateProcess 		(u16 Copy_u16BurstTime, u32 Copy_u32ArrivalTime){
	u8 LOC_u8ErrorState = OK;
	static u8 Counter =0;
	if (Counter < MuximumProcesses){
		if ((Copy_u16BurstTime >0 )&&(Copy_u32ArrivalTime >=0)){
			Ps[Counter].ArrivalTime = Copy_u32ArrivalTime;
			Ps[Counter].BurstTime = Copy_u16BurstTime;
			Counter++;
		}
		else {
			LOC_u8ErrorState = NOK;
		}
	}
	else {
		LOC_u8ErrorState = NOK;
	}
	return LOC_u8ErrorState;
}
u8 OS_u8CalculateWaitingTime(void){

	u8 LOC_u8ErrorState = OK;
	if (MuximumProcesses != 0){
		//Burst - Arrival
		for (u8 i = 0 ; i < MuximumProcesses ; i++){
			if (i == 0 ){
				Ps[i].WaitingTime = 0;
				Ps[i].StartTime= 0;
			}
			else{
				Ps[i].StartTime		= Ps[i-1].BurstTime + Ps[i-1].StartTime;
				Ps[i].WaitingTime 	= (Ps[i].StartTime ) - Ps[i].ArrivalTime;
			}
			printf("    %d \t\t %d \t\t %d\n",(i+1),Ps[i].StartTime,Ps[i].WaitingTime);
		}

	}
	return LOC_u8ErrorState;
}
