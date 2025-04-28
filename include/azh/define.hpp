#ifndef DEFINE_H
#define DEFINE_H

#define SINGLETONE(Name,Type) \
class Name \
{ \
    public: \
        static Name& getInstance() \
        { \
            static Name instance; \
            return instance; \
        } \
        Type& get() {  return m_Instance; } \
        void set(Type data) { m_Instance=data; } \
    private: \
        explicit Name() { } \
        Type m_Instance; \
};

#endif