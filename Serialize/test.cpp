#include "User.h"
int main() {
    User user("John Ditor", 17);
    std::cout << user << std::endl;
    User user2(QFileInfo("John Ditor.dat"));
    std::cout << user2 << std::endl;
    return 0;
}