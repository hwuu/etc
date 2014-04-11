// $Id: vbe.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_VBE_H_
#define _ETC_VBE_H_

#include <assert.h>
#include <vector>

using namespace std;

class VBE // Variable Byte Encoding
{
public:
	VBE();
	~VBE();
	char* Encode(const vector<int>& nums, int& len);
	void Decode(char* buf, int len, vector<int>& nums);
private:
  void Encode(int num, char buf[16]);
};

#endif
