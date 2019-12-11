#include <iostream>
#include <string>
#include <math.h>
#include "RSA.h"

using namespace std;

void CryptStr(RSA* crypter, string str);
void DecryptStr(RSA* crypter, size_t strLength);
void PrintCryptedStr(RSA* crypter, size_t strLength);
void PrintDecryptedStr(RSA* crypter, size_t strLength);

int main()
{
	RSA crypter;
	string msg;

	cout << "Enter p:" << endl;
	cin >> crypter.p;
	cout << "Enter q:" << endl;
	cin >> crypter.q;

	crypter.CalculateN();
	crypter.CalculateT();
	crypter.CalculateE();
	crypter.CalculateD();

	cout << "n = " << crypter.n << endl;
	cout << "f(n) = " << crypter.t << endl;
	cout << "K(e) = (" << crypter.n << ", " << crypter.e << ")" << endl;
	cout << "K(d) = (" << crypter.n << ", " << crypter.d << ")" << endl;

	cout << "Message to encrypting:" << endl;
	cin.ignore();
	getline(cin, msg);

	CryptStr(&crypter, msg);
	DecryptStr(&crypter, msg.length());
	PrintCryptedStr(&crypter, msg.length());
	PrintDecryptedStr(&crypter, msg.length());

	cout << endl;
	return 0;
}

void CryptStr(RSA* crypter, string str)
{
	for (long int i = 0; i < str.length(); i++)
	{
		crypter->encryptedText[i] = crypter->Encrypt(str[i]);
	}
}

void DecryptStr(RSA* crypter, size_t strLength)
{
	for(long int i = 0; i < strLength; i++)
	{
		crypter->decryptedText[i] = crypter->Decrypt(crypter->encryptedText[i]);
	}
}
void PrintCryptedStr(RSA* crypter, size_t strLength)
{
	cout << endl << "Encrypted:" << endl;
	for (long int i = 0; i < strLength; i++)
	{
		cout << static_cast<char>(crypter->encryptedText[i]);
	}
}
void PrintDecryptedStr(RSA* crypter, size_t strLength)
{
	cout << endl << "Decrypted:" << endl;
	for (long int i = 0; i < strLength; i++)
	{
		cout << static_cast<char>(crypter->decryptedText[i]);
	}
}