#pragma once
#include "../../src/models/TaxRate.h"
#include <memory>
#include <stdexcept>
#include <iostream>

namespace sales_taxes 
{
    // Standard runtime exception class
    class ProductOriginException : public std::runtime_error 
    {
    public:
        ProductOriginException(const std::string& msg = "") :
            runtime_error(msg) {}
    };

    // Represents product origin and related tax
    class ProductOrigin 
    {
    public:
        // Origin types
        enum class Origin { local, imported };

    public:
        // Constructor 
        ProductOrigin(const Origin origin);

        // Copy constructor 
        ProductOrigin(const ProductOrigin& po);

        // Getters and Setters
        Origin get_origin() const;
        void set_origin(const Origin origin);
        TaxRate get_tax_rate() const;
        void set_tax_rate(const std::shared_ptr<TaxRate> tax_rate);

        // Calculates taxes applied depending on origin of the product
        double calculate_tax(double price) const;

        // Equality operator
        friend bool operator==(const ProductOrigin& pod, const ProductOrigin& pos);

    private:
        Origin origin;
        std::shared_ptr<TaxRate> tax_rate;
    };

    bool operator==(const ProductOrigin& pod, const ProductOrigin& pos);
}