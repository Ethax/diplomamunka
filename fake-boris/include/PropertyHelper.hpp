#ifndef PROPERTYHELPER_H
#define PROPERTYHELPER_H

#include <QObject>

#define AUTOMATIC_PROPERTY(Type, Name)                                                             \
    Q_PROPERTY(Type Name READ Name WRITE Name NOTIFY Name##Changed)                                \
                                                                                                   \
public:                                                                                            \
    void Name(const Type& value) {                                                                 \
        if (value != m_##Name) {                                                                   \
            m_##Name = value;                                                                      \
            emit Name##Changed(value);                                                             \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    Type Name() const {                                                                            \
        return m_##Name;                                                                           \
    }                                                                                              \
                                                                                                   \
    Q_SIGNAL void Name##Changed(Type value);                                                       \
                                                                                                   \
private:                                                                                           \
    Type m_##Name

#define READONLY_PROPERTY(Type, Name)                                                              \
    Q_PROPERTY(Type Name READ Name NOTIFY Name##Changed)                                           \
                                                                                                   \
public:                                                                                            \
    Type Name() const {                                                                            \
        return m_##Name;                                                                           \
    }                                                                                              \
                                                                                                   \
    Q_SIGNAL void Name##Changed(Type value);                                                       \
                                                                                                   \
private:                                                                                           \
    void Name(const Type& value) {                                                                 \
        if (value != m_##Name) {                                                                   \
            m_##Name = value;                                                                      \
            emit Name##Changed(value);                                                             \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    Type m_##Name

#endif // PROPERTYHELPER_H
