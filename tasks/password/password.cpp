#include "password.h"
bool ValidatePassword(const std::string &password) {
    if (password.size() < 8 || password.size() > 14) {
        return false;
    } else {
        bool lowercase = false;
        bool figure = false;
        bool uppercase = false;
        bool other = false;
        for (char i : password) {
            if (static_cast<int>(i) < 33 || static_cast<int>(i) > 126) {
                return false;
            } else {
                if (std::isupper(i)) {
                    uppercase = true;
                } else if (std::isdigit(i)) {
                    figure = true;
                } else if (std::islower(i)) {
                    lowercase = true;
                } else {
                    other = true;
                }
            }
        }
        return (other + lowercase + figure + uppercase >= 3);
    }
}