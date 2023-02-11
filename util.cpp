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
    set<string> out_set;
    int start=0;
    int len=0;
    for (unsigned int idx=0; idx<rawWords.size(); idx++){
        if (ispunct(rawWords[idx]) || isspace(rawWords[idx])){
            len=idx-start;
            if (len>1){
                out_set.insert(convToLower(rawWords.substr(start, len)));
                start=idx+1;
                len=0;
            }
            else{
                start=idx+1;
                len=0;
            }
        }
        if (idx == rawWords.size()-1){
          len=idx-start;
            if (len>1){
                out_set.insert(convToLower(rawWords.substr(start, len+1)));
                break;
            }
        }
    }
    return out_set;
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


// int main(){
//     string test_str = "a,bcd,efgh'hijk lmn,opq";
//     set<string> s = parseStringToWords(test_str);
//     for(set<string>::iterator it = s.begin(); it != s.end(); ++it)
//     {
//       cout << "Word " << *it << endl;
//     }
// }