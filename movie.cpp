#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;


Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating):
  Product("movie", name, price, qty),
  genre_(genre),
  rating_(rating)
{
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
  set<std::string> ret_set;
  ret_set = parseStringToWords(name_);
  ret_set.insert(convToLower(genre_));
  return ret_set;
}


std::string Movie::displayString() const{
  std::string ret_str="";
  ret_str=name_+'\n'+"Genre: " + genre_ + " Rating: " + rating_ + '\n' + to_string(price_) + " " + to_string(qty_) + " left.";
  return ret_str;
}

void Movie::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}