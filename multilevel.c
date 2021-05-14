#include <stdio.h>
#define MAX 10


//Structure of the process

struct process{

  int process_id;
  int arrival_time;
  int burst_time;
  int responseTime;
  int waitingTime;
  int turnaroundTime;
  int completionTime;
  int queue;
  int ready;

}processes[MAX], queueOne[MAX], queueTwo[MAX], queueThree[MAX];



int main(){
  //declaring variables
  int processLimit;
  int time;
  int initialArrivalTime;
  int fig;
  int num;
  int responseTimeArrives;
  struct process temp_process;

  //Number of Process
  printf("Enter the number of process: " );
  scanf("%d", &processLimit);
  //process process[processLimit];
  // process queueOne[processLimit];
  // process queueTwo[MAX];
  // process queueThree[MAX];


  //loop to create processes
  //this process has automatically enter the first Queue
  for(num = 0, fig = 1; num < processLimit; num++, fig ++ ){
    //setting the process id
    processes[num].process_id = fig;

    //Get Arrival Time
    printf("\nArrival Time of Process %c: ", processes[num].process_id);
    scanf("%d", &processes[num].arrival_time);

    //Get Process Burst Time
    printf("Burst Time of Process %c: ", processes[num].process_id);
    scanf("%d", &processes[num].burst_time);

    //Save Response time - this will be updated later
    //intial response time for the first process is when it start processing
    //processes[num].responseTime = processes[num].burst_time;


    //Set the process ready to not ready
    processes[num].ready = 0;


  }


  int startTime = 0;
  int timeQuantum = 4;
  int nextQueue;
  int k = 0;
  int r = 0;
  int m = 0;


  //sorting queues of the same priority using the arrival times
  for(int i = 0; i < processLimit; i++)
  {
        for(int k = i + 1; k < processLimit; k++)
        {

                      if(processes[i].arrival_time > processes[k].arrival_time)
                      {
                            temp_process = processes[i];
                            processes[i] = processes[k];
                            processes[k] = temp_process;
                      }
        }
  }

  //first process burst time
  //time = processes[0].burst_time;
  //initialArrivalTime = processes[0].arrival_time;
  time = processes[0].arrival_time;

  //move all the processes to the first priority queue
  for (int j = 0; j < processLimit; j ++){


      printf("\nProcesses\n");
      printf("Process_id: %d\n", processes[j].process_id);
      printf("Arrival Time: %d\n", processes[j].arrival_time);
      printf("Burst Time: %d\n", processes[j].burst_time);
      printf("Response Time: %d\n", processes[j].responseTime);
      printf("Turnaround Time: %d\n", processes[j].turnaroundTime);
      printf("completionTime: %d\n", processes[j].completionTime);

       //add to the first queue
       queueOne[j].process_id = processes[j].process_id;
       queueOne[j].responseTime = processes[j].responseTime;
       queueOne[j].burst_time = processes[j].burst_time;
       queueOne[j].arrival_time = processes[j].arrival_time;
       queueOne[j].turnaroundTime = processes[j].turnaroundTime;
       queueOne[j].completionTime = processes[j].completionTime;
       queueOne[j].queue = processes[j].queue = 1;



       printf("\nInitial Priority Queue\n");
       printf("Process_id: %d\n", queueOne[j].process_id);
       printf("Arrival Time: %d\n", queueOne[j].arrival_time);
       printf("Burst Time: %d\n", queueOne[j].burst_time);
       printf("Response Time: %d\n", queueOne[j].responseTime);
       printf("Turnaround Time: %d\n", queueOne[j].turnaroundTime);
       printf("completionTime: %d\n",queueOne[j].completionTime);

  }





  //for every process
  for(int i = 0; i < processLimit; i++){



      //get the first arrival time - in this case the lowest


      //moving in between queues;
      //perform RR on the first queue with quantum of 4
      //for (int i = j ; i < processLimit; i ++){

        //if the process's time quantum <= the burst time
        if(queueOne[i].burst_time <= timeQuantum){

            //get the response time;
            //responseTimeArrives = initialArrivalTime;
            queueOne[i].responseTime = time - queueOne[i].arrival_time;

            //perfoms the action
            time += queueOne[i].burst_time;

            queueOne[i].completionTime = time;

            queueOne[i].turnaroundTime =queueOne[i].completionTime  - queueOne[i].arrival_time;

            queueOne[i].waitingTime =  queueOne[i].turnaroundTime - queueOne[i].burst_time;

            queueOne[i].queue = processes[m].queue = 1;


            printf("\nAfter Priority Queue\n");
            printf("Process_id: %d\n", queueOne[i].process_id);
            printf("Arrival Time: %d\n", queueOne[i].arrival_time);
            printf("Burst Time: %d\n", queueOne[i].burst_time);
            printf("Response Time: %d\n", queueOne[i].responseTime);
            printf("Turnaround Time: %d\n", queueOne[i].turnaroundTime);
            printf("Waiting Time: %d\n", queueOne[i].waitingTime);
            printf("completionTime: %d\n",queueOne[i].completionTime);

            m++;

        }



        else{

           //move to the second priority queue
           queueTwo[k].process_id = queueOne[i].process_id;



           queueTwo[k].arrival_time = queueOne[i].arrival_time;

           queueTwo[k].responseTime = time - queueOne[i].arrival_time;;



            //queueTwo[k].responseTime = queueTwo[k].waitingTime -

            time += timeQuantum;

            //queueOne[i].responseTime -= timeQuantum;

            queueTwo[k].burst_time = queueOne[i].burst_time - timeQuantum;

            //queueTwo[k].responseTime  = queueTwo[k].burst_time ;








           printf("\nInitial Priority Queue Two\n");
           printf("Process_id: %d\n", queueTwo[k].process_id);
           printf("Arrival Time: %d\n", queueTwo[k].arrival_time);
           printf("Burst Time: %d\n", queueTwo[k].burst_time);
           printf("Response Time: %d\n", queueTwo[k].responseTime);
           printf("Turnaround Time: %d\n", queueTwo[k].turnaroundTime);
           printf("Waiting Time: %d\n", queueTwo[k].waitingTime);
           printf("completionTime: %d\n",queueTwo[k].completionTime);

           k = k+ 1;
           nextQueue = 2;
        }
    }




    //MOVE TO THE SECOND PRIORITY QUEUE using time quantum of 8
    for (int i = 0; i < k; i++){

      if(queueTwo[i].burst_time <= (timeQuantum *2)){

        //get the response time;
        //responseTimeArrives = initialArrivalTime;
        ///queueTwo[i].responseTime = initialArrivalTime;

        //printf("\n%d\n",initialArrivalTime );

        //perfoms the action
        time += queueTwo[i].burst_time;

        queueTwo[i].completionTime = time;

        queueTwo[i].turnaroundTime =queueTwo[i].completionTime  - queueTwo[i].arrival_time;

        queueTwo[i].waitingTime =  queueTwo[i].turnaroundTime - queueTwo[i].burst_time;

        queueTwo[i].queue = processes[m].queue = 2;


        printf("\nAfter Priority Queue Two\n");
        printf("Process_id: %d\n", queueTwo[i].process_id);
        printf("Arrival Time: %d\n", queueTwo[i].arrival_time);
        printf("Burst Time: %d\n", queueTwo[i].burst_time);
        printf("Response Time: %d\n", queueTwo[i].responseTime);
        printf("Turnaround Time: %d\n", queueTwo[i].turnaroundTime);
        printf("Waiting Time: %d\n", queueTwo[i].waitingTime);
        printf("completionTime: %d\n",queueTwo[i].completionTime);

        m++;

      }
      else{

         //move to the second priority queue
         queueThree[r].process_id = queueTwo[i].process_id;



         queueThree[r].arrival_time = queueTwo[i].arrival_time;

         queueThree[r].responseTime = time - queueTwo[i].arrival_time;;



          //queueTwo[k].responseTime = queueTwo[k].waitingTime -

          time += (timeQuantum * 2);

          //queueOne[i].responseTime -= timeQuantum;

          queueThree[r].burst_time = queueTwo[i].burst_time - (timeQuantum * 2);

          //queueTwo[k].responseTime  = queueTwo[k].burst_time ;



          queueThree[r].queue = processes[m].queue = 3;







        printf("\nInitial Priority Queue Three\n");
        printf("Process_id: %d\n", queueThree[r].process_id);
        printf("Arrival Time: %d\n", queueThree[r].arrival_time);
        printf("Burst Time: %d\n", queueThree[r].burst_time);
        printf("Response Time: %d\n", queueThree[r].responseTime);
        printf("Turnaround Time: %d\n", queueThree[r].turnaroundTime);
        printf("Waiting Time: %d\n", queueThree[r].waitingTime);
        printf("completionTime: %d\n",queueThree[r].completionTime);

        r = r + 1;
        m++;
        nextQueue = 3;

      }

    }

    //using first come first serve
    for (int i = 0; i < r; i ++){

      if(i==0){
          queueThree[i].completionTime = queueThree[i].burst_time + time ;

      }
      else{
          queueThree[i].completionTime = queueThree[i - 1].completionTime + queueThree[i].burst_time;
      }

      queueThree[i].turnaroundTime = queueThree[i].completionTime - queueThree[i].arrival_time;;
      queueThree[i].waitingTime = queueThree[i].turnaroundTime - queueThree[i].burst_time;

      printf("\nInitial Priority Queue Three\n");
      printf("Process_id: %d\n", queueThree[i].process_id);
      printf("Arrival Time: %d\n", queueThree[i].arrival_time);
      printf("Burst Time: %d\n", queueThree[i].burst_time);
      printf("Response Time: %d\n", queueThree[i].responseTime);
      printf("Turnaround Time: %d\n", queueThree[i].turnaroundTime);
      printf("Waiting Time: %d\n", queueThree[i].waitingTime);
      printf("completionTime: %d\n",queueThree[i].completionTime);

    }




















      //if at a particular time no process is running then
      //priority == -1
      //priority == process[i].Queue

      //printf("\n%d\t", startTime,)
      //printf("\n%d\t%d\t%d\n",startTime, processes[j].queue, processes[j].process_id);


      //increase start time
      //startTime = startTime + processes[j].burst_time;
      //for(int i = j; i < processLimit; i++)
      // {
      //       if(processes[i].ready == 1)
      //       {
      //             processes[i].ready = 0;
      //       }
      // }

  //}







 return 0;

}
