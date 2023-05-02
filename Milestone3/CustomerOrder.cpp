// Name: Juan David Avendano
// Seneca Student ID: 16509521
// Seneca email: javendan0-ariza@myseneca.ca
// Date of completion: 24 March 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Station.h"
#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "CustomerOrder.h"
#include <vector>

namespace sdds {
	size_t CustomerOrder::m_widthField{};
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities utils{};
		size_t next_pos{ 0 };
		size_t startCpy{ 0 };
		bool more = true;
		m_cntItem = 0;

		m_name = utils.extractToken(str, next_pos, more);
		m_product = utils.extractToken(str, next_pos, more);

		startCpy = next_pos;

		while (more) {
			utils.extractToken(str, next_pos, more);
			m_cntItem++;
		}

		next_pos = startCpy;
		more = true;
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(utils.extractToken(str, next_pos, more));
		}
		(m_widthField < utils.getFieldWidth()) ? m_widthField = utils.getFieldWidth() : m_widthField;
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& scr)
	{
		throw std::string("You can not copy CustomerOrder object");
	};
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
		*this = std::move(other);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		if (this != &other) {
			if (m_lstItem)
			{
				for (size_t i = 0; i < m_cntItem; i++) {
					// Deallocating memory for individual items
					delete m_lstItem[i];
				}
				// Deallocating memory for the array of item pointers
				delete[] m_lstItem;
			}

			m_name = other.m_name;
			other.m_name = "";
			m_product = other.m_product;
			other.m_product = "";
			m_cntItem = other.m_cntItem;
			other.m_cntItem = 0;
			m_lstItem = other.m_lstItem;
			other.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		if (m_lstItem)
		{
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}
	}


	bool CustomerOrder::isOrderFilled() const
	{
		bool flag = true;
		size_t i = 0;
		while (flag && i < m_cntItem)
		{
			flag = m_lstItem[i]->m_isFilled;
			i++;
		}
		return flag;
	};
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		std::vector<Item>byName;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				byName.push_back(*m_lstItem[i]);
			}
		}
		for (auto& x : byName)
		{
			if (x.m_isFilled != true)
				return false;
		}
		return true;
	};
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    ";
					os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << ']' << std::endl;
					return;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << ']' << std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << '[';
			os << std::right;
			os << std::setw(6) <<std::setfill('0') << m_lstItem[i]->m_serialNumber;
			os << std::left;
			os << "] " << std::setfill(' ');
			os << std::setw(m_widthField+2);
			os << m_lstItem[i]->m_itemName;
			if (m_lstItem[i]->m_isFilled)
			{
				os << " - FILLED" << std::endl;
			}
			else
			{
				os << " - TO BE FILLED" << std::endl;
			}
		}
	}
}