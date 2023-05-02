// Name: Juan David Avendano
// Seneca Student ID: 165095217
// Seneca email: javendano-ariza@myseneca.ca
// Date of completion: 08 April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<deque>
#include<iostream>
#include"Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;
	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	};
	bool Workstation::attemptToMoveOrder() {
		bool moved{};
		if (!m_orders.empty()) {
			if (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName())) {
				if (!m_nextStation) {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(std::move(m_orders.front()));
					}
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
					}
				}
				// Move to next station
				else {
					*m_nextStation += std::move(m_orders.front());
				}
				m_orders.pop_front();
				moved = true;
			}
		}
		return moved;
	}
	void Workstation::setNextStation(Workstation* station) {this->m_nextStation = station;};
	Workstation* Workstation::getNextStation() const {return m_nextStation;};
	void Workstation::display(std::ostream& os) const {
		os << getItemName() << " --> ";
		if (m_nextStation)
		{
			os<<m_nextStation->getItemName();
		}
		else
		{
			os << "End of Line";
		}
		os << std::endl;
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}