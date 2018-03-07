// -*- c++ -*-

#pragma once

#include "HIDTables.h"
#include "kaleidoscope/Key.h"


namespace kaleidoscope {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`
namespace cKey {

namespace system {

constexpr Key PowerDown = Key::systemKey(HID_SYSTEM_POWER_DOWN);
constexpr Key Sleep = Key::systemKey(HID_SYSTEM_SLEEP);
constexpr Key WakeUp = Key::systemKey(HID_SYSTEM_WAKE_UP);
constexpr Key ContextMenu = Key::systemKey(HID_SYSTEM_CONTEXT_MENU);
constexpr Key MainMenu = Key::systemKey(HID_SYSTEM_MAIN_MENU);
constexpr Key AppMenu = Key::systemKey(HID_SYSTEM_APP_MENU);
constexpr Key MenuHelp = Key::systemKey(HID_SYSTEM_MENU_HELP);
constexpr Key MenuExit = Key::systemKey(HID_SYSTEM_MENU_EXIT);
constexpr Key MenuSelect = Key::systemKey(HID_SYSTEM_MENU_SELECT);
constexpr Key MenuRight = Key::systemKey(HID_SYSTEM_MENU_RIGHT);
constexpr Key MenuLeft = Key::systemKey(HID_SYSTEM_MENU_LEFT);
constexpr Key MenuUp = Key::systemKey(HID_SYSTEM_MENU_UP);
constexpr Key MenuDown = Key::systemKey(HID_SYSTEM_MENU_DOWN);
constexpr Key ColdRestart = Key::systemKey(HID_SYSTEM_COLD_RESTART);
constexpr Key WarmRestart = Key::systemKey(HID_SYSTEM_WARM_RESTART);
constexpr Key DPadUp = Key::systemKey(HID_D_PAD_UP);
constexpr Key DPadDown = Key::systemKey(HID_D_PAD_DOWN);
constexpr Key DPadRight = Key::systemKey(HID_D_PAD_RIGHT);
constexpr Key DPadLeft = Key::systemKey(HID_D_PAD_LEFT);

constexpr Key Dock = Key::systemKey(HID_SYSTEM_DOCK);
constexpr Key Undock = Key::systemKey(HID_SYSTEM_UNDOCK);
constexpr Key Setup = Key::systemKey(HID_SYSTEM_SETUP);
constexpr Key Break = Key::systemKey(HID_SYSTEM_BREAK);
constexpr Key DebuggerBreak = Key::systemKey(HID_SYSTEM_DEBUGGER_BREAK);
constexpr Key ApplicationBreak = Key::systemKey(HID_APPLICATION_BREAK);
constexpr Key ApplicationDebuggerBreak = Key::systemKey(HID_APPLICATION_DEBUGGER_BREAK);
constexpr Key SpeakerMute = Key::systemKey(HID_SYSTEM_SPEAKER_MUTE);
constexpr Key Hibernate = Key::systemKey(HID_SYSTEM_HIBERNATE);

constexpr Key DisplayInvert = Key::systemKey(HID_SYSTEM_DISPLAY_INVERT);
constexpr Key DisplayInternal = Key::systemKey(HID_SYSTEM_DISPLAY_INTERNAL);
constexpr Key DisplayExternal = Key::systemKey(HID_SYSTEM_DISPLAY_EXTERNAL);
constexpr Key DisplayBoth = Key::systemKey(HID_SYSTEM_DISPLAY_BOTH);
constexpr Key DisplayDual = Key::systemKey(HID_SYSTEM_DISPLAY_DUAL);
constexpr Key DisplayToggleIntSlashExt = Key::systemKey(HID_SYSTEM_DISPLAY_TOGGLE_INT_SLASH_EXT);
constexpr Key DisplaySwapPrimarySlashSecondary = Key::systemKey(HID_SYSTEM_DISPLAY_SWAP_PRIMARY_SLASH_SECONDARY);
constexpr Key DisplayLCDAutoscale = Key::systemKey(HID_SYSTEM_DISPLAY_LCD_AUTOSCALE);

} // namespace consumer {

} // namespace cKey {

} // namespace kaleidoscope {
