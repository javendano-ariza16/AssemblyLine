// Name: Juan David Avendano
// Seneca Student ID: 16509521
// Seneca email: javendan0-ariza@myseneca.ca
// Date of completion: 24 March 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H
#include "Station.h"
namespace sdds {
	struct Item
	{
	public:
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder
	{
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem{nullptr};
		static size_t m_widthField;

	public:
		CustomerOrder() = default;
		//The constructor extracts Customer Order, Order Name, The list of Items
		CustomerOrder(const std::string& str);
		// Copy constructor (Throw an exception)
		CustomerOrder(const CustomerOrder& scr);
		// Copy assignment operator (deleted)
		CustomerOrder& operator=(const CustomerOrder& other) = delete;
		//Move assigment 
		CustomerOrder(CustomerOrder&& scr) noexcept;
		//Move operator
		CustomerOrder& operator=(CustomerOrder&& scr)noexcept;
		//Destructor
		~CustomerOrder();

		//Other class methods
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !SDDS_CUSTOMER_ORDER_H

