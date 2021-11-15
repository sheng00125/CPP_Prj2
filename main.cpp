#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
//初始化

//转换前后的进制
int oldBase = 10;
int newBase = 10;
int SigA = 1;
int SigB = 1;
int diaohuan = 0;
void change(char *result, int *start)
{ //各个数位还原为数字形式
    int i, len = strlen(result);
    start[0] = len;
    for (i = 1; i <= len; i++)
    {
        if (result[i - 1] >= '0' && result[i - 1] <= '9')
        {
            start[i] = result[i - 1] - '0';
        }
        if (result[i - 1] >= 'A' && result[i - 1] <= 'Z')
        {
            start[i] = result[i - 1] - 'A' + 10;
        }
        if (result[i - 1] >= 'a' && result[i - 1] <= 'z')
        {
            start[i] = result[i - 1] - 'a' + 10;
        }
    }
}
void solve(int *res, int *ans, int *start)
{
    memset(res, 0, sizeof(res)); //余数初始化为空
    int y, i, j;
    //模n取余法，(总体规律是先余为低位，后余为高位)
    while (start[0] >= 1)
    { //只要被除数仍然大于等于1，那就继续“模2取余”
        y = 0;
        i = 1;
        ans[0] = start[0];
        //
        while (i <= start[0])
        {
            y = y * oldBase + start[i];
            ans[i++] = y / newBase;
            y %= newBase;
        }
        res[++res[0]] = y; //这一轮运算得到的余数
        i = 1;
        //找到下一轮商的起始处
        while ((i <= ans[0]) && (ans[i] == 0))
            i++;
        //清除这一轮使用的被除数
        memset(start, 0, sizeof(start));
        //本轮得到的商变为下一轮的被除数
        for (j = i; j <= ans[0]; j++)
            start[++start[0]] = ans[j];
        memset(ans, 0, sizeof(ans)); //清除这一轮的商，为下一轮运算做准备
    }
}
string output(int *res)
{ //从高位到低位逆序输出
    string outaa;
    outaa.clear();
    int i;

    // for (i = res[0]; i >= 1; --i)
    // {
    //     cout << res[i];
    // }

    // cout << endl;

    for (i = res[0]; i >= 1; --i)
    {

        if (res[i] <= 9 & res[i] >= 0)
        {
            string s(1, (res[i] + '0'));
            outaa.append(s);
        }
        else
        {
            string s(1, (res[i] + 'a' - 10));
            outaa.append(s);
        }
    }
    return outaa;
}

void initial(string &a, string &b)
{
    while (a.size() < b.size())
        a = '0' + a;
    while (b.size() < a.size())
        b = '0' + b;
}

//找出最大的字符串
void findMax(string &a, string &b)
{
    string tmp;
    if (a < b)
    {
        diaohuan = 1;
        tmp = b;
        b = a;
        a = tmp;
    }
    else
    {
        diaohuan = 0;
    }
}

//删除第一个字符'0'
bool del(string &a)
{
    if (a[0] == '0')
    {
        a.erase(0, 1);
        return true;
    }
    else
        return false;
}
//删除前面所有的 0
void delAllZroe(string &a)
{
    while (del(a))
    {
        del(a);
    };
}
//大数加法
string bigItergeAdd(string a, string b)
{
    initial(a, b);
    a = '0' + a;
    b = '0' + b;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        int num1 = a[i] - '0';
        int num2 = b[i] - '0';
        if (num1 + num2 > 9)
        {
            a[i - 1] = a[i - 1] - '0' + 1 + '0';
            a[i] = (num1 + num2) - 10 + '0';
        }
        else
        {
            a[i] = (num1 + num2) + '0';
        }
    }
    del(a);
    cout << a << endl;
    return a;
}
//大数减法
string bigItergeSub(string a, string b)
{
    initial(a, b);
    findMax(a, b);
    for (int i = a.size() - 1; i >= 0; i--)
    {
        int num1 = a[i] - '0';
        int num2 = b[i] - '0';
        if (num1 < num2)
        {
            a[i - 1] = a[i - 1] - '0' - 1 + '0';
            a[i] = (num1 + 10 - num2) + '0';
        }
        else
        {
            a[i] = (num1 - num2) + '0';
        }
    }
    del(a);
    // cout << a << endl;
    return a;
}

string shuru_jinzhiA(string input)
{
    string decinput;
    newBase = 10;
    char inputchar[1000];

    int start[1000];

    input.copy(inputchar, input.length(), 0);

    if (inputchar[0] == '-')
    {
        SigA = -1;

        memset(inputchar, '\0', sizeof(inputchar));
        input.erase(0, 1);
        input.copy(inputchar, input.length(), 0);
    }
    if (inputchar[0] == '+')
    {
        SigA = 1;
        memset(inputchar, '\0', sizeof(inputchar));
        input.erase(0, 1);
        input.copy(inputchar, input.length(), 0);
    }

    //各个数位还原为数字形式
    change(inputchar, start);
    int res[1000];
    int ans[1000];
    // 输出新的进制数
    solve(res, ans, start);
    // 一个一个打印出来
    decinput = output(res);
    return decinput;
}
string shuru_jinzhiB(string input)
{
    string decinput;
    newBase = 10;
    char inputchar[1000];
    memset(inputchar, '\0', sizeof(inputchar));
    int start[1000];

    input.copy(inputchar, input.length(), 0);

    if (inputchar[0] == '-')
    {
        SigB = -1;

        memset(inputchar, '\0', sizeof(inputchar));
        input.erase(0, 1);
        input.copy(inputchar, input.length(), 0);
    }
    if (inputchar[0] == '+')
    {
        SigA = 1;
        memset(inputchar, '\0', sizeof(inputchar));
        input.erase(0, 1);
        input.copy(inputchar, input.length(), 0);
    }

    //各个数位还原为数字形式
    change(inputchar, start);
    int res[1000];
    int ans[1000];
    // 输出新的进制数
    solve(res, ans, start);
    // 一个一个打印出来
    decinput = output(res);
    return decinput;
}

string shuchu_jinzhi(string result)
{
    oldBase = 10;

    char resultchar[1000];
    memset(resultchar, '\0', sizeof(resultchar));
    int start[1000];

    result.copy(resultchar, result.length(), 0);
    //各个数位还原为数字形式
    change(resultchar, start);
    int res[1000];
    int ans[1000];
    // 输出新的进制数
    solve(res, ans, start);
    string out;
    // 一个一个打印出来
    out = output(res);
    return out;
}

int jinzhi_duqu(string jinzhi)
{

    char jinzhi_char[1];
    int jinzhi_i;
    jinzhi.copy(jinzhi_char, 1, 0);

    // bigItergeAdd(a, b);
    if (jinzhi_char[0] >= 'a' & jinzhi_char[0] <= 'z')
    {
        jinzhi_i = jinzhi_char[0] - 'a' + 10;
        /* code */
    }
    if (jinzhi_char[0] >= 'A' & jinzhi_char[0] <= 'Z')
    {
        jinzhi_i = jinzhi_char[0] - 'A' + 10;
        /* code */
    }
    if (jinzhi_char[0] >= '0' & jinzhi_char[0] <= '9')
    {
        jinzhi_i = jinzhi_char[0] - '0' + 0;
        /* code */
    }
    return jinzhi_i;
}
int main(int argc, char *argv[])
{
    string a, b;
    string jinzhi;
    string old_Basee, new_Basee;

    // argv[1] = 'a';
    // argv[2] = 'b';
    int old_Basee_i, new_Basee_i;
    ifstream infile;
    // infile.open("../reading");
    string filepath = argv[1];
    infile.open(filepath);
    getline(infile, a);
    getline(infile, b);
    cout << "输入A（N进制）：" << a << endl;
    cout << "输入B（N进制）：" << b << endl;
    //读取文件里面的 输入文件进制
    // 获取到当前的进制情况
    // getline(infile, old_Basee);
    old_Basee = argv[2];

    old_Basee_i = jinzhi_duqu(old_Basee);
    cout << "其中N=" << old_Basee_i << endl;
    oldBase = old_Basee_i;

    // 将当前进制的字符串，转成十进制的字符串
    string dec_a, dec_b;
    dec_a = shuru_jinzhiA(a);
    dec_b = shuru_jinzhiB(b);
    cout << "输入A（10进制）：" << dec_a << endl;
    cout << "输入B（10进制）：" << dec_b << endl;

    //读取 输出进制
    // getline(infile, new_Basee);
    new_Basee = argv[3];
    new_Basee_i = jinzhi_duqu(new_Basee);
    cout << "输出进制：" << new_Basee_i << endl;
    newBase = new_Basee_i;

    // 将十进制的字符串，放入十进制的长加减法运算 函数
    // bigItergeSub一顿操作，得到十进制的 结果 字符串
    string result;
    findMax(dec_a, dec_b);
    if ((SigA * SigB) < 0)
    {
        if ((SigA < 0) & (diaohuan == 0))
        {

            result = bigItergeSub(dec_a, dec_b);
            cout << "输出（10进制）：" << '-' << result << endl;
            string out = shuchu_jinzhi(result);
            cout << "输出（N进制）：" << '-' << out << endl;
        }
        else if ((SigB < 0) & (diaohuan == 1))
        {

            result = bigItergeSub(dec_a, dec_b);
            cout << "输出（10进制）：" << '-' << result << endl;
            string out = shuchu_jinzhi(result);
            cout << "输出（N进制）：" << '-' << out << endl;
        }
        else
        {
            result = bigItergeSub(dec_a, dec_b);
            cout << "输出（10进制）：" << '+' << result << endl;
            string out = shuchu_jinzhi(result);
            cout << "输出（N进制）：" << '+' << out << endl;
        }
    }

    if (SigA > 0 & SigB > 0)
    {
        result = bigItergeAdd(dec_a, dec_b);
        cout << "输出（10进制）：" << '+' << result << endl;
        string out = shuchu_jinzhi(result);
        cout << "输出（N进制）：" << '+' << out << endl;
    }

    if (SigA < 0 & SigB < 0)
    {
        result = bigItergeAdd(dec_a, dec_b);

        cout << "输出（10进制）：" << '-' << result << endl;
        string out = shuchu_jinzhi(result);
        cout << "输出（N进制）：" << '-' << out << endl;
    }

    // 将十进制的字符串，转成目标进制的字符串，打在console上

    return 0;
}