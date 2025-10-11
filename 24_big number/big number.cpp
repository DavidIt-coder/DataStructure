#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class MyBigInteger {
private:
    string num;
    bool isNegative;

    void removeLeadingZeros() {
        while (num.length() > 1 && num[0] == '0') {
            num.erase(0, 1);
        }
        if (num == "0") {
            isNegative = false;
        }
    }

    bool absGreater(const MyBigInteger& other) const {
        if (num.length() != other.num.length()) {
            return num.length() > other.num.length();
        }
        return num > other.num;
    }

    string absAdd(const string& a, const string& b) const {
        string result;
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string absSub(const string& a, const string& b) const {
        string result;
        int borrow = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        while (i >= 0) {
            int diff = (a[i] - '0') - borrow;
            if (j >= 0) diff -= (b[j] - '0');
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff + '0');
            i--;
            j--;
        }
        reverse(result.begin(), result.end());
        while (result.length() > 1 && result[0] == '0') {
            result.erase(0, 1);
        }
        return result;
    }

    string absMul(const string& a, const string& b) const {
        string result(a.length() + b.length(), '0');
        for (int i = a.length() - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = b.length() - 1; j >= 0; j--) {
                int mul = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
                result[i + j + 1] = mul % 10 + '0';
                carry = mul / 10;
            }
            result[i] += carry;
        }
        while (result.length() > 1 && result[0] == '0') {
            result.erase(0, 1);
        }
        return result;
    }

    string absDiv(const string& a, const string& b) const {
        if (b == "0") {
            throw;
        }
        string quotient;
        string remainder;
        for (char digit : a) {
            remainder += digit;
            while (remainder.length() > 1 && remainder[0] == '0') {
                remainder.erase(0, 1);
            }
            int count = 0;
            while (absGreaterOrEqual(remainder, b)) {
                remainder = absSub(remainder, b);
                count++;
            }
            quotient += to_string(count);
        }
        while (quotient.length() > 1 && quotient[0] == '0') {
            quotient.erase(0, 1);
        }
        return quotient;
    }

    bool absGreaterOrEqual(const string& a, const string& b) const {
        if (a.length() != b.length()) {
            return a.length() > b.length();
        }
        return a >= b;
    }

public:
    MyBigInteger(const string& str = "0") {
        if (str[0] == '-') {
            isNegative = true;
            num = str.substr(1);
        } else {
            isNegative = false;
            num = str;
        }
        removeLeadingZeros();
    }

    MyBigInteger add(const MyBigInteger& other) const {
        if (isNegative == other.isNegative) {
            MyBigInteger result(absAdd(num, other.num));
            result.isNegative = isNegative;
            return result;
        }
        if (absGreater(other)) {
            MyBigInteger result(absSub(num, other.num));
            result.isNegative = isNegative;
            return result;
        } else {
            MyBigInteger result(absSub(other.num, num));
            result.isNegative = other.isNegative;
            return result;
        }
    }

    MyBigInteger subtract(const MyBigInteger& other) const {
        MyBigInteger temp = other;
        temp.isNegative = !temp.isNegative;
        return add(temp);
    }

    MyBigInteger multiply(const MyBigInteger& other) const {
        MyBigInteger result(absMul(num, other.num));
        result.isNegative = isNegative != other.isNegative;
        return result;
    }

    MyBigInteger divide(const MyBigInteger& other) const {
        MyBigInteger result(absDiv(num, other.num));
        result.isNegative = isNegative != other.isNegative;
        return result;
    }

    string toString() const {
        if (isNegative && num != "0") {
            return "-" + num;
        }
        return num;
    }
};

int main() {
    string n, m;
    char op;
    cin >> n >> m >> op;

    MyBigInteger num1(n);
    MyBigInteger num2(m);

    MyBigInteger result;
    switch (op) {
        case '+':
            result = num1.add(num2);
            break;
        case '-':
            result = num1.subtract(num2);
            break;
        case '*':
            result = num1.multiply(num2);
            break;
        case '/':
                result = num1.divide(num2);
            break;
        default:
            return 1;
    }

    cout << result.toString() << endl;
    return 0;
}    