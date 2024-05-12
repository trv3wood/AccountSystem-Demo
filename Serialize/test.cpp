#include "User.h"
int main() {
    User user("John Ditor", 17);
    QFile file("user.dat");
    user.serialize(file);
    User* user2 = dynamic_cast<User*>(user.deserialize(file));
    std::cout << *user2 << '\n';
    return 0;
}