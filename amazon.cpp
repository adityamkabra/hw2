#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <queue>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "clothing.h"
#include "book.h"
#include "movie.h"
#include "datastore.h"
#include "mydatastore.h"



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

    vector<Product*> hits;
   
   
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) 
        {
            if( cmd == "AND") 
            {
                string term;
                vector<string> terms;
                while(ss >> term) 
                {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                set<Product*> track;
                vector<Product*>hit;
                //removing repeated products in search
                for(unsigned int i=0; i<hits.size();i++)
                {
                  if(track.find(hits[i])==track.end())
                  {
                    hit.push_back(hits[i]);
                    track.insert(hits[i]);
                  }
                }
                displayProducts(hit);
            } 
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                set<Product*> track;
                vector<Product*>hit;
                //removing repeated products in search
                for(unsigned int i=0; i<hits.size();i++)
                {
                  if(track.find(hits[i])==track.end())
                  {
                    hit.push_back(hits[i]);
                    track.insert(hits[i]);
                  }
                }
                displayProducts(hit);
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
            else if (cmd == "ADD")
            {
                string user_name;
                vector<User*> data_user=ds.ret_User();//getting the vector of all users in our datastorage
                if(ss>>ws>>user_name)
                {
                    int ctr =0;
                    User* u = nullptr;
                    //checking if username is valid
                    for(unsigned int i=0; i<data_user.size();i++)
                    {
                        if(convToLower(data_user[i]->getName())==(convToLower(user_name)))
                        {
                            ctr++;
                        }
                    }
                    if(ctr==0)
                    {
                        cout<<"Invalid request"<<endl;
                        continue;
                    }
                    std::string hit;
                    ss>>hit;//getting in hit from string stream
                    int hit_index = stoi(hit);
                    if(hit_index>0 && hit_index<=hits.size())//checking if hit index is valid
                    {
                        Product* p = hits[hit_index-1];
                        ds.addToCart(convToLower(user_name), p);//calling add to cart in mydatastore
                    }
                    else
                    {
                        cout<<"Invalid request"<<endl;
                    }
                  }
              else
              {
                  cout<<"Invalid request"<<endl;

              }
            }
            else if(cmd=="VIEWCART")
            {
                string user_name;
                vector<User*> data_user=ds.ret_User();//getting vector of all users in our database
                if(ss>>ws>>user_name)//reading username
                {
                  User* u = nullptr;
                  //checking if username is valid
                  for(unsigned int i=0; i<data_user.size();i++)
                  {
                    if(convToLower(data_user[i]->getName())==convToLower(user_name))
                    {
                        u=data_user[i];
                    }
                  }
                  if(u==nullptr)
                  {
                      cout<<"Invalid username"<<endl;
                      continue;
                  }
                  ds.viewCart(u);//calling viewcart defined in mydatastorage
                }
                else
                {
                    cout<<"Invalid username"<<endl;
                    continue;
                }
            }
            else if(cmd=="BUYCART")
            {
                string user_name;
                vector<User*> data_user=ds.ret_User();//getting vector of all users in our database
                if(ss>>user_name)//reading username from string stream
                {
                  User* u = nullptr;
                  //checking if username is valid
                  for(unsigned int i=0; i<data_user.size();i++)
                  {
                    if(convToLower(data_user[i]->getName())==convToLower(user_name))
                    {
                        u=data_user[i];
                    }
                  }
                  if(u==nullptr)
                  {
                      cout<<"Invalid username"<<endl;
                      continue;
                  }
                  ds.buyCart(u);//calling buyCart function defined in mydatastore
                }
                else
                {
                    cout<<"Invalid username"<<endl;
                    continue;
                }
            }
            else 
            {
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
