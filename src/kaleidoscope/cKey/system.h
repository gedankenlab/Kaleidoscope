// -*- c++ -*-

#pragma once

#include "HIDTables.h"
#include "kaleidoscope/Key.h"


namespace kaleidoscope {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`
namespace cKey {

namespace system {

constexpr Key PowerDown = systemKey(HID_SYSTEM_POWER_DOWN);
constexpr Key Sleep = systemKey(HID_SYSTEM_SLEEP);
constexpr Key WakeUp = systemKey(HID_SYSTEM_WAKE_UP);
constexpr Key ContextMenu = systemKey(HID_SYSTEM_CONTEXT_MENU);
constexpr Key MainMenu = systemKey(HID_SYSTEM_MAIN_MENU);
constexpr Key AppMenu = systemKey(HID_SYSTEM_APP_MENU);
constexpr Key MenuHelp = systemKey(HID_SYSTEM_MENU_HELP);
constexpr Key MenuExit = systemKey(HID_SYSTEM_MENU_EXIT);
constexpr Key MenuSelect = systemKey(HID_SYSTEM_MENU_SELECT);
constexpr Key MenuRight = systemKey(HID_SYSTEM_MENU_RIGHT);
constexpr Key MenuLeft = systemKey(HID_SYSTEM_MENU_LEFT);
constexpr Key MenuUp = systemKey(HID_SYSTEM_MENU_UP);
constexpr Key MenuDown = systemKey(HID_SYSTEM_MENU_DOWN);
constexpr Key ColdRestart = systemKey(HID_SYSTEM_COLD_RESTART);
constexpr Key WarmRestart = systemKey(HID_SYSTEM_WARM_RESTART);
constexpr Key DPadUp = systemKey(HID_D_PAD_UP);
constexpr Key DPadDown = systemKey(HID_D_PAD_DOWN);
constexpr Key DPadRight = systemKey(HID_D_PAD_RIGHT);
constexpr Key DPadLeft = systemKey(HID_D_PAD_LEFT);

constexpr Key Dock = systemKey(HID_SYSTEM_DOCK);
constexpr Key Undock = systemKey(HID_SYSTEM_UNDOCK);
constexpr Key Setup = systemKey(HID_SYSTEM_SETUP);
constexpr Key Break = systemKey(HID_SYSTEM_BREAK);
constexpr Key DebuggerBreak = systemKey(HID_SYSTEM_DEBUGGER_BREAK);
constexpr Key ApplicationBreak = systemKey(HID_APPLICATION_BREAK);
constexpr Key ApplicationDebuggerBreak = systemKey(HID_APPLICATION_DEBUGGER_BREAK);
constexpr Key SpeakerMute = systemKey(HID_SYSTEM_SPEAKER_MUTE);
constexpr Key Hibernate = systemKey(HID_SYSTEM_HIBERNATE);

constexpr Key DisplayInvert = systemKey(HID_SYSTEM_DISPLAY_INVERT);
constexpr Key DisplayInternal = systemKey(HID_SYSTEM_DISPLAY_INTERNAL);
constexpr Key DisplayExternal = systemKey(HID_SYSTEM_DISPLAY_EXTERNAL);
constexpr Key DisplayBoth = systemKey(HID_SYSTEM_DISPLAY_BOTH);
constexpr Key DisplayDual = systemKey(HID_SYSTEM_DISPLAY_DUAL);
constexpr Key DisplayToggleIntSlashExt = systemKey(HID_SYSTEM_DISPLAY_TOGGLE_INT_SLASH_EXT);
constexpr Key DisplaySwapPrimarySlashSecondary = systemKey(HID_SYSTEM_DISPLAY_SWAP_PRIMARY_SLASH_SECONDARY);
constexpr Key DisplayLCDAutoscale = systemKey(HID_SYSTEM_DISPLAY_LCD_AUTOSCALE);

} // namespace consumer {

} // namespace cKey {

} // namespace kaleidoscope {
