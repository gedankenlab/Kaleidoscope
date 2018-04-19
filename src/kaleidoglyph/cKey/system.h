// -*- c++ -*-

#pragma once

#include "HIDTables.h"
#include "kaleidoglyph/Key.h"


namespace kaleidoglyph {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`
namespace cSystemKey {

constexpr SystemKey PowerDown { HID_SYSTEM_POWER_DOWN };
constexpr SystemKey Sleep { HID_SYSTEM_SLEEP };
constexpr SystemKey WakeUp { HID_SYSTEM_WAKE_UP };
constexpr SystemKey ContextMenu { HID_SYSTEM_CONTEXT_MENU };
constexpr SystemKey MainMenu { HID_SYSTEM_MAIN_MENU };
constexpr SystemKey AppMenu { HID_SYSTEM_APP_MENU };
constexpr SystemKey MenuHelp { HID_SYSTEM_MENU_HELP };
constexpr SystemKey MenuExit { HID_SYSTEM_MENU_EXIT };
constexpr SystemKey MenuSelect { HID_SYSTEM_MENU_SELECT };
constexpr SystemKey MenuRight { HID_SYSTEM_MENU_RIGHT };
constexpr SystemKey MenuLeft { HID_SYSTEM_MENU_LEFT };
constexpr SystemKey MenuUp { HID_SYSTEM_MENU_UP };
constexpr SystemKey MenuDown { HID_SYSTEM_MENU_DOWN };
constexpr SystemKey ColdRestart { HID_SYSTEM_COLD_RESTART };
constexpr SystemKey WarmRestart { HID_SYSTEM_WARM_RESTART };
constexpr SystemKey DPadUp { HID_D_PAD_UP };
constexpr SystemKey DPadDown { HID_D_PAD_DOWN };
constexpr SystemKey DPadRight { HID_D_PAD_RIGHT };
constexpr SystemKey DPadLeft { HID_D_PAD_LEFT };

constexpr SystemKey Dock { HID_SYSTEM_DOCK };
constexpr SystemKey Undock { HID_SYSTEM_UNDOCK };
constexpr SystemKey Setup { HID_SYSTEM_SETUP };
constexpr SystemKey Break { HID_SYSTEM_BREAK };
constexpr SystemKey DebuggerBreak { HID_SYSTEM_DEBUGGER_BREAK };
constexpr SystemKey ApplicationBreak { HID_APPLICATION_BREAK };
constexpr SystemKey ApplicationDebuggerBreak { HID_APPLICATION_DEBUGGER_BREAK };
constexpr SystemKey SpeakerMute { HID_SYSTEM_SPEAKER_MUTE };
constexpr SystemKey Hibernate { HID_SYSTEM_HIBERNATE };

constexpr SystemKey DisplayInvert { HID_SYSTEM_DISPLAY_INVERT };
constexpr SystemKey DisplayInternal { HID_SYSTEM_DISPLAY_INTERNAL };
constexpr SystemKey DisplayExternal { HID_SYSTEM_DISPLAY_EXTERNAL };
constexpr SystemKey DisplayBoth { HID_SYSTEM_DISPLAY_BOTH };
constexpr SystemKey DisplayDual { HID_SYSTEM_DISPLAY_DUAL };
constexpr SystemKey DisplayToggleIntSlashExt { HID_SYSTEM_DISPLAY_TOGGLE_INT_SLASH_EXT };
constexpr SystemKey DisplaySwapPrimarySlashSecondary { HID_SYSTEM_DISPLAY_SWAP_PRIMARY_SLASH_SECONDARY };
constexpr SystemKey DisplayLCDAutoscale { HID_SYSTEM_DISPLAY_LCD_AUTOSCALE };

} // namespace cSystemKey {

} // namespace kaleidoglyph {
