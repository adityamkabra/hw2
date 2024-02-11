#include <sstream>
#include <iomanip>
#include "product.h"
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author_name, const std::string isbn):Product(category, name, price, qty)
{
  isbn_=isbn;
  author_=author_name;
}
std::set<std::string> Book::keywords() const
{
  std::string key = name_+" "+author_+" "+isbn_;
  return parseStringToWords(key);
}
std::string Book::displayString() const
{
  
  std::stringstream ss;
  ss<<std::fixed<<setprecision(2);
  ss<<name_<<"\n"<<"Author: "<<author_<<" ISBN: "<<isbn_<<"\n"<<price_<<" "<<qty_<<" left.";
  return ss.str();

}
void Book::dump(std::ostream& os) const
{
  os<<category_<<"\n"<<name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<isbn_<<"\n"<<author_<<endl;
}
