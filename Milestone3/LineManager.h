// Name: Juan David Avendano
// Seneca Student ID: 165095217
// Seneca email: javendano-ariza@myseneca.ca
// Date of completion: 08 April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINE_MANAGER_H
#define SDDS_LINE_MANAGER_H
#include <vector>
#include<iostream>
#include"Workstation.h"

namespace sdds {

	class LineManager {
		std::vector<Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder{ 0 };
		Workstation* m_firstStation{ nullptr };
	public:
		LineManager() = default;
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_LINE_MANAGER_H_
