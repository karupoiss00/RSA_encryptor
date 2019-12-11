#include <iostream>
#include <string>
#include <math.h>
#include "RSA.h"

using namespace std;

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


	for (long int i = 0; i < msg.length(); i++)
	{
		crypter.encryptedText[i] = crypter.Encrypt(msg[i]);
	}
	cout << endl << "Encrypted:" << endl;
	for (long int i = 0; i < msg.length(); i++)
	{
		cout << static_cast<char>(crypter.encryptedText[i]);
	}


	for (long int i = 0; i < msg.length(); i++)
	{
		crypter.decryptedText[i] = crypter.Decrypt(crypter.encryptedText[i]);
	}
	cout << endl << "Decrypted:" << endl;
	for (long int i = 0; i < msg.length(); i++)
	{
		cout << static_cast<char>(crypter.decryptedText[i]);
	}


	cout << endl;
	return 0;
}