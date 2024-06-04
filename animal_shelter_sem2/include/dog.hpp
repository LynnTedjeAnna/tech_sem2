//
// Created by Lynn Tedje Anna Meindertsma on 05/03/2024.
//

#ifndef DOG_HPP
#define DOG_HPP

#include "animal.hpp"
#include "simple_date.hpp"

class Dog : public Animal {
public:
    // Constructor declaration
    Dog(uint64_t tagID, Simple_Date date_of_birth,
        std::string name, Simple_Date lastWalkDate);

    // Getter method for last walk date
    Simple_Date get_lastWalkDate() const;

    // Override method to retrieve information about the dog
    std::string to_string();

private:
    Simple_Date lastWalkDate;
};

#endif //DOG_HPP
