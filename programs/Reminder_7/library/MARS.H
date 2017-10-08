#ifndef _MARS_H_
#define _MARS_H_

#include "std_defs2.h"
#include <string>
using namespace std;

class mars : public AES
{
private:
	u4byte   l_key[40];
	void set_key(const u1byte key[], const u4byte key_bits);
	void encrypt(const u1byte in_blk[16], u1byte out_blk[16]);
	void decrypt(const u1byte in_blk[16], u1byte out_blk[16]);

public:
	char *name(void);
	string encrypt(string str, int ed = 1);
	string encrypt16(string str, int ed = 1);
};

#endif