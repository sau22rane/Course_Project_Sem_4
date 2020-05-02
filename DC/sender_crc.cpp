
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string msg, crc, encoded = "";
    cout<<"Enter the message"<<endl;
    getline(cin,msg);
    cout<<"Enter the CRC generator polynomial "<<endl;
    getline(cin,crc);
    int m = msg.length();
    int n =crc.length();
    encoded+=msg;
    for(int i=0;i<n-1;i++)
        encoded+='0';   

    for (int i=0 ;i<=encoded.length()-n;)  // stop when we complete all the message bits
    {
        for(int j=0;j<n;j++)
        {
            if(encoded[i+j]==crc[j])  // condition for 1 XOR 1 or 0 XOR 0
                encoded[i+j] = '0';
            else
                encoded[i+j] = '1';
        }
        
        for(;i<encoded.length() && encoded[i]!='1';i++) ; // remainder 1 not 0 
            
        
    }
    cout<<"Redundant Bits to be added are : "<<endl;
    for(int i= encoded.length()-(n-1);i<encoded.length();i++)
        cout<<encoded[i];
    cout<<endl;
}
