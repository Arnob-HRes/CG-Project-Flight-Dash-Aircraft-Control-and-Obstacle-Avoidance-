#include<iostream>
#include<fstream>
#include<string.h>
#include <cstdlib>
#include <windows.h>
#include <GL/glut.h>
using namespace std;

void startMainGame(int argc, char** argv);

void LOGIN_PAGE(){
    string USER,PASS, user, pass;
    bool Validity=false;
    system("cls");
    cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|------------------LOGIN PAGE-----------------|\n\n\n\n";
    cout<<"\t\t\t\t_______________________________________________________________\n\n";
    cout<<"\t\t\t\t                   USERNAME: ";
    cin>>USER;
    cout<<"\t\t\t\t                   PASSWORD: ";
    cin>>PASS;

    ifstream check("USER_INFORMATION.txt");

    while(check>>user>>pass){
        if(user==USER && pass==PASS){
            Validity=true;
            break;
        }
    }
    check.close();
    if(Validity){
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\n\t\t\t\t                   Login Successful!\n";
        cout<<"\n\t\t\t\t                   USER: "<<USER<<"\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        system("pause");
        system("cls");
        cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
        cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
        cout<<"\t\t\t\t\t|----------------LONCHING GAME----------------|\n\n\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\t\t\t\t                Launching Flight Dash...\n\n";
        char a=221;
        cout<<"\t\t\t\t       Loading: ";
        for(int i=0;i<=30;i++){
            cout<<a;
            Sleep(100+i+i);
        }
        cout<<"\n\n\t\t\t\t                 100% Loading Successful\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n\n\n\t\t\t\t";
        system("pause");
        startMainGame(__argc, __argv);
    }
    else{
        system("cls");
        cout<<"\t\t\t\t\tUnsuccessful Login "<<USER;
    }

}

void Registration();

int main(){
    int key;
    char C;
    bool A=true;
    cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|------------------HOME PAGE------------------|\n\n\n\n";
    cout<<"________________________________________________________________________________________________________________________\n\n";
    cout<<"\t\t\t\t\t    GO TO LOGIN PAGE             PRESS [1]\n\n";
    cout<<"\t\t\t\t\t    GO TO REGISTRATION PAGE      PRESS [2]\n\n";
    cout<<"\t\t\t\t\t    GO TO GAME INFORMATION PAGE  PRESS [3]\n\n";
    cout<<"\t\t\t\t\t    EXIT                         PRESS [0]\n\n";
    cout<<"________________________________________________________________________________________________________________________\n\n";
    cout<<" WHAT IS YOUR CHOOISE: ";
    cin>>key;
    switch(key){
        case 1:
            LOGIN_PAGE();
            break;
        case 2:
            Registration();
            break;
        case 3:
        case 0:
            break;
        default:
            cout<<" INVALIDE INPUT. PRESS 1/2/3/0 TO CONTINUE\n";
            while(A){
                    cout<<" DO YOU WANT TO CONTINUE [y/n]: ";
                    cin>>C;
                    switch(C){
                        case 'y':
                            system("cls");
                            main();
                        case 'n':
                            A=false;
                            break;
                        default:
                            cout<<" INVALIDE INPUT. TRY AGAIN [y/n]\n";
                    }
            }
    }

}

void Registration(){
    string USER, PASS, user, pass;
    bool Validity = false;

    system("cls");
    cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
    cout<<"\t\t\t\t\t|---------------REGISTRATION PAGE-------------|\n\n\n\n";
    cout<<"\t\t\t\t_______________________________________________________________\n\n";
    cout<<"\t\t\t\t                   USERNAME: ";
    cin>>USER;
    cout<<"\t\t\t\t                   PASSWORD: ";
    cin>>PASS;
    cout<<"\t\t\t\t_______________________________________________________________\n\n";

    ifstream check("USER_INFORMATION.txt");
    while(check >> user >> pass){
        if(USER == user){
            Validity = true;
            break;
        }
    }
    check.close();

    if(Validity){
        cout << "\nUser [" << USER << "] already exists!\n";
        return;
    }

    ofstream reg("USER_INFORMATION.txt", std::ios::app);
    if(!reg){
        cout << "File open failed!\n";
        return;
    }

    reg << USER << " " << PASS <<endl;
    reg.close();

    system("cls");
    cout << "\nUser [" << USER << "] successfully registered!\n\n";
    main();
}

