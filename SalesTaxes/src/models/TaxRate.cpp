#include "../../src/models/TaxRate.h"

using namespace sales_taxes;

TaxRate::TaxRate(const TaxRate::RateTypes rate_type) : rate_type(rate_type) 
{
    switch (rate_type)
    {
    case RateTypes::basic_tax:
        rate = BASIC_TAX_RATE;
        break;
    case RateTypes::exempted:
        rate = EXEMPTED_RATE;
        break;
    case RateTypes::import_duty:
        rate = IMPORT_DUTY_RATE;
        break;
    default:
        throw TaxRateException("Invalid rate type.");
        break;
    }
}

TaxRate::TaxRate(const TaxRate& t) : TaxRate(t.rate_type) {}

TaxRate::RateTypes TaxRate::get_rate_type() const 
{
    return rate_type;
}

void TaxRate::set_rate_type(const TaxRate::RateTypes rate_type) 
{
    this->rate_type = rate_type;
}

double TaxRate::get_rate() const 
{
    return rate;
}

void TaxRate::set_rate(const double rate) 
{
    this->rate = rate;
}

double TaxRate::calculate_tax(double price) const 
{
    if (price < 0)
        throw TaxRateException("Price should be greater or equal to 0.");

    return std::ceil(price * rate * 20.0) / 20.0;
}

bool sales_taxes::operator==(const TaxRate& trd, const TaxRate& trs)
{
    return trd.rate == trs.rate && trd.rate_type == trs.rate_type;
}
