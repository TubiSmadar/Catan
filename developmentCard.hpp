// Tuvia Smadar
// gunslokij@gmail.com
#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>
using namespace std;

class DevelopmentCard {
public:
    DevelopmentCard(const string& type);
    string getType() const;

private:
    string type;
};

#endif // DEVELOPMENTCARD_HPP
