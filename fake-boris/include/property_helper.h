#ifndef PROPERTYHELPER_H
#define PROPERTYHELPER_H

#include <QObject>

#define PROPERTY_GETTER(Type, Name)                                                                \
    Type Get##Name() const { return m_##Name; }

#define PROPERTY_SETTER(Type, Name)                                                                \
    void Set##Name(const Type &value) {                                                            \
        if (value != m_##Name) {                                                                   \
            m_##Name = value;                                                                      \
            emit Name##Changed();                                                                  \
        }                                                                                          \
    }                                                                                              \
    Q_SIGNAL void Name##Changed();

#define AUTOMATIC_PROPERTY(Type, Name)                                                             \
    Q_PROPERTY(Type Name READ Get##Name WRITE Set##Name NOTIFY Name##Changed)                      \
                                                                                                   \
public:                                                                                            \
    PROPERTY_GETTER(Type, Name)                                                                    \
    PROPERTY_SETTER(Type, Name)                                                                    \
                                                                                                   \
private:                                                                                           \
    Type m_##Name

#define READONLY_PROPERTY(Type, Name)                                                              \
    Q_PROPERTY(Type Name READ Get##Name NOTIFY Name##Changed)                                      \
                                                                                                   \
public:                                                                                            \
    PROPERTY_GETTER(Type, Name)                                                                    \
                                                                                                   \
private:                                                                                           \
    PROPERTY_SETTER(Type, Name)                                                                    \
    Type m_##Name

#endif // PROPERTYHELPER_H
