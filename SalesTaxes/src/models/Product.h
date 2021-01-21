#pragma once
#include "../../src/models/ProductType.h"
#include "../../src/models/ProductOrigin.h"
#include <string>
#include <stdexcept>
#include <iostream>

namespace sales_taxes 
{    
    // Standard runtime exception class
    class ProductException : public std::runtime_error 
    {
    public:
        ProductException(const std::string& msg = "") :
            runtime_error(msg) {}
    };

    class Product 
    {
    public:
        // Constructor
        Product(const std::string name, const double price, std::shared_ptr <ProductType>  type,
            std::shared_ptr <ProductOrigin> origin);

        // Copy constructor 
        Product(const Product& pr);

        // getter and setters
        std::string get_name() const;
        void set_name(const std::string name);
        double get_price() const;
        void set_price(const double price);
        std::shared_ptr <ProductType> get_product_type() const;
        void set_product_type(std::shared_ptr <ProductType> type);
        std::shared_ptr <ProductOrigin> get_product_origin() const;
        void set_product_origin(std::shared_ptr <ProductOrigin> origin);

        // Calculates taxes applied to product
        double calculate_taxes() const;

        // Prints product
        friend std::ostream& operator<<(std::ostream& os, const Product& pr);

        // Equality operator
        friend bool operator==(const Product& prd, const Product& prs);

    private:
        std::string name;
        double price;
        std::shared_ptr <ProductType> type;
        std::shared_ptr <ProductOrigin> origin;
    };
    
    std::ostream& operator<<(std::ostream& os, const Product& pr);
    bool operator==(const Product& prd, const Product& prs);
}
