#pragma once

#include <QtCore/QWeakPointer>
#include <QtCore/QSharedPointer>

#include <odb/qt/lazy-ptr.hxx>

template<class T>
using Pointer = QSharedPointer<T>;

template<class T>
using WeakPointer = QWeakPointer<T>;

template<class T>
using LazyPointer = QLazySharedPointer<T>;

template<class T>
using LazyWeakPointer = QLazyWeakPointer<T>;

template<class T, class ... Args>
Pointer<T> make(Args && ... args)
{
    return QSharedPointer<T>::create(std::forward<Args>(args)...);
}
