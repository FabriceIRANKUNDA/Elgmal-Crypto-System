#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<string>
#include<cmath>
using namespace std;
long long int R;
string msg;
bool is_Prime(long long int p)    // a function to check if entered number is a prime number
{
   int count = 0;                
    for (int i = 2; i <= p; i++) // loop to find if there is more than one divisor of p
	{
		if (p % i == 0)
		{
			count += 1;          // counting those divisor 
		}
	}
    if (count > 1)
        return false;           // if divisor are more than one p is not a prime otherwise is a prime
    else
        return true;	
}

// a function to support find power to manupulate value of y and g using pass by refference

int FastExponention(int r, int p, int* y, int* g)
{
	if (r == 1)
		*y = (*y * (*g)) % p;  // modify y when m is odd number

	*g = (*g) * (*g) % p;     // modify g otherwise
}

// a function to calculate power and remainder because c++ do not support power of large numbers
// that why we need to find the corresponding power and remainder by refering to a small number

int find_power(int g, int m, int p)
{
	int r;
	int y = 1;

	while (m > 0)
	{
		r = m % 2;
		FastExponention(r, p, &y, &g);
		m = m / 2;
	}

	return y;
}

// a function to encrypt plain text

 int* encrypt(long long int g, long long int p, long long int A)
{
	long long int r;
	cout<<"..............Sender side............"<<endl<<endl;
	cout<<"choose your private key r which must be in interval [1, p-2]: ";
	cin>>r;                                    // generate random number r, 1 < r < p - 2 which is private key of sender
	cout<<endl;
	cout<<"enter message to be encrypted: ";
	cin.ignore();
	getline(cin, msg );                      // input message to be encrypted
	int k = msg.length();                   // store lenght of message in variable k
	int * cipher_text = new int[k];        // allocate a pointer to store encrypted text                                    
	R = find_power(g, r, p);                   //  find R = g ^ r  mod p
	for(int i = 0; i < msg.size(); i++)       //   encrypt each character of message, cipher = m * A ^ r mod p
	{
		cipher_text[i]= (int(msg.at(i)) *  find_power(A,r,p)) % p;	
	}
	return cipher_text;
}
//  a function to decrypt cipher text to get plain text
 int* decrypt(long long int R, int* cipher_text, long long int p, long long int a)
{
	 int* plain_text = new int[msg.length()];  // allocate a pointer to store decrypted text
	for(int i = 0;i < msg.length(); i++)        //  decrypt each character of cipher text, plain text = cipher * (R ^ (p -1 - a) mod p)
	{
		plain_text[i] = (cipher_text[i] * find_power(R, p - 1 - a, p)) % p;
	}

	return plain_text;
}
// a function to check if p is at least greater than 123
bool gtr(long long int p)
{
	return p > 123;
}

int main(int argc, char** argv) {
	long long int p,g,a,A;
	srand(time(NULL));
	cout<<"............. WELCOME TO ELGMAL ENCRYPTION ALGORITHM ..............."<<endl<<endl;
	cout<<"enter the value of a more than 123 prime number p: ";
	cin>>p;
	cout<<endl<<endl;
	// loop to continuously ask to enter a valid value of p and break when p is valid
	while (true)
	{
		if (is_Prime(p) and gtr(p))
			break;
		else
		{
			cout<<"remember that p must be a large prime number, try again: ";
			cin>>p; // input p again until it is valid
		}
	}
	cout<<"...............Receiver side........."<<endl<<endl;
	cout<<"enter the value of g which must be in interval [1, p-1]: ";
	cin>>g;              // select a generator g
	cout<<endl;
	cout<<"enter your private key a which must be in interval [1, p-2]: ";
	cin>>a;             // select a random integer a, 1 <= a <= p-2 which is private key 
	cout<<endl;
	A = find_power(g,a,p);	             //  compute A = g * a mod p and get a public key (p,g,A)
	cout<<"shared public key: ( g= "<<g<<", p= "<<p<<", A="<<A<<")"<<endl<<endl;
	int* cipher_text = encrypt(g, p, A); // share public key with sender 
	int* plain_text= decrypt(R, cipher_text, p, a); // decrypt cipher text using R calculated by sender
	cout<<endl<<endl;
	cout<<"cipher text is: ";                  // displaying ciphered text
	for(int i=0; i<msg.size(); i++)
	{
		cout<<(char)cipher_text[i];
	}
	cout<<endl<<endl;
	cout<<"plain text is: ";
	for(int i=0; i<msg.size();i++)            // displaying plain text
	{
		cout<<(char)plain_text[i];
	}
	cout<<endl<<endl;
	cout<<"..............Thank you for using Elgmal Encryption Algorithm.........";
	cout<<endl<<endl;
	delete(cipher_text);                   // deallocate the memory 
	delete(plain_text);                   // deallocate the memory 
		return 0;
}
