#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <fstream>
#include <locale>

using namespace std;
typedef map<char, int> LetterMap;
typedef map<string, int> WordMap;

int main(int argc, char** argv)
{
  int count = 0, best = 0;
  int letterValues[] = {1, 3, 3, 2, 1, 4, 2, 4, 2, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  LetterMap lettermap;
  WordMap wordmap;
  set<string> words;
  string t = "", temp = "", s = "", orig = "";

  for(int i = 0; i < 26; i ++)
    lettermap.insert(LetterMap::value_type(i + 'a', letterValues[i]));

  ifstream inf("dictionary.txt");
  while(getline(inf, temp))
  {
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    count = 0;
    for(size_t j = 0; j < temp.length(); j++)
      count += lettermap.at(temp.at(j));
    wordmap.insert(WordMap::value_type(temp, count));
  }
  inf.close();

  ifstream in(argv[1]);
  while(getline(in, s))
  {
    orig = s;
    sort(s.begin(), s.end());
    do
    {
      for(size_t i = 2; i < s.length() + 1; i++) //2 s.length
      {
        t = s.substr(0, i);
        count = 0;
        if(wordmap.find(t) != wordmap.end())
        {
          count = wordmap.at(t);
          if(count >= best)
          {
            if(count > best)
            {
              words.clear();
              best = count;
            } //if
            words.insert(t);
          } //if
        } //if
      }// for
    } while(std::next_permutation(s.begin(), s.end()));

    cout << setw(2) << best << ' ' << orig << ": ";
    if(!words.empty())
    {
      for(set<string>::iterator it = words.begin(); it != words.end(); it++)
         cout << *it << ' ';
      cout << endl;
    }
    else
    {
      cout << "No words found." << endl;
    }
    words.clear();
    best = 0;
  }
  in.close();
  return 0;
}
