#include <iostream>
#include <cstdint>

using i64 = int64_t;
void Assert(bool cond, const char *cond_str)
{
    if (!cond)
    {
        throw std::logic_error(std::string("") + cond_str);
    }
}

#define AS

std::string ReadString(std::istream &is);
i64 ReadInteger(std::istream &is);
std::string ReadLiteral(std::istream &is);
void EatWhitespace(std::istream &is);

i64 ReadInteger(std::istream &is)
{
    i64 val = 0;
    bool negative = false;

    char c = is.peek();
    if ((c == '-') || (c == '+'))
    {
        negative = (c == '-');
        is.get();
        EatWhitespace(is);
        c = is.peek();
    }

    ASSERT(isdigit(c));

    do
    {
        val *= 10;
        val += (c - '0');
        is.get();
        c = is.peek();
    } while (isdigit(c));

    if (negative)
        val = -val;
    return val;
}

void EatWhitespace(std::istream &is)
{
    while (isspace(is.peek()))
    {
        is.get();
    }
}

bool is_letter(char c)
{
    if ((c >= 'a') && (c <= 'z'))
    {
        return true;
    }
    if ((c >= 'A') && (c <= 'Z'))
    {
        return true;
    }
    return false;
}

std::string ReadLiteral(std::istream &is)
{
    std::string smth;

    char c = is.peek();
    if (is_letter(c))
    {
        while (is_letter(c) || (isdigit(c)))
        {
            smth += c;
            c = is.peek();
        }
    }
    else
    {
        ASSERT(c);
    }
}

bool ReadCompChar(char *symbol, std::istream &is)
{
    char cand = is.peek();
    if (cand == '\\')
    {
        return true;
    }
    *symbol = cand;
    return false;
}

std::string ReadString(std::istream &is)
{
    std::string smth;
    char c = is.peek();
    if (c == '"')
    {
        is.get();
        c = is.peek();
        while (c != '"' &&)
    }
}