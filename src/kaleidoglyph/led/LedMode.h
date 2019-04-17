// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include "kaleidoglyph/KeyAddr.h"

// To enable placement new, we need to supply a global operator
// function.
//
inline void* operator new (size_t, void* ptr) throw() {
  return ptr;
}


namespace kaleidoglyph {

// Forward declaration; we can't include the header
class LedManager;

// ============================================================================
// This is the LED mode class. Child classes should contain an inner class
// called "Updater", which inherits from the LedModeUpdater class.
class LedMode {
  friend class LedManager;

 public:
  static LedManager& manager();

 protected:
  bool isActive() const;

 private:
  static LedManager* led_manager_p_;

  static void init(LedManager* led_manager_p);

  byte id_;

  void assignId(byte id) { id_ = id; }
};


// ============================================================================
// This is the base class for an LED mode's inner Updater class, which gets
// swapped in and out of memory.
class LedModeUpdater {

 public:
  //LedModeUpdater(LedMode& owner) : owner_(owner) {}
  virtual void activate() {}
  virtual void update() {}
  virtual void restore(KeyAddr /*k*/) const {}

  // I'm considering these two helpers:
  //LedMode& owner() const { return owner_; }
  LedManager& manager() const { return LedMode::manager(); }

 protected:
  // The updater needs access to its "owner" (the corresponding LedMode
  // instance).
  //LedMode& owner_;
};


// ============================================================================
// Function for factory interface to create "load" the Updater object for the
// active LED mode class:
template <typename _LedModeType>
LedModeUpdater* loadLedModeUpdater(LedMode* generic_mode_p, void* updater_buffer) {
  // Convert the generic LED mode pointer to the specific one (child class)
  auto specific_mode_p = static_cast<_LedModeType*>(generic_mode_p);
  // The compiler won't let us refer to `_LedModeType::Updater` without using
  // the `typename` keyword, but that makes the followin line even more
  // confusing, so I added this typedef.
  typedef typename _LedModeType::Updater _UpdaterType;
  // Create a new LedModeUpdater of the child class's actual type, and give its
  // constructor the pointer to its owner's (enclosing) LedMode object.
  auto updater_p = new (updater_buffer) _UpdaterType{*specific_mode_p};
  return updater_p;
}

// Confusing function pointer typedef. This defines `LoadUpdaterFunction` as a
// function pointer type that takes two parameters and returns an LedModeUpdater
// pointer.
typedef LedModeUpdater* (*LoadUpdaterFunction)(LedMode* led_mode_p, void* buffer);


// ============================================================================
// factory object to be stored in an array in PROGMEM, and used to create the
// LED mode updater objects in the swap area in RAM
struct LedModeLoader {
  LedMode*            led_mode_p;
  LoadUpdaterFunction loadUpdater;
  //LedModeUpdater* (*loadUpdater)(LedMode*);
};


// ============================================================================
// Size computation for largest LedModeUpdater object that can be instantiated

// inner class object size template
template <typename _LedMode>
struct UpdaterSize {
  static constexpr size_t value = sizeof(typename _LedMode::Updater);
};

// variadic template
template <typename _FirstLedMode, typename... _OtherLedModes>
struct MaxUpdaterSize {
  static constexpr size_t first_size = UpdaterSize<_FirstLedMode>::value;
  static constexpr size_t others_max_size =
      MaxUpdaterSize<_OtherLedModes...>::value;
  static constexpr size_t value =
      (first_size > others_max_size) ? first_size : others_max_size;
};

// variadic template terminator
template <typename _LastLedMode>
struct MaxUpdaterSize<_LastLedMode> {
  static constexpr size_t value = UpdaterSize<_LastLedMode>::value;
};

}  // namespace kaleidoglyph


// ============================================================================
// Example sketch configuration

#if 0

// define LED mode objects
LedMode0 led_mode_0{};
LedMode1 led_mode_1{};
LedMode2 led_mode_2{};
LedMode3 led_mode_3{};

// calculate the biggest updater footprint
constexpr byte max_updater_size = MaxUpdaterSize<decltype(led_mode_0),
                                                 decltype(led_mode_1),
                                                 decltype(led_mode_2),
                                                 decltype(led_mode_3)>::value;
// allocate memory for the active updater
static byte updater_buffer[max_updater_size];

// create array of updater factories("loaders")
const LedModeLoader pgm_led_mode_loaders[] PROGMEM = {
    {&led_mode_0, loadLedModeUpdater<decltype(led_mode_0), updater_buffer>},
    {&led_mode_1, loadLedModeUpdater<decltype(led_mode_1), updater_buffer>},
    {&led_mode_2, loadLedModeUpdater<decltype(led_mode_2), updater_buffer>},
    {&led_mode_3, loadLedModeUpdater<decltype(led_mode_3), updater_buffer>},
};

// create LED manager
LedManager led_manager{pgm_led_mode_loaders, updater_buffer, keyboard};

#endif
