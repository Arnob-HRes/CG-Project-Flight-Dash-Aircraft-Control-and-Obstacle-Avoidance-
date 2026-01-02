#include<iostream>
#include<string.h>
#include <cstdlib>
#include <windows.h>
#include <GL/glut.h>
#include <mysql.h>
#include <sstream>
using namespace std;

void startMainGame(int argc, char** argv);
void setScore(int S);


void LOGIN_PAGE();
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

void LOGIN_PAGE(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn, "127.0.0.1", "root","","flight_dash",0,NULL,0);
    string USER,PASS, user;
    int score;
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

    if(conn){
        int qstate=mysql_query(conn, "SELECT username,password,score FROM user");

        if(!qstate){
            res=mysql_store_result(conn);

            while(row=mysql_fetch_row(res)){
                if(USER==row[0] && PASS==row[1]){
                    score=atoi(row[2]);
                    Validity=true;
                }
            }
        }
    }

    if(Validity){
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\n\t\t\t\t                   Login Successful!\n";
        cout<<"\n\t\t\t\t                   USER: "<<USER<<"\n\n";
        cout<<"\n\t\t\t\t      Highest score of the user: "<<score<<" Points\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        system("pause");
        system("cls");
        cout<<"\t\t\t\t\t|-----------------FLIGHT DASH-----------------|\n\t\t\t\t\t|                                             |\n";
        cout<<"\t\t\t\t\t|     WELCOME TO A 2D FLIGHT SIMULATING GAME  |\n\t\t\t\t\t|                                             |\n";
        cout<<"\t\t\t\t\t|----------------LAUNCHING GAME---------------|\n\n\n\n";
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
        setScore(score);
        startMainGame(__argc, __argv);
    }
    else{
        system("cls");
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\t\t\t\t  Unsuccessful Login [Invalid username or password ["<<USER<<"]\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        main();
    }

}

void Registration(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn, "127.0.0.1", "root","","flight_dash",0,NULL,0);
    string USER, PASS;
    bool Validity = false;
    int score=0,q=0;
    stringstream ss;

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

    if(conn){
        int qstate=mysql_query(conn, "SELECT username FROM user");

        if(!qstate){
            res=mysql_store_result(conn);

            while(row=mysql_fetch_row(res)){
                if(USER==row[0]){
                    Validity=true;
                }
            }
        }
    }
    if(Validity){
        system("cls");
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        cout<<"\t\t\t\t   User [ "<<USER<<"] already registered! Please Login\n\n";
        cout<<"\t\t\t\t_______________________________________________________________\n\n";
        main();
    }
    else{
        ss<<"INSERT INTO user(username, password, score) values('"<<USER<<"','"<<PASS<<"','"<<score<<"')";

    string query=ss.str();
    const char* qq=query.c_str();
    q=mysql_query(conn, qq);
    system("cls");
    cout << "\nUser [" << USER << "] successfully registered!\n\n";
    main();
    }
}

