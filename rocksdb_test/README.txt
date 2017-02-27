
reader + writer process working on same rocksdb instance

get 2 types of errors
1) log file not present during db::openForReadOnly
2) sst file gets deleted but reader process continues since it has a refcnt on the deleted file, courtesy of unix

See post on rocksdb group

http://www.facebook.com/groups/rocksdb.dev/permalink/1062821910482989
