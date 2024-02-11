#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "util.h"
#include "user.h"
#include "datastore.h"
#include "mydatastore.h"
#include <map>
#include <queue>

using namespace std;

void MyDataStore::addProduct(Product* P)
{
  set<std::string> keyw = P->keywords();//storing keywords for given product in keyw
  data_product.push_back(P);
  for(std::set<std::string>::iterator it=keyw.begin(); it != keyw.end(); ++it)//iterating through keywords for the product
  { std::string lowerK ;
    if((*it).find("-")==std::string::npos)
    {
       lowerK = convToLower(*it);
    }
    else
    {
      lowerK = *it;
    }
    if(data_map.find(lowerK)==data_map.end())//checking if the keyword is in the data map
    {
      std::set<Product*> prod;
      data_map.insert(std::make_pair(lowerK, prod));
    }
    data_map[lowerK].insert(P);//inserting a product for a keyword in a vector linked to the keyword via a map
  }
}
void MyDataStore::addUser(User* U)
{
  data_user.push_back(U);
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  vector<Product*>ret;
  set<Product*> prd;
  vector<set<std::string>> key;
  for(unsigned int i =0; i<terms.size(); i++)//iterating through terms to push a parsed set of keywords to key
  {
    key.push_back(parseStringToWords(terms[i]));
  }
  if((*(key[0].begin())).find("-")==std::string::npos)
  {
      prd = data_map[convToLower(*(key[0].begin()))];
  }
  else
  {
      prd = data_map[(*(key[0].begin()))];
  }
  for(unsigned int i =0; i<key.size();i++)//iterating through a vector of sets of keywords
  {
    for(std::set<std::string>::iterator it=key[i].begin(); it != key[i].end(); ++it)//using iterator to iterate through each set
    {
        std::string curr = *it;
        if(curr.find("-")==std::string::npos)//checking if the current string is an isbn
        {
          curr = convToLower(curr);
        }
        if(type==0)
        {
          prd=setIntersection(prd,data_map[curr]);//finding set intersection
        }
        else
        {
          prd=setUnion(prd,data_map[curr]);//finding set union
        }
    }
  }
  for(std::set<Product*>::iterator it=prd.begin(); it != prd.end(); ++it)//iterating through set of products for each keyword
  {
     ret.push_back(*it);//pushing back to a return vector
  }
  return ret;
}
void MyDataStore::dump(std::ostream& ofile)//outputting to a file in the desired format
{
  ofile<<"<products>"<<"\n";
  for(unsigned int i =0; i<data_product.size();i++)
  {
    data_product[i]->dump(ofile);
  }  
  ofile<<"</products>"<<"\n";

  ofile<<"<users>"<<"\n";
  for(unsigned int i =0; i<data_user.size();i++)
  {
    data_user[i]->dump(ofile);
  }
  ofile<<"</users>"<<"\n";
}
std::vector<User*> MyDataStore::ret_User()
{
  return data_user;
}
void MyDataStore::addToCart(std::string user_name, Product* p)
{   //using a map linking a user_name to a queue of product* for a cart
    if(cart_map.find(convToLower(user_name))==cart_map.end())
    {
      std::queue<Product*> prod;
      cart_map.insert(std::make_pair(convToLower(user_name), prod));//inserting a new pair 
    }
    cart_map[convToLower(user_name)].push(p);//pushing the product in the cart queue
}
void MyDataStore::buyCart(User* u)
{
  std::queue<Product*> q = cart_map[convToLower(u->getName())];//getting the queue of product in cart for the given user
  std::queue<Product*> temp_q;
  while(!q.empty())//iterating through the queue
  {
    if(q.front()->getQty()>0)//checking if the given item at the front of the queue is in stock
    {
      if((q.front()->getPrice())<(u->getBalance()))//checking if user has enough balence to buy the front item
      {
        if(q.front()->getQty()>0)
        {
          q.front()->subtractQty(1);//subtracting the quantity in stock
          u->deductAmount(q.front()->getPrice());//deducting from users balene
        }
        q.pop();
      }
      else
      {
        temp_q.push(q.front());
        q.pop();
        continue;
      }
    }
    else
    {
      temp_q.push(q.front());
      q.pop();
      continue;
    }
  }
  cart_map[convToLower(u->getName())]=temp_q;//linking the new cart queue to the user_name in cart map
}
void MyDataStore::viewCart(User* u)
{
  std::queue<Product*> q = cart_map[convToLower(u->getName())];//getting the product queue in the users cart
  std::queue<Product*> temp_q;
  int ctr =1;
  while(!q.empty())//iterating through the queue
  {
    cout<<"Item "<<ctr<<endl;
    cout<<q.front()->displayString()<<endl;//printing the product using displayString
    temp_q.push(q.front());
    q.pop();
    ctr++;
  }
  cart_map[convToLower(u->getName())]=temp_q;//linking the orignal cart queue back to the user_name in cart map
}
MyDataStore::~MyDataStore()
{//deleting all the dynamically allocated users and products
  for(unsigned int i =0; i<data_user.size();i++)
  {
    delete data_user[i];
  }
  for(unsigned int i =0; i<data_product.size();i++)
  {
    delete data_product[i];
  }
}

