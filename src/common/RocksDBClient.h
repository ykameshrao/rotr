//
// Created by Kamesh Rao Yeduvakula on 31/3/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#ifndef ROTR_ROCKSDBCLIENT_H
#define ROTR_ROCKSDBCLIENT_H


#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>

using namespace std;

namespace rotr::common {
    class RocksDBClient {
    public:
        RocksDBClient();
        RocksDBClient(const string& dbP);
        RocksDBClient(const string& dbP, const vector<string>& columnFamilies);
        ~RocksDBClient();

        void open(const string& dbP);
        void openWithCF(const string& dbP, const vector<string>& columnFamilies);
        void put(const string& k, const string& v);
        void get(const string& k, string& v);
        void del(const string& k);
        void putInCF(const string& cf, const string& k, const string& v);
        void getInCF(const string& cf, const string& k, string& v);
        void delInCF(const string& cf, const string& k);
    private:
        string dbPath;
        unique_ptr<rocksdb::DB> db;
        rocksdb::Options options;
        unordered_map<string, unique_ptr<rocksdb::ColumnFamilyHandle>> columnFamilyHandles;
        unordered_map<string, rocksdb::ColumnFamilyDescriptor> columnFamilyDescriptor;
        rocksdb::DbPath path;
    };
}

namespace rotr::util {
    template <typename T>
    string Pack(const T* data) {
        string d(sizeof(T), L'\0');
        memcpy(&d[0], data, d.size());
        return d;
    }

    template <typename T>
    unique_ptr<T> Unpack(const string& data) {
        if (data.size() != sizeof(T))
            return nullptr;

        auto d = make_unique<T>();
        memcpy(d.get(), data.data(), data.size());
        return d;
    }

}


#endif //ROTR_ROCKSDBCLIENT_H
