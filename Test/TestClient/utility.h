#pragma once

#include <QTextStream>

inline QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}
