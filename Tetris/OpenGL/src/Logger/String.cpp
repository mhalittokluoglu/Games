#include "String.hpp"
#include <cstring>
String::String() :
m_Size { 0 } 
{
    memset(m_String, 0, 4096);
}

String::String(const char *string, uint32_t size)
{
    memset(m_String, 0, 4096);
    for (uint32_t i = 0; i < size; i++)
    {
        m_String[i] = string[i];
    }
    m_Size = size;
}
String::String(const char *string)
{
    memset(m_String, 0, 4096);
    uint32_t i = 0;
    while (string[i] != 0)
    {
        this->m_String[i] = string[i];
        i++;
    }
    m_Size = i;
}

void String::Copy(const String & other)
{
    uint32_t i = 0;
    for (i = 0; i < other.m_Size; i++)
    {
        this->m_String[i] = other[i];
    }
    m_Size = i;
}

String::String(const String& other)
{
    memset(m_String, 0, 4096);
    uint32_t i = 0;
    for (i = 0; i < other.m_Size; i++)
    {
        this->m_String[i] = other[i];
    }
    m_Size = i;
}

String &String::operator=(const String &other)
{
    memset(m_String, 0, 4096);
    uint32_t i = 0;
    for (i = 0; i < other.m_Size; i++)
    {
        this->m_String[i] = other[i];
    }
    m_Size = i;
    return *this;
}

char &String::operator[](uint32_t index)
{
    return m_String[index];
}

const char &String::operator[](uint32_t index) const
{
    return m_String[index];
}
String &String::operator=(const char *string)
{
    uint32_t i = 0;
    while (string[i] != 0)
    {
        this->m_String[i] = string[i];
        i++;
    }
    m_Size = i;
    return *this;
}

std::ostream &operator<<( std::ostream &output, const String &str )
{ 
    output << str.m_String;
    return output;            
}
    
String::operator const char* () const
{
    return this->m_String;
}

String::operator char* ()
{
    return this->m_String;
}

String String::operator+(String other)
{
    uint32_t i;
    for (i = m_Size; i < m_Size + other.Size(); i++)
    {
        this->m_String[i] = other.m_String[i];
    }
    m_Size = i;
    return *this;
}

void String::UpdateSize()
{
    uint32_t i = 0;
    while (m_String[i] != 0)
    {
        i++;
    }
    m_Size = i;
}