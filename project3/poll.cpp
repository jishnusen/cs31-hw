#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode) // from class website
{
  const string codes = "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
                       "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
                       "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
  return (stateCode.size() == 2 &&
          stateCode.find('.') == string::npos &&  // no '.' in stateCode
          codes.find(stateCode) != string::npos); // match found
}

bool isSyntacticallyCorrect(string pollData) {
  int idx = 0;
  for (size_t i = 0; i < pollData.size(); i++) {
    // capitalize everything for convenience
    pollData.at(i) = toupper(pollData.at(i));
    if (i > 0) {
      // find state code when chars switch from number to letter or last code
      if (isalpha(pollData.at(i - 1)) && !isalpha(pollData.at(i)) ||
          i == pollData.size() - 1) {
        size_t poll_str_size = i - idx;
        // for last state code we need to increase size by 1
        if (i == pollData.size() - 1) {
          poll_str_size += 1;
        }
        string poll_str = pollData.substr(idx, poll_str_size);
        // must be at least 4 chars for one-digit number, state code, and party
        // letter
        if (poll_str.size() < 4) {
          return false;
        }
        // extract party from last character
        char party_code = poll_str.at(poll_str.size() - 1);
        // party must be a letter
        if (!isalpha(party_code)) {
          return false;
        }
        // get index for start of state code
        size_t state_code_idx = poll_str.size() - 3;
        // pull state code
        string state_code = poll_str.substr(state_code_idx, 2);
        if (!isValidUppercaseStateCode(state_code)) {
          return false;
        }
        if (state_code_idx > 2) {
          return false;
        }
        string vote_count = poll_str.substr(0, state_code_idx);
        if (!isdigit(poll_str.at(0)) ||
            !isdigit(poll_str.at(state_code_idx - 1))) {
          return false;
        }
        idx = i;
      }
    }
  }
  return true;
}

int tallyVotes(string pollData, char party, int &voteTally) {
  int idx = 0;
  // check syntax
  if (!isSyntacticallyCorrect(pollData)) {
    return 1;
  }
  // check requested party code validity
  if (!isalpha(party)) {
    return 2;
  }
  // store input count in case of error
  int oldCnt = voteTally;
  voteTally = 0;
  // capitalize party so matches with everything else
  party = toupper(party);
  for (size_t i = 0; i < pollData.size(); i++) {
    // capitalize everything for convenience
    pollData.at(i) = toupper(pollData.at(i));
    if (i > 0) {
      // find state code when chars switch from number to letter or last code
      if (isalpha(pollData.at(i - 1)) && !isalpha(pollData.at(i)) ||
          i == pollData.size() - 1) {
        size_t poll_str_size = i - idx;

        // for last state code we need to increase size by 1
        if (i == pollData.size() - 1) {
          poll_str_size += 1;
        }
        string poll_str = pollData.substr(idx, poll_str_size);
        idx = i;

        // extract party from last character
        char party_code = poll_str.at(poll_str.size() - 1);

        // get index for start of state code
        size_t state_code_idx = poll_str.size() - 3;
        string vote_count = poll_str.substr(0, state_code_idx);

        // read vote count from string
        int cnt = stoi(vote_count);
        if (cnt == 0) {
          voteTally = oldCnt;
          return 3;
        }

        // only increase tally if party codes match
        if (party_code == party) {
          voteTally += cnt;
        }
      }
    }
  }
  return 0;
}

int main() { // from clas website
  assert(isSyntacticallyCorrect("22CAD1NYr10PAD"));
  assert(!isSyntacticallyCorrect("38MXR55CAD"));
  assert(isSyntacticallyCorrect("38TXR55CAD"));
  assert(isSyntacticallyCorrect("22CAD1NYr10PAD"));
  assert(!isSyntacticallyCorrect("222CAD1NYr10PAD"));
  assert(!isSyntacticallyCorrect("22CAD1NYr101PAD"));
  assert(!isSyntacticallyCorrect("aCAD1NYr10PAD"));
  assert(!isSyntacticallyCorrect("5ccad"));

  int votes;
  votes = -999;
  assert(tallyVotes("38TXR55CAD6Msr29nYd06UTL", 'd', votes) == 0);
  assert(votes == 84);
  votes = -999; // so we can detect whether tallyVotes sets votes
  assert(tallyVotes("38TXR55CAD", '%', votes) == 2);
  assert(votes == -999);
  assert(tallyVotes("0TXR55CAD", 'd', votes) == 3);
  assert(votes == -999);
  assert(tallyVotes("5cad", 'd', votes) == 0);
  assert(votes == 5);

  cout << "All tests succeeded" << endl;
}
