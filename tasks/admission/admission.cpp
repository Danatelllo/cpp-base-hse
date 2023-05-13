#include "admission.h"
#include "vector"
#include "tuple"
#include "string"
#include "unordered_map"

bool CompareStudent(const Applicant* student1, const Applicant* student2) {
    if (student1->points != student2->points) {
        return student1->points > student2->points;
    } else if (std::tie(student1->student.birth_date.year, student1->student.birth_date.month,
                        student1->student.birth_date.day) != std::tie(student2->student.birth_date.year,
                                                                      student2->student.birth_date.month,
                                                                      student2->student.birth_date.day)) {
        return std::tie(student1->student.birth_date.year, student1->student.birth_date.month,
                        student1->student.birth_date.day) < std::tie(student2->student.birth_date.year,
                                                                     student2->student.birth_date.month,
                                                                     student2->student.birth_date.day);
    } else {
        return student1->student.name > student2->student.name;
    }
}
bool CompareEnd(const Student* student1, const Student* student2) {
    if (student1->name == student2->name) {
        return std::tie(student1->birth_date.year, student1->birth_date.month, student1->birth_date.day) <
               std::tie(student2->birth_date.year, student2->birth_date.month, student2->birth_date.day);

    } else {
        return student1->name < student2->name;
    }
}
AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::unordered_map<std::string, std::vector<const Student*>> answer;
    std::unordered_map<std::string, const University*> list_universities;
    std::vector<const Applicant*> sorted_students;
    for (size_t i = 0; i < applicants.size(); ++i) {
        sorted_students.push_back(&applicants[i]);
    }
    for (size_t j = 0; j < universities.size(); ++j) {
        list_universities[universities[j].name] = &universities[j];
    }
    std::sort(sorted_students.begin(), sorted_students.end(), CompareStudent);
    for (auto student : sorted_students) {
        for (const auto& student_wish : student->wish_list) {
            if (list_universities[student_wish]->max_students > answer[student_wish].size()) {
                answer[student_wish].push_back(&(student->student));
                break;
            }
        }
    }
    for (auto& admission_result : answer) {
        std::sort(admission_result.second.begin(), admission_result.second.end(), CompareEnd);
    }
    return answer;
}