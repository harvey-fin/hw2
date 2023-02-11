#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;



Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand):
  Product("clothing", name, price, qty),
  size_(size),
  brand_(brand)
{
}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
  set<std::string> name_set = parseStringToWords(name_);
  set<std::string> brand_set = parseStringToWords(brand_);
  return setUnion(name_set, brand_set);
}


std::string Clothing::displayString() const{
  std::string ret_str="";
  ret_str=name_+'\n'+"Size: " + size_ + " Brand: " + brand_ + '\n' + to_string(price_) + " " + to_string(qty_) + " left.";
  return ret_str;
}

void Clothing::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;

}