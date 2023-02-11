#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;


Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author):
  Product("book", name, price, qty),
  isbn_(isbn),
  author_(author)
{
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
  set<std::string> ret_set;
  set<std::string> name_set = parseStringToWords(name_);
  set<std::string> author_set = parseStringToWords(author_);
  ret_set = setUnion(name_set, author_set);
  ret_set.insert(isbn_);
  return ret_set;
}


std::string Book::displayString() const
{
  std::string ret_str="";
  ret_str=name_+'\n'+"Author: " + author_ + " ISBN: " + isbn_ + '\n' + to_string(price_) + " " + to_string(qty_) + " left.";
  return ret_str;
}


void Book::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;

}