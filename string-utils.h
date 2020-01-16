#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>
#include <iomanip>


using namespace std;

string join(vector<string> strings, string separator = ",");
string ftos(double d, int precision);
string format(double d);
string format(double d, int width, int precision);
vector<string> split(const string& s, const string & delim_string);
vector<string> split(const string& s, char delim_char=',', bool all = true);


// trim from start (in place)
void ltrim(std::string &s);

// trim from end (in place)
void rtrim(std::string &s);

// trim from both ends (in place)
void trim(std::string &s);

// trim from start (copying)
std::string ltrimmed(std::string s);

// trim from end (copying)
std::string rtrimmed(std::string s);

// trim from both ends (copying)
std::string trimmed(std::string s);

string to_fixed_width_string(int n, int width, char fill);

template <class T>
string vector_to_string(const vector<T> &v) {
  if (v.size() == 0) {
    return "";
  }
  string rv;
  rv += "[";
  rv += to_string(v[0]);
  for (int i = 1; i < v.size(); ++i) {
    rv += (string) ", " + to_string(v[i]);
  }
  rv += "]";
  return rv;
}

string join(vector<string> strings, string separator) {
  bool first = true;
  stringstream ss;
  for(string s:strings) {
    if(!first)
      ss << separator;
    ss << s;
    first=false;
  }
  return ss.str();
}

string format(double d) {
  stringstream ss;
  ss<<d;
  return ss.str();
}

string ftos(double d, int precision) {
  stringstream ss;
  ss << std::fixed << std::setprecision( precision ) << d;
  return ss.str();
}

string format(double d, int width, int precision) {
  stringstream ss;
  ss<< std::fixed << std::setw( width ) << std::setprecision( precision )
   <<  d;
  return ss.str();
}

string  to_fixed_width_string(int n, int width, char fill) {
    std::ostringstream ss;
    ss << std::setw( width ) << std::setfill( fill ) << n;
    return ss.str();
}

// setting all to true splits all occurances
// setting to false only splits on first occurance of delim_char - if any
vector<string> split(const string& s, const string & delim_string) {

  vector<string> items;
  size_t start = 0;
  while(start < s.length()-1) {
    size_t pos = s.find(delim_string, start);
    if(pos == string::npos) {
      break;
    }
    items.push_back(s.substr(start, pos-start));
    start = pos+delim_string.length();
  }
  items.push_back(s.substr(start, string::npos));
  return items;
}


// setting all to true splits all occurances
// setting to false only splits on first occurance of delim_char - if any
vector<string> split(const string& s, char delim_char, bool all) {
  string delim = string(1, delim_char);
  vector<string> items;
  string::const_iterator substart = s.begin(), subend;
  while (true) {
    subend = search(substart, s.end(), delim.begin(), delim.end());
    string temp(substart, subend);
    items.push_back(temp);
    if (subend == s.end()) {
      break;
    }
    substart = subend + delim.size();
    if (!all) {
      string temp(substart, s.end());
      items.push_back(temp);
      break;
    }
  }
  return items;
}

// http://stackoverflow.com/a/217605/383967

// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
string ltrimmed(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
string rtrimmed(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
string trimmed(std::string s) {
    trim(s);
    return s;
}



#endif // STRING_UTILS_H
