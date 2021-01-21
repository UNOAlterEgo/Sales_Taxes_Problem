#include "ProductType.h"

using namespace sales_taxes;

ProductType::ProductType(const ProductType::Type type) : type(type) 
{
    switch (type) 
    {
    case Type::book:
    case Type::food:
    case Type::medical:
        tax_rate = std::make_shared<TaxRate>(TaxRate::RateTypes::exempted);
        break;
    case Type::other:
        tax_rate = std::make_shared<TaxRate>(TaxRate::RateTypes::basic_tax);
        break;
    default:
        throw ProductTypeException("Invalid product type");
    }
};

ProductType::ProductType(const ProductType& pt) : ProductType(pt.type) {}

ProductType::Type ProductType::get_type() const 
{
    return type;
}

void ProductType::set_type(const Type type) 
{
    this->type = type;
}

TaxRate ProductType::get_tax_rate() const 
{
    return *tax_rate;
}

void ProductType::set_tax_rate(const std::shared_ptr<TaxRate> tax_rate) 
{
    this->tax_rate = tax_rate;
}

double ProductType::calculate_tax(double price) const 
{
    if (price < 0)
        throw ProductTypeException("Price should be greater or equal to 0.");

    return tax_rate->calculate_tax(price);
}

bool sales_taxes::operator==(const ProductType& ptd, const ProductType& pts) 
{
    return ptd.tax_rate == pts.tax_rate && ptd.type == pts.type;
}
