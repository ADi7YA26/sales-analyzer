# SalesAnalyzer

SalesAnalyzer is a C++ project designed to process and analyze sales data from CSV files, generating insightful reports such as total sales, monthly sales totals, and statistics on the most popular and top-revenue-generating items. The project is ideal for businesses that need to track product sales, identify trends, and generate sales reports for different time periods.

## Features

-   Total Sales of the Store: Computes the total sales for the entire store.
-   Month-wise Sales Totals: Provides a breakdown of sales per month.
-   Most Popular Item per Month: Identifies the item with the highest quantity sold each month.
-   Top Revenue-Generating Item per Month: Identifies the item that generated the most revenue each month.
-   Statistics for Popular Items: Displays the minimum, maximum, and average quantities sold for the most popular items each month.

## Requirements

-   C++14 (or higher)
-   A C++ compiler (e.g., GCC, Clang, or MSVC)
-   A CSV file with the following columns:
    -   Date: The date of the sale in YYYY-MM-DD format.
    -   SKU: The unique identifier for the product.
    -   Unit Price: The price per unit of the item.
    -   Quantity: The number of units sold.
    -   Total Price: The total sales value for the transaction (Unit Price * Quantity).


## How It Works

The program reads the sales_data.csv file and processes each row to:

-   Extracts the sale's date, SKU, unit price, quantity, and total price.
-   Aggregates the data by month.
-   Computes the total sales for the store and each month.
-   Identifies the most popular items by quantity and by revenue.
-   Calculates basic statistics for the most popular items each month.