/* Copyright 2021, Sergey Popov (i@sergobot.com) */

#include <cstring>
#include <iostream>
#include <utility>

using namespace std;

class String {
    char *str;
    int n;

    int IsEqual(const String &S) const { return strcmp(str, S.str); }

    int IsLessThan(const String &S) const { return (strcmp(str, S.str) <= 0); }

public:
    String() {
        n = -1;
        str = nullptr;
    };

    String(int nstr) {
        n = nstr < 0 ? 0 : nstr;
        str = new char[n + 1];
        str[n] = '\0';
    }

    String(const char *s);

    String(const String &);

    String(String && o) : str(std::exchange(o.str, nullptr)), n(std::exchange(o.n, 0)) {};

    ~String() { delete[] str; };

    const char* c_str() const { return str; };

    char &operator[](int i);

    const char &operator[](int i) const;

    String &operator=(const String &);

    String &operator=(String &&) noexcept;

    String &operator+=(const String &);

    String operator()(int i, int j); //возвращает подстроку

    // operator char*() {return str;} // оператор преобразования типа String к char*
    friend int operator==(const String &s1, const String &s2) { return s1.IsEqual(s2); }

    friend int operator<(const String &s1, const String &s2) { return s1.IsLessThan(s2); }

    friend int operator!=(const String &s1, const String &s2) { return !(s1 == s2); }

    friend int operator>(const String &s1, const String &s2) { return (s2 < s1); }

    friend int operator<=(const String &s1, const String &s2) { return !(s2 < s1); }

    friend int operator>=(const String &s1, const String &s2) { return !(s1 < s2); }

    friend String operator+(const String &, const String &);

    friend ostream &operator<<(ostream &out, const String &S) {
        if (S.str) out << S.str;
        return out;
    };

    friend istream &operator>>(istream &in, String &S) {
        if (S.str) in >> S.str;
        return in;
    };
};

String::String(const char *s) {
    n = strlen(s);
    str = new char[n + 1];
    strncpy(str, s, n + 1);
}

String::String(const String &o) {
    n = o.n;
    str = new char[n + 1];
    strncpy(str, o.str, n + 1);
}

char &String::operator[](int i) {
    return str[i];
}

const char &String::operator[](int i) const {
    return str[i];
}

String &String::operator=(const String &o) {
    delete str;
    n = o.n;
    str = new char[n + 1];
    strncpy(str, o.str, n + 1);
    return *this;
}

String &String::operator=(String &&s) noexcept {
    n = std::exchange(s.n, 0);
    str = std::exchange(s.str, nullptr);
    return *this;
}

String &String::operator+=(const String &o) {
    int newn = o.n + n;
    char *newstr = new char[newn + 1];
    strncpy(newstr, str, n);
    strncpy(newstr + n, o.str, o.n + 1);

    delete str;
    str = newstr;
    n = newn;

    return *this;
}

String String::operator()(int i, int j) {
    int newn = j - i;
    char *newstr = new char[newn];
    strncpy(newstr, str + i, newn);
    return String(newstr);
}

String operator+(const String &a, const String &b) {
    int newn = a.n + b.n;
    char *newstr = new char[newn + 1];
    strncpy(newstr, a.str, a.n);
    strncpy(newstr + a.n, b.str, b.n + 1);

    return String(newstr);
}


int main()
{
    return 0;
}