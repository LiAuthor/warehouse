//#include"Book.h"
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;
#define NUM1 128
#define NUM2 50
class CBook
{
    public:
    CBook(){}
    ~CBook(){}
    CBook(char* cName,char* clsbn,char* cPrice,char* cAuthor);
    public:
    char *GetName();
    void SetName(char *cName);
    char *Getlsbn();
    void Setlsbn(char *clsbn);
    char* GetPrice();
    void SetPrice(char *cPrice);
    char *GetAuthor();
    void SetAuthor(char *cAuthor);

    void WriteData();
    void DeleteDate(int iCount);
    void GetBookFromFile(int iCount);
    protected:
    char m_cName[NUM1];
    char m_clsbn[NUM1];
    char m_cPrice[NUM2];
    char m_cAuthor[NUM2];
};

CBook::CBook(char* cName,char* clsbn,char* cPrice,char* cAuthor)
{
    strncpy(m_cName,cName,NUM1);
    strncpy(m_clsbn,clsbn,NUM1);
    strncpy(m_cPrice,cPrice,NUM2);
    strncpy(m_cAuthor,cAuthor,NUM2);
}
char* CBook::GetName()
{
    return m_cName;
}
void CBook::SetName(char* cName)
{
    strncpy(m_cName,cName,NUM1);
}
char* CBook::Getlsbn()
{
    return m_clsbn;
}
void CBook::Setlsbn(char* clsbn)
{
    strncpy(m_clsbn,clsbn,NUM1);
}
char* CBook::GetAuthor()
{
    return m_cAuthor;
}
void CBook::SetAuthor(char* cAuthor)
{
    strncpy(m_cAuthor,cAuthor,NUM2);
}
char* CBook::GetPrice()
{
    return m_cPrice;
}
void CBook::SetPrice(char* cPrice)
{
    strncpy(m_cPrice,cPrice,NUM2);
}

void CBook::WriteData()
{
    ofstream ofile;
    ofile.open("book.dat",ios::binary|ios::app);
    try
    {
        ofile.write(m_cName,NUM1);
        ofile.write(m_clsbn,NUM1);
        ofile.write(m_cPrice,NUM2);
        ofile.write(m_cAuthor,NUM2);
    }
    catch(...)
    {
        throw "file error occurred";
        ofile.close();
    }
}
void CBook::GetBookFromFile(int iCount)
{
    char cName[NUM1];
    char clsbn[NUM1];
    char cPrice[NUM2];
    char cAuthor[NUM2];
    ifstream ifile;
    ifile.open("book.dat",ios::binary);
    try
    {
        ifile.seekg(iCount*(NUM1+NUM1+NUM2+NUM2),ios::beg);
        ifile.read(cName,NUM1);
        if(ifile.tellg()>0)
            strncpy(m_cName,cName,NUM1);
        ifile.read(clsbn,NUM1);
        if(ifile.tellg()>0)
            strncpy(m_clsbn,clsbn,NUM1);
        ifile.read(cPrice,NUM2);
        if(ifile.tellg()>0)
            strncpy(m_cPrice,cPrice,NUM2);
        ifile.read(cAuthor,NUM2);
        if(ifile.tellg()>0)
            strncpy(m_cAuthor,cAuthor,NUM2);
    }
    catch (...)
    {
        throw "file error occurred";
        ifile.close();
    }
    ifile.close();
}
void CBook::DeleteDate(int iCount)
{
    long respos;
    int iDataCount=0;
    fstream file;
    fstream tmpfile;
    ofstream ofile;
    char cTempBuf[NUM1+NUM1+NUM2+NUM2];
    file.open("book.dat",ios::binary|ios::in|ios::out);
    tmpfile.open("temp.dat",ios::binary|ios::in|ios::out|ios::trunc);
    file.seekg(0,ios::end);
    respos=file.tellg();
    iDataCount=respos/(NUM1+NUM1+NUM2+NUM2);
    if(iCount<0&&iCount>iDataCount)
    {
        throw "Input number error";
    }
    else
    {
        file.seekg((NUM1+NUM1+NUM2+NUM2),ios::beg);
        for(int j=0;j<(iDataCount-iCount);j++)
        {
            memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);
            file.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);
            tmpfile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);
        }
        file.close();
        tmpfile.seekg(0,ios::beg);
        ofile.open("book.dat");
        ofile.seekp((iCount-1)*(NUM1+NUM1+NUM2+NUM2),ios::beg);
        for(int i=0;i<(iDataCount-iCount);i++)
        {
            memset(cTempBuf,0,NUM1+NUM1+NUM2+NUM2);
            tmpfile.read(cTempBuf,NUM1+NUM1+NUM2+NUM2);
            ofile.write(cTempBuf,NUM1+NUM1+NUM2+NUM2);
        }
    }
    tmpfile.close();
    ofile.close();
    remove("temp.dat");
}