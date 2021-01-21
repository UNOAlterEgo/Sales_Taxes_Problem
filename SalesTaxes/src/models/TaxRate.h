#pragma once
#include "../../src/models/TaxRate.h"
#include <stdexcept>
#include <cmath>

namespace sales_taxes 
{
    // Standard runtime exception class
    class TaxRateException : public std::runtime_error 
    {
    public:
        TaxRateException(const std::string& msg = "") :
            runtime_error(msg) {}
    };

    class TaxRate 
    {
    public:
        enum class RateTypes { basic_tax, exempted, import_duty };
    public:
        // Constructor
        TaxRate(const RateTypes rate_type);

        // Copy constructor 
        TaxRate(const TaxRate& t);

        // Getters and setters
        RateTypes get_rate_type() const;
        void set_rate_type(const RateTypes rate_type);

        double get_rate() const;
        void set_rate(const double rate);

        // Calculate tax given price and rate
        // rounded up to the nearest 0.05
        double calculate_tax(double price) const;

        // Equality operator
        friend bool operator==(const TaxRate& trd, const TaxRate& trs);

    private:
        RateTypes rate_type;

        const double BASIC_TAX_RATE = 0.1;
        const double EXEMPTED_RATE = 0.0;
        const double IMPORT_DUTY_RATE = 0.05;

        double rate;
    };

    bool operator==(const TaxRate& trd, const TaxRate& trs);
}