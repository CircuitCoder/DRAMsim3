#include "memory_system.h"

extern "C" {
  dramsim3::MemorySystem* ds3_create_memory_system(
    void *data,
    const char *config_path,
    const char *sim_path,
    void (*callback)(void *, uint64_t, bool),
  ) {
    return new dramsim3::MemorySystem(
      config_path,
      sim_path,
      [=](uint64_t addr) { callback(data, false, addr); },
      [=](uint64_t addr) { callback(data, true, addr); }
    );
  }

  void ds3_tick(dramsim3::MemorySystem *sys) {
    sys->ClockTick();
  }

  bool ds3_can_add(const dramsim3::MemorySystem *sys, uint64_t addr, bool is_write) {
    return sys->WillAcceptTransaction(addr, is_write);
  }

  bool ds3_add(dramsim3::MemorySystem *sys, uint64_t addr, bool is_write) {
    return sys->WillAcceptTransaction(addr, is_write);
  }
}
