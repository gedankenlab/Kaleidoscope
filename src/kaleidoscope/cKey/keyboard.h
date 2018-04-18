// -*- c++ -*-

#pragma once

#include "kaleidoscope/cKey/HIDTables.h"
#include "kaleidoscope/Key.h"


// Keyboard HID mappings
namespace kaleidoscope {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`, so any symbol that begins with `cKey::` can be assumed to be a
// `constexpr Key` object.
namespace cKeyboardKey {

// Reserved (no_event_indicated)
constexpr KeyboardKey NoEvent { HID_KEYBOARD_NO_EVENT };
constexpr KeyboardKey ErrorRollover { HID_KEYBOARD_ERROR_ROLLOVER };
constexpr KeyboardKey PostFail { HID_KEYBOARD_POST_FAIL };
constexpr KeyboardKey ErrorUndefined { HID_KEYBOARD_ERROR_UNDEFINED };
constexpr KeyboardKey A { HID_KEYBOARD_A_AND_A };
constexpr KeyboardKey B { HID_KEYBOARD_B_AND_B };
constexpr KeyboardKey C { HID_KEYBOARD_C_AND_C };
constexpr KeyboardKey D { HID_KEYBOARD_D_AND_D };
constexpr KeyboardKey E { HID_KEYBOARD_E_AND_E };
constexpr KeyboardKey F { HID_KEYBOARD_F_AND_F };
constexpr KeyboardKey G { HID_KEYBOARD_G_AND_G };
constexpr KeyboardKey H { HID_KEYBOARD_H_AND_H };
constexpr KeyboardKey I { HID_KEYBOARD_I_AND_I };
constexpr KeyboardKey J { HID_KEYBOARD_J_AND_J };
constexpr KeyboardKey K { HID_KEYBOARD_K_AND_K };
constexpr KeyboardKey L { HID_KEYBOARD_L_AND_L };
constexpr KeyboardKey M { HID_KEYBOARD_M_AND_M };
constexpr KeyboardKey N { HID_KEYBOARD_N_AND_N };
constexpr KeyboardKey O { HID_KEYBOARD_O_AND_O };
constexpr KeyboardKey P { HID_KEYBOARD_P_AND_P };
constexpr KeyboardKey Q { HID_KEYBOARD_Q_AND_Q };
constexpr KeyboardKey R { HID_KEYBOARD_R_AND_R };
constexpr KeyboardKey S { HID_KEYBOARD_S_AND_S };
constexpr KeyboardKey T { HID_KEYBOARD_T_AND_T };
constexpr KeyboardKey U { HID_KEYBOARD_U_AND_U };
constexpr KeyboardKey V { HID_KEYBOARD_V_AND_V };
constexpr KeyboardKey W { HID_KEYBOARD_W_AND_W };
constexpr KeyboardKey X { HID_KEYBOARD_X_AND_X };
constexpr KeyboardKey Y { HID_KEYBOARD_Y_AND_Y };
constexpr KeyboardKey Z { HID_KEYBOARD_Z_AND_Z };
// Can't use raw digits as identifiers here, so I prepended underscores. I'm not entirely
// happy with this yet. `cKey::_1` is a bit ugly, when there's `cKey::A` for
// comparison. Maybe `cKey::d1` would be better? (`d` for "digit") Or maybe `cKey::_A` for
// symmetry? Either way, it's turning out longer than `Key_A`, but I do think it's much
// clearer with the namespace for constants named after the type name (since C++ won't let
// me have `Key::A`)
constexpr KeyboardKey _1 { HID_KEYBOARD_1_AND_EXCLAMATION_POINT };
constexpr KeyboardKey _2 { HID_KEYBOARD_2_AND_AT };
constexpr KeyboardKey _3 { HID_KEYBOARD_3_AND_POUND };
constexpr KeyboardKey _4 { HID_KEYBOARD_4_AND_DOLLAR };
constexpr KeyboardKey _5 { HID_KEYBOARD_5_AND_PERCENT };
constexpr KeyboardKey _6 { HID_KEYBOARD_6_AND_CARAT };
constexpr KeyboardKey _7 { HID_KEYBOARD_7_AND_AMPERSAND };
constexpr KeyboardKey _8 { HID_KEYBOARD_8_AND_ASTERISK };
constexpr KeyboardKey _9 { HID_KEYBOARD_9_AND_LEFT_PAREN };
constexpr KeyboardKey _0 { HID_KEYBOARD_0_AND_RIGHT_PAREN };
constexpr KeyboardKey Enter { HID_KEYBOARD_ENTER };		 // (MARKED AS ENTER_SLASH_RETURN)
constexpr KeyboardKey Escape { HID_KEYBOARD_ESCAPE };
constexpr KeyboardKey Backspace { HID_KEYBOARD_DELETE };		// (BACKSPACE)
constexpr KeyboardKey Tab { HID_KEYBOARD_TAB };
constexpr KeyboardKey Spacebar { HID_KEYBOARD_SPACEBAR };
constexpr KeyboardKey Minus { HID_KEYBOARD_MINUS_AND_UNDERSCORE }; // (UNDERSCORE)
constexpr KeyboardKey Equals { HID_KEYBOARD_EQUALS_AND_PLUS };
constexpr KeyboardKey LeftBracket { HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE };
constexpr KeyboardKey RightBracket { HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE };
constexpr KeyboardKey Backslash { HID_KEYBOARD_BACKSLASH_AND_PIPE };
constexpr KeyboardKey NonUsPound { HID_KEYBOARD_NON_US_POUND_AND_TILDE };
constexpr KeyboardKey Semicolon { HID_KEYBOARD_SEMICOLON_AND_COLON };
constexpr KeyboardKey Quote { HID_KEYBOARD_QUOTE_AND_DOUBLEQUOTE };
constexpr KeyboardKey Backtick { HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE };
constexpr KeyboardKey Comma { HID_KEYBOARD_COMMA_AND_LESS_THAN };
constexpr KeyboardKey Period { HID_KEYBOARD_PERIOD_AND_GREATER_THAN };
constexpr KeyboardKey Slash { HID_KEYBOARD_SLASH_AND_QUESTION_MARK };
constexpr KeyboardKey CapsLock { HID_KEYBOARD_CAPS_LOCK };
constexpr KeyboardKey F1 { HID_KEYBOARD_F1 };
constexpr KeyboardKey F2 { HID_KEYBOARD_F2 };
constexpr KeyboardKey F3 { HID_KEYBOARD_F3 };
constexpr KeyboardKey F4 { HID_KEYBOARD_F4 };
constexpr KeyboardKey F5 { HID_KEYBOARD_F5 };
constexpr KeyboardKey F6 { HID_KEYBOARD_F6 };
constexpr KeyboardKey F7 { HID_KEYBOARD_F7 };
constexpr KeyboardKey F8 { HID_KEYBOARD_F8 };
constexpr KeyboardKey F9 { HID_KEYBOARD_F9 };
constexpr KeyboardKey F10 { HID_KEYBOARD_F10 };
constexpr KeyboardKey F11 { HID_KEYBOARD_F11 };
constexpr KeyboardKey F12 { HID_KEYBOARD_F12 };
constexpr KeyboardKey PrintScreen { HID_KEYBOARD_PRINTSCREEN };
constexpr KeyboardKey ScrollLock { HID_KEYBOARD_SCROLL_LOCK };
constexpr KeyboardKey Pause { HID_KEYBOARD_PAUSE };
constexpr KeyboardKey Insert { HID_KEYBOARD_INSERT };
constexpr KeyboardKey Home { HID_KEYBOARD_HOME };
constexpr KeyboardKey PageUp { HID_KEYBOARD_PAGE_UP };
constexpr KeyboardKey Delete { HID_KEYBOARD_DELETE_FORWARD };
constexpr KeyboardKey End { HID_KEYBOARD_END };
constexpr KeyboardKey PageDown { HID_KEYBOARD_PAGE_DOWN };
constexpr KeyboardKey RightArrow { HID_KEYBOARD_RIGHT_ARROW };
constexpr KeyboardKey LeftArrow { HID_KEYBOARD_LEFT_ARROW };
constexpr KeyboardKey DownArrow { HID_KEYBOARD_DOWN_ARROW };
constexpr KeyboardKey UpArrow { HID_KEYBOARD_UP_ARROW };
constexpr KeyboardKey KeypadNumLock { HID_KEYPAD_NUM_LOCK_AND_CLEAR };
constexpr KeyboardKey KeypadDivide { HID_KEYPAD_DIVIDE };
constexpr KeyboardKey KeypadMultiply { HID_KEYPAD_MULTIPLY };
constexpr KeyboardKey KeypadSubtract { HID_KEYPAD_SUBTRACT };
constexpr KeyboardKey KeypadAdd { HID_KEYPAD_ADD };
constexpr KeyboardKey KeypadEnter { HID_KEYPAD_ENTER };
constexpr KeyboardKey Keypad1 { HID_KEYPAD_1_AND_END };
constexpr KeyboardKey Keypad2 { HID_KEYPAD_2_AND_DOWN_ARROW };
constexpr KeyboardKey Keypad3 { HID_KEYPAD_3_AND_PAGE_DOWN };
constexpr KeyboardKey Keypad4 { HID_KEYPAD_4_AND_LEFT_ARROW };
constexpr KeyboardKey Keypad5 { HID_KEYPAD_5 };
constexpr KeyboardKey Keypad6 { HID_KEYPAD_6_AND_RIGHT_ARROW };
constexpr KeyboardKey Keypad7 { HID_KEYPAD_7_AND_HOME };
constexpr KeyboardKey Keypad8 { HID_KEYPAD_8_AND_UP_ARROW };
constexpr KeyboardKey Keypad9 { HID_KEYPAD_9_AND_PAGE_UP };
constexpr KeyboardKey Keypad0 { HID_KEYPAD_0_AND_INSERT };
constexpr KeyboardKey KeypadDot { HID_KEYPAD_PERIOD_AND_DELETE };
constexpr KeyboardKey NonUsBackslashAndPipe { HID_KEYBOARD_NON_US_BACKSLASH_AND_PIPE };
constexpr KeyboardKey PcApplication { HID_KEYBOARD_APPLICATION };
constexpr KeyboardKey Power { HID_KEYBOARD_POWER };
constexpr KeyboardKey KeypadEquals { HID_KEYPAD_EQUALS };
constexpr KeyboardKey F13 { HID_KEYBOARD_F13 };
constexpr KeyboardKey F14 { HID_KEYBOARD_F14 };
constexpr KeyboardKey F15 { HID_KEYBOARD_F15 };
constexpr KeyboardKey F16 { HID_KEYBOARD_F16 };
constexpr KeyboardKey F17 { HID_KEYBOARD_F17 };
constexpr KeyboardKey F18 { HID_KEYBOARD_F18 };
constexpr KeyboardKey F19 { HID_KEYBOARD_F19 };
constexpr KeyboardKey F20 { HID_KEYBOARD_F20 };
constexpr KeyboardKey F21 { HID_KEYBOARD_F21 };
constexpr KeyboardKey F22 { HID_KEYBOARD_F22 };
constexpr KeyboardKey F23 { HID_KEYBOARD_F23 };
constexpr KeyboardKey F24 { HID_KEYBOARD_F24 };
constexpr KeyboardKey Execute { HID_KEYBOARD_EXECUTE };
constexpr KeyboardKey Help { HID_KEYBOARD_HELP };
constexpr KeyboardKey Menu { HID_KEYBOARD_MENU };
constexpr KeyboardKey Select { HID_KEYBOARD_SELECT };
constexpr KeyboardKey Stop { HID_KEYBOARD_STOP };
constexpr KeyboardKey Again { HID_KEYBOARD_AGAIN };
constexpr KeyboardKey Undo { HID_KEYBOARD_UNDO };
constexpr KeyboardKey Cut { HID_KEYBOARD_CUT };
constexpr KeyboardKey Copy { HID_KEYBOARD_COPY };
constexpr KeyboardKey Paste { HID_KEYBOARD_PASTE };
constexpr KeyboardKey Find { HID_KEYBOARD_FIND };
constexpr KeyboardKey Mute { HID_KEYBOARD_MUTE };
constexpr KeyboardKey VolumeUp { HID_KEYBOARD_VOLUME_UP };
constexpr KeyboardKey VolumeDown { HID_KEYBOARD_VOLUME_DOWN };
constexpr KeyboardKey LockingCapsLock { HID_KEYBOARD_LOCKING_CAPS_LOCK };
constexpr KeyboardKey LockingNumLock { HID_KEYBOARD_LOCKING_NUM_LOCK };
constexpr KeyboardKey LockingScrollLock { HID_KEYBOARD_LOCKING_SCROLL_LOCK };
constexpr KeyboardKey KeypadComma { HID_KEYPAD_COMMA };
constexpr KeyboardKey KeypadEqualSign { HID_KEYPAD_EQUAL_SIGN };
constexpr KeyboardKey International1 { HID_KEYBOARD_INTERNATIONAL1 };
constexpr KeyboardKey International2 { HID_KEYBOARD_INTERNATIONAL2 };
constexpr KeyboardKey International3 { HID_KEYBOARD_INTERNATIONAL3 };
constexpr KeyboardKey International4 { HID_KEYBOARD_INTERNATIONAL4 };
constexpr KeyboardKey International5 { HID_KEYBOARD_INTERNATIONAL5 };
constexpr KeyboardKey International6 { HID_KEYBOARD_INTERNATIONAL6 };
constexpr KeyboardKey International7 { HID_KEYBOARD_INTERNATIONAL7 };
constexpr KeyboardKey International8 { HID_KEYBOARD_INTERNATIONAL8 };
constexpr KeyboardKey International9 { HID_KEYBOARD_INTERNATIONAL9 };
constexpr KeyboardKey Lang1 { HID_KEYBOARD_LANG1 };
constexpr KeyboardKey Lang2 { HID_KEYBOARD_LANG2 };
constexpr KeyboardKey Lang3 { HID_KEYBOARD_LANG3 };
constexpr KeyboardKey Lang4 { HID_KEYBOARD_LANG4 };
constexpr KeyboardKey Lang5 { HID_KEYBOARD_LANG5 };
constexpr KeyboardKey Lang6 { HID_KEYBOARD_LANG6 };
constexpr KeyboardKey Lang7 { HID_KEYBOARD_LANG7 };
constexpr KeyboardKey Lang8 { HID_KEYBOARD_LANG8 };
constexpr KeyboardKey Lang9 { HID_KEYBOARD_LANG9 };
constexpr KeyboardKey AlternateErase { HID_KEYBOARD_ALTERNATE_ERASE };
constexpr KeyboardKey Sysreq { HID_KEYBOARD_SYSREQ_SLASH_ATTENTION };
constexpr KeyboardKey Cancel { HID_KEYBOARD_CANCEL };
constexpr KeyboardKey Clear { HID_KEYBOARD_CLEAR };
constexpr KeyboardKey Prior { HID_KEYBOARD_PRIOR };
constexpr KeyboardKey Return { HID_KEYBOARD_RETURN };
constexpr KeyboardKey Separator { HID_KEYBOARD_SEPARATOR };
constexpr KeyboardKey Out { HID_KEYBOARD_OUT };
constexpr KeyboardKey Oper { HID_KEYBOARD_OPER };
constexpr KeyboardKey ClearSlashAgain { HID_KEYBOARD_CLEAR_SLASH_AGAIN };
constexpr KeyboardKey CrselSlashProps { HID_KEYBOARD_CRSEL_SLASH_PROPS };
constexpr KeyboardKey Exsel { HID_KEYBOARD_EXSEL };
// Reserved	0xA5-AF
constexpr KeyboardKey Keypad00 { HID_KEYPAD_00 };
constexpr KeyboardKey Keypad000 { HID_KEYPAD_000 };
constexpr KeyboardKey ThousandsSeparator { HID_THOUSANDS_SEPARATOR };
constexpr KeyboardKey DecimalSeparator { HID_DECIMAL_SEPARATOR };
constexpr KeyboardKey CurrencyUnit { HID_CURRENCY_UNIT };
constexpr KeyboardKey CurrencySubunit { HID_CURRENCY_SUBUNIT };
constexpr KeyboardKey KeypadLeftParen { HID_KEYPAD_LEFT_PAREN };
constexpr KeyboardKey KeypadRightParen { HID_KEYPAD_RIGHT_PAREN };
constexpr KeyboardKey KeypadLeftCurlyBrace { HID_KEYPAD_LEFT_CURLY_BRACE };
constexpr KeyboardKey KeypadRightCurlyBrace { HID_KEYPAD_RIGHT_CURLY_BRACE };
constexpr KeyboardKey KeypadTab { HID_KEYPAD_TAB };
constexpr KeyboardKey KeypadBackspace { HID_KEYPAD_BACKSPACE };
constexpr KeyboardKey KeypadA { HID_KEYPAD_A };
constexpr KeyboardKey KeypadB { HID_KEYPAD_B };
constexpr KeyboardKey KeypadC { HID_KEYPAD_C };
constexpr KeyboardKey KeypadD { HID_KEYPAD_D };
constexpr KeyboardKey KeypadE { HID_KEYPAD_E };
constexpr KeyboardKey KeypadF { HID_KEYPAD_F };
constexpr KeyboardKey KeypadXor { HID_KEYPAD_XOR };
constexpr KeyboardKey KeypadCarat { HID_KEYPAD_CARAT };
constexpr KeyboardKey KeypadPercent { HID_KEYPAD_PERCENT };
constexpr KeyboardKey KeypadLessThan { HID_KEYPAD_LESS_THAN };
constexpr KeyboardKey KeypadGreaterThan { HID_KEYPAD_GREATER_THAN };
constexpr KeyboardKey KeypadAmpersand { HID_KEYPAD_AMPERSAND };
constexpr KeyboardKey KeypadDoubleampersand { HID_KEYPAD_DOUBLEAMPERSAND };
constexpr KeyboardKey KeypadPipe { HID_KEYPAD_PIPE };
constexpr KeyboardKey KeypadDoublepipe { HID_KEYPAD_DOUBLEPIPE };
constexpr KeyboardKey KeypadColon { HID_KEYPAD_COLON };
constexpr KeyboardKey KeypadPoundSign { HID_KEYPAD_POUND_SIGN };
constexpr KeyboardKey KeypadSpace { HID_KEYPAD_SPACE };
constexpr KeyboardKey KeypadAtSign { HID_KEYPAD_AT_SIGN };
constexpr KeyboardKey KeypadExclamationPoint { HID_KEYPAD_EXCLAMATION_POINT };
constexpr KeyboardKey KeypadMemoryStore { HID_KEYPAD_MEMORY_STORE };
constexpr KeyboardKey KeypadMemoryRecall { HID_KEYPAD_MEMORY_RECALL };
constexpr KeyboardKey KeypadMemoryClear { HID_KEYPAD_MEMORY_CLEAR };
constexpr KeyboardKey KeypadMemoryAdd { HID_KEYPAD_MEMORY_ADD };
constexpr KeyboardKey KeypadMemorySubtract { HID_KEYPAD_MEMORY_SUBTRACT };
constexpr KeyboardKey KeypadMemoryMultiply { HID_KEYPAD_MEMORY_MULTIPLY };
constexpr KeyboardKey KeypadMemoryDivide { HID_KEYPAD_MEMORY_DIVIDE };
constexpr KeyboardKey KeypadPlusSlashMinus { HID_KEYPAD_PLUS_SLASH_MINUS };
constexpr KeyboardKey KeypadClear { HID_KEYPAD_CLEAR };
constexpr KeyboardKey KeypadClearEntry { HID_KEYPAD_CLEAR_ENTRY };
constexpr KeyboardKey KeypadBinary { HID_KEYPAD_BINARY };
constexpr KeyboardKey KeypadOctal { HID_KEYPAD_OCTAL };
constexpr KeyboardKey KeypadDecimal { HID_KEYPAD_DECIMAL };
constexpr KeyboardKey KeypadHexadecimal { HID_KEYPAD_HEXADECIMAL };

constexpr KeyboardKey LeftControl { HID_KEYBOARD_LEFT_CONTROL };
constexpr KeyboardKey LeftShift { HID_KEYBOARD_LEFT_SHIFT };
constexpr KeyboardKey LeftAlt { HID_KEYBOARD_LEFT_ALT };
constexpr KeyboardKey LeftGui { HID_KEYBOARD_LEFT_GUI };
constexpr KeyboardKey RightControl { HID_KEYBOARD_RIGHT_CONTROL };
constexpr KeyboardKey RightShift { HID_KEYBOARD_RIGHT_SHIFT };
constexpr KeyboardKey RightAlt { HID_KEYBOARD_RIGHT_ALT };
constexpr KeyboardKey RightGui { HID_KEYBOARD_RIGHT_GUI };

//} // namespace Keyboard {

// Aliases for modifier keys
constexpr KeyboardKey l_ctl = LeftControl;
constexpr KeyboardKey l_sft = LeftShift;
constexpr KeyboardKey l_alt = LeftAlt;
constexpr KeyboardKey l_gui = LeftGui;
constexpr KeyboardKey r_ctl = RightControl;
constexpr KeyboardKey r_sft = RightShift;
constexpr KeyboardKey r_alt = RightAlt;
constexpr KeyboardKey r_gui = RightGui;

// Aliases for macOS
constexpr KeyboardKey l_opt = LeftAlt;
constexpr KeyboardKey l_cmd = LeftGui;
constexpr KeyboardKey r_opt = RightAlt;
constexpr KeyboardKey r_cmd = RightGui;

// Aliases for Windows
constexpr KeyboardKey l_win = LeftGui;
constexpr KeyboardKey r_win = RightGui;

constexpr KeyboardKey first_modifier = LeftControl;
constexpr KeyboardKey last_modifier  = RightGui;

} // namespace cKeyboardKey {

} // namespace kaleidoscope {
