# Sales Taxes Problem

## Introduction
This is a solution to the sales taxes problem in C++ tested using [Google Test](https://github.com/google/googletest).

## Problem
Basic sales tax is applicable at a rate of 10% on all goods, except books, food, and medical products that are exempt. Import duty is an additional sales tax applicable on all imported goods at a rate of 5%, with no exemptions.

When I purchase items I receive a receipt which lists the name of all the items and their price (including tax), finishing with the total cost of the items, and the total amounts of sales taxes paid. The rounding rules for sales tax are that for a tax rate of n%, a shelf price of p contains (np/100 rounded up to the nearest 0.05) amount of sales tax.

### Project structure
```bash
SalesTaxes
    ├── CMakeLists.txt
    ├── CMakeLists.txt.in
    └── src
        ├── models
        │   ├── Invoice.cpp
        │   ├── Invoice.h
        │   ├── InvoiceItem.cpp
        │   ├── InvoiceItem.h
        │   ├── Product.cpp
        │   ├── Product.h
        │   ├── ProductOrigin.cpp
        │   ├── ProductOrigin.h
        │   ├── ProductType.cpp
        │   ├── ProductType.h
        │   ├── TaxRate.cpp
        │   └── TaxRate.h
        ├── SalesTaxes.cpp
        ├── SalesTaxes.h
        └── test
            └── Test.cpp
```
The source file named Test.cpp contains the three tests for the inputs stated in the problem description.

### Assumptions
- Price can't be negative
- The invoice items are ordered
- An invoice has at least one invoice item
- An invoice item has at least one product

For more details, see the header's files comments.

### To do
Due to time constraint:
- A parser class for input ( using regular expressions ) and a writer class for output should be created. The inputs are hardcoded in the tests;
- A structure such as a hashmap should be added, to perform an association between product name to its type (i.e., <product name, category> );
- Test's inputs should be preferable stored in text files;
- Test's expected outputs should be preferable written in text files.

## How to build and test
The project can be built using [Travis CI](https://www.travis-ci.com/).
A YAML file is present with the necessary commands. Alternatively, see the following sections.

### Requirments
To manually build the project, the following requirements should be fulfilled:
- C++ 14 or higher;
- [Git](https://git-scm.com/downloads) (for Google Test download);
- [CMake](https://cmake.org/download/) 3.8 or higher; A CMakeList file is present;
Google Test is automatically installed.

### Manual build and test
From the main folder run:
```bash
mkdir build
cd build
cmake ..
make
cd SalesTaxes
./SalesTaxes
```
