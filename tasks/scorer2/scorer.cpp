#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    tasks_student_[student_name].erase(task_name);
    if (tasks_student_[student_name].empty()) {
        Scorer::tasks_student_.erase(student_name);
    }
}
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    Scorer::tasks_student_[student_name].insert(task_name);
    if (Scorer::tasks_student_[student_name].empty()) {
        Scorer::tasks_student_.erase(student_name);
    }
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    Scorer::merge_status_[student_name].insert(task_name);
    Scorer::tasks_student_[student_name].erase(task_name);
    if (Scorer::tasks_student_[student_name].empty()) {
        Scorer::tasks_student_.erase(student_name);
    }
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    Scorer::merge_status_[student_name].erase(task_name);
}
void Scorer::Reset() {
    Scorer::merge_status_.clear();
    Scorer::tasks_student_.clear();
}
ScoreTable Scorer::GetScoreTable() {
    for (auto& student : merge_status_) {
        for (auto& del_task : student.second) {
            tasks_student_[student.first].erase(del_task);
        }
        if (Scorer::tasks_student_[student.first].empty()) {
            Scorer::tasks_student_.erase(student.first);
        }
    }
    return Scorer::tasks_student_;
}