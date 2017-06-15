#pragma once

#include <odb/transaction.hxx>

#include <memory>

class odb::transaction_impl;
class Transaction
{
private:
    std::unique_ptr<odb::transaction> transaction;

public:
    Transaction() = default;
    Transaction(Transaction&& t) = default;
    Transaction(const Transaction& t) = delete;

    Transaction& operator=(Transaction&& t) = default;
    Transaction& operator=(const Transaction& t) = delete;

public:
    Transaction(odb::transaction_impl* impl)
        : transaction{ std::make_unique<odb::transaction>(impl) }
    {
    }

public:
    void commit() {
        transaction->commit();
    }
    void rollback() {
        transaction->rollback();
    }
    void reset(odb::transaction_impl* impl) {
        transaction->reset(impl);
    }
    bool finalized() const {
        return transaction->finalized();
    }

public:
    static bool active() {
        return odb::transaction::has_current();
    }
};

