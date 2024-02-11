#include <sstream>
#include <iomanip>
#include "product.h"
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, std::string rating):Product(category, name, price, qty)
{
  genre_=genre;
  rating_ = rating;
}
std::set<std::string> Movie::keywords() const
{
  std::string key = name_+" "+genre_;
  return parseStringToWords(key);
}
std::string Movie::displayString() const
{
  std::stringstream ss;
  ss<<std::fixed<<setprecision(2);
  ss<<name_<<"\n"<<"Genre: "<<genre_<<" Rating: "<<rating_<<"\n"<<price_<<" "<<qty_<<" left.";
  return ss.str();

}
void Movie::dump(std::ostream& os) const
{
  os<<category_<<"\n"<<name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<genre_<<"\n"<<rating_<<endl;
}
