#include <iostream>
#include <string>
#include <sstream>

#include "ActivityBST.h"

using namespace std;

void print_calendar(const ActivityBST& cal) {
    cout << "Calender:\n" << cal;
    ActivityBST study_sessions(cal);
    study_sessions.add(1000, "study");
    study_sessions.add(1600, "study");
    cout << "Study sessions with calender:\n"
        << study_sessions;
    ActivityBST meetings;
    meetings.add(930, "meeting");
    meetings.add(2500, "meeting");
    cout << "Calender with meetings:\n" << cal + meetings;
    ActivityBST complete_calendar;
    complete_calendar += study_sessions + meetings + cal;
    cout << "Complete calendar:\n" << complete_calendar;
}

int main() {

    
    ActivityBST a1;
    a1.add(700, "run");
    a1.add(1200, "break");
    a1.add(800, "breakfast");
    ActivityBST a2(a1);
    a2.add(600,"journaling");
    print_calendar(a2);
    
    return 0;
}
