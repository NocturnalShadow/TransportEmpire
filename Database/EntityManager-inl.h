#include "Database/EntityManager.h"
#include "Database/Transaction.h"

#include "Utility.h"

#include <odb/transaction.hxx>
#include <odb/database.hxx>
#include <odb/mssql/database.hxx>
#include <odb/query.hxx>
#include <odb/core.hxx>
#include <odb/session.hxx>

#include <type_traits>
#include "function_traits.h"

namespace db {

template<class T>
Pointer<T> EntityManager::load(unsigned int id)
{
    return transactive([&] () {
        return db->load<T>(id);
    });
}

template<class T>
void EntityManager::reload(Pointer<T> entity)
{
    transactive([&] () {
        db->reload(entity);
    });
}

template<class T>
Pointer<T> EntityManager::queryOne(const Query<T>& _query)
{
    return transactive([&] () {
        return db->query_one<T>(_query);
    });
}

template<class T>
QVector<Pointer<T>> EntityManager::query()
{
    return transactive([&] ()
    {
        odb::result<T>      queryResult = db->query<T>(false);
        QVector<Pointer<T>> loadResult;

        for(auto iter = queryResult.begin(); iter != queryResult.end(); ++iter) {
            loadResult.append(iter.load());
        }

        return std::move(loadResult);
    });
}

template<class T>
QVector<Pointer<T>> EntityManager::query(const Query<T>& _query)
{
    return transactive([&] ()
    {
        odb::result<T>      queryResult = db->query<T>(_query, false) ;
        QVector<Pointer<T>> loadResult;

        for(auto iter = queryResult.begin(); iter != queryResult.end(); ++iter) {
            loadResult.append(iter.load());
        }

        return std::move(loadResult);
    });
}

template<class T>
LazyPointer<T> EntityManager::loadLater(unsigned int id)
{
    return LazyPointer<T>{ *db, id };
}

template<class T>
LazyPointer<T> EntityManager::queryOneLater(const Query<T>& _query)
{
    return transactive([&] ()
    {
        odb::result<T> queryResult = db->query<T>(_query, false);
        return LazyPointer<T>{ *db,
                    queryResult.begin() != queryResult.end() ?
                        queryResult.begin().id() : nullptr
        };
    });
}


template<class T>
QVector<LazyPointer<T>> EntityManager::queryLater()
{
        return transactive([&] ()
        {
            odb::result<T>          queryResult = db->query<T>(false);
            QVector<LazyPointer<T>> loadResult;

            for(auto iter = queryResult.begin(); iter != queryResult.end(); ++iter) {
                loadResult.append(LazyPointer<T>{ *db, iter.id()});
            }

            return std::move(loadResult);
        });
}

template<class T>
QVector<LazyPointer<T>> EntityManager::queryLater(const Query<T>& _query)
{
    return transactive([&] ()
    {
        odb::result<T>          queryResult = db->query<T>(_query, false);
        QVector<LazyPointer<T>> loadResult;

        for(auto iter = queryResult.begin(); iter != queryResult.end(); ++iter) {
            loadResult.append(LazyPointer<T>{ *db, iter.id()});
        }

        return std::move(loadResult);
    });
}

template<class T>
void EntityManager::erase()
{
    transactive([&] () {
        db->erase_query<T>();
    });
}

template<class T>
void EntityManager::erase(const Query<T>& _query)
{
    transactive([&] () {
        db->erase_query<T>(_query);
    });
}

template<typename T>
void EntityManager::clearTable()
{
        auto table =
                QString{ typeid(T).name() }
                .remove("class")
                .remove(" ");
        erase<Entity>(Query<Entity>{ "[typeid] = " + Query<Entity>::_ref(table) });
}

template<class Action>
void EntityManager::_transactive(Action action, std::true_type)
{
    if(Transaction::active()) {
        action();
    } else {
        auto t = transaction();
        action();
        t.commit();
    }
}

template<class Action>
auto EntityManager::_transactive(Action action, std::false_type)
{
    if(Transaction::active()) {
        return action();
    } else {
        auto t = transaction();
        auto result = action();
        t.commit();
        return result;
    }
}

template<typename Action>
auto EntityManager::transactive(Action action)
{
    return _transactive(action, std::is_void<return_type<Action>>::type());
}

} // namespace db
