//
// Created by Kamesh Rao Yeduvakula on 31/3/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#include "RocksDBClient.h"

rotr::common::RocksDBClient::RocksDBClient() {

}

rotr::common::RocksDBClient::RocksDBClient(const string &dbP) :
        dbPath {move(dbP)} {
    open(dbPath);
}

rotr::common::RocksDBClient::RocksDBClient(const string &dbP, const vector<string> &columnFamilies) : dbPath {move(dbP)} {
    openWithCF(dbPath, columnFamilies);
}

rotr::common::RocksDBClient::~RocksDBClient() {
    for ( const auto& cf : columnFamilyHandles ) {
        cout << cf.first << ":" << cf.second.get();
    }
    db->Close();
    db.release();
}

void rotr::common::RocksDBClient::open(const string &dbP) {
    // best way to make rocks db perform well
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();

    // create the DB if it's not already present
    options.create_if_missing = true;

    // open DB
    if (db != nullptr) {
        db->Close();
        db.release();
    }

    rocksdb::DB* tmp;
    rocksdb::Status s = rocksdb::DB::Open(options, dbPath, &tmp);
    assert(s.ok());
    db.reset(tmp);
}


void rotr::common::RocksDBClient::openWithCF(const string &dbP, const vector<string> &columnFamilies) {
    // best way to make rocks db perform well
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();

    // create the DB if it's not already present
    options.create_if_missing = true;

    vector<rocksdb::ColumnFamilyDescriptor> cfDescriptors;
    vector<rocksdb::ColumnFamilyHandle*> cfHandles;

    for (const string& cfName : columnFamilies) {
        auto cfDesc = rocksdb::ColumnFamilyDescriptor(cfName, rocksdb::ColumnFamilyOptions());
        cfDescriptors.push_back(cfDesc);
        columnFamilyDescriptor[cfDesc.name] = cfDesc;
    }

    // open DB
    if (db != nullptr) {
        db->Close();
        db.release();
    }

    rocksdb::DB* tmp;
    rocksdb::Status s = rocksdb::DB::Open(options, dbPath, cfDescriptors, &cfHandles, &tmp);
    assert(s.ok());
    db.reset(tmp);

    // setting up the handles map
    for (const auto& cfHandle : cfHandles) {
        columnFamilyHandles[cfHandle->GetName()].reset(cfHandle);
    }
}

void rotr::common::RocksDBClient::put(const string &k, const string &v) {
    rocksdb::Status s = db->Put(rocksdb::WriteOptions(), k, v);
    assert(s.ok());
}

void rotr::common::RocksDBClient::get(const string &k, string &v) {
    rocksdb::Status s = db->Get(rocksdb::ReadOptions(), k, &v);
    assert(s.ok());
}

void rotr::common::RocksDBClient::del(const string &k) {
    rocksdb::Status s = db->Delete(rocksdb::WriteOptions(), k);
    assert(s.ok());
}

void rotr::common::RocksDBClient::putInCF(const string &cf, const string &k, const string &v) {
    rocksdb::Status s = db->Put(rocksdb::WriteOptions(), columnFamilyHandles[cf].get(), k, v);
    assert(s.ok());
}

void rotr::common::RocksDBClient::getInCF(const string &cf, const string &k, string &v) {
    rocksdb::Status s = db->Get(rocksdb::ReadOptions(), columnFamilyHandles[cf].get(), k, &v);
    assert(s.ok());
}

void rotr::common::RocksDBClient::delInCF(const string &cf, const string &k) {
    rocksdb::Status s = db->Delete(rocksdb::WriteOptions(), columnFamilyHandles[cf].get(), k);
    assert(s.ok());
}
