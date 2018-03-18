// -*- c++ -*-

#pragma once

#include "kaleidoscope/cKey/HIDTables.h"
#include "kaleidoscope/Key.h"


// Keyboard HID mappings
namespace kaleidoscope {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`, so any symbol that begins with `cKey::` can be assumed to be a
// `const Key` object.
namespace cKey {

// Reserved (no_event_indicated)
constexpr Key NoEvent { HID_KEYBOARD_NO_EVENT };
constexpr Key ErrorRollover { HID_KEYBOARD_ERROR_ROLLOVER };
constexpr Key PostFail { HID_KEYBOARD_POST_FAIL };
constexpr Key ErrorUndefined { HID_KEYBOARD_ERROR_UNDEFINED };
constexpr Key A { HID_KEYBOARD_A_AND_A };
constexpr Key B { HID_KEYBOARD_B_AND_B };
constexpr Key C { HID_KEYBOARD_C_AND_C };
constexpr Key D { HID_KEYBOARD_D_AND_D };
constexpr Key E { HID_KEYBOARD_E_AND_E };
constexpr Key F { HID_KEYBOARD_F_AND_F };
constexpr Key G { HID_KEYBOARD_G_AND_G };
constexpr Key H { HID_KEYBOARD_H_AND_H };
constexpr Key I { HID_KEYBOARD_I_AND_I };
constexpr Key J { HID_KEYBOARD_J_AND_J };
constexpr Key K { HID_KEYBOARD_K_AND_K };
constexpr Key L { HID_KEYBOARD_L_AND_L };
constexpr Key M { HID_KEYBOARD_M_AND_M };
constexpr Key N { HID_KEYBOARD_N_AND_N };
constexpr Key O { HID_KEYBOARD_O_AND_O };
constexpr Key P { HID_KEYBOARD_P_AND_P };
constexpr Key Q { HID_KEYBOARD_Q_AND_Q };
constexpr Key R { HID_KEYBOARD_R_AND_R };
constexpr Key S { HID_KEYBOARD_S_AND_S };
constexpr Key T { HID_KEYBOARD_T_AND_T };
constexpr Key U { HID_KEYBOARD_U_AND_U };
constexpr Key V { HID_KEYBOARD_V_AND_V };
constexpr Key W { HID_KEYBOARD_W_AND_W };
constexpr Key X { HID_KEYBOARD_X_AND_X };
constexpr Key Y { HID_KEYBOARD_Y_AND_Y };
constexpr Key Z { HID_KEYBOARD_Z_AND_Z };
// Can't use raw digits as identifiers here, so I prepended underscores. I'm not entirely
// happy with this yet. `cKey::_1` is a bit ugly, when there's `cKey::A` for
// comparison. Maybe `cKey::d1` would be better? (`d` for "digit") Or maybe `cKey::_A` for
// symmetry? Either way, it's turning out longer than `Key_A`, but I do think it's much
// clearer with the namespace for constants named after the type name (since C++ won't let
// me have `Key::A`)
constexpr Key _1 { HID_KEYBOARD_1_AND_EXCLAMATION_POINT };
constexpr Key _2 { HID_KEYBOARD_2_AND_AT };
constexpr Key _3 { HID_KEYBOARD_3_AND_POUND };
constexpr Key _4 { HID_KEYBOARD_4_AND_DOLLAR };
constexpr Key _5 { HID_KEYBOARD_5_AND_PERCENT };
constexpr Key _6 { HID_KEYBOARD_6_AND_CARAT };
constexpr Key _7 { HID_KEYBOARD_7_AND_AMPERSAND };
constexpr Key _8 { HID_KEYBOARD_8_AND_ASTERISK };
constexpr Key _9 { HID_KEYBOARD_9_AND_LEFT_PAREN };
constexpr Key _0 { HID_KEYBOARD_0_AND_RIGHT_PAREN };
constexpr Key Enter { HID_KEYBOARD_ENTER };		 // (MARKED AS ENTER_SLASH_RETURN)
constexpr Key Escape { HID_KEYBOARD_ESCAPE };
constexpr Key Backspace { HID_KEYBOARD_DELETE };		// (BACKSPACE)
constexpr Key Tab { HID_KEYBOARD_TAB };
constexpr Key Spacebar { HID_KEYBOARD_SPACEBAR };
constexpr Key Minus { HID_KEYBOARD_MINUS_AND_UNDERSCORE }; // (UNDERSCORE)
constexpr Key Equals { HID_KEYBOARD_EQUALS_AND_PLUS };
constexpr Key LeftBracket { HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE };
constexpr Key RightBracket { HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE };
constexpr Key Backslash { HID_KEYBOARD_BACKSLASH_AND_PIPE };
constexpr Key NonUsPound { HID_KEYBOARD_NON_US_POUND_AND_TILDE };
constexpr Key Semicolon { HID_KEYBOARD_SEMICOLON_AND_COLON };
constexpr Key Quote { HID_KEYBOARD_QUOTE_AND_DOUBLEQUOTE };
constexpr Key Backtick { HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE };
constexpr Key Comma { HID_KEYBOARD_COMMA_AND_LESS_THAN };
constexpr Key Period { HID_KEYBOARD_PERIOD_AND_GREATER_THAN };
constexpr Key Slash { HID_KEYBOARD_SLASH_AND_QUESTION_MARK };
constexpr Key CapsLock { HID_KEYBOARD_CAPS_LOCK };
constexpr Key F1 { HID_KEYBOARD_F1 };
constexpr Key F2 { HID_KEYBOARD_F2 };
constexpr Key F3 { HID_KEYBOARD_F3 };
constexpr Key F4 { HID_KEYBOARD_F4 };
constexpr Key F5 { HID_KEYBOARD_F5 };
constexpr Key F6 { HID_KEYBOARD_F6 };
constexpr Key F7 { HID_KEYBOARD_F7 };
constexpr Key F8 { HID_KEYBOARD_F8 };
constexpr Key F9 { HID_KEYBOARD_F9 };
constexpr Key F10 { HID_KEYBOARD_F10 };
constexpr Key F11 { HID_KEYBOARD_F11 };
constexpr Key F12 { HID_KEYBOARD_F12 };
constexpr Key PrintScreen { HID_KEYBOARD_PRINTSCREEN };
constexpr Key ScrollLock { HID_KEYBOARD_SCROLL_LOCK };
constexpr Key Pause { HID_KEYBOARD_PAUSE };
constexpr Key Insert { HID_KEYBOARD_INSERT };
constexpr Key Home { HID_KEYBOARD_HOME };
constexpr Key PageUp { HID_KEYBOARD_PAGE_UP };
constexpr Key Delete { HID_KEYBOARD_DELETE_FORWARD };
constexpr Key End { HID_KEYBOARD_END };
constexpr Key PageDown { HID_KEYBOARD_PAGE_DOWN };
constexpr Key RightArrow { HID_KEYBOARD_RIGHT_ARROW };
constexpr Key LeftArrow { HID_KEYBOARD_LEFT_ARROW };
constexpr Key DownArrow { HID_KEYBOARD_DOWN_ARROW };
constexpr Key UpArrow { HID_KEYBOARD_UP_ARROW };
constexpr Key KeypadNumLock { HID_KEYPAD_NUM_LOCK_AND_CLEAR };
constexpr Key KeypadDivide { HID_KEYPAD_DIVIDE };
constexpr Key KeypadMultiply { HID_KEYPAD_MULTIPLY };
constexpr Key KeypadSubtract { HID_KEYPAD_SUBTRACT };
constexpr Key KeypadAdd { HID_KEYPAD_ADD };
constexpr Key KeypadEnter { HID_KEYPAD_ENTER };
constexpr Key Keypad1 { HID_KEYPAD_1_AND_END };
constexpr Key Keypad2 { HID_KEYPAD_2_AND_DOWN_ARROW };
constexpr Key Keypad3 { HID_KEYPAD_3_AND_PAGE_DOWN };
constexpr Key Keypad4 { HID_KEYPAD_4_AND_LEFT_ARROW };
constexpr Key Keypad5 { HID_KEYPAD_5 };
constexpr Key Keypad6 { HID_KEYPAD_6_AND_RIGHT_ARROW };
constexpr Key Keypad7 { HID_KEYPAD_7_AND_HOME };
constexpr Key Keypad8 { HID_KEYPAD_8_AND_UP_ARROW };
constexpr Key Keypad9 { HID_KEYPAD_9_AND_PAGE_UP };
constexpr Key Keypad0 { HID_KEYPAD_0_AND_INSERT };
constexpr Key KeypadDot { HID_KEYPAD_PERIOD_AND_DELETE };
constexpr Key NonUsBackslashAndPipe { HID_KEYBOARD_NON_US_BACKSLASH_AND_PIPE };
constexpr Key PcApplication { HID_KEYBOARD_APPLICATION };
constexpr Key Power { HID_KEYBOARD_POWER };
constexpr Key KeypadEquals { HID_KEYPAD_EQUALS };
constexpr Key F13 { HID_KEYBOARD_F13 };
constexpr Key F14 { HID_KEYBOARD_F14 };
constexpr Key F15 { HID_KEYBOARD_F15 };
constexpr Key F16 { HID_KEYBOARD_F16 };
constexpr Key F17 { HID_KEYBOARD_F17 };
constexpr Key F18 { HID_KEYBOARD_F18 };
constexpr Key F19 { HID_KEYBOARD_F19 };
constexpr Key F20 { HID_KEYBOARD_F20 };
constexpr Key F21 { HID_KEYBOARD_F21 };
constexpr Key F22 { HID_KEYBOARD_F22 };
constexpr Key F23 { HID_KEYBOARD_F23 };
constexpr Key F24 { HID_KEYBOARD_F24 };
constexpr Key Execute { HID_KEYBOARD_EXECUTE };
constexpr Key Help { HID_KEYBOARD_HELP };
constexpr Key Menu { HID_KEYBOARD_MENU };
constexpr Key Select { HID_KEYBOARD_SELECT };
constexpr Key Stop { HID_KEYBOARD_STOP };
constexpr Key Again { HID_KEYBOARD_AGAIN };
constexpr Key Undo { HID_KEYBOARD_UNDO };
constexpr Key Cut { HID_KEYBOARD_CUT };
constexpr Key Copy { HID_KEYBOARD_COPY };
constexpr Key Paste { HID_KEYBOARD_PASTE };
constexpr Key Find { HID_KEYBOARD_FIND };
constexpr Key Mute { HID_KEYBOARD_MUTE };
constexpr Key VolumeUp { HID_KEYBOARD_VOLUME_UP };
constexpr Key VolumeDown { HID_KEYBOARD_VOLUME_DOWN };
constexpr Key LockingCapsLock { HID_KEYBOARD_LOCKING_CAPS_LOCK };
constexpr Key LockingNumLock { HID_KEYBOARD_LOCKING_NUM_LOCK };
constexpr Key LockingScrollLock { HID_KEYBOARD_LOCKING_SCROLL_LOCK };
constexpr Key KeypadComma { HID_KEYPAD_COMMA };
constexpr Key KeypadEqualSign { HID_KEYPAD_EQUAL_SIGN };
constexpr Key International1 { HID_KEYBOARD_INTERNATIONAL1 };
constexpr Key International2 { HID_KEYBOARD_INTERNATIONAL2 };
constexpr Key International3 { HID_KEYBOARD_INTERNATIONAL3 };
constexpr Key International4 { HID_KEYBOARD_INTERNATIONAL4 };
constexpr Key International5 { HID_KEYBOARD_INTERNATIONAL5 };
constexpr Key International6 { HID_KEYBOARD_INTERNATIONAL6 };
constexpr Key International7 { HID_KEYBOARD_INTERNATIONAL7 };
constexpr Key International8 { HID_KEYBOARD_INTERNATIONAL8 };
constexpr Key International9 { HID_KEYBOARD_INTERNATIONAL9 };
constexpr Key Lang1 { HID_KEYBOARD_LANG1 };
constexpr Key Lang2 { HID_KEYBOARD_LANG2 };
constexpr Key Lang3 { HID_KEYBOARD_LANG3 };
constexpr Key Lang4 { HID_KEYBOARD_LANG4 };
constexpr Key Lang5 { HID_KEYBOARD_LANG5 };
constexpr Key Lang6 { HID_KEYBOARD_LANG6 };
constexpr Key Lang7 { HID_KEYBOARD_LANG7 };
constexpr Key Lang8 { HID_KEYBOARD_LANG8 };
constexpr Key Lang9 { HID_KEYBOARD_LANG9 };
constexpr Key AlternateErase { HID_KEYBOARD_ALTERNATE_ERASE };
constexpr Key Sysreq { HID_KEYBOARD_SYSREQ_SLASH_ATTENTION };
constexpr Key Cancel { HID_KEYBOARD_CANCEL };
constexpr Key Clear { HID_KEYBOARD_CLEAR };
constexpr Key Prior { HID_KEYBOARD_PRIOR };
constexpr Key Return { HID_KEYBOARD_RETURN };
constexpr Key Separator { HID_KEYBOARD_SEPARATOR };
constexpr Key Out { HID_KEYBOARD_OUT };
constexpr Key Oper { HID_KEYBOARD_OPER };
constexpr Key ClearSlashAgain { HID_KEYBOARD_CLEAR_SLASH_AGAIN };
constexpr Key CrselSlashProps { HID_KEYBOARD_CRSEL_SLASH_PROPS };
constexpr Key Exsel { HID_KEYBOARD_EXSEL };
// Reserved	0xA5-AF
constexpr Key Keypad00 { HID_KEYPAD_00 };
constexpr Key Keypad000 { HID_KEYPAD_000 };
constexpr Key ThousandsSeparator { HID_THOUSANDS_SEPARATOR };
constexpr Key DecimalSeparator { HID_DECIMAL_SEPARATOR };
constexpr Key CurrencyUnit { HID_CURRENCY_UNIT };
constexpr Key CurrencySubunit { HID_CURRENCY_SUBUNIT };
constexpr Key KeypadLeftParen { HID_KEYPAD_LEFT_PAREN };
constexpr Key KeypadRightParen { HID_KEYPAD_RIGHT_PAREN };
constexpr Key KeypadLeftCurlyBrace { HID_KEYPAD_LEFT_CURLY_BRACE };
constexpr Key KeypadRightCurlyBrace { HID_KEYPAD_RIGHT_CURLY_BRACE };
constexpr Key KeypadTab { HID_KEYPAD_TAB };
constexpr Key KeypadBackspace { HID_KEYPAD_BACKSPACE };
constexpr Key KeypadA { HID_KEYPAD_A };
constexpr Key KeypadB { HID_KEYPAD_B };
constexpr Key KeypadC { HID_KEYPAD_C };
constexpr Key KeypadD { HID_KEYPAD_D };
constexpr Key KeypadE { HID_KEYPAD_E };
constexpr Key KeypadF { HID_KEYPAD_F };
constexpr Key KeypadXor { HID_KEYPAD_XOR };
constexpr Key KeypadCarat { HID_KEYPAD_CARAT };
constexpr Key KeypadPercent { HID_KEYPAD_PERCENT };
constexpr Key KeypadLessThan { HID_KEYPAD_LESS_THAN };
constexpr Key KeypadGreaterThan { HID_KEYPAD_GREATER_THAN };
constexpr Key KeypadAmpersand { HID_KEYPAD_AMPERSAND };
constexpr Key KeypadDoubleampersand { HID_KEYPAD_DOUBLEAMPERSAND };
constexpr Key KeypadPipe { HID_KEYPAD_PIPE };
constexpr Key KeypadDoublepipe { HID_KEYPAD_DOUBLEPIPE };
constexpr Key KeypadColon { HID_KEYPAD_COLON };
constexpr Key KeypadPoundSign { HID_KEYPAD_POUND_SIGN };
constexpr Key KeypadSpace { HID_KEYPAD_SPACE };
constexpr Key KeypadAtSign { HID_KEYPAD_AT_SIGN };
constexpr Key KeypadExclamationPoint { HID_KEYPAD_EXCLAMATION_POINT };
constexpr Key KeypadMemoryStore { HID_KEYPAD_MEMORY_STORE };
constexpr Key KeypadMemoryRecall { HID_KEYPAD_MEMORY_RECALL };
constexpr Key KeypadMemoryClear { HID_KEYPAD_MEMORY_CLEAR };
constexpr Key KeypadMemoryAdd { HID_KEYPAD_MEMORY_ADD };
constexpr Key KeypadMemorySubtract { HID_KEYPAD_MEMORY_SUBTRACT };
constexpr Key KeypadMemoryMultiply { HID_KEYPAD_MEMORY_MULTIPLY };
constexpr Key KeypadMemoryDivide { HID_KEYPAD_MEMORY_DIVIDE };
constexpr Key KeypadPlusSlashMinus { HID_KEYPAD_PLUS_SLASH_MINUS };
constexpr Key KeypadClear { HID_KEYPAD_CLEAR };
constexpr Key KeypadClearEntry { HID_KEYPAD_CLEAR_ENTRY };
constexpr Key KeypadBinary { HID_KEYPAD_BINARY };
constexpr Key KeypadOctal { HID_KEYPAD_OCTAL };
constexpr Key KeypadDecimal { HID_KEYPAD_DECIMAL };
constexpr Key KeypadHexadecimal { HID_KEYPAD_HEXADECIMAL };

constexpr Key LeftControl { HID_KEYBOARD_LEFT_CONTROL };
constexpr Key LeftShift { HID_KEYBOARD_LEFT_SHIFT };
constexpr Key LeftAlt { HID_KEYBOARD_LEFT_ALT };
constexpr Key LeftGui { HID_KEYBOARD_LEFT_GUI };
constexpr Key RightControl { HID_KEYBOARD_RIGHT_CONTROL };
constexpr Key RightShift { HID_KEYBOARD_RIGHT_SHIFT };
constexpr Key RightAlt { HID_KEYBOARD_RIGHT_ALT };
constexpr Key RightGui { HID_KEYBOARD_RIGHT_GUI };

// Aliases for modifier keys
constexpr Key l_ctl = LeftControl;
constexpr Key l_sft = LeftShift;
constexpr Key l_alt = LeftAlt;
constexpr Key l_gui = LeftGui;
constexpr Key r_ctl = RightControl;
constexpr Key r_sft = RightShift;
constexpr Key r_alt = RightAlt;
constexpr Key r_gui = RightGui;

// Aliases for macOS
constexpr Key l_opt = LeftAlt;
constexpr Key l_cmd = LeftGui;
constexpr Key r_opt = RightAlt;
constexpr Key r_cmd = RightGui;

// Aliases for Windows
constexpr Key l_win = LeftGui;
constexpr Key r_win = RightGui;

constexpr Key first_modifier = LeftControl;

} // namespace cKey {

} // namespace kaleidoscope {
