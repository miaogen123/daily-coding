//sha256的产生过程
//常量预设
//附加填充比特
//附加消息长度
//逻辑函数预设
//每512位分块
//对每512位构造64个字
//进行64次循环得到H(i-1）
#include"sha256.h" 

namespace{
	const uint32_t blockSize = 512;
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

	uint32_t constKey[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
		0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
		0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
		0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
		0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
		0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};
}

//函数
inline uint32_t Ch_Mix(uint32_t x, uint32_t y, uint32_t z) {
	return (x&y) ^ (~x&z);
}
inline uint32_t Ma_Mix(uint32_t x, uint32_t y, uint32_t z) {
	return (x&y) ^ (x&z)^(y&z);
}
inline uint32_t Sigma0_Mix(uint32_t x) {
	return (x >> 2|x<<(32-2)) ^ (x >> 13|x<<(32-13)) ^ (x >> 22|x<<(32-22));
}
inline uint32_t Sigma1_Mix(uint32_t x) {
	return (x >> 6|x<<(32-6)) ^ (x >> 11|x<<(32-11)) ^ (x >> 25|x<<(32-25));
}
inline uint32_t Omiga0_Mix(uint32_t x) {
	return (x >> 7|x<<(32-7)) ^ (x >> 18|x<<(32-18)) ^ (x >> 3);
}
inline uint32_t Omiga1_Mix(uint32_t x) {
	return (x >> 17|x<<(32-17)) ^ (x >> 19|x<<(32-19)) ^ (x >> 10);
}

#define BigLittleSwap32(A)        ((((uint32_t)(A) & 0xff000000) >> 24) | \
								   (((uint32_t)(A) & 0x00ff0000) >> 8) | \
								   (((uint32_t)(A) & 0x0000ff00) << 8) | \
								   (((uint32_t)(A) & 0x000000ff) << 24))


//判断大小端
bool isBigEnd() {
	uint64_t test = 1;
	char* ptrTo64 = (char*)(&test);
	if (int(*ptrTo64) == 1) {
		return false;
	}
	else {
		return true;
	}
}

std::vector<uint32_t> sha256(std::string contents){
	char firstToAppend = char(128);
	char nullCha = char(0);
	contents.push_back(firstToAppend);
	uint64_t bitLen = contents.size()*8;
	//填充长度 
	if ((bitLen & 511) != 448) {
		int numOfBitToAppend = 0;
		numOfBitToAppend=(bitLen & 511 > 448)?448 + 512 - (bitLen & 511):448- (bitLen&511);
		assert(numOfBitToAppend % 8 == 0);// "补充字符的时候出现意外"
		std::string appendAtEnd(numOfBitToAppend / 8, nullCha);
		contents += appendAtEnd;
	}
	assert(((contents.size()*8)& 511) == 448);// "补全后长度不为448,逻辑出错"
	//附加长度
	//通过强制类型转化实现:但需要判断大小端序
	bitLen -= 8;
	char* ptrTo64 = (char*)(&bitLen);
	if (isBigEnd()) {
		contents += std::string(ptrTo64, 8);
	}else {
		//FIXME:容易溢出,注意检查
		std::string lenStr("");
		char* ptrTo8=(char*)ptrTo64;
		for (int i = 7; i >= 0; i--) {
			lenStr.push_back(*(ptrTo8+ i));
		}
		contents += lenStr;
	}
	assert(((contents.size()*8)& 511) == 0);// "补全后长度不为512的整数,逻辑出错"
	//分块迭代
	auto contSize=contents.size();
	auto ptrTo32 = (uint32_t*)(contents.c_str());
	std::array<uint32_t, 64> wordOf64;
	wordOf64.fill(0);
	for (int i = 0; i < contSize; i+=64) {
		//生成64个字
		for (int j = 0; j < 64; j++) {
			if (j < 16) {
				//这里要做一个大小端的转化
				if (!isBigEnd())
					wordOf64[j] = BigLittleSwap32(*(ptrTo32 + j));
				else
					wordOf64[j] = (*(ptrTo32 + j));
			}
			else {
				wordOf64[j] = Omiga1_Mix(wordOf64[j - 2]) + wordOf64[j - 7] + Omiga0_Mix(wordOf64[j - 15]) + wordOf64[j - 16];
			}
			//uint32_t hel=(wordOf64[j]+wordOf64[j])&(0xFFFFFFFF);

		}
		//逻辑运算
		uint32_t t0 = h0, t1 = h1, t2 = h2, t3 = h3, t4 = h4, t5 = h5, t6 = h6, t7 = h7;
		for (int j = 0; j < 64; j++) {
			uint32_t mid0 = Ch_Mix(t4, t5, t6) + wordOf64[j] + constKey[j] + t7 + Sigma1_Mix(t4);
			uint32_t mid1 = mid0 + Ma_Mix(t0, t1, t2) + Sigma0_Mix(t0);
			t7 = t6;
			t6 = t5;
			t5 = t4;
			t4 = mid0+t3;
			t3 = t2;
			t2 = t1;
			t1 = t0;
			t0 = mid1;
			//cout <<hex<< t0 << t1 << t2 << t3 << t4 << t5 << t6 << t7 << endl;
		}

		h0 += t0;
		h1 += t1;
		h2 += t2;
		h3 += t3;
		h4 += t4;
		h5 += t5;
		h6 += t6;
		h7 += t7;
		ptrTo32 += 16;
	}
	return std::vector<uint32_t>{h0, h1, h2, h3, h4, h5, h6, h7};
}
