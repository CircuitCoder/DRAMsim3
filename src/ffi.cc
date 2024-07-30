#include "memory_system.h"

extern "C" {
  dramsim3::MemorySystem* ds3_create(
    void *data,
    const char *config_path,
    const char *sim_path,
    void (*callback)(void *, uint64_t, bool)
  ) {
    return new dramsim3::MemorySystem(
      config_path,
      sim_path,
      [=](uint64_t addr) { callback(data, addr, false); },
      [=](uint64_t addr) { callback(data, addr, true); }
    );
  }

  void ds3_tick(dramsim3::MemorySystem *sys) {
    sys->ClockTick();
  }

  bool ds3_can_add(const dramsim3::MemorySystem *sys, uint64_t addr, bool is_write) {
    return sys->WillAcceptTransaction(addr, is_write);
  }

  bool ds3_add(dramsim3::MemorySystem *sys, uint64_t addr, bool is_write) {
    return sys->AddTransaction(addr, is_write);
  }

  void ds3_drop(dramsim3::MemorySystem *sys) {
    delete sys;
  }

  double ds3_get_tck(dramsim3::MemorySystem *sys) {
    return sys->GetTCK();
  }

  int ds3_get_bus_bits(dramsim3::MemorySystem *sys) {
    return sys->GetBusBits();
  }

  int ds3_get_burst_length(dramsim3::MemorySystem *sys) {
    return sys->GetBurstLength();
  }

  int ds3_get_queue_size(dramsim3::MemorySystem *sys) {
    return sys->GetQueueSize();
  }
}
