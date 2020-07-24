#pragma once

#include <atomic>

#include "common/macros.h"
#include "common/type.h"

namespace pidan {
// 用于数据项的锁
class DataLatch {
 public:
  DISALLOW_COPY_AND_MOVE(DataLatch);

  DataLatch() = default;

  // 尝试为此数据项加写锁，加锁成功返回true，否则返回false
  bool TryWriteLock(txn_id_t txn_id);

  // 尝试为此数据项加读锁，加锁成功返回true，否则返回false
  bool TryReadLock();

  void ReadUnlock();

  void WriteUnlock(txn_id_t txn_id);

 private:
  // 根据latch_flag的值返回一个新值，新的值表示加了读锁。
  uint64_t SetReadBits(uint64_t latch) { return latch + (1UL << 48); }
  // 
  uint64_t UnsetReadBits(uint64_t latch) { return latch - (1UL << 48); }

  // 判断flag上是否已经加了写锁了
  bool LockedOnWrite(uint64_t latch) {
    return GetWriteBits(latch) != NULL_DATA_LATCH;
  }
  //
  bool LockedOnRead(uint64_t latch) {
    return GetReadBits(latch) != NULL_DATA_LATCH;
  }
  
  uint64_t GetReadBits(uint64_t latch) {
    return latch & ~((1UL << 48) - 1);
  }

  uint64_t GetWriteBits(uint64_t latch) {
    return latch & ((1UL << 48) - 1);
  }

  std::atomic<uint64_t> latch_{NULL_DATA_LATCH};
};
}  // namespace pidan