// Name: Juan David Avendano
// Seneca Student ID: 16509521
// Seneca email: javendan0-ariza@myseneca.ca
// Date of completion: 17 March 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter{};
	//sets the field width of the current object to the value of parameter newWidth
	void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; };

	//returns the field width of the current object
	size_t Utilities::getFieldWidth() const { return m_widthField; };

	// extracts a token from string str referred to by the first parameter.
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

		std::string tok;
		size_t endIndex = str.find(this->m_delimiter, next_pos);
		if (endIndex != std::string::npos)
		{
			tok = str.substr(next_pos, endIndex - next_pos);
			next_pos = endIndex + 1;
			more = true;
		}
		else
		{
			tok = str.substr(next_pos);
			more = false;
		}
		tok.erase(0,tok.find_first_not_of(" \t\r\n"));
		tok.erase(tok.find_last_not_of(" \t\r\n") + 1);
		(tok.length() > m_widthField ) ? m_widthField = tok.length() : m_widthField;
		if (tok.empty()) {
			more = false;
			throw "ERROR: Token is empty!";
		}
		return tok;
	};


	void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

	// Returns the delimiter for this class.
	char Utilities::getDelimiter() { return m_delimiter; }

}