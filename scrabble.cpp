#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <fstream>
#include <locale>
#include <cctype>

using namespace std;
typedef map<char, int> LetterMap;
typedef map<string, int> WordMap;

int main(int argc, char** argv)
{
  int count = 0, best = 0, good = 1;
  int letterValues[] = {1, 3, 3, 2, 1, 4, 2, 4, 2, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  LetterMap lettermap;
  WordMap wordmap;
  set<string> words, blank;
  string t = "", temp = "", s = "", orig = "";

  for(int i = 0; i < 26; i ++) //assigning pt values to letters
    lettermap.insert(LetterMap::value_type(i + 'a', letterValues[i]));

  ifstream inf("words.txt"); //open up file of valid words

  while(getline(inf, temp)) //read entire file
  {
    good = 1; //flag for checking

    for(size_t i = 0; i < temp.length(); i++)
    {
      if(!islower(temp.at(i)) || temp.length() > 7)
        good = 0; //not all lower or more than 7 chars
    } //for

    if(good)
    {
      count = 0; //reset conut

      for(size_t j = 0; j < temp.length(); j++) //entire string
        count += lettermap.at(temp.at(j)); //add each char pt val to count
      wordmap.insert(WordMap::value_type(temp, count)); //insert word + score
    } //if
  } //while
  inf.close(); //close file

  ifstream in(argv[1]); //open input

  while(getline(in, s)) //read entire input
  {
    good = 1; //reset flag
    orig = s; //save string for print
    sort(s.begin(), s.end()); //sort to get all possible when using next_perm

    if(isspace(s.at(0))) //if blank
    {
      good = 0; //set flag for blank

      for(int i = 0; i < 26; i++)
      {
        s.at(0) = 'a' + i;
        blank.insert(s); //insert all 26 combinations
      }
    }
    else
    {
      blank.insert(s);
    }

    for(set<string>::iterator it = blank.begin(); it != blank.end(); it++)
    {
      s = *it;
      sort(s.begin(), s.end()); //resort for max perm
      do
      {
        for(size_t i = 2; i < s.length() + 1; i++) //get all substrings
        {
          t = s.substr(0, i); //get substring
          count = 0; //reset count

          if(wordmap.find(t) != wordmap.end()) //word in map
          {
            if(!good) //if blank remove blank pt score
              count = wordmap.at(t) - lettermap.at((*it).at(0));
            else //no blanks
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
    }
    cout << setw(2) << best << ' ' << orig << ": ";

    if(!words.empty()) //words
    {
      for(set<string>::iterator it = words.begin(); it != words.end(); it++)
        cout << *it << ' ';
      cout << endl;
    } //if
    else//no words
      cout << "No words found." << endl;

    words.clear(); //clear output set
    blank.clear(); //clear input set
    best = 0; //reset best score
    good = 1; //reset blank flag
  } //while
  in.close();
  return 0;
} //main()
