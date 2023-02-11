#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include <queue>

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    // set<string> test_set1;
    // set<string> test_set2;
    // test_set1.insert("1");
    // test_set1.insert("2");
    // test_set1.insert("3");
    // test_set1.insert("5");
    // test_set2.insert("1");
    // test_set2.insert("2");
    // test_set2.insert("4");
    // test_set2.insert("6");
    // set<string> outset = setIntersection(test_set1, test_set2);
    // for (set<string>::iterator it=outset.begin(); it!=outset.end(); ++it){
    //     cout << " " << (*it) << endl;
    // }




    // for (unsigned int i=0; i<ds.product_list.size(); i++){
    //     set<string> tmp = ds.product_list[i]->keywords();
    //     cout << ds.product_list[i]->getName() << endl;
    //     for (set<string>::iterator it=tmp.begin(); it!=tmp.end(); ++it){
    //         cout << " " << (*it) << endl;
    //     }
    // }

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if (cmd == "ADD"){
                int search_size = ds.get_search_size();
                string cmd2;
                if (ss>>cmd2){
                    cmd2 = convToLower(cmd2);
                    if (!ds.user_check(cmd2)){
                        cout << "Invalid request" << endl;
                        continue;
                    }
                    int cmd3;
                    if (ss>>cmd3){
                        if (cmd3 <0 || cmd3>search_size){
                            cout << "Invalid request" << endl;
                            continue;
                        }
                        ds.add_to_cart(cmd2, cmd3);
                    }
                    else{
                        cout << "Invalid request" << endl;
                    }
                }
                else{
                    cout << "Invalid request" << endl;
                }
            }

            else if (cmd == "VIEWCART"){
                string cmd2;
                if (ss>>cmd2){
                    cmd2 = convToLower(cmd2);
                    if (!ds.user_check(cmd2)){
                        cout << "Invalid username" << endl;
                        continue;
                    }
                    queue<Product*> user_queue = ds.get_cart(cmd2);
                    if (user_queue.size() == 0){
                        continue;
                    }
                    else{
                        int index = 1;
                        while (!user_queue.empty()){
                            Product* curr_item = user_queue.front();
                            string tmp_str = curr_item->displayString();
                            cout << "Item " << index << endl;
                            cout << tmp_str << endl;
                            user_queue.pop();
                            index++;
                        }
                    }
                }
            }

            else if (cmd == "BUYCART"){
                string cmd2;
                if (ss>>cmd2){
                    cmd2 = convToLower(cmd2);
                    if (!ds.user_check(cmd2)){
                        cout << "Invalid username" << endl;
                        continue;
                    }
                    ds.buy_cart(cmd2);
                }
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
