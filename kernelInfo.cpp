//****************************************************************
//
//   Program 1 by Daniel Branham - 1/16/18
//        This Program is designed to read different /proc files
//        and print out a variety of info about the system it is
//        running on.
//
//****************************************************************
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;

int main()
{
     fstream procFile;
     string info, moreInfo;


     //Gather Hostname-----------------------------------------
     cout << endl << "--------------------------------------------" << endl;
     procFile.open("/proc/sys/kernel/hostname", ios::in);

     if(!procFile.is_open()) //always check for file open
          cout << "Didn't open file." << endl;

     getline(procFile, info); //read first and only line in file
     cout << "Host Name: " << info << endl;
     procFile.close();

     //Gather number of processing units-----------------------
     cout << "Number of processors: " << endl;
     system("cat /proc/cpuinfo | grep 'processor' | wc -l");
     //UNIX command that counts number of occurences of the word 'processor'

     cout << endl;
     //--------------------------------------------------------


     //Gather individual processor info------------------------
     procFile.open("/proc/cpuinfo", ios::in);

     if(!procFile.is_open())
          cout << "Didn't open file." << endl;

     getline(procFile, info);
     while(!procFile.eof()) //print every time one of the following strings is read
     {
          if(info.find("processor") != string::npos) //look for 'processor' until the end of the line
               cout<< info << endl;
          else if(info.find("vendor_id") != string::npos)
               cout << info << endl;
          else if(info.find("model		:") != string::npos)
               cout << info << endl;
          else if(info.find("model name") != string::npos)
          {
               cout << info << endl;
               cout << endl;
          }
          getline(procFile, info);
     }
     procFile.close();
     //--------------------------------------------------------


     //Gather Linux Kernel Version-----------------------------
     procFile.open("/proc/version", ios::in);

     if(!procFile.is_open())
          cout << "Didn't open file." << endl;

     getline(procFile, info); //read and save only line in file
     cout << "Linux Kernel Version: " << info << endl;
     procFile.close();
     //--------------------------------------------------------


     //Gather system uptime------------------------------------
     procFile.open("/proc/uptime", ios::in);

     if(!procFile.is_open())
          cout << "Didn't open file." << endl;

     getline(procFile, info, ' '); //read until the space
     getline(procFile, moreInfo); //read the rest after space
     procFile.close();

     cout << endl << "Uptime: " << info << endl;
     cout << "Idle Time: " << moreInfo << endl;
     //--------------------------------------------------------


     //Gather memory information-------------------------------
     procFile.open("/proc/meminfo", ios::in);

     if(!procFile.is_open())
          cout << "Didn't open file." << endl;

     getline(procFile, info); //first 2 lines contain needed info
     getline(procFile, moreInfo);
     procFile.close();

     cout << endl << info << endl;
     cout << moreInfo << endl;
     //--------------------------------------------------------


     cout << "--------------------------------------------" << endl;
     cout << "Program by Daniel Branham" << endl;
     cout << endl;
     return 0;
}
