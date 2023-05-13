#include "scorer.h"

bool CompareStudent(const Event* student1, const Event* student2) {
        return student1->time > student2->time;
}
ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> student_event;
    std::map<StudentName, std::set<TaskName>> answer;
    std::map<StudentName, std::map<TaskName, std::vector<EventType>>> status_merge;
    for (size_t i = 0; i < events.size(); ++i) {
        student_event.push_back(&events[i]);
    }
    std::sort(student_event.begin(), student_event.end(), CompareStudent);
    for (size_t i = 0; i < events.size(); ++i) {
        if ((events[i].event_type == EventType::CheckSuccess || events[i].event_type == EventType::CheckFailed) &&
            events[i].time < score_time) {
            if (status_merge[events[i].student_name][events[i].task_name].empty()) {
                status_merge[events[i].student_name][events[i].task_name] = {events[i].event_type,
                                                                             EventType::MergeRequestClosed};
            } else if (events[i].time < score_time) {
                status_merge[events[i].student_name][events[i].task_name][0] = events[i].event_type;
            }
        } else if ((events[i].event_type == EventType::MergeRequestClosed ||
                    events[i].event_type == EventType::MergeRequestOpen) &&
                   events[i].time < score_time) {
            if (status_merge[events[i].student_name][events[i].task_name].empty()) {
                status_merge[events[i].student_name][events[i].task_name] = {EventType::CheckFailed,
                                                                             events[i].event_type};
            } else if (events[i].time < score_time) {
                status_merge[events[i].student_name][events[i].task_name][1] = events[i].event_type;
            }
        }
    }
    for (auto cont : status_merge) {
        for (auto student_info : cont.second) {
            if (student_info.second[0] == EventType::CheckSuccess &&
                student_info.second[1] == EventType::MergeRequestClosed) {
                answer[cont.first].insert(student_info.first);
            }
        }
    }
    return answer;
}