#include "../../src/models/InvoiceItem.h"

using namespace sales_taxes;

InvoiceItem::InvoiceItem(std::shared_ptr<Product> product, unsigned int quantity) : product(product) 
{
	if (product == nullptr)
		throw InvoiceItemException("Product can't be null");

	set_quantity(quantity);
}

InvoiceItem::InvoiceItem(const InvoiceItem& r) : InvoiceItem(r.product, r.quantity) {};

std::shared_ptr<Product> InvoiceItem::get_product() const 
{
	if (product == nullptr)
		throw InvoiceItemException("Product can't be null");

	// Return copy of product
	return std::make_shared<Product>(*product);
}

unsigned long int InvoiceItem::get_quantity() const 
{
	return quantity;
}

void InvoiceItem::set_quantity(unsigned int quantity) 
{
	if (quantity < 1)
		throw InvoiceItemException("Invoice item should have a quantity >= 1");

	this->quantity = quantity;

	total_price = product->get_price() * quantity;
	total_sales_taxes = quantity * product->calculate_taxes();
	total_amount = total_price + total_sales_taxes;
}

void InvoiceItem::increment_quantity() 
{
	set_quantity(++quantity);
}

void InvoiceItem::decrement_quantity() 
{
	if (quantity <= 1)
		throw InvoiceItemException("Invoice item should have a quantity >= 1");

	set_quantity(--quantity);
}

double InvoiceItem::get_total_price() 
{
	return total_price;
}

double InvoiceItem::get_total_sales_taxes() 
{
	return total_sales_taxes;
}

double InvoiceItem::get_total_amount() 
{
	return total_amount;
}

std::string InvoiceItem::get_invoice_item() 
{
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << total_amount;
	std::string truncated_total_amount = ss.str();

	if (product->get_product_origin()->get_origin() == ProductOrigin::Origin::imported)
		return std::to_string(quantity) + " imported " + product->get_name() + " : "
		+ truncated_total_amount;
	else
		return std::to_string(quantity) + " " + product->get_name() + " : "
		+ truncated_total_amount;

}

std::ostream& sales_taxes::operator<<(std::ostream& os, const InvoiceItem& in)
{
	os << in.quantity << " " << in.product->get_name() << ": " << in.total_amount;

	return os;
}

bool sales_taxes::operator==(const InvoiceItem& iid, const InvoiceItem& iis)
{
	return iid.get_product() == iis.get_product()
		&& iid.get_quantity() == iis.get_quantity();
}
