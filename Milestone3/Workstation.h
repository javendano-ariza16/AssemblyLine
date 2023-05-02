// Name: Juan David Avendano
// Seneca Student ID: 165095217
// Seneca email: javendano-ariza@myseneca.ca
// Date of completion: 08 April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include<deque>
#include<iostream>
#include<string>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station{
		std::deque<CustomerOrder>m_orders;
		Workstation* m_nextStation{nullptr};
	public:
		Workstation& operator=(Workstation&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		Workstation(const std::string& record) :Station(record){};
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};

}


#endif // !SDDS_WORKSTATION_H
