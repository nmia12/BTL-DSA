#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm> 
#include <set>
#include "D:\Document\BTLDSA\vector.cpp"
#define endl "\n"
#define Nhom22 main
#define int long long

using namespace std;

class Answer {
private:
    Vector<string> ans;
public:
    Answer() {
        ans.assign({"", "", "", ""});
    }
    string getAns(int i) {return ans[i];}
    void setAns(int i, string s) {ans[i] = s;}

    friend istream& operator>> (istream& is, Answer& a) {
        for (int i = 0; i < 4; i++) getline(is, a.ans[i]);
        return is;
    }
    friend ostream& operator<< (ostream& os, Answer& a) {
        for (int i = 0; i < 4; i++) os << a.ans[i] << endl;
        return os;
    }
};
class Test {
private:
    string Question;
    Answer Ans;
    int correctAns;
public:
    Test() {}

    string getQs() {return Question;}
    string getAnswer(int i) {return Ans.getAns(i);}
    int getCorrectAns() {return correctAns;}
    void setCorrectAns(int x) {correctAns = x;}
    void setAnswer(int i, string s) {Ans.setAns(i, s);}

    friend istream& operator>> (istream& is, Test& t) {
        getline(is, t.Question);  
        is >> t.Ans;  
        is >> t.correctAns;  
        is.ignore(); 
        return is;
    }
    friend ostream& operator<< (ostream& os, Test& t) {
        os << t.Question << endl;
        os << t.Ans;
        os << t.correctAns;
        return os;
    }
};
Nhom22() {
    ifstream ifs;
    ofstream ofs;
    ifs.open("D:\\Document\\BTLDSA\\input22.txt");
    ofs.open("D:\\Document\\BTLDSA\\output22.txt");

    if (!ifs) {
        cout << "Failed to open input22.txt!" << endl;
        return 1; 
    }

    if (!ofs) {
        cout << "Failed to open output22.txt!" << endl;
        return 1;
    }

    int n; 
    ifs >> n; 
    ifs.ignore();

    Vector<Test> LTest;
    for (int i = 0; i < n; i++) {
        Test temp;
        ifs >> temp;
        LTest.push_back(temp);
    }
    random_shuffle(LTest.begin(), LTest.end());
    for (int i = 0; i < n; i++) {
        ofs << LTest[i] << endl;
    }
    srand(time(NULL));
    int k;
    do {
        cout << "Nhap so cau hoi cho bai lam moi: ";
        cin >> k;
    } while (k > n);

    Vector<Test> newTest;

    set<int> se;
    while (se.size() < k) {
        int num = rand();
        num %= n;
        se.insert(num);
    }

    for (auto x : se) {
        newTest.push_back(LTest[x]);
    }

    for (int i = 0; i < newTest.size(); i++) {
        int num = rand() % 4;
        if (num == newTest[i].getCorrectAns()) {
            newTest[i].setCorrectAns(3 - num);
        } else if (3 - num == newTest[i].getCorrectAns()) {
            newTest[i].setCorrectAns(num);
        }
        string tg1 = newTest[i].getAnswer(num);
        string tg2 = newTest[i].getAnswer(3 - num);
        newTest[i].setAnswer(num, tg2);
        newTest[i].setAnswer(3 - num, tg1);
    }

    int user_point = 0;
    for (int i = 0; i < newTest.size(); i++) {
        cout << newTest[i].getQs() << endl;
        for (int j = 0; j < 4; j++) {
            cout << j << ". " << newTest[i].getAnswer(j) << endl;
        }
        int user_ans; cin >> user_ans;
        if (user_ans == newTest[i].getCorrectAns()) ++user_point;
    }

    cout << "You got " << user_point << " point! Congratulations!!!";

    ofs.close();
}