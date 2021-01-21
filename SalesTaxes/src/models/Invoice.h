#pragma once
#include "../../src/models/InvoiceItem.h"
#include <list>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

namespace sales_taxes 
{
	// Standard runtime exception class
	class InvoiceException : public std::runtime_error 
	{
	public:
		InvoiceException(const std::string& msg = "") :
			runtime_error(msg) {}
	};

	// Class that represents the Invoice
	class Invoice 
	{
	public:
		// Constructors
		Invoice();
		Invoice(const std::list <std::shared_ptr<InvoiceItem>>& items_list);

		// Copy constructor 
		Invoice(const Invoice& i);

		// Operations on items list
		void remove_item(std::shared_ptr<InvoiceItem> item);
		void add_item(std::shared_ptr<InvoiceItem> item);
		std::list<std::shared_ptr<InvoiceItem>> get_items() const;
		int get_items_list_size() const;

		// Returns total taxes of products
		double get_total_sales_taxes();
		// Returns total prices of products before taxes
		double get_total_price();
		// Returns total 
		double get_total_amount();

		// Prints invoice
		std::string get_invoice();
		friend std::ostream& operator<<(std::ostream& os, const Invoice& pr);

	private:
		std::list <std::shared_ptr<InvoiceItem>> items_list;
		double total_sales_taxes;
		double total_price;
		double total_amount;
	};
	
	std::ostream& operator<<(std::ostream& os, const Invoice& pr);
}
