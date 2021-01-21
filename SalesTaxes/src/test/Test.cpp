#include "../../src/SalesTaxes.h"
#include <gtest/gtest.h>
#include <memory>

namespace sales_taxes 
{

    class InvoiceTests : public ::testing::Test 
    {
    protected:
        //Product types
        std::shared_ptr<ProductType> type_book;
        std::shared_ptr<ProductType> type_food;
        std::shared_ptr<ProductType> type_medical;
        std::shared_ptr<ProductType> type_other;

        // Product origins
        std::shared_ptr<ProductOrigin> origin_imported;
        std::shared_ptr<ProductOrigin> origin_local;

        virtual void SetUp() 
        {
            type_book = std::make_shared<ProductType>(ProductType::Type::book);
            type_food = std::make_shared<ProductType>(ProductType::Type::food);
            type_medical = std::make_shared<ProductType>(ProductType::Type::medical);
            type_other = std::make_shared<ProductType>(ProductType::Type::other);

            origin_imported = std::make_shared<ProductOrigin>(ProductOrigin::Origin::imported);
            origin_local = std::make_shared<ProductOrigin>(ProductOrigin::Origin::local);
        }
    };

    TEST_F(InvoiceTests, Output1) 
    {
        //Input 1:
        //1 book at 12.49
        //1 music CD at 14.99
        //1 chocolate bar at 0.85

        // Products
        std::shared_ptr<Product> product_book =
            std::make_shared<Product>("book", 12.49, type_book, origin_local);
        std::shared_ptr<Product> product_music_cd =
            std::make_shared<Product>("music CD", 14.99, type_other, origin_local);
        std::shared_ptr<Product> product_chocolate_bar =
            std::make_shared<Product>("chocolate bar", 0.85, type_food, origin_local);

        // Add items to invoice
        std::unique_ptr<Invoice> invoice = std::make_unique<Invoice>();
        invoice->add_item(std::make_shared<InvoiceItem>(product_book, 1));
        invoice->add_item(std::make_shared<InvoiceItem>(product_music_cd, 1));
        invoice->add_item(std::make_shared<InvoiceItem>(product_chocolate_bar, 1));

        EXPECT_DOUBLE_EQ(invoice->get_total_price(), 28.33);
        // Sales taxes must be rounded so we use EXPECT_EQ
        EXPECT_EQ(invoice->get_total_sales_taxes(), 1.5);
        EXPECT_DOUBLE_EQ(invoice->get_total_amount(), 29.83);
        EXPECT_EQ(invoice->get_invoice(),
            "1 book : 12.49\n"
            "1 music CD : 16.49\n"
            "1 chocolate bar : 0.85\n"
            "Sales Taxes : 1.50\n"
            "Total : 29.83");
    }

    TEST_F(InvoiceTests, Output2) 
    {
        //Input 2:
        //1 imported box of chocolates at 10.00
        //1 imported bottle of perfume at 47.50

        // Products
        std::shared_ptr<Product> product_imported_box_of_chocolates =
            std::make_shared<Product>("box of chocolates", 10.00, type_food, origin_imported);
        std::shared_ptr<Product> product_imported_bottle_of_perfume =
            std::make_shared<Product>("bottle of perfume", 47.50, type_other, origin_imported);

        // Add items to invoice
        std::unique_ptr<Invoice> invoice = std::make_unique<Invoice>();
        invoice->add_item(std::make_shared<InvoiceItem>(product_imported_box_of_chocolates, 1));
        invoice->add_item(std::make_shared<InvoiceItem>(product_imported_bottle_of_perfume, 1));

        EXPECT_DOUBLE_EQ(invoice->get_total_price(), 57.5);
        // Sales taxes must be rounded so we use EXPECT_EQ
        EXPECT_EQ(invoice->get_total_sales_taxes(), 7.65);
        EXPECT_DOUBLE_EQ(invoice->get_total_amount(), 65.15);
        EXPECT_EQ(invoice->get_invoice(),
            "1 imported box of chocolates : 10.50\n"
            "1 imported bottle of perfume : 54.65\n"
            "Sales Taxes : 7.65\n"
            "Total : 65.15");
    }

    TEST_F(InvoiceTests, Output3) 
    {
        //Input 3:
        //1 imported bottle of perfume at 27.99
        //1 bottle of perfume at 18.99
        //1 packet of headache pills at 9.75
        //1 box of imported chocolates at 11.25

        // Products
        std::shared_ptr<Product> product_imported_bottle_of_perfume =
            std::make_shared<Product>("bottle of perfume", 27.99, type_other, origin_imported);
        std::shared_ptr<Product> product_bottle_of_perfume =
            std::make_shared<Product>("bottle of perfume", 18.99, type_other, origin_local);
        std::shared_ptr<Product> product_packet_of_headache_pills =
            std::make_shared<Product>("packet of headache pills", 9.75, type_medical, origin_local);
        std::shared_ptr<Product> product_imported_box_of_chocolates =
            std::make_shared<Product>("box of chocolates", 11.25, type_food, origin_imported);

        // Add items to invoice
        std::unique_ptr<Invoice> invoice = std::make_unique<Invoice>();
        invoice->add_item(std::make_shared<InvoiceItem>(product_imported_bottle_of_perfume, 1));
        invoice->add_item(std::make_shared<InvoiceItem>(product_bottle_of_perfume, 1));
        invoice->add_item(std::make_shared<InvoiceItem>(product_packet_of_headache_pills, 1));
        invoice->add_item(std::make_shared<InvoiceItem>(product_imported_box_of_chocolates, 1));

        EXPECT_DOUBLE_EQ(invoice->get_total_price(), 67.98);
        // Sales taxes must be rounded so we use EXPECT_EQ
        EXPECT_DOUBLE_EQ(invoice->get_total_sales_taxes(), 6.70);
        EXPECT_DOUBLE_EQ(invoice->get_total_amount(), 74.68);
        EXPECT_EQ(invoice->get_invoice(),
            "1 imported bottle of perfume : 32.19\n"
            "1 bottle of perfume : 20.89\n"
            "1 packet of headache pills : 9.75\n"
            "1 imported box of chocolates : 11.85\n"
            "Sales Taxes : 6.70\n"
            "Total : 74.68");
    }
}