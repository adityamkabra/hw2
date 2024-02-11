#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "util.h"

class Clothing:public Product{
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
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
  private:
    std::string brand_ = "";
    std::string size_;
};
#endif

