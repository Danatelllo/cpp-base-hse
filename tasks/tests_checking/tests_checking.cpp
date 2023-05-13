#include <tests_checking.h>
#include <deque>
#include <string>
std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::vector<std::string> answer;
    std::deque<std::string> moves;
    for (auto action : student_actions) {
        if (action.side == Side::Top) {
            moves.push_front(action.name);
        } else {
            moves.push_back(action.name);
        }
    }
    for (auto query : queries) {
        answer.push_back(moves[query - 1]);
    }
    return answer;
}
