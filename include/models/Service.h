#ifndef SERVICE_H
#define SERVICE_H
#include <string>

class Service {
private:
    std::string name;
    double price;
public:
    Service();
    Service(const std::string&, double);
    void showDetails() const;
    const std::string& getName() const;
    double getPrice() const;
};

#endif // SERVICE_H
