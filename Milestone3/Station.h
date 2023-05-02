// Name: Juan David Avendano
// Seneca Student ID: 16509521
// Seneca email: javendan0-ariza@myseneca.ca
// Date of completion: 17 March 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>

namespace sdds {
    class Station {
    private:
        size_t m_id{};
        std::string m_item{};
        std::string m_description{};
        size_t m_serial{};
        size_t m_quantity{ 0 };
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station() = default;
        // This constructor extracts name, starting serial number, and quantity from the string
        Station(const std::string str);
        // Returns the name of the current Station object
        const std::string& getItemName() const;
        // Returns the next serial number to be used on the assembly line and increments m_serialNumber
        size_t getNextSerialNumber();
        // Returns the remaining quantity of items in the Station object
        size_t getQuantity() const;
        // Subtracts 1 from the available quantity; should not drop below 0
        void updateQuantity();
        // Inserts information about the current object into stream os
        void display(std::ostream& os, bool full) const;
    };
}

#endif // SDDS_STATION_H