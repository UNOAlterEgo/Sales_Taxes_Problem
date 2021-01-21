#include "../../src/models/Product.h"

using namespace sales_taxes;

Product::Product(const std::string name, const double price, std::shared_ptr <ProductType>  type,
	std::shared_ptr <ProductOrigin> origin) : name(name), price(price), type(type), origin(origin) 
{
	if (type == nullptr)
		throw ProductException("Product type can't be null");

	if (origin == nullptr)
		throw ProductException("Product origin can't be null");
}

Product::Product(const Product& pr) : Product(pr.name, pr.price, pr.type, pr.origin) {}

std::string Product::get_name() const 
{
	return name;
}

void Product::set_name(const std::string name) 
{
	this->name = name;
}

double Product::get_price() const 
{
	if (price < 0)
		throw ProductException("Price should be greater or equal to 0");

	return price;
}

void Product::set_price(const double price) 
{
	this->price = price;
}

std::shared_ptr <ProductType> Product::get_product_type() const 
{
	if (type == nullptr)
		throw ProductException("Product type can't be null");

	return std::make_shared<ProductType>(*type);
}
void Product::set_product_type(std::shared_ptr <ProductType> type) 
{
	if (type == nullptr)
		return;

	this->type = type;
}

std::shared_ptr <ProductOrigin> Product::get_product_origin() const 
{
	if (origin == nullptr)
		throw ProductException("Product origin can't be null");

	return std::make_shared<ProductOrigin>(*origin);
}

void Product::set_product_origin(std::shared_ptr <ProductOrigin> origin) 
{
	if (type == nullptr)
		return;

	this->origin = origin;
}

double Product::calculate_taxes() const 
{
	return type->calculate_tax(price) + origin->calculate_tax(price);
}

std::ostream& sales_taxes::operator<<(std::ostream& os, const Product& pr) 
{
	os << pr.name << " " << pr.price << " " << pr.origin << " " << pr.type;
	return os;
}

bool sales_taxes::operator==(const Product& prd, const Product& prs) 
{
	return prd.name == prs.name && prd.origin == prs.origin
		&& prd.type == prs.type && prd.origin == prs.origin
		&& prd.price == prs.price;
}
