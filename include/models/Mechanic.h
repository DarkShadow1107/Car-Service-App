#ifndef MECHANIC_H
#define MECHANIC_H
#include <string>

class Mechanic {
private:
    std::string name;
    std::string specialization;
public:
    Mechanic();
    Mechanic(const std::string&, const std::string&);
    void showDetails() const;
    const std::string& getName() const;
    const std::string& getSpecialization() const;
};

#endif // MECHANIC_H
