#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <queue>
#include <map>

class MyDataStore: public DataStore
{
  public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    bool user_check(std::string username);
    void add_to_cart(std::string username, int idx);
    std::queue<Product*> get_cart(std::string username);
    int get_search_size();
    void buy_cart(std::string username);
    User* retrieve_user(std::string username);


  private:
    std::vector<Product*> product_list;
    std::vector<User*> user_list;
    std::vector<Product*> search_list;
    std::map<std::string, std::queue<Product*>> cart_;

};

#endif