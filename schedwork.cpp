#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& hours,
    int day,
    int num
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	 AvailabilityMatrix temp = avail;
   // cout<< "here" << endl;
    if(avail.size() == 0U){
        return false;
    }
    //cout << avail.size() << endl;
    sched.clear();
    // Add your code below
    vector<int> hours;
    for(int i =0; i<avail.size(); i++){
         hours.push_back(0);
    }
		sched.resize(avail.size());
		for(int i=0; i<sched.size(); i++){
			sched[i].resize(dailyNeed);
		}
    int day = avail.size();
    // vector<vector<int>>avail_time;
    // for(int i=0; i<avail.size();i++){
    //     for(int j=0; j<avail[0].size; j++){
    //         if(avail[i][j]){
    //             avail[i].push_back(j);
    //         }
    //     }
    // }
    return scheduleHelper(temp,dailyNeed,maxShifts,sched,hours,day,0);



}

// bool isValid(vector<size_t>& hours,const size_t maxShifts){
//     for(vector<size_t> iterator it= hours.begin(); it!=hours.end(); ++it){
//         if(*it>=maxShifts) return false;
//     }
//     return true;
// }

bool scheduleHelper(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& hours,
    int day,
    int num
) {
    //cout<< "here" << endl;
    if(day==0){
        return true;
    }
    else if(num == dailyNeed){
        return scheduleHelper(avail,dailyNeed,maxShifts,sched,hours,day-1,0);
    }
		else{
			for(int i = 0; i<avail[0].size(); i++){
				//cout<< "here" << endl;
					if(avail[avail.size()-day][i]){
						//cout<< "here" << avail.size()-day << " " << sched.size() << endl;
							sched[avail.size()-day][num]=i;
							//cout<< "here" << endl;
							hours[i] += 1;
							avail[avail.size()-day][i] = 0;
							if(hours[i]<=maxShifts){
								  //cout<< "here" << endl;
									bool result = scheduleHelper(avail,dailyNeed,maxShifts,sched,hours,day,num+1);
									if(result){
											return true;
									}
							}
						hours[i] -= 1;
						sched[avail.size()-day][num]=INVALID_ID;
						avail[avail.size()-day][i] = 1;
					}
					//avail[avail.size()-day][i] = 1;       
			}
		}

    return false;
}