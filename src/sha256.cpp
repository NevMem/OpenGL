#include <iostream>
#include <chrono>
using namespace std;

unsigned long long
	h0 = 0x6a09e667, 
	h1 = 0xbb67ae85, 
	h2 = 0x3c6ef372, 
	h3 = 0xa54ff53a, 
	h4 = 0x510e527f, 
	h5 = 0x9b05688c, 
	h6 = 0x1f83d9ab, 
	h7 = 0x5be0cd19;

unsigned long long k[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

unsigned long long mask = 0xFFFFFFFF;

unsigned long long rotate(unsigned long long value, int k){
	return (value >> k) | (value << (32 - k));
}

unsigned long long shift(unsigned long long value, int k){
	return (value >> k);
}

void hashIt(unsigned long long *from, unsigned long long *to){
	unsigned long long *w = new unsigned long long[64];

	for(int i = 0;i < 16;i++){
		w[i] = mask & ((*(from + (i >> 1))) >> (32 * (1 - (i & 1))));
	}

	for(int i = 16;i < 64;i++){
		unsigned int s0 = rotate(w[i - 15], 7) ^ rotate(w[i - 15], 18) ^ shift(w[i - 15], 3);
		unsigned int s1 = rotate(w[i - 2], 17) ^ rotate(w[i - 2], 19) ^ shift(w[i - 2], 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		w[i] &= mask;
	}

	unsigned int a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;

	for(int i = 0;i < 64;i++){
		unsigned int S1 = rotate(e, 6) ^ rotate(e, 11) ^ rotate(e, 25);
		unsigned int ch = (e & f) ^ ((~e) & g);
		unsigned int temp1 = h + S1 + ch + k[i] + w[i];
		temp1 &= mask;
		unsigned int S0 = rotate(a, 2) ^ rotate(a, 13) ^ rotate(a, 22);
		unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
		unsigned int temp2 = S0 + maj;
		temp2 &= mask;

		h = g;
		g = f;
		f = e;
		e = (d + temp1) & mask;
		d = c;
		c = b;
		b = a;
		a = (temp1 + temp2) & mask;
	}

	h0 = (h0 + a) & mask;
	h1 = (h1 + b) & mask;
	h2 = (h2 + c) & mask;
	h3 = (h3 + d) & mask;
	h4 = (h4 + e) & mask;
	h5 = (h5 + f) & mask;
	h6 = (h6 + g) & mask;
	h7 = (h7 + h) & mask;

	delete w;
}

string hexIt(unsigned int value){
	string s = "";
	while(value > 0){
		int now = value & 15;
		value >>= 4;
		
		char add = '-';
		if(now < 10)
			add = '0' + now;
		else
			add = 'a' + now - 10;

		s = add + s;
	}
	while(s.size() < 8)
		s = "0" + s;
	return s;
}

void initialize(){
	h0 = 0x6a09e667, 
	h1 = 0xbb67ae85, 
	h2 = 0x3c6ef372, 
	h3 = 0xa54ff53a, 
	h4 = 0x510e527f, 
	h5 = 0x9b05688c, 
	h6 = 0x1f83d9ab, 
	h7 = 0x5be0cd19;
}

void encode(string &s, unsigned int *res){ // res - array of unsigned int, with size 8(8 * 32bit = 256bit)
	initialize();

	int len = s.size() * 8;
	len += 1;

	while((len + 64) % 512 != 0)
		len += 1;
	len += 64;

	unsigned long long *msg = new unsigned long long[len / 64];
	for(int i = 0;i < len / 64;i++)
		msg[i] = 0;

	for(int i = 0;i < s.size();i++){
		unsigned long long now = s[i];
		msg[i / 8] |= ((unsigned long long)(s[i])) << (8 * (7 - (i & 7)));
	}
	
	int pos = s.size() * 8;
	msg[pos / 64] |= 1ll << (63 - (pos & 63));

	msg[len / 64 - 1] = s.size() * 8;

	pos = 0;
	while(pos < len){
		hashIt(msg + pos / 64, msg + pos + 512 / 64);
		pos += 512;
	}

	delete msg;

	*res = h0;
	*(res + 1) = h1;
	*(res + 2) = h2;
	*(res + 3) = h3;
	*(res + 4) = h4;
	*(res + 5) = h5;
	*(res + 6) = h6;
	*(res + 7) = h7;
}

void write(unsigned int value){
	for(int i = 31;i >= 0;i--)
		cout << ((value & (1 << i)) != 0);
}

string createHexString(unsigned int *arr){
	string ans = "";
	for(int i = 0;i < 8;i++){
		ans += hexIt(*(arr + i));
	}
	return ans;
}

string hashIt(string s){
	unsigned int *rs = new unsigned int[8];
	encode(s, rs);
	return createHexString(rs);
}

template < class T >
void assertEq(T a, T b){
	if(a == b)
		cout << "ok" << endl;
	else
		cout << "wrong. expected: " << a << " found: " << b << endl;
}

string toString(int value){
	string s = "";
	while(value > 0){
		s = (char)(value % 10 + '0') + s;
		value = value / 10;
	}
	return s;
}

int main(){
	string f = "startHash";

	unsigned int *rs = new unsigned int[8];

	int nonce = 0;
	while(true){
		string now = f + toString(nonce);
		encode(now, rs);

		int count = 0;
		while((rs[0] & (1ll << (31 - count))) == 0)
			count++;

		if(count >= 10){
			cout << now << endl;
			cout << createHexString(rs) << endl;
			break;
		}

		nonce++;
	}
	delete rs;
}