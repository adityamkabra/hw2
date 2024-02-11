#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"
#include "datastore.h"
#include <map>
#include <queue>

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */


class MyDataStore:public DataStore {
public:
    
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);
    void viewCart(User* u);//function for viewing cart
    void buyCart(User* u);//function buying cart items in database
    void addToCart(std::string user_name, Product* p);//function for adding to cart in database
    std::vector<User*> ret_User();//getter function to get data_user outside this class
protected:
    std::vector<Product*> data_product;
    std::vector<User*> data_user;
    std::vector<Product*> hits_;
    std::map<std::string,std::set<Product*>> data_map;
    std::map<std::string,std::queue<Product*>> cart_map;
  
};

#endif
