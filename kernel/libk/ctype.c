#include <libk/ctype.h>

int isalnum(int c)
{
    return isalpha(c) || isdigit(c);
}

int isalpha(int c)
{
    //outside of the "C" locale, any other character
    //may be included as long as it isn't in
    //iscntrl, isdigit, ispunct, or isspace

    return isupper(c) || islower(c);
}

int isblank(int c)
{
    return c == ' ' || c == '\t';
}

int iscntrl(int c)
{
    return c < ' ' || c == 0x7F;
}

int isdigit(int c)
{
    return c >= '0' && c <= '9';
}

int isgraph(int c)
{
    return isalnum(c) || ispunct(c);
}

int islower(int c)
{
    return c >= 'a' && c <= 'z';
}

int isprint(int c)
{
    return isgraph(c) || c == ' ';
}

int ispunct(int c)
{
    return !(isalnum(c) || isspace(c) || iscntrl(c));
}

int isspace(int c)
{
    switch (c) {
    case ' ':
    case '\t':
    case '\n':
    case '\r':
    case '\v':
    case '\f':
        return 1;
    }
    return 0;
}

int isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}

int isxdigit(int c)
{
    return isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

int tolower(int c)
{
    if (isupper(c)) {
        c -= 'A';
        c += 'a';
    }
    return c;
}

int toupper(int c)
{
    if (islower(c)) {
        c -= 'a';
        c += 'A';
    }
    return c;
}