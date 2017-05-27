#include "EntityManager.h"

namespace db {

template<class T>
Pointer<T> EntityManager::load(unsigned int id)
{
    return transactive([&] () {
        return db->load<T>(id);
    });
}

template<class T>
QVector<Pointer<T>> EntityManager::load(const query<T>& _query)
{
    return transactive([] () {
        result<T> queryResult{ db->query<T>(_query) };
        return QVector<Pointer<T>>{ queryResult.begin(), queryResult.end() };
    });
}

template<class T>
LazyPointer<T> EntityManager::loadLater(unsigned int id)
{
    return LazyPointer<T>{ db, id };
}

template<class T>
QVector<LazyPointer<T>> EntityManager::loadLater(const query<T> &_query)
{
    return transactive([] () {
        result<T> queryResult{ db->query<T>(_query) };

        QVector<LazyPointer<T>> loadResult;
        loadResult.reserve(queryResult.size());

        for(auto iter = queryResult.begin(); iter != queryResult.end(); ++iter) {
            loadResult.append(LazyPointer<T>{ db, iter.id()});
        }

        return std::move(loadResult);
    });
}

template<class T>
void EntityManager::erase(const query<T>& _query)
{
    transactive([&] () {
        db->erase_query<T>(_query);
    });
}

template<typename Action>
auto EntityManager::transactive(Action action)
{
    if(transaction::has_current()) {
        return action();
    } else {
        transaction(db->begin());
        return action();
        transaction::current().commit();
    }
}

} // namespace db
