#ifndef GROUPCOMMIT_H
#define GROUPCOMMIT_H

#include <pthread.h>
#include "Common.h"
#include <TimeDiff.h>
#include "RecoveryLog.h"
#include "Bitmap.h"
#include "RawDeviceBlockStore.h"

#define TIMEOUT_VALUE 1000000 // 1 millisecond = 1 million nano second

class GroupCommit
{
	pthread_mutex_t mutex;
	pthread_cond_t condvar;
	RawDeviceBlockStore *writeCacheData;
	RecoveryLog<WriteCacheLogRecord> *writeCacheRecoveryLog;
	uint32_t counter;
	uint32_t syncAfter;

	TimeDiff timeDiff;
	unsigned long defaultNano;

	unsigned long timeOutValue; // added for manual timeout
	bool isAdaptive; // added for manual timeout

	bool isSingleThread; 

	MyTimeSpec average;
	uint32_t averageCount;
	uint64_t generation; // TODO handle rounding

	dev_t fsid;

	// statistics
	struct Statistics
	{
		uint64_t normalWakeup;
		uint64_t spuriousWakeup;
		uint64_t oldGenWakeup;
		uint64_t timeoutSameGen;
		uint64_t sleepingThreads ;
		uint64_t totalSyncs ;
		uint64_t numNormalSyncs ;
		uint64_t syncAfterTimeout ;
		list<uint32_t> syncAfterList;

        Statistics();
        void init();

	} stats;
	
    friend ostream& operator << (ostream& ostr, GroupCommit::Statistics& me);

public:
	
	GroupCommit() {}

	void init(RecoveryLog<WriteCacheLogRecord> *in_recLog, RawDeviceBlockStore *writeCacheData, 
		uint32_t in_syncAfter /* = PAGE_SIZE/sizeof(WriteCacheLogRecord) */, unsigned long defaultNanoSecs = 5000000);

	~GroupCommit();

	Status realSync(off_t logOffset);
	Status sync(off_t logOffset);

	void print(ostream& ostr, int isVerbose) ;
	void clearStats() ;
	void setDynamicTimeout() ;
	void setFixedTimeout(unsigned long newTimeoutValue) ;
	void setThreads(bool isThreaded) ;
};

#endif
