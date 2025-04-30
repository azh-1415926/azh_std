#pragma once

#include <exception>
#include <string>

#define ERROR_LINE std::string()+"in "+__FILE__+" at line:"+std::to_string(__LINE__)

namespace azh
{
    enum class ERROR_TYPE
    {
        INVALID_ARGUMENT=1,
        OUT_OF_RANGE
    };

    class exception : public std::exception
    {
        public:
            exception(ERROR_TYPE error_type, const std::string& str) : m_Type(error_type),m_Str(str)
            {
                m_Str="error code "+std::to_string((int)m_Type)+" " + m_Str;
            }
    
            const char* what() const noexcept override
            {
                return m_Str.c_str();
            }
        private:
            ERROR_TYPE m_Type;
            std::string m_Str;
    };
}