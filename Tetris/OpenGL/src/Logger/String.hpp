#ifndef _STRING_HPP_
#define _STRING_HPP_
#include <inttypes.h>
#include <iostream>
class String
{
public:
    String();
    String(const char *string, uint32_t size);
    String(const char *string);
    void Copy(const String & other);
    void UpdateSize();

    String(const String& other); // copy constructor
    String &operator=(const String &other);
    String &operator=(const char *string);
    String operator+(String other);
    String operator+(const char other);
    operator const char* () const;
    operator char* ();
    char &operator[](uint32_t);
    const char &operator[](uint32_t) const;
    friend std::ostream &operator<<(std::ostream &output, const String &str);
    inline uint32_t Size()const { return m_Size; } 
private:
    char m_String[4096];
    uint32_t m_Size;
};
#endif