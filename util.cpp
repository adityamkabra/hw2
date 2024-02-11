#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> retWords;//declaring a return word set
    stringstream ss(rawWords);//declaring a string stream to read rawWords
    string word;
    while(ss>>word)
    { 
        if((word).find("-")!=std::string::npos)//checking if its an isbn
        {
          retWords.insert(word);
          continue;
        }
        word=convToLower(word);
        string word_actual = "";
        for(int i=0; i<word.size();i++)
        {
            char c=word[i];
            if(!ispunct(c))//checking if c is a punctuation
            {
                word_actual +=c;//adding c to word_actual
            }
            if(word_actual.length()>1&&!ispunct(c))//checking if the length matches the prerequisite for keyword if a punctuation is encountered
            {
                retWords.insert(convToLower(word_actual));//inseting keyword to set
                word_actual="";
                continue;
            }
            if(ispunct(c)||i==word.size()-1)
            {
              if(word_actual.length()>1)//checking if the length matches the prerequisite for keyword 
              {
                retWords.insert(convToLower(word_actual));//inserting keyword to set
                word_actual.clear();
                continue;
              }
            }
          }
      }
  return retWords;
  }


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

