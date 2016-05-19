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

  for(int i = 0; i < 26; i ++) //assigning pt values to letters
    lettermap.insert(LetterMap::value_type(i + 'a', letterValues[i]));

  ifstream inf("dictionary.txt"); //open up file of valid words

  while(getline(inf, temp)) //read entire file
  {
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //lowercase
    //need to add checking for only lowercase and 7 or less characters
    count = 0; //reset conut

    for(size_t j = 0; j < temp.length(); j++) //entire string
      count += lettermap.at(temp.at(j)); //add each char pt val to count
    wordmap.insert(WordMap::value_type(temp, count)); //insert word + score
  } //while
  inf.close(); //close file

  ifstream in(argv[1]); //open input
  while(getline(in, s)) //read entire input
  {
    orig = s; //save string for print
    //transform(s.begin(), s.end(), s.begin(), ::tolower); //lowercase
    sort(s.begin(), s.end()); //sort to get all possible when using next_perm

    do
    {
      for(size_t i = 2; i < s.length() + 1; i++) //get all substrings
      {
        t = s.substr(0, i); //get substring
        count = 0; //reset count
        if(wordmap.find(t) != wordmap.end()) //word in map
        {
          count = wordmap.at(t); //get count from map
          if(count >= best)
          {
            if(count > best)
            {
              words.clear(); //clear wordset
              best = count; //set new best pts
            } //if
            words.insert(t); //insert into worset
          } //if
        } //if
      }// for
    } while(std::next_permutation(s.begin(), s.end())); //give all perm

    cout << setw(2) << best << ' ' << orig << ": ";

    if(!words.empty()) //words
    {
      for(set<string>::iterator it = words.begin(); it != words.end(); it++)
         cout << *it << ' ';
      cout << endl;
    } //if
    else//no words
      cout << "No words found." << endl;
    words.clear();
    best = 0;
  } //while
  in.close();
  return 0;
}
