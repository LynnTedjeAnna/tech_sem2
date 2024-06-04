//
// Created by Lynn Tedje Anna Meindertsma on 05/03/2024.
//

#include "dog.hpp"

// TODO: Modify the constructor. Make sure it initializes all properties of the class.

// Constructor definition
Dog::Dog    (uint64_t tagID, Simple_Date date_of_birth, std::string name, Simple_Date lastWalkDate)
    :Animal (tagID, date_of_birth, name), lastWalkDate(lastWalkDate) {}

// Getter method for last walk date
Simple_Date Dog::get_lastWalkDate() const {
    return this->lastWalkDate;
}

// Override method to retrieve information about the dog

/// <summary>
/// Retrieve information about this dog
///
/// Note: Every class inherits (automagically) from the 'Object' class,
/// which contains the virtual ToString() method which you can override.
/// </summary>
/// <returns>A string containing the information of this animal.
///          The format of the returned string is
///          "Dog: <ChipRegistrationNumber>, <DateOfBirth>, <Name>, <IsReserved>, <LastWalkDate>"
///          Where: IsReserved will be "reserved" if reserved or "not reserved" otherwise.
///                 LastWalkDate will be "unknown" if unknown or the date of the last doggywalk otherwise.
/// </returns>
std::string Dog::to_string() {
    std::string isReservedString = this->get_reserved() ? "reserved" : "not reserved";
    std::string lastWalkDateString = this->lastWalkDate.is_valid() ? this->lastWalkDate.to_string() : "unknown";
    return "Dog: " + std::to_string(this->getChipIdNumber()) + ", " +
           this->get_date_of_birth().to_string() + ", " +
           this->get_name() + ", " +
           isReservedString + ", " +
           lastWalkDateString;
}
// TODO: Put your own code here to make the method return the string specified in the method description.