#pragma once
#include "../../src/models/TaxRate.h"
#include <memory>
#include <stdexcept>
#include <iostream>

namespace sales_taxes 
{
    // Standard runtime exception class
    class ProductTypeException : public std::runtime_error 
    {
    public:
        ProductTypeException(const std::string& msg = "") :
            runtime_error(msg) {}
    };

    // Represents product type and related tax
    class ProductType 
    {
    public:
        // Types of products
        enum class Type { book, food, medical, other };

    public:
        // Constructor
        ProductType(const Type type);

        // Copy constructor 
        ProductType(const ProductType& pt);

        // Getters and setters
        Type get_type() const;
        void set_type(const Type type);
        TaxRate get_tax_rate() const;
        void set_tax_rate(const std::shared_ptr<TaxRate> tax_rate);

        // Calculates taxes applied depending on origin of the product
        double calculate_tax(double price) const;

        // Equality operator
        friend bool operator==(const ProductType& ptd, const ProductType& pts);

    private:
        Type type;
        std::shared_ptr<TaxRate> tax_rate;
    };

    bool operator==(const ProductType& ptd, const ProductType& pts);
}