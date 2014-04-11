#include "../util/vbe.h"
#include <cstdlib>
#include <ctime>
#include <cassert>

void testVBEncoding(vector<int>& nums)
{
  VBE vbe;
  int len;
  char* buf = vbe.Encode(nums, len);
  vector<int> cpnums;
  vbe.Decode(buf, len, cpnums);
  assert(nums.size() == cpnums.size());
  for (unsigned int i = 0; i < nums.size(); ++i)
    assert(nums[i] == cpnums[i]);
  delete[] buf; // Do not forget that!
}

/*
int main()
{
  vector<int> nums;

  int times = 10;
  srand(unsigned(time(NULL)));
  while (times--) {
    int n = rand() % 10000 + 1;
    for (unsigned i = 0; i < n; ++i) {
      if (rand() % 2 == 0) nums.push_back(rand());
      else {
        nums.push_back((rand() << 16) + rand());
      }
    }
    testVBEncoding(nums);
  }
  return 0;
}
*/
