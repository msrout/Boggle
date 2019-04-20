#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<map>
#include<sstream>
#include<algorithm>
#include<fstream>
// changing void to int main

int
CalculateScore (vector < string > wordlist)
{
  int score = 0;
for (string str:wordlist)
    {
      if (str.length () == 3 || str.length () == 4)
	{
	  score += 1;
	}
      else if (str.length () == 5)
	{
	  score += 2;
	}
      else if (str.length () == 6)
	{
	  score += 3;
	}
      else if (str.length () == 7)
	{
	  score += 5;
	}
      else if (str.length () >= 8)
	{
	  score += 11;
	}
    }
  return score;
}

/*
* calculates score for each player and stopre ina map where the key is player name.
*/
map < string, int >
MultiplayerScore (map < string, vector < string >> wordlistmap)
{
  map < string, int >resultmap;
for (auto itr:wordlistmap)
    {
      int score = CalculateScore (itr.second);
      resultmap.insert (std::pair < string, int >(itr.first, score));
    }
  return resultmap;
}

/*
* checking if the entered word is in the given text file
*/
bool
CheckWord (string wordname)
{
  string line;
  ifstream file ("wordlist-english.txt");
  int value;
  bool bFound = false;
  while (!file.eof ())
    {
      getline (file, line);
      if ((value = line.find (wordname, 0)) != string::npos)
	{
	  bFound = true;
	}
    }
  return bFound;
}

void
ParseWordlist (string wordlist, vector < string > &vec)
{
  istringstream iss (wordlist);
  while (iss)
    {
      string substr;
      iss >> substr;
      //validating words
      std::cout << "Validating your word\n";
      if (CheckWord (substr))
	{
	  vec.push_back (substr);
	}

    }
}

int
main ()
{
  // write code to rejetc entries not found in the map
  string playerName;
  string wordlist;
  int n;
  map < string, vector < string >> playerWordlistMap;
  std::cout << "Enter number of player\n";
  std::cin >> n;
  for (int i = 0; i < n; i++)
    {

      std::cout << "Enter  player name\n";
      std::cin >> playerName;
      cin.ignore ();
      std::cout << "Enter wordlist separated by space\n";
      getline (cin, wordlist);

      std::vector < string > wordvec;
      ParseWordlist (wordlist, wordvec);
      // parse the strings ang get the word
      playerWordlistMap.insert (std::pair < string,
				vector < string >> (playerName, wordvec));

    }
  map < string, int >playerScoremap = MultiplayerScore (playerWordlistMap);
  // find the key from the map who is having highest score
  auto itr = std::max_element (playerScoremap.begin (), playerScoremap.end (),
			       [](const pair < string, int >&p1,
				  const pair < string,
				  int >&p2) { return p1.second < p2.second;
			       }
  );
  std::cout << "Winner is: " << itr->first;
  getchar ();
  return 0;
}
