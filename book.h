#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "util.h"

class Book:public Product{
  public:
   std::set<std::string> keywords() const;//returns a set of keywords for the product
     /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;
    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;
    Book(const std::string category, const std::string name, double price, int qty, const std::string author_name, const std::string isbn);
  private:
    std::string author_ = "";
    std::string isbn_;
};
#endif


