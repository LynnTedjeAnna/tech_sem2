//
// Created by Lynn Tedje Anna Meindertsma on 05/03/2024.
//
#include <iostream>
#include "animal.hpp"

//constructor
Animal::Animal(uint32_t chip_reg_number, Simple_Date date_of_birth, std::string name) {
    this->chip_reg_number = chip_reg_number;
    this->date_of_birth =   date_of_birth;
    this->name =            name;
    this->reserved =        false;
}
// Getter methods
uint32_t Animal::getChipIdNumber() const {
    return this->chip_reg_number;
}

Simple_Date Animal::get_date_of_birth() const {
    return this->date_of_birth;
}

std::string Animal::get_name() const {
    return this->name;
}

bool Animal::get_reserved() const {
    return this->reserved;
}

std::string Animal::to_string() {
    std::string isReservedString = this->reserved ? "reserved" : "not reserved";
    return std::to_string(this->chip_reg_number) + ", " +
           this->date_of_birth.to_string() + ", " +
           this->name + ", " +
           isReservedString;
}
