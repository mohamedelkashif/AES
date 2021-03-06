#include<iostream>
#include<math.h>
#include<string>
#include<cmath>
#include<vector>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include  <iomanip>


using namespace std;

unsigned char result[4][4];
unsigned char rkey[176];
unsigned char Key[16];
unsigned char in[4][4];
unsigned char out[16];
#define xtime(x)  ((x<<1) ^ (((x>>7) & 1) * 0x1b))



int sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

int Rcon[255] = {
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb };


unsigned int return_sbox(unsigned int num)
{
	return sbox[num];

}

unsigned char subistiute_byte(unsigned char in[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = return_sbox(in[i][j]);

			//cout << hex <<(unsigned int) result[i][j] << endl;
		}
	}
	return **result;
}
//cout << *result << endl;

unsigned char shiftrow()
{
	unsigned char temp;
	temp = result[0][1];
	// row 1
	result[0][1] = result[1][1];
	result[1][1] = result[2][1];
	result[2][1] = result[3][1];
	result[3][1] = temp;

	//row 2
	temp = result[0][2];
	result[0][2] = result[2][2];
	result[2][2] = temp;


	temp = result[1][2];
	result[1][2] = result[3][2];
	result[3][2] = temp;

	//row 3
	temp = result[0][3];
	result[0][3] = result[3][3];
	result[3][3] = result[2][3];
	result[2][3] = result[1][3];
	result[1][3] = temp;
	/*for (int i = 0; i < 4; i++)
	{
	/*for (int j = 0; j < 4; j++)
	{
	cout << hex <<(int) result[i][j] << endl;
	}
	}*/

	return **result;

}

int mixcolumns()
{
	int i;
	unsigned char t;
	unsigned char temp1;
	unsigned char temp2;

	for (i = 0; i < 4; i++)
	{
		t = result[i][0];
		temp1 = result[i][0] ^ result[i][1] ^ result[i][2] ^ result[i][3];
		temp2 = result[i][0] ^ result[i][1];
		temp2 = xtime(temp2);
		result[i][0] = result[i][0] ^ temp2 ^ temp1;

		temp2 = result[i][1] ^ result[i][2];
		temp2 = xtime(temp2);
		result[i][1] = result[i][1] ^ temp2 ^ temp1;

		temp2 = result[i][2] ^ result[i][3];
		temp2 = xtime(temp2);
		result[i][2] = result[i][2] ^ temp2 ^ temp1;

		temp2 = result[i][3] ^ t;
		temp2 = xtime(temp2);
		result[i][3] = result[i][3] ^ temp2 ^ temp1;


	}
	/*for (int i = 0; i < 4; i++)
	{
	for (int j = 0; j < 4; j++)
	{
	unsigned char b = result[i][j];
	cout  <<hex<< (int)b << endl;
	}
	}*/
	//cout <<hex<<(unsigned int) result[0][1] << endl;
	//cout << (int)**result << endl;
	return **result;

}
void addrkey(int round)
{


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = result[i][j] ^ rkey[round * 16 + i * 4 + j];

			//cout <<hex<< (unsigned int)result[i][j] << endl;
		}
	}



}

void keyExpansion(unsigned char key[16])
{
	int i; unsigned char w[44]; unsigned char temp[4]; unsigned char k;
	for (i = 0; i < 4; i++)
	{

		/*for (int j = 0; j < 4; j++)
		{*/
		rkey[i * 4] = key[i * 4];
		rkey[i * 4 + 1] = key[i * 4 + 1];
		rkey[i * 4 + 2] = key[i * 4 + 2];
		rkey[i * 4 + 3] = key[i * 4 + 3];
		//w[i] = key[i*4+3];
		//w[i] =  key[i* 1][j] ;
		//rkey[i] = key[i];//
		//cout << hex << (unsigned int)rkey[i] << endl;
		//cout << hex << (unsigned int)w[3] << endl;
		//cout  <<hex<< (unsigned int)w[3] << endl;

		//}	

		//cout << hex << (unsigned int)rkey[i] << endl;
		//cout << i << endl;
	}
	//cout << i << endl;
	while (i<44)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[j] = rkey[(i - 1) * 4 + j];
		}

		if (i % 4 == 0)
		{
			{
				k = temp[0];
				temp[0] = temp[1];
				temp[1] = temp[2];
				temp[2] = temp[3];
				temp[3] = k;
			}
			{
				temp[0] = return_sbox(temp[0]);
				temp[1] = return_sbox(temp[1]);
				temp[2] = return_sbox(temp[2]);
				temp[3] = return_sbox(temp[3]);
			}
			temp[0] = temp[0] ^ Rcon[i / 4];


		}
		else if (4 > 6 && i % 4 == 4)
		{
			// Function Subword()
			{
				temp[0] = return_sbox(temp[0]);
				temp[1] = return_sbox(temp[1]);
				temp[2] = return_sbox(temp[2]);
				temp[3] = return_sbox(temp[3]);
			}
		}
		rkey[i * 4 + 0] = rkey[(i - 4) * 4 + 0] ^ temp[0];
		rkey[i * 4 + 1] = rkey[(i - 4) * 4 + 1] ^ temp[1];
		rkey[i * 4 + 2] = rkey[(i - 4) * 4 + 2] ^ temp[2];
		rkey[i * 4 + 3] = rkey[(i - 4) * 4 + 3] ^ temp[3];
		i++;
	}

	//cout <<hex<<(unsigned int) rkey[i] << endl;
}

void encrypt()
{
	/*int i, j;
	for (int i = 0; i < 4; i++)
	{
	for (int j = 0; j < 4; j++)
	{
	result[i][j] = in[i][j];
	}
	}*/
	//cout <<(unsigned int) result[0][0] << endl;

	addrkey(0);
	for (int round = 1; round < 10; round++)
	{
		subistiute_byte(result);
		shiftrow();
		mixcolumns();
		addrkey(round);
	}
	subistiute_byte(result);
	shiftrow();
	addrkey(10);

	//for (i = 0; i<4; i++)
	//{
	//	for (j = 0; j<4; j++)
	//	{
	//		out[i * 4 + j] = result[i][j];
	//		//cout << hex << (unsigned int)result[i][j] << endl;
	//	}
	//}

}
int  main()
{
	int n;
	cout << "Enter no of inputs" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "\n" "Enter plain text" << endl;
		string p;
		cin >> p;
		cout << "Enter key" << endl;
		string k;
		cin >> k;
		unsigned plain[4][4] = { strtoul(p.substr(0, 2).c_str(), NULL, 16), strtoul(p.substr(2, 2).c_str(), NULL, 16), strtoul(p.substr(4, 2).c_str(), NULL, 16), strtoul(p.substr(6, 2).c_str(), NULL, 16), strtoul(p.substr(8, 2).c_str(), NULL, 16), strtoul(p.substr(10, 2).c_str(), NULL, 16), strtoul(p.substr(12, 2).c_str(), NULL, 16), strtoul(p.substr(14, 2).c_str(), NULL, 16), strtoul(p.substr(16, 2).c_str(), NULL, 16), strtoul(p.substr(18, 2).c_str(), NULL, 16), strtoul(p.substr(20, 2).c_str(), NULL, 16), strtoul(p.substr(22, 2).c_str(), NULL, 16), strtoul(p.substr(24, 2).c_str(), NULL, 16), strtoul(p.substr(26, 2).c_str(), NULL, 16), strtoul(p.substr(28, 2).c_str(), NULL, 16), strtoul(p.substr(30, 2).c_str(), NULL, 16) };
		unsigned char key[16] = { strtoul(k.substr(0, 2).c_str(), NULL, 16), strtoul(k.substr(2, 2).c_str(), NULL, 16), strtoul(k.substr(4, 2).c_str(), NULL, 16), strtoul(k.substr(6, 2).c_str(), NULL, 16), strtoul(k.substr(8, 2).c_str(), NULL, 16), strtoul(k.substr(10, 2).c_str(), NULL, 16), strtoul(k.substr(12, 2).c_str(), NULL, 16), strtoul(k.substr(14, 2).c_str(), NULL, 16), strtoul(k.substr(16, 2).c_str(), NULL, 16), strtoul(k.substr(18, 2).c_str(), NULL, 16), strtoul(k.substr(20, 2).c_str(), NULL, 16), strtoul(k.substr(22, 2).c_str(), NULL, 16), strtoul(k.substr(24, 2).c_str(), NULL, 16), strtoul(k.substr(26, 2).c_str(), NULL, 16), strtoul(k.substr(28, 2).c_str(), NULL, 16), strtoul(k.substr(30, 2).c_str(), NULL, 16) };




		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result[i][j] = plain[i][j];


			}
		}
		/*for (int i = 0; i < 16; i++)
		{
		key[i] = key[i];
		}*/


		int m;
		cout << "Enter no of times of encryption" << endl;
		cin >> m;
		keyExpansion(key);
		clock_t t1 = clock();
		for (int i = 0; i < m; i++)
		{
			encrypt();
		}

		cout << "Text after encryption:" << endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout<<setfill('0')<<setw(2) << hex << (unsigned int)result[i][j];
				//printf("%x", (unsigned int)result[i][j]);

			}

		}
		clock_t t2 = clock();
		cout << endl;
		printf("%f", ((double)(t2 - t1)) * 1000 / (double)CLOCKS_PER_SEC);
	}


	//double msec = ((double)(t2 - t1)) * 1000 /(double) CLOCKS_PER_SEC;
	//cout << "\n""time: " << msec << endl;




	//cout << "\n""time: " << ((t2 - t1) / double(CLOCKS_PER_SEC)) *1000 << endl;
	//printf("%f", ((t2 - t1) / double(CLOCKS_PER_SEC)) * 1000);
	return 0;


}
