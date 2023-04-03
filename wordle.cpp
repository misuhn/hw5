#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

bool wordleWordCheck(const std::string& floating, const std::set<std::string>& dict, const std::string& curr);
void wordleHelperFunc(const std::string& in, const std::string& floating, 
const std::set<std::string>& dict, std::set<std::string>& mySet, std::string curr, int cnt);

// Primary wordle function definition
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{

  // Prototypes of helper functions
  bool wordleWordCheck(const std::string& floating, const std::set<std::string>& dict, const std::string& curr);
  void wordleHelperFunc(const std::string& in, const std::string& floating, 
    const std::set<std::string>& dict, std::set<std::string>& mySet, std::string curr, int cnt);

  // The code starts here
  std::set<std::string> mySet;
  bool check = true;
  std::string curr = "";
  int cnt = 0;

  // Count the number of open spots in the input string
  for (size_t i = 0; i < in.length(); ++i) {
    if (in[i] == '-') {
      cnt++;
      check = false;
    }
  }

  // Case 1: if input string is empty
  if (in.empty()) { 
    return mySet;
  }

  // Case 2: if the input string is complete
  else if (check == true) {
    mySet.insert(in);
  }

  // Case 3: not solved yet
  else {
    wordleHelperFunc(in, floating, dict, mySet, curr, cnt);
  }

  return mySet;
}

// Helper function to check if the word can be made with floating letters
bool wordleWordCheck(const std::string& floating, const std::set<std::string>& dict, const std::string& curr)
{
  int cnt = 0;
  std::string currString = curr;

  for (int i = floating.length() - 1; i >= 0; --i) {
    char floatingChar = floating[i];
    size_t currLoc = currString.find(floatingChar);

    // If the character is found
    if (currLoc != string::npos) {
      currString.erase(currString.begin() + (int)currLoc);
      cnt++;
    }
  }

  if (dict.find(curr) == dict.end()) {
    return false;
  }
  
  if ((unsigned int)cnt != floating.length()) {
    return false;
  }

  return true;
}

// Helper function to generate all possible combinations
void wordleHelperFunc(const std::string& in, const std::string& floating, const std::set<std::string>& dict, 
  std::set<std::string>& mySet, std::string curr, int cnt)
{
  // Case 1: length of the string is the same as the input string
  if (curr.length() == in.length()) { 
    if (wordleWordCheck(floating, dict, curr)) {
      mySet.insert(curr);
    }
    return;
  }

// Case 2: if the character at point is already figured out (not a dash)
if (in[curr.length()] != '-') {
std::string myString = curr + in[curr.length()];
wordleHelperFunc(in, floating, dict, mySet, myString, cnt);
}

// Case 3: if all floating letters are used up
else if (cnt == (int)floating.length()) {
for (int i = floating.length() - 1; i >= 0; --i) {
std::string myFloatingString = floating;
std::string currCopy = curr + myFloatingString[i];
myFloatingString.erase(i, 1);
wordleHelperFunc(in, myFloatingString, dict, mySet, currCopy, cnt - 1);
}
}

// Case 4: if there are still floating letters left
else {
for (char i = 'a'; i <= 'z'; ++i) {
std::string myFloatingString = floating;
if (myFloatingString.find(i) != string::npos) {
myFloatingString.erase(myFloatingString.find(i), 1);
}
wordleHelperFunc(in, myFloatingString, dict, mySet, curr + i, cnt - 1);
}
}
}