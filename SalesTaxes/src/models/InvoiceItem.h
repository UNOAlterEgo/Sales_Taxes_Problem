#pragma once
#include "../../src/models/Product.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace sales_taxes 
{    
    // Standard runtime exception class
    class InvoiceItemException : public std::runtime_error 
    {
    public:
        InvoiceItemException(const std::string& msg = "") :
            runtime_error(msg) {}
    };

    class InvoiceItem 
    {
    public:
        InvoiceItem(std::shared_ptr <Product> product, unsigned int quantity);

        // Copy constructor 
        InvoiceItem(const InvoiceItem& r);

        // Return copy product
        std::shared_ptr <Product> get_product() const;

        // Getters and setters
        unsigned long int get_quantity() const;
        void set_quantity(unsigned int quantity);

        // Increments product quantity in invoice item
        void increment_quantity();
        // Decrements product quantity in invoice item
        void decrement_quantity();

        // Returns price and tax values
        double get_total_price();
        double get_total_sales_taxes();
        double get_total_amount();

        // Prints invoice item
        std::string get_invoice_item();
        friend std::ostream& operator<<(std::ostream& os, const InvoiceItem& ii);

        // Equality operator
        friend bool operator==(const InvoiceItem& iid, const InvoiceItem& iis);

    private:
        std::shared_ptr <Product> product;
        unsigned int quantity;
        double total_price, total_sales_taxes, total_amount;

        // Truncates double
        double truncate_number(double in);
    };
    
    std::ostream& operator<<(std::ostream& os, const InvoiceItem& ii);
    bool operator==(const InvoiceItem& iid, const InvoiceItem& iis);
}
