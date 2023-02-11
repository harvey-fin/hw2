#include <iomanip>
#include "util.h"
#include "mydatastore.h"


using namespace std;
MyDataStore::MyDataStore(){}


MyDataStore::~MyDataStore(){
  for (unsigned int i=0; i<product_list.size(); i++){
    delete product_list[i];
  }
  for (unsigned int i=0; i<user_list.size(); i++){
    delete user_list[i];
  }
}


void MyDataStore::addProduct(Product* p){
  product_list.push_back(p);
}

void MyDataStore::addUser(User* u){
  user_list.push_back(u);
  std::queue<Product*> new_cart;
  cart_.insert(std::pair<std::string, std::queue<Product*>>(convToLower(u->getName()), new_cart));
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  vector<Product*> ret_vec;
  set<string> search_term = {convToLower(terms[0])};
  for (vector<string>::iterator it = terms.begin(); it!=terms.end(); ++it){
      set<string> current_term = {convToLower(*it)};
      search_term = setUnion(search_term, current_term);
  }
  if (type == 0){
    for (vector<Product*>::iterator it = product_list.begin(); it!=product_list.end(); ++it){
      set<string> current_pro = (*it)->keywords();
      if (setIntersection(current_pro, search_term).size() == search_term.size()){
        ret_vec.push_back(*it);
      }
    }
  }
  else{
    for (vector<Product*>::iterator it = product_list.begin(); it!=product_list.end(); ++it){
      set<string> current_pro = (*it)->keywords();
      if (setIntersection(current_pro, search_term).size() != 0){
        ret_vec.push_back(*it);
      }
    }
  }
  search_list = ret_vec;
  return ret_vec;
}

void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>\n";
  if (!product_list.empty()){
    for (vector<Product*>::iterator it = product_list.begin(); it!=product_list.end(); ++it){
      (*it)->dump(ofile);
    }
  }
  ofile << "</products>\n<users>\n";
  if (!user_list.empty()){
    for (vector<User*>::iterator it = user_list.begin(); it!=user_list.end(); ++it){
      (*it)->dump(ofile);
    }
  }
  ofile << "</users>";
}

bool MyDataStore::user_check(std::string username){
  if (cart_.find(username) != cart_.end()){
    return true;
  }
  else{
    return false;
  }
}

int MyDataStore::get_search_size() {return search_list.size();}

void MyDataStore::add_to_cart(std::string username, int idx)
{
  if (cart_.find(username) == cart_.end()){
    queue<Product*> new_cart;
    new_cart.push(search_list[idx-1]);
    cart_.insert({username, new_cart});
  }
  else
  {
    cart_[username].push(search_list[idx-1]);
  }
}

std::queue<Product*> MyDataStore::get_cart(std::string username){
  return cart_[username];
}

void MyDataStore::buy_cart(std::string username){
  queue<Product*> user_queue = cart_[username];
  User* current_user = retrieve_user(username);
  while (!user_queue.empty()){
    Product* curr_item = user_queue.front();
    double item_price = curr_item->getPrice();
    if (curr_item->getQty()>0 && curr_item->getPrice() < current_user->getBalance()){
      current_user->deductAmount(item_price);
      cart_[username].pop();
      curr_item->subtractQty(1);
    }
    user_queue.pop();
  }
}

User* MyDataStore::retrieve_user(std::string username){
  User* current_user;
  for (vector<User*>::iterator it = user_list.begin(); it!=user_list.end(); ++it){
    if ((*it)->getName() == username){
      current_user = *it;
    }
  }
  return current_user;
}