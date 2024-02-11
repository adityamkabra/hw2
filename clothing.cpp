#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):Product(category, name, price, qty)
{
  brand_= brand;
  size_=size;
}
std::set<std::string> Clothing::keywords() const
{
    std::string key = name_+" "+brand_;
    return parseStringToWords(key);
}
std::string Clothing::displayString() const
{
  std::stringstream ss;
  ss<<std::fixed<<setprecision(2);
  ss<<name_<<"\n"<<"Size: "<<size_<<" Brand: "<<brand_<<"\n"<<price_<<" "<<qty_<<" left.";
  return ss.str();
}
void Clothing::dump(std::ostream& os) const
{
  os<<category_<<"\n"<<name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<size_<<"\n"<<brand_<<endl;
}
