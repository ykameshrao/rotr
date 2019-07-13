//
// Created by Kamesh Rao Yeduvakula on 31/3/19.
// Copyright (c) 2019, Kaleidosoft Labs. All rights reserved.
//
#include <algorithm>
#include "RocksDBClient.h"
#include "Container.h"

rotr::common::RocksDBClient::RocksDBClient() {

}

rotr::common::RocksDBClient::RocksDBClient(const string &dbP) :
        dbPath {move(dbP)} {
    open(dbPath);
}

rotr::common::RocksDBClient::RocksDBClient(const string &dbP, const vector<string> &columnFamilies) : dbPath {move(dbP)} {
    openWithCF(dbPath, columnFamilies);
}

rotr::common::RocksDBClient::RocksDBClient(const string &dbP, const vector<string> &columnFamilies, bool fifoCompaction, unordered_map<string, uint64_t> ttls) : dbPath {move(dbP)} {
    openWithCF(dbPath, columnFamilies, fifoCompaction, ttls);
}

rotr::common::RocksDBClient::~RocksDBClient() {
    for ( const auto& cf : columnFamilyHandles ) {
        cout << cf.first << ":" << cf.second.get();
    }
    db->Close();
    db.release();
}

void rotr::common::RocksDBClient::open(const string &dbP, bool fifoCompaction, uint64_t ttl) {
    // best way to make rocks db perform well
    options.IncreaseParallelism();

    if (fifoCompaction) {
        options.compaction_options_fifo.allow_compaction = true;
        options.ttl = ttl;
    } else {
        options.OptimizeLevelStyleCompaction();
    }

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


void rotr::common::RocksDBClient::openWithCF(const string &dbP, const vector<string> &columnFamilies, bool fifoCompaction, unordered_map<string, uint64_t> ttls) {
    auto logger = Container::I().logger;

    // best way to make rocks db perform well
    options.IncreaseParallelism();

    if (fifoCompaction) {
        options.compaction_options_fifo.allow_compaction = true;
    } else {
        options.OptimizeLevelStyleCompaction();
    }

    // create the DB if it's not already present
    options.create_if_missing = true;

    vector<rocksdb::ColumnFamilyDescriptor> cfDescriptors;
    vector<rocksdb::ColumnFamilyHandle*> cfHandles;

    rocksdb::Options localOpts;
    localOpts.create_if_missing = true;
    localOpts.error_if_exists = true;
    rocksdb::DB* tdb;
    rocksdb::Status s = rocksdb::DB::Open(localOpts, dbPath, &tdb);
    logger->info("[RockDBClient Constructor]: {}", s.ToString());

    vector<string> existingCFs;
    tdb->ListColumnFamilies(localOpts, dbPath, &existingCFs);

    for (const string& cfName : columnFamilies) {
        auto opts = rocksdb::ColumnFamilyOptions();
        opts.ttl = ttls[cfName];
        auto cfDesc = rocksdb::ColumnFamilyDescriptor(cfName, opts);
        cfDescriptors.push_back(cfDesc);
        columnFamilyDescriptor[cfDesc.name] = cfDesc;

        if (existingCFs.end() != find_if(existingCFs.begin(), existingCFs.end(),[&](string s) {return s == cfName;})) {
            continue;
        } else {
            rocksdb::ColumnFamilyHandle *t;
            rocksdb::Status status = tdb->CreateColumnFamily(opts, cfDesc.name, &t);
            logger->info("[RockDBClient Constructor]: {}", status.ToString());
            assert(status.ok());
            delete t;
        }
    }

    if (existingCFs.end() != find_if(existingCFs.begin(), existingCFs.end(),[&](string s) {return s == "default";})) {
        cfDescriptors.push_back(rocksdb::ColumnFamilyDescriptor("default", rocksdb::ColumnFamilyOptions()));
    }

    delete tdb;

    // open DB
    if (db != nullptr) {
        db->Close();
        db.release();
    }

    rocksdb::DB* tmp;
    rocksdb::Status status = rocksdb::DB::Open(options, dbPath, cfDescriptors, &cfHandles, &tmp);
    assert(status.ok());
    logger->info("[RockDBClient Constructor]: {}", status.ToString());
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
