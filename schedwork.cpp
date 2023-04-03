#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // delete if necessary
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


// Add your implementation of schedule() and other helper functions here

bool isWorkerScheduled(
    const Worker_T& currWorker,
    const vector<vector<Worker_T>>& sched,
    const int& day
) {
    if (sched[day].empty()) {
        return true;
    }
    else {
        for (const auto& worker : sched[day]) {
            if (worker == currWorker) {
                return false;
            }
        }
    }
    return true;
}

void scheduleHelper(
    const AvailabilityMatrix& avail,
    vector<vector<Worker_T>>& sched,
    int shiftNum[],
    int& day,
    const size_t dailyNeed,
    const size_t maxShifts,
    bool& valid
) {
    for (size_t i = 0; i < avail[0].size(); ++i) {
        Worker_T currWorker = static_cast<Worker_T>(i);
        if (avail[day][i] && shiftNum[currWorker] < static_cast<int>(maxShifts) && isWorkerScheduled(currWorker, sched, day)) {
            ++shiftNum[currWorker];
            sched[day].push_back(currWorker);
            if (sched[day].size() == dailyNeed) {
                if (day < static_cast<int>(avail.size() - 1)) {
                    ++day;
                    scheduleHelper(avail, sched, shiftNum, day, dailyNeed, maxShifts, valid);
                    if (valid) {
                        return;
                    }
                    else {
                        --shiftNum[currWorker];
                        --day;
                        sched[day].pop_back();
                    }
                }
                else {
                    valid = true;
                    return;
                }
            }
            else {
                scheduleHelper(avail, sched, shiftNum, day, dailyNeed, maxShifts, valid);
                if (valid) {
                    return;
                }
                else {
                    sched[day].pop_back();
                    --shiftNum[currWorker];
                }
            }
        }
    }
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if (avail.empty()) {
        return false;
    }
    sched.clear();
    vector<Worker_T> vecId;
    bool valid = false;
    int day = 0;
    for (size_t i = 0; i < avail.size(); ++i) {
        sched.push_back(vecId);
    }
    int shiftNum[avail[0].size()];
    memset(shiftNum, 0, sizeof(shiftNum));
    scheduleHelper(avail, sched, shiftNum, day, dailyNeed, maxShifts, valid);
    return valid;
}


