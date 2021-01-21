#include "../../src/models/Invoice.h"

using namespace sales_taxes;

Invoice::Invoice() :
	items_list(std::list <std::shared_ptr<InvoiceItem>>()),
	total_price(0), total_sales_taxes(0), total_amount(0) {}

Invoice::Invoice(const std::list <std::shared_ptr<InvoiceItem>>& items_list) :
	items_list(items_list), total_price(0), total_sales_taxes(0), total_amount(0) 
{
	for (auto& it : items_list)
		if (it == nullptr)
			throw InvoiceException("Invoice item can't be null.");
}

Invoice::Invoice(const Invoice& in) :
	total_sales_taxes(in.total_sales_taxes), total_price(in.total_price) 
{
	// Return copy of items_list
	std::list<std::shared_ptr<InvoiceItem>> copy_items_list = in.get_items();
	for (auto& it : copy_items_list) 
	{
		items_list.push_back(std::make_shared<InvoiceItem>(*it));
	}
}

void Invoice::remove_item(std::shared_ptr<InvoiceItem> item) 
{
	if (item == nullptr)
		return;

	// Find and delete element if present
	for (auto it = items_list.begin(); it != items_list.end(); ++it)
	{
		if (*it == nullptr)
			throw InvoiceException("Invoice item can't be null.");

		std::shared_ptr<InvoiceItem>& list_item = *it;
		if (*list_item == *item) 
		{
			total_price -= (*it)->get_total_price();
			total_sales_taxes -= (*it)->get_total_sales_taxes();
			total_amount = total_price + total_sales_taxes;
			items_list.erase(it);
			return;
		}
	}
}

void Invoice::add_item(std::shared_ptr<InvoiceItem> item) 
{
	if (item == nullptr)
		return;

	// If item not present add it
	if (std::find(items_list.begin(), items_list.end(), item) == items_list.end()) 
	{
		items_list.push_back(item);
		total_price += item->get_total_price();
		total_sales_taxes += item->get_total_sales_taxes();
		total_amount = total_price + total_sales_taxes;
	}
}

std::list<std::shared_ptr<InvoiceItem>> Invoice::get_items() const 
{
	// An invoice has 1..* InvoiceItems
	if (items_list.empty())
		throw InvoiceException("Invoice should have at least an invoice item.");

	// Return copy of items_list
	std::list<std::shared_ptr<InvoiceItem>> copy_items_list;
	for (auto& it : items_list) 
	{
		if (it == nullptr)
			throw InvoiceException("Invoice item can't be null.");

		copy_items_list.push_back(std::make_shared<InvoiceItem>(*it));
	}

	return copy_items_list;
}

int Invoice::get_items_list_size() const 
{
	return items_list.size();
}

double Invoice::get_total_sales_taxes() 
{
	return total_sales_taxes;
}

double Invoice::get_total_amount() 
{
	return total_amount;
}

double Invoice::get_total_price() 
{
	return total_price;
}

std::string Invoice::get_invoice() 
{
	std::string invoice = "";
	for (const auto& it : items_list) 
	{
		invoice += it->get_invoice_item() + "\n";
	}

	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << total_sales_taxes;
	std::string truncated_total_sales_taxes = ss.str();
	invoice += "Sales Taxes : " + truncated_total_sales_taxes + "\n";

	std::ostringstream s2;
	s2 << std::fixed << std::setprecision(2) << total_amount;
	std::string truncated_total_amount = s2.str();
	invoice += "Total : " + truncated_total_amount;

	return invoice;
}

std::ostream& sales_taxes::operator<<(std::ostream& os, const Invoice& in) 
{
	for (const auto& it : in.get_items()) 
	{
		os << *it << '\n';
	}
	os << "Sales taxes: " << in.total_sales_taxes << '\n';
	os << "Total: " << in.total_amount;

	return os;
}