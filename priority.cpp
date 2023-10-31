Sanzid Arefin Shihab
#include<bits/stdc++.h>
using namespace std;

int main()
{

//    int n=4;
//    int process[n]= {1,2,3,4};
//    int arrival_time[n]= {1,2,1,4};
//    int burst_time[n]= {3,4,2,4};


    int n=5;
    int process[n]= {1,2,3,4,5};
    int arrival_time[n]= {1,2,5,1,2};
    int burst_time[n]= {4,3,2,2,1};
    int priority[n] = {3,1,4,5,2};
    // Ans: 4,5,2,3,1


    cout<<"Processes before sort:    ";
    for(int i=0; i<n; i++)
    {
        cout<<process[i]<<" ";
    }
    cout<<endl;
    cout<<"Arrival Time before sort: ";
    for(int i=0; i<n; i++)
    {
        cout<<arrival_time[i]<<" ";
    }
    cout<<endl;
    cout<<"Burst Time before sort:   ";
    for(int i=0; i<n; i++)
    {
        cout<<burst_time[i]<<" ";
    }
    cout<<endl;
    cout<<"Priority before sort:     ";
    for(int i=0; i<n; i++)
    {
        cout<<priority[i]<<" ";
    }
    cout<<endl;
    cout<<endl;

    //Sort by Arrival Time
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            int tempTosort;
            if(arrival_time[j]<arrival_time[i])
            {
                //sort arrivalTime
                tempTosort = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = tempTosort;

                //sort process
                tempTosort = process[i];
                process[i] = process[j];
                process[j] = tempTosort;

                //sort burstTime
                tempTosort = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = tempTosort;

                //sort priority
                tempTosort = priority[i];
                priority[i] = priority[j];
                priority[j] = tempTosort;
            }
            else if(arrival_time[j]==arrival_time[i])
            {
                if(priority[j]<priority[i])
                {
                    //sort arrivalTime
                    tempTosort = arrival_time[i];
                    arrival_time[i] = arrival_time[j];
                    arrival_time[j] = tempTosort;

                    //sort process
                    tempTosort = process[i];
                    process[i] = process[j];
                    process[j] = tempTosort;

                    //sort burstTime
                    tempTosort = burst_time[i];
                    burst_time[i] = burst_time[j];
                    burst_time[j] = tempTosort;

                    //sort priority
                    tempTosort = priority[i];
                    priority[i] = priority[j];
                    priority[j] = tempTosort;
                }
            }
        }
    }

    cout<<"Processes after sort:     ";
    for(int i=0; i<n; i++)
    {
        cout<<process[i]<<" ";
    }
    cout<<endl;
    cout<<"Arrival Time after sort:  ";
    for(int i=0; i<n; i++)
    {
        cout<<arrival_time[i]<<" ";
    }
    cout<<endl;
    cout<<"Burst Time after sort:    ";
    for(int i=0; i<n; i++)
    {
        cout<<burst_time[i]<<" ";
    }
    cout<<endl;
    cout<<"Priority after sort:      ";
    for(int i=0; i<n; i++)
    {
        cout<<priority[i]<<" ";
    }
    cout<<endl;
    cout<<endl;

    int temp_time=0;
    int result[n];

    for(int i=0; i<n; i++)
    {
        if(arrival_time[i]<=temp_time)
        {
            result[i] = process[i];
            cout<<result[i]<<"\n";
            temp_time = temp_time + burst_time[i];
        }
        else if(arrival_time[i]>temp_time)
        {
            int idle_time = arrival_time[i]-temp_time;
            temp_time = temp_time + burst_time[i] + idle_time;
            result[i] = process[i];
            cout<<result[i]<<"\n";
        }

        // Re Sort Priority
        int temp_priority = 1000;
        int flag = 0;
        int temp_index;
        for(int j=i+1; j<n; j++)
        {
            if(arrival_time[j]<=temp_time)
            {
                if(priority[j]<temp_priority)
                {
                    temp_priority = priority[j];
                    temp_index = j;
                    flag = 1;
                }
            }

        }
        if(flag == 1)
        {
            int tempTosort;
            //sort arrivalTime
            tempTosort = arrival_time[i+1];
            arrival_time[i+1] = arrival_time[temp_index];
            arrival_time[temp_index] = tempTosort;

            //sort process
            tempTosort = process[i+1];
            process[i+1] = process[temp_index];
            process[temp_index] = tempTosort;

            //sort burstTime
            tempTosort = burst_time[i+1];
            burst_time[i+1] = burst_time[temp_index];
            burst_time[temp_index] = tempTosort;

            //sort priority
            tempTosort = priority[i+1];
            priority[i+1] = priority[temp_index];
            priority[temp_index] = tempTosort;
        }

    }
    for(int i=0; i<n; i++)
    {
        cout<<" >> "<<"P:"<<result[i];
    }


}
