
#include "../../src/models/ProductOrigin.h"

using namespace sales_taxes;

ProductOrigin::ProductOrigin(const Origin origin) : origin(origin) 
{
    switch (origin) 
    {
    case Origin::local:
        tax_rate = std::make_shared<TaxRate>(TaxRate::RateTypes::exempted);
        break;
    case Origin::imported:
        tax_rate = std::make_shared<TaxRate>(TaxRate::RateTypes::import_duty);
        break;
    default:
        throw ProductOriginException("Invalid product origin");
    }
}

ProductOrigin::ProductOrigin(const ProductOrigin& po) : ProductOrigin(po.origin) {}

ProductOrigin::Origin ProductOrigin::get_origin() const 
{
    return origin;
}

void ProductOrigin::set_origin(const Origin origin) 
{
    this->origin = origin;
}

TaxRate ProductOrigin::get_tax_rate() const 
{
    return *tax_rate;
}

void ProductOrigin::set_tax_rate(const std::shared_ptr<TaxRate> tax_rate) 
{
    this->tax_rate = tax_rate;
}

double ProductOrigin::calculate_tax(double price) const 
{
    if (price < 0)
        throw ProductOriginException("Price should be greater or equal to 0.");

    return tax_rate->calculate_tax(price);
}

bool sales_taxes::operator==(const ProductOrigin& pod, const ProductOrigin& pos) 
{
    return pod.origin == pos.origin && pod.tax_rate == pos.tax_rate;
}
