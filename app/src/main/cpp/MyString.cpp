#include "MyString.h"  
#include <cassert>  

// constructor  
MyString::MyString() : p_str(NULL), strLength(0) {}

MyString::MyString(const MyString &str)//
{
    if (NULL == str.p_str) {
        return;
    }
    strLength = str.strLength;
    p_str = new char[strLength + 1];
    std::strcpy(p_str, str.p_str);
}

MyString::MyString(const char *str) {
    if (NULL == str) {
        return;
    }
    strLength = strlen(str);
    p_str = new char[strLength + 1];
    std::strcpy(p_str, str);
}

MyString::MyString(const size_t len, const char ch) {
    if (NULL == ch) {
        return;
    }
    strLength = len;
    p_str = new char[strLength + 1];
    for (size_t i = 0; i < strLength; i++) {
        p_str[i] = ch;
    }
    p_str[strLength] = '\0';// 因为strset以'\0'结束的
    cout << p_str << " &&" << endl;
    //strset(p_str,ch);
    //cout << p_str[0] << ",,,"<<strlen(p_str) << "," << strLength << endl;
}

// destructor
MyString::~MyString() {
    delete[] p_str;
}

// attributes
size_t MyString::length()// 字符串长度
{
    return strLength;
}

bool MyString::isEmpty()// 返回字符串是否为空
{
    return strLength == 0 ? true : false;
}

const char *MyString::c_str() {
    return p_str;
}

// 为什么不是引用呢？？？ friend 使用在类里面进行声明的，外面就不需要了，而且友元函数不属于类的成员函数，所以不用MyString：：
// ostream
ostream &operator<<(ostream &out, const MyString &str) {
    if (str.p_str != NULL) {
        out << str.p_str;
    }
    return out;
}

// istream,一个是const另一个不是，根据变还是不变
istream &operator>>(istream &in, MyString &str) {
    char tmp[100];// 临时字符串
    if (in >> tmp) {
        delete[] str.p_str;
        str.strLength = strlen(tmp);
        str.p_str = new char[str.strLength + 1];
        strcpy(str.p_str, tmp);
    }
    return in;
}

// + 加
MyString operator+(const MyString &lhs, const MyString &rhs) {
    MyString ret;
    ret.strLength = lhs.strLength + rhs.strLength;
    ret.p_str = new char[ret.strLength + 1];
    strcpy(ret.p_str, lhs.p_str);
    strcat(ret.p_str, rhs.p_str);
    return ret;
}

// compare operations
bool operator==(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.p_str, rhs.p_str) == 0 ? true : false;
}

bool operator!=(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.p_str, rhs.p_str) != 0 ? true : false;
}

bool operator<(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.p_str, rhs.p_str) < 0 ? true : false;
}

bool operator<=(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.p_str, rhs.p_str) <= 0 ? true : false;
}

bool operator>(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.p_str, rhs.p_str) > 0 ? true : false;
}

bool operator>=(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.p_str, rhs.p_str) >= 0 ? true : false;
}

// 成员函数实现运算符重载
// index operation
char &MyString::operator[](const size_t index) {
    if (index < 0 || index >= strLength) {
        throw Outofbond();
    }
    return p_str[index];
}

const char &MyString::operator[](const size_t index) const {
    if (index < 0 || index >= strLength) {
        throw Outofbond();
    }
    return p_str[index];
}

// = 赋值构造函数（判断是否是自身） 为什么要这样删除呢？
MyString &MyString::operator=(const MyString &other) {
    if (this != &other) {
        if (strLength < other.strLength) {
            delete[] p_str;
            p_str = new char[other.strLength + 1];
        }
        strLength = other.strLength;
        strcpy(p_str, other.p_str);
    }// 这样可能会产生多余的未释放的空间
    return *this;
}

// += 相当于返回的是备份的，内部对象的销毁，不影响的 和 下面的完全不一样的
//    MyString MyString::operator+=(const MyString& other)  
//    {  
//        if(NULL == other.p_str)  
//        {  
//            return *this;  
//        }  
//        MyString ret;  
//        ret.strLength = strLength + other.strLength;  
//        ret.p_str = new char[ret.strLength+1];  
//        strcpy(ret.p_str,p_str);  
//        strcat(ret.p_str,other.p_str);  
//        return ret;  
//    }  
// 返回的是当前对象的引用，当前对象就在调用函数里，所以不会销毁的
// 判断一下是否是自身相加
MyString &MyString::operator+=(const MyString &other) {
    if (NULL == other.p_str) {
        return *this;
    }
    if (this == &other) {
        MyString copy(*this);
        return *this += copy;
    }// 必须判断是否相等的，而且要+=的，这样相当于调用了自身，但是这次直接下面去了，不进入if的
    strLength += other.strLength;
    //strLength *= 2;
    char *p_old = p_str;
    p_str = new char[strLength + 1];
    strcpy(p_str, p_old);
    strcat(p_str, other.p_str);
    delete[] p_old;// 删除旧的空间
    return *this;
}

// 成员操作函数
// substr  返回应用是不行的，错误的；取从pos开始的n个字符组成的子串
//MyString& MyString::substr(size_t pos,const size_t n)
MyString MyString::substr(size_t pos, const size_t n) {
    if ((pos + n) >= strLength) {
        throw Outofbond();
    }
    MyString ret;
    ret.strLength = n;
    //ret.p_str = new char[n+1];
    ret.p_str = new char[ret.strLength + 1]; //也可以
    for (size_t i = 0; i < n; i++) {
        ret.p_str[i] = p_str[pos + i];
    }
    ret.p_str[n] = '\0';
//        for(size_t i=0;i<ret.strLength;i++)  
//        {  
//            ret[i] = (*this)[pos+i];  
//            cout << ret[i] << ",,";  
//        }// 也行的，利用刚刚重载的【】,这样更好，不用再次判断越界了,不知道为什么，报错误的  
//        ret[ret.strLength] = '\0';  
    return ret;
}

// append 同 += 追加到末尾
MyString &MyString::append(const MyString &other) {
    *this += other;// 利用刚刚那重载的+=
    return *this;
}

//insert 从pos开始的插入other
MyString &MyString::insert(size_t pos, const MyString &other) {
    if (pos < 0 || pos >= strLength) {
        throw Outofbond();
    }
    char *p_old = p_str;
    strLength += other.strLength;
    p_str = new char[strLength + 1];
    for (size_t i = 0; i < pos; i++) {
        *(p_str + i) = *(p_old + i);
    }
    for (size_t i = pos; i < other.strLength + pos; i++) {
        *(p_str + i) = other.p_str[i - pos];
    }
    for (size_t i = other.strLength + pos; i < strLength; i++) {
        *(p_str + i) = p_old[i - other.strLength];
    }
    *(p_str + strLength) = '\0';
    return *this;
}

//assign 替换  用other的POS开始的n对应替换this的pos开始的
MyString &MyString::assign(MyString &other, size_t pos, size_t n) {
//        if(pos<0 || pos>=strLength)  
//        {  
//            throw Outofbond();  
//        }  
    assert(pos > 0 && pos < strLength);// assert 的好处
    assert(pos + n < other.strLength);
    if (strLength < pos + n) {
        char *p_old = p_str;
        strLength = pos + n;
        p_str = new char[strLength + 1];
        for (size_t i = 0; i < pos; i++) {
            *(p_str + i) = *(p_old + i);
        }
        delete[] p_old;
    }
    for (size_t i = pos; i < pos + n; i++) {
        *(p_str + i) = other.p_str[i];
    }
    *(p_str + pos + n) = '\0';
    return *this;
}

// erase 删除 这个方法并不是很好的，并没有释放所erase的空间,请看下面的
//    MyString& MyString::erase(size_t pos,size_t n)  
//    {  
//        if((pos+n)>strLength)  
//        {  
//            throw Outofbond();  
//        }  
//        size_t index = pos + n;  
//        while(*(p_str+index)!='\0')  
//        {  
//            *(p_str+index-n) = *(p_str+index);  
//            ++index;  
//        }  
//        *(p_str+index-n) = '\0';  
//        return *this;  
//    }  
// erase 删除 从pos开始的n个字符
MyString &MyString::erase(size_t pos, size_t n) {
    if ((pos + n) > strLength) {
        throw Outofbond();
    }
    char *p_old = p_str;
    strLength -= n;
    p_str = new char[strLength + 1];
    for (size_t i = 0; i < pos; i++) {
        p_str[i] = p_old[i];
    }
    for (size_t i = pos; i < strLength; i++) {
        p_str[i] = p_old[i + n];
    }
    *(p_str + strLength) = '\0';
    return *this;
}

//find_first_of 查找某一个字符 size_t 是非符号数的
// 查找在字符串中第一个与str中的某个字符匹配的字符，返回它的位置。
//搜索从index开始，如果没找到就返回string::npos
int MyString::find_first_of(const char *str, size_t index) {
    if (NULL == str || index >= strLength)
        return npos;
    int tmp_len = strlen(str), j;
    size_t flag, min_index = INI_MAX;
    for (j = 0; j < tmp_len; j++) {
        flag = npos;
        for (size_t i = index; i < strLength; i++) {
            if (str[j] == p_str[i]) {
                flag = i;
                break;
            }
        }
//            indexs[j] = flag;  
        if (flag != npos) {
            min_index = min_index < flag ? min_index : flag;
        }
    }
//        for(j=0;j<tmp_len;j++)  
//        {  
//            if(indexs[j]!=npos)  
//                min = min<indexs[j]?min:indexs[j];  
//        }  
    if (min_index == INI_MAX) {
        return npos;
//            min_index = npos;  
//           cout << "---npos----" << min_index << ",,,,";  
    }
    return min_index;
}

int MyString::find_first_of(const char ch, size_t index) {
    if (NULL == ch || index >= strLength)
        return npos;
    int j;
    size_t flag = npos;
    for (size_t i = index; i < strLength; i++) {
        if (ch == p_str[i]) {
            flag = i;
            break;
        }
    }
    return flag;
}

int MyString::find_first_of(const MyString &str, size_t index) {
    if (NULL == str || index >= strLength)
        return npos;
    int j;
    size_t flag, min_index = INI_MAX;
    for (j = 0; j < str.strLength; j++) {
        flag = npos;
        for (size_t i = index; i < strLength; i++) {
            if (str[j] == p_str[i]) {
                flag = i;
                break;
            }
        }
        if (flag != npos) {
            min_index = min_index < flag ? min_index : flag;
        }
    }
    if (min_index == INI_MAX) {
        return npos;
    }
    return min_index;
}

// 在字符串中查找第一个与str中的字符都不匹配的字符，返回它的位置。
//搜索从index开始。如果没找到就返回string::nops O(N^2)
int MyString::find_first_not_of(const char *str, size_t index) {
    if (NULL == str || index >= strLength)
        return npos;
    size_t i = 0, j = 0;
    size_t tmp_len = strlen(str);
    for (i = index; i < strLength; i++) {
        for (; j < tmp_len; j++) {
            if (p_str[i] == str[j])
                break;
        }
        if (j == tmp_len)
            break;// 根据跳出的内层for的条件判断，找到即结束循环
    }
    if (i == strLength)
        return npos;// 未找到，// 根据跳出的内层for的条件判断，找到即结束循环
    return i;
}

int MyString::find_first_not_of(const MyString &str, size_t index) {
    if (NULL == str || index >= strLength)
        return npos;
    size_t i = 0, j = 0;
    for (i = index; i < strLength; i++) {
        for (; j < str.strLength; j++) {
            if (p_str[i] == str[j])
                break;// 如果相等 本轮i就无效了，进行下一轮
        }
        if (j == str.strLength)
            break;// 根据跳出的内层for的条件判断，找到即结束循环
    }
    if (i == strLength)
        return npos;// 未找到，// 根据跳出的内层for的条件判断，找到即结束循环
    return i;
}

int MyString::find_first_not_of(const char ch, size_t index) {
    if (NULL == ch || index >= strLength)
        return npos;
    size_t i = 0;
    for (i = index; i < strLength; i++) {
        if (p_str[i] != ch)// 跟上面的略微不同，找一个不等就可以了
            break;
    }
    if (i == strLength)
        return npos;// 未找到，// 根据跳出的内层for的条件判断，找到即结束循环
    return i;
}

// swap  都得变得，所以非const
void MyString::swap(MyString &lhs, MyString &rhs) {
    lhs.strLength ^= rhs.strLength;
    rhs.strLength ^= lhs.strLength;
    lhs.strLength ^= rhs.strLength;
    char *p_tmp = rhs.p_str;
    rhs.p_str = lhs.p_str;
    lhs.p_str = p_tmp;
}

// replace_all  这个东西还是不太好弄的啊，不是很理想
MyString &MyString::replace_all(const char oldc, const char newc) {
    if (NULL == oldc) {
        return *(this);
    }
    for (size_t i = 0; i < strLength; i++) {
        if (p_str[i] == oldc) {
            p_str[i] = newc;
        }
    }
    return *(this);
}

MyString &MyString::replace(size_t index, size_t num1, size_t num2, const char ch) {

}

// find 函数
int MyString::find(const char *str, size_t index) {
    assert(str != NULL && index < strLength);
    // kmp 中的getnext函数
    size_t len = strlen(str);
    size_t next[len + 1];
    size_t j, k;
    next[0] = npos;
    j = 0;
    k = npos;
    while (j < len) {
        if (k == npos || str[j] == str[k]) {
            j++;
            k++;
            next[j] = k;
        } else
            k = next[k];
    }
    // kmp 算法
    k = index;
    j = 0;
    while (p_str[k] != '\0') {
        if (j == 0 || p_str[k] == str[j]) {
            k++;
            j++;
        } else {
            j = next[j];// 消除指针回溯
        }
        if (str[j] == '\0')//匹配成功
            return k - j;
    }
    return npos;
}

int MyString::find(const MyString &str, size_t index) {
//        if(this == &str)  
//        {  
//            MyString other(*this);  
//            find(other,index);  
//        }  
    assert(NULL != str && index < strLength);
    // kmp 中的getnext函数

    size_t next[str.strLength + 2];
    size_t j, k;
    next[0] = npos;
    j = 0;
    k = npos;
    while (j < str.strLength) {
        if (k == npos || str.p_str[j] == str.p_str[k]) {
            j++;
            k++;
            next[j] = k;
        } else
            k = next[k];
    }
    int i;
    for (i = 1; i <= j; i++)
        cout << next[i] << ",";
    // kmp 算法
    k = index;
    j = 0;
    while (p_str[k] != '\0') {
        if (j == 0 || p_str[k] == str.p_str[j]) {
            k++;
            j++;
        } else {
            j = next[j];// 消除指针回溯
        }
        if (str.p_str[j] == '\0')//匹配成功,不知道为什么调用自身的str[]重载总是报错的
            return k - j;
    }
    if (str.p_str[j] == '\0')// 同一个字符串
        return k - j;
    return npos;
}

int MyString::find(const char ch, size_t index) {
    assert(NULL != ch && index < strLength);
    for (size_t i = index; i < strLength; i++) {
        if (p_str[i] == ch)
            return i;
    }
    return npos;
}