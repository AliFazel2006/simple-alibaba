#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <conio.h> //برای تابع _getch()
#include <algorithm> //برای تابع find
#include <cstdlib> //برای تابع system
#include <cstdlib> // برای rand() و srand()
#include <ctime>

using namespace std;

void clearScreen() {
    system("cls");
}

class user {
public:
    vector < string > title;
    vector < array<int,2> > tedad_mablagh;

    ~user (){
        exit(0);
    }

    string getusername() {
        string username;
        char ch;
        cout << "Enter username: ";

        while ((ch = _getch()) != '\r') { // تا زمانی که Enter زده نشده
            if (ch == '\b') { // اگر کلید Backspace زده شد
                if (!username.empty()) {
                    username.pop_back();
                    cout << "\b \b"; // کاراکتر قبلی را پاک کن
                }
            } else {
                username.push_back(ch);
                cout << ch; // نمایشی کاراکتر واقعی
            }
        }
        cout << endl;
        return username;
    }

    string getpassword() {
        string password;
        char ch;
        cout << "Enter password: ";

        while ((ch = _getch()) != '\r') { // تا زمانی که Enter زده نشده
            if (ch == '\b') { // اگر کلید Backspace زده شد
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // کاراکتر قبلی را پاک کن
                }
            } else {
                password.push_back(ch);
                cout << '*'; // نمایش * به جای کاراکتر واقعی
            }
        }
        cout << endl;
        return password;
    }

    int searchInFile(const string& filename, const string& keyword) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "opening " << filename << " eror (searchInFile)" << endl;
            exit(0);
        }

        string line;
        int lineNumber = 1;
        bool found = false;

        while (getline(file, line)) {
            if (line.find(keyword) != string::npos) {
                found = true;
                break;
            }
            lineNumber++;
        }

        file.close();
        if ( found == true ) return lineNumber;
        if ( found == false) return 0;
    }

    bool login (){

        for ( int i = 2 ; i >= 0 ; i-- ){
            string us = getusername();
            string pas = getpassword();

            int u = searchInFile("username.txt", us);
            int p = searchInFile("password.txt", pas);

            if ( u != 0 && u == p ) {
                cout << "Login successful!" << endl;
                return true;
            } else if ( i == 0 ){
                cout << "Wrong username or password\nYou don't have any more try" << endl;
                exit(0);
            } else if ( u == 0 || u != p ){
                cout << "Wrong username or password\nPlease enter your info again\nYou have " << i << " more try" << endl;
            }
        }
    }

    bool signup (){

        ofstream ufile("username.txt", ios::app);
        ofstream pfile("password.txt", ios::app);

        if (!ufile) {
            cerr << "opening username.txt eror (signup)" << endl;
            exit(0);
        }
        if (!pfile) {
            cerr << "opening password.txt eror (signup)" << endl;
            exit(0);
        }

        string us = getusername();
        string pas = getpassword();

        int u = searchInFile("username.txt", us);

        if ( u == 0 ) {
            ufile << "\n" << us << endl;
            pfile << "\n" << pas << endl;
            cout << "Login successful!" << endl;
            ufile.close();
            pfile.close();
            return true;
        } else {
            cout << "Username already exists" << endl;
            ufile.close();
            pfile.close();
            return false;
        }
    }

    void factor (){
        int total = 0;
        cout << "\t\t\t\tYour final factor" << endl;
        cout << "Title\t\tTickets/Days\t\tUnit price\t\tTotal amount" << endl;
        for ( int i = 0 ; i < title.size() ; i++ ){
            cout << title [i] << "\t\t" << tedad_mablagh[i][0] << "\t\t\t" << tedad_mablagh[i][1] << " Tooman\t\t" << tedad_mablagh[i][0]*tedad_mablagh[i][1] << " Tooman" << endl;
            total += tedad_mablagh[i][0]*tedad_mablagh[i][1];
        }
        cout << "Total: " << total << " Tooman" << endl;
    }
};

class buy {
private:
    int day, month, year;
    unsigned int seed;

    bool isValidDate (int day, int month, int year) {
        if (year < 1) return false;
        if (month < 1 || month > 12) return false;

        int daysInMonth;
        switch (month) {
            case 12:
                daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
                break;
            case 6: case 7: case 8: case 9: case 10: case 11:
                daysInMonth = 30;
                break;
            default:
                daysInMonth = 31;
        }

        return day >= 1 && day <= daysInMonth;
    }

    unsigned int dateToSeed(int year, int month, int day) {
        return (year * 10000) + (month * 100) + day;
    }

    void initializeRandom() {
        seed = dateToSeed(year, month, day);
        srand(seed);
    }

    virtual int gheymat () { return 0; }

public:
    void tarikh () {
        cout << "Enter day (1-31): ";
        cin >> day;

        cout << "Enter month (1-12): ";
        cin >> month;

        cout << "Enter year: ";
        cin >> year;

        if (!isValidDate(day, month, year)) {
            cout << "Invalid date!" << endl;
        }
    }

    void toLowerCase(string &str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    int tedad ( int price ) {
        clearScreen();
        cout << "Har blit baraye tarikhe mored nazar " << price << " Tooman ast." << endl;
        cout << "Tedad blit mored niaz ra vared konid ya baraye enseraf as kharind 0 ra vared konid" << endl;
        int n;
        cin >> n;
        return n;
    }

    int rooz ( int price ) {
        clearScreen();
        cout << "bahye har rooz hotel as tarikhe mored nazar " << price << " Tooman ast." << endl;
        cout << "Tedad rooz mored niaz ra vared konid ya baraye enseraf as kharind 0 ra vared konid" << endl;
        int n;
        cin >> n;
        return n;
    }

    void resid ( int t, int price, string s, string p ) {
        clearScreen();
        cout << t << " blit as " << s << " be " << p << " Baraye tarikh " << year << "/" << month << "/" << day << endl;
        cout << "majmoo: " << t*price << "Tooman" << endl;
    }

    void resid ( int t, int price, string s ) {
        clearScreen();
        cout << t << " rooz dar " << " as tarikh " << year << "/" << month << "/" << day << endl;
        cout << "majmoo: " << t*price << "Tooman" << endl;
    }
};

class airplane: public buy {
private:

public:
    int price;
    bool check;

    int gheymat () {
        return 1500000*(rand() % 100 + 1);
    }

    airplane (string a, string b){
        check = true;
        price = gheymat();

        toLowerCase(a);
        toLowerCase(b);

        vector<string> validCities = {"tehran", "isfahan", "shiraz"};

        if (find(validCities.begin(), validCities.end(), a) == validCities.end()) {
            cout << "blit as foroodgah mored nazar dar dastres nist" << endl;
            check = false;
        }

        if (find(validCities.begin(), validCities.end(), b) == validCities.end()) {
            cout << "blit be foroodgah mored nazar dar dastres nist" << endl;
            check = false;
        }

        if ( a==b ){
            cout << "mabda va maghsad yeki ast!" << endl;
            check = false;
        }
    }

};

class train: public buy {
private:

public:
    int price;
    bool check;

    int gheymat () {
        return 500000*(rand() % 100 + 1);
    }

    train (string a, string b){
        check = true;
        price = gheymat();

        toLowerCase(a);
        toLowerCase(b);

        vector<string> validCities = {"tehran", "isfahan", "mashhad", "shiraz", "hormozgan"};

        if (find(validCities.begin(), validCities.end(), a) == validCities.end()) {
            cout << "blit as istgah mored nazar dar dastres nist" << endl;
            check = false;
        }

        if (find(validCities.begin(), validCities.end(), b) == validCities.end()) {
            cout << "blit be istgah mored nazar dar dastres nist" << endl;
            check = false;
        }

        if ( a==b ){
            cout << "mabda va maghsad yeki ast!" << endl;
            check = false;
        }
    }

};

class bus: public buy {
private:

public:
    int price;

    int gheymat () {
        return 150000*(rand() % 100 + 1);
    }

    bus () {
        price = gheymat();
    }

};

class hotel: public buy {
public:
    int price;

    int gheymat () {
        return 250000*(rand() % 100 + 1);
    }

    hotel () {
        price = gheymat ();
    }
};

int main()
{
    user u;
    string start, payan, shahr;
    char x;
    int n;

    cout << "Welcome" << endl;

    bool check = false;
    while ( !check ){ //ورود
        cout << "Do yuo have account?\nYes(Y)\tNo(N)" << endl;
        char x;
        cin >> x;
        switch (x){
            case 'Y': case 'y':{
                check = u.login();
                break;
            }
            case 'N': case 'n':{
                check = u.signup();
                break;
            }
            default: {
                cout << "invalid input" << endl;
                break;
            }
        }
    }

    check = true;
    while ( check ){ //منو
        //clearScreen();
        cout << "Buy ticket (B)\tRezerve hotel (R)\tExit (E)" << endl;
        cin >> x;
        switch (x){
            case 'B': case 'b': {
                cout << "choose vehicle\nBus (B)\tTrain (T)\tAirplane (A)\tBack to Menu (M)" << endl;
                cin >> x;
                switch (x){
                    case 'B': case 'b': {
                        cout << "As che shahri" << endl;
                        cin >> start;
                        cout << "Be che shahri" << endl;
                        cin >> payan;
                        bus b;
                        cout << "Baraye che tarikhi?" << endl;
                        b.tarikh();
                        int tedad = b.tedad( b.price );
                        if ( tedad == 0 ) break;
                        b.resid( tedad, b.price, start, payan);
                        u.title.push_back ( "Bus" );
                        u.tedad_mablagh.push_back ( {tedad,b.price});
                        break;
                    }
                    case 'T': case 't': {
                        cout << "As che istgahi" << endl;
                        cin >> start;
                        cout << "Be che istgahi" << endl;
                        cin >> payan;
                        train t (start,payan);
                        if ( t.check == false ) break;
                        cout << "Baraye che tarikhi?" << endl;
                        t.tarikh();
                        int tedad = t.tedad( t.price );
                        if ( tedad == 0 ) break;
                        t.resid( tedad, t.price, start, payan);
                        u.title.push_back ( "Train" );
                        u.tedad_mablagh.push_back ( {tedad,t.price});
                        break;
                    }
                    case 'A': case 'a': {
                        cout << "As che foroodgahi" << endl;
                        cin >> start;
                        cout << "Be che foroodgahi" << endl;
                        cin >> payan;
                        airplane a (start,payan);
                        if ( a.check == false ) break;
                        cout << "Baraye che tarikhi?" << endl;
                        a.tarikh();
                        int tedad = a.tedad( a.price );
                        if ( tedad == 0 ) break;
                        a.resid( tedad, a.price, start, payan);
                        u.title.push_back ( "Airplane" );
                        u.tedad_mablagh.push_back ( {tedad,a.price});
                        break;
                }
                    case 'M': case 'm': {
                        break;
                    }
                    default: {
                cout << "invalid input" << endl;
                break;
            }
                }
                break;
            }
            case 'R': case 'r': {
                cout << "baraye che shahri hotel mikhahid?" << endl;
                cin >> shahr;
                hotel h;
                cout << "Baraye che tarikhi?" << endl;
                h.tarikh();
                int rooz = h.rooz( h.price );
                if ( rooz == 0 ) break;
                h.resid( rooz, h.price, shahr);
                u.title.push_back ( "Hotel" );
                u.tedad_mablagh.push_back ( {rooz,h.price});
                break;
            }
            case 'E': case 'e': {
                check = false;
            }
            default: {
                cout << "invalid input" << endl;
                break;
            }
        }

    }

    clearScreen();
    if ( u.title.size() != 0 ) u.factor();

    return 0;
}
