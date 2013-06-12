#ifndef PROT_US_STRING_DYNAMIC_H_INCLUDED
#define PROT_US_STRING_DYNAMIC_H_INCLUDED

struct  ES_STRING_DYNAMIC
{
    wchar_t*    string;
    size_t      string_size;
    size_t      cursor;
};

#endif // US_STRING_DYNAMIC_H_INCLUDED
