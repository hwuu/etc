#include "vbe.h"

VBE::VBE(void)
{
}

VBE::~VBE(void)
{
}

char* VBE::Encode(const vector<int>& nums, int& len)
{
  vector<char> bufVec;
  char buf[16];
  for (int i = 0; i < (int)nums.size(); ++i)
  {
    Encode(nums[i], buf);
    for (int j=0; j<16; ++j)
    {
      bufVec.push_back(buf[j]);
      if (buf[j] < 0)
        break;
    }
  }
  len = bufVec.size();
  char* bufstream = new char[len];
  for (int i = 0; i < len; ++i)
    bufstream[i] = bufVec[i];
  return bufstream;
}

void VBE::Decode(char* buf, int len, vector<int>& nums)
{
  int n = 0;
  for (int i = 0; i < len; ++i) {
    n = (n << 7) | (buf[i] & 0x7f);
    if (buf[i] < 0) {
      nums.push_back(n);
      n = 0;
    }
  }
}

//

void VBE::Encode(int num, char buf[16])
{
  int buflen = 0;
  while (true) {
    buf[buflen] = num & 0x7f;
    ++buflen;
    assert(buflen <= 5);
    if (num < 128)
      break;
    num >>= 7;
  }
  for (int i = 0; i< buflen / 2; ++i) {
    char c = buf[i];
    buf[i] = buf[buflen - i - 1];
    buf[buflen - i - 1] = c;
  }
  buf[buflen - 1] = -1;
}
