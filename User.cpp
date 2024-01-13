#include<iostream>     // Input and output stream handling
#include<fstream>      // File stream handling
#include<windows.h>    // Windows API functions for console manipulation and others
#include<sstream>      // String stream for parsing
#include<cctype>       // Character handling function
#include <winnt.h>     // Windows NT definitions
#include<conio.h>      // Console input/output functions
using namespace std;
const char* redText = "\x1B[31m";
const char* resetText = "\x1B[0m";
class Login
{
  private:
     string LoginID,Password;
  public:
     Login():LoginID(""),Password(""){};
     void set_LoginId(string LoginID)
     {
       this->LoginID=LoginID;
     }
     void set_Password(string Password)
     {
        this->Password=Password;
     }
     string get_LoginId()
     {
        return LoginID;
     }
     string get_Password()
     {
        return Password;
     }
};
/* Function For Password Masking */
string Password_Hidden(string Password) 
{  
   char ch;
   while(true)
   {
      ch=_getch();
      if(ch==13)
      {
         break;
      }
      else if(ch==8 && !Password.empty())
      {
          cout<<"\b \b";
          Password.pop_back();
      }
      else
      {
          cout<<"*";
          Password.push_back(ch);
      }
   }
   return Password;
}
/* Password Checker For Minimal Password Conditions*/
bool Password_Check(string Password)
{
   if(Password.length()>=8)
   {
      for(char ch:Password)
      {
            if(isalnum(ch) && isupper(ch))
            {
               return true;
            }
            else
            {
              return false;
            }
      }
   }
   else
   {
     return false;
   }
      
}
/* Function for Registration*/
void registration(Login Log)
{
   system("cls");
   string LoginId,Pass;
   cout<<"\tEnter Login ID:";
   cin>>LoginId;
   Log.set_LoginId(LoginId);
   start:
   cout<<"\tEnter a Strong Password:";
   string Password=Password_Hidden(Pass);
   if(Password_Check(Password))
   {
      Log.set_Password(Password);
   }
   else
   {
     cout<<redText<<"\n\tError:Include 8 Characters,Special Characters,Upper case Letter\n"<<resetText;
     goto start;
   }
   ofstream outfile("E:/Project/User_Login/Login.txt",ios::app);
    if(!outfile)
    {
       cout<<"\n\tError: File Can't Open!"<<endl;
    }
    else
    {
       outfile<<"\t"<<Log.get_LoginId()<<" : "<<Log.get_Password()<<endl<<endl;
       cout<<"\n\tUser Registered Succesfully!"<<endl;
    }
    outfile.close();
    Sleep(3000);
}
/*Login Function For User*/
void login()
{
   system("cls");
   string LoginId,Pass;
   cout<<"\tEnter the Login Id:";
   cin>>LoginId;

   cout<<"\tEnter Password:";
   string Password=Password_Hidden(Pass);
   ifstream infile("E:/Project/User_Login/Login.txt");
   if(!infile)
   {
      cout<<"\t Error: File Can't Open!"<<endl;
   }
   else
   {
      string line;
      bool found=false;
      while(getline(infile,line))
      {
         stringstream ss;
         ss<<line;
         string User_ID,User_Password;
         char delimiter;
         ss>>User_ID>>delimiter>>User_Password;
         if(User_ID==LoginId&&User_Password==Password)
         {
           found=true;
         }
      }
      if(found)
      {
           found=true;
           cout<<"\n\tPlease Wait"<<endl;
           cout<<"\t\t";
           for(int i=0;i<10;i++)
           {
            cout<<".";
            Sleep(100);
           }
           system("cls");
           cout<<endl;
           cout<<"\tWelcome to Page!"<<endl;
      }
      else
      {
       cout<<redText<<"\n\tError:Invalid Credentials\n"<<resetText;

      }
      
   }
Sleep(1000);
}
int main()
{
  Login Log;

  bool exit=false;
  while(!exit)
  {
     system("cls");
     int val;
     start:
      cout<<"\tWelcome to Registration & Login Form"<<endl;
      cout<<"\t************************************"<<endl;
      cout<<"\t1.Register"<<endl;
      cout<<"\t2.Login"<<endl;
      cout<<"\t3.Exit"<<endl;
      cout<<"\tEnter Choice:";
      cin>>val;
     if(val==1)
     {
       registration(Log);
     }
     else if(val==2)
     {
       login();
     }
     else if(val==3)
     {
       exit=true;
     }
     else
     {
      cout<<"\n";
      cout<<redText<<"\n\tError:Invalid Choice\n"<<resetText;
      Sleep(100);
      system("cls");
      goto start;
     }
     Sleep(3000);
   }
}