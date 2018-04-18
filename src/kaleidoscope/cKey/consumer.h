// -*- c++ -*-

#pragma once

#include "HIDTables.h"
#include "kaleidoscope/Key.h"
#include "kaleidoscope/Key/Consumer.h"


namespace kaleidoscope {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`
// `const Key` object.
namespace cKey {

namespace Consumer {

constexpr ConsumerKey NumericKeyPad { HID_CONSUMER_NUMERIC_KEY_PAD };
constexpr ConsumerKey ProgrammableButtons { HID_CONSUMER_PROGRAMMABLE_BUTTONS };
constexpr ConsumerKey MicrophoneCa { HID_CONSUMER_MICROPHONE_CA };
constexpr ConsumerKey HeadphoneCa { HID_CONSUMER_HEADPHONE_CA };
constexpr ConsumerKey GraphicEqualizerCa { HID_CONSUMER_GRAPHIC_EQUALIZER_CA };

constexpr ConsumerKey Plus10 { HID_CONSUMER_PLUS_10 };
constexpr ConsumerKey Plus100 { HID_CONSUMER_PLUS_100 };
constexpr ConsumerKey AMSlashPM { HID_CONSUMER_AM_SLASH_PM };

constexpr ConsumerKey Power { HID_CONSUMER_POWER };
constexpr ConsumerKey Reset { HID_CONSUMER_RESET };
constexpr ConsumerKey Sleep { HID_CONSUMER_SLEEP };
constexpr ConsumerKey Sleep_After { HID_CONSUMER_SLEEP_AFTER };
constexpr ConsumerKey Sleep_Mode { HID_CONSUMER_SLEEP_MODE };
constexpr ConsumerKey Illumination { HID_CONSUMER_ILLUMINATION };
constexpr ConsumerKey Function_Buttons { HID_CONSUMER_FUNCTION_BUTTONS };

constexpr ConsumerKey Menu { HID_CONSUMER_MENU };
constexpr ConsumerKey MenuPick { HID_CONSUMER_MENU_PICK };
constexpr ConsumerKey MenuUp { HID_CONSUMER_MENU_UP };
constexpr ConsumerKey MenuDown { HID_CONSUMER_MENU_DOWN };
constexpr ConsumerKey MenuLeft { HID_CONSUMER_MENU_LEFT };
constexpr ConsumerKey MenuRight { HID_CONSUMER_MENU_RIGHT };
constexpr ConsumerKey MenuEscape { HID_CONSUMER_MENU_ESCAPE };
constexpr ConsumerKey MenuValueIncrease { HID_CONSUMER_MENU_VALUE_INCREASE };
constexpr ConsumerKey MenuValueDecrease { HID_CONSUMER_MENU_VALUE_DECREASE };

constexpr ConsumerKey DataOnScreen { HID_CONSUMER_DATA_ON_SCREEN };
constexpr ConsumerKey ClosedCaption { HID_CONSUMER_CLOSED_CAPTION };
constexpr ConsumerKey ClosedCaptionSelect { HID_CONSUMER_CLOSED_CAPTION_SELECT };
constexpr ConsumerKey VCRSlashTV { HID_CONSUMER_VCR_SLASH_TV };
constexpr ConsumerKey BroadcastMode { HID_CONSUMER_BROADCAST_MODE };
constexpr ConsumerKey SNapshot { HID_CONSUMER_SNAPSHOT };
constexpr ConsumerKey Still { HID_CONSUMER_STILL };

constexpr ConsumerKey Selection { HID_CONSUMER_SELECTION };
constexpr ConsumerKey AssignSelection { HID_CONSUMER_ASSIGN_SELECTION };
constexpr ConsumerKey ModeStep { HID_CONSUMER_MODE_STEP };
constexpr ConsumerKey RecallLast { HID_CONSUMER_RECALL_LAST };
constexpr ConsumerKey EnterChannel { HID_CONSUMER_ENTER_CHANNEL };
constexpr ConsumerKey OrderMovie { HID_CONSUMER_ORDER_MOVIE };
constexpr ConsumerKey Channel { HID_CONSUMER_CHANNEL };
constexpr ConsumerKey MediaSelection { HID_CONSUMER_MEDIA_SELECTION };
constexpr ConsumerKey MediaSelectComputer { HID_CONSUMER_MEDIA_SELECT_COMPUTER };
constexpr ConsumerKey MediaSelectTV { HID_CONSUMER_MEDIA_SELECT_TV };
constexpr ConsumerKey MediaSelectWww { HID_CONSUMER_MEDIA_SELECT_WWW };
constexpr ConsumerKey MediaSelectDvd { HID_CONSUMER_MEDIA_SELECT_DVD };
constexpr ConsumerKey MediaSelectTelephone { HID_CONSUMER_MEDIA_SELECT_TELEPHONE };
constexpr ConsumerKey MediaSelectProgramGuide { HID_CONSUMER_MEDIA_SELECT_PROGRAM_GUIDE };
constexpr ConsumerKey MediaSelectVideoPhone { HID_CONSUMER_MEDIA_SELECT_VIDEO_PHONE };
constexpr ConsumerKey MediaSelectGames { HID_CONSUMER_MEDIA_SELECT_GAMES };
constexpr ConsumerKey MediaSelectMessages { HID_CONSUMER_MEDIA_SELECT_MESSAGES };
constexpr ConsumerKey MediaSelectCd { HID_CONSUMER_MEDIA_SELECT_CD };
constexpr ConsumerKey MediaSelectVcr { HID_CONSUMER_MEDIA_SELECT_VCR };
constexpr ConsumerKey MediaSelectTuner { HID_CONSUMER_MEDIA_SELECT_TUNER };
constexpr ConsumerKey Quit { HID_CONSUMER_QUIT };
constexpr ConsumerKey Help { HID_CONSUMER_HELP };
constexpr ConsumerKey MediaSelectTape { HID_CONSUMER_MEDIA_SELECT_TAPE };
constexpr ConsumerKey MediaSelectCable { HID_CONSUMER_MEDIA_SELECT_CABLE };
constexpr ConsumerKey MediaSelectSatellite { HID_CONSUMER_MEDIA_SELECT_SATELLITE };
constexpr ConsumerKey MediaSelectSecurity { HID_CONSUMER_MEDIA_SELECT_SECURITY };
constexpr ConsumerKey MediaSelectHome { HID_CONSUMER_MEDIA_SELECT_HOME };
constexpr ConsumerKey MediaSelectCall { HID_CONSUMER_MEDIA_SELECT_CALL };
constexpr ConsumerKey ChannelIncrement { HID_CONSUMER_CHANNEL_INCREMENT };
constexpr ConsumerKey ChannelDecrement { HID_CONSUMER_CHANNEL_DECREMENT };
constexpr ConsumerKey MediaSelectSap { HID_CONSUMER_MEDIA_SELECT_SAP };

constexpr ConsumerKey VcrPlus { HID_CONSUMER_VCR_PLUS };
constexpr ConsumerKey Once { HID_CONSUMER_ONCE };
constexpr ConsumerKey Daily { HID_CONSUMER_DAILY };
constexpr ConsumerKey Weekly { HID_CONSUMER_WEEKLY };
constexpr ConsumerKey Monthly { HID_CONSUMER_MONTHLY };

constexpr ConsumerKey Play { HID_CONSUMER_PLAY };
constexpr ConsumerKey Pause { HID_CONSUMER_PAUSE };
constexpr ConsumerKey Record { HID_CONSUMER_RECORD };
constexpr ConsumerKey FastForward { HID_CONSUMER_FAST_FORWARD };
constexpr ConsumerKey Rewind { HID_CONSUMER_REWIND };
constexpr ConsumerKey ScanNextTrack { HID_CONSUMER_SCAN_NEXT_TRACK };
constexpr ConsumerKey ScanPreviousTrack { HID_CONSUMER_SCAN_PREVIOUS_TRACK };
constexpr ConsumerKey Stop { HID_CONSUMER_STOP };
constexpr ConsumerKey Eject { HID_CONSUMER_EJECT };
constexpr ConsumerKey RandomPlay { HID_CONSUMER_RANDOM_PLAY };
constexpr ConsumerKey SelectDisc { HID_CONSUMER_SELECT_DISC };
constexpr ConsumerKey EnterDiscMc { HID_CONSUMER_ENTER_DISC_MC };
constexpr ConsumerKey Repeat { HID_CONSUMER_REPEAT };
constexpr ConsumerKey Tracking { HID_CONSUMER_TRACKING };
constexpr ConsumerKey Track_Normal { HID_CONSUMER_TRACK_NORMAL };
constexpr ConsumerKey SlowTracking { HID_CONSUMER_SLOW_TRACKING };
constexpr ConsumerKey FrameForward { HID_CONSUMER_FRAME_FORWARD };
constexpr ConsumerKey FrameBack { HID_CONSUMER_FRAME_BACK };
constexpr ConsumerKey Mark { HID_CONSUMER_MARK };
constexpr ConsumerKey ClearMark { HID_CONSUMER_CLEAR_MARK };
constexpr ConsumerKey RepeatFromMark { HID_CONSUMER_REPEAT_FROM_MARK };
constexpr ConsumerKey ReturnTo_Mark { HID_CONSUMER_RETURN_TO_MARK };
constexpr ConsumerKey SearchMarkForward { HID_CONSUMER_SEARCH_MARK_FORWARD };
constexpr ConsumerKey SearchMarkBackwards { HID_CONSUMER_SEARCH_MARK_BACKWARDS };
constexpr ConsumerKey CounterReset { HID_CONSUMER_COUNTER_RESET };
constexpr ConsumerKey ShowCounter { HID_CONSUMER_SHOW_COUNTER };
constexpr ConsumerKey TrackingIncrement { HID_CONSUMER_TRACKING_INCREMENT };
constexpr ConsumerKey TrackingDecrement { HID_CONSUMER_TRACKING_DECREMENT };
constexpr ConsumerKey StopSlashEject { HID_CONSUMER_STOP_SLASH_EJECT };
constexpr ConsumerKey PlaySlashPause { HID_CONSUMER_PLAY_SLASH_PAUSE };
constexpr ConsumerKey PlaySlashSkip { HID_CONSUMER_PLAY_SLASH_SKIP };
constexpr ConsumerKey Volume { HID_CONSUMER_VOLUME };
constexpr ConsumerKey Balance { HID_CONSUMER_BALANCE };
constexpr ConsumerKey Mute { HID_CONSUMER_MUTE };
constexpr ConsumerKey Bass { HID_CONSUMER_BASS };
constexpr ConsumerKey Treble { HID_CONSUMER_TREBLE };
constexpr ConsumerKey BassBoost { HID_CONSUMER_BASS_BOOST };
constexpr ConsumerKey SurroundMode { HID_CONSUMER_SURROUND_MODE };
constexpr ConsumerKey Loudness { HID_CONSUMER_LOUDNESS };
constexpr ConsumerKey Mpx { HID_CONSUMER_MPX };
constexpr ConsumerKey VolumeIncrement { HID_CONSUMER_VOLUME_INCREMENT };


constexpr ConsumerKey VolumeDecrement { HID_CONSUMER_VOLUME_DECREMENT };

constexpr ConsumerKey SpeedSelect { HID_CONSUMER_SPEED_SELECT };
constexpr ConsumerKey PlaybackSpeed { HID_CONSUMER_PLAYBACK_SPEED };
constexpr ConsumerKey StandardPlay { HID_CONSUMER_STANDARD_PLAY };
constexpr ConsumerKey LongPlay { HID_CONSUMER_LONG_PLAY };
constexpr ConsumerKey ExtendedPlay { HID_CONSUMER_EXTENDED_PLAY };
constexpr ConsumerKey Slow { HID_CONSUMER_SLOW };

constexpr ConsumerKey FanEnable { HID_CONSUMER_FAN_ENABLE };
constexpr ConsumerKey FanSpeed { HID_CONSUMER_FAN_SPEED };
constexpr ConsumerKey LightEnable { HID_CONSUMER_LIGHT_ENABLE };
constexpr ConsumerKey LightIlluminationLevel { HID_CONSUMER_LIGHT_ILLUMINATION_LEVEL };
constexpr ConsumerKey ClimateControlEnable { HID_CONSUMER_CLIMATE_CONTROL_ENABLE };
constexpr ConsumerKey RoomTemperature { HID_CONSUMER_ROOM_TEMPERATURE };
constexpr ConsumerKey SecurityEnable { HID_CONSUMER_SECURITY_ENABLE };
constexpr ConsumerKey FireAlarm { HID_CONSUMER_FIRE_ALARM };
constexpr ConsumerKey PoliceAlarm { HID_CONSUMER_POLICE_ALARM };
constexpr ConsumerKey Proximity { HID_CONSUMER_PROXIMITY };
constexpr ConsumerKey Motion { HID_CONSUMER_MOTION };
constexpr ConsumerKey DuressAlarm { HID_CONSUMER_DURESS_ALARM };
constexpr ConsumerKey HoldupAlarm { HID_CONSUMER_HOLDUP_ALARM };
constexpr ConsumerKey MedicalAlarm { HID_CONSUMER_MEDICAL_ALARM };

constexpr ConsumerKey BalanceRight { HID_CONSUMER_BALANCE_RIGHT };
constexpr ConsumerKey BalanceLeft { HID_CONSUMER_BALANCE_LEFT };
constexpr ConsumerKey BassIncrement { HID_CONSUMER_BASS_INCREMENT };
constexpr ConsumerKey BassDecrement { HID_CONSUMER_BASS_DECREMENT };
constexpr ConsumerKey TrebleIncrement { HID_CONSUMER_TREBLE_INCREMENT };
constexpr ConsumerKey TrebleDecrement { HID_CONSUMER_TREBLE_DECREMENT };

constexpr ConsumerKey SpeakerSystem { HID_CONSUMER_SPEAKER_SYSTEM };
constexpr ConsumerKey ChannelLeft { HID_CONSUMER_CHANNEL_LEFT };
constexpr ConsumerKey ChannelRight { HID_CONSUMER_CHANNEL_RIGHT };
constexpr ConsumerKey ChannelCenter { HID_CONSUMER_CHANNEL_CENTER };
constexpr ConsumerKey ChannelFront { HID_CONSUMER_CHANNEL_FRONT };
constexpr ConsumerKey ChannelCenterFront { HID_CONSUMER_CHANNEL_CENTER_FRONT };
constexpr ConsumerKey ChannelSide { HID_CONSUMER_CHANNEL_SIDE };
constexpr ConsumerKey ChannelSurround { HID_CONSUMER_CHANNEL_SURROUND };
constexpr ConsumerKey ChannelLowFrequencyEnhancement { HID_CONSUMER_CHANNEL_LOW_FREQUENCY_ENHANCEMENT };
constexpr ConsumerKey ChannelTop { HID_CONSUMER_CHANNEL_TOP };
constexpr ConsumerKey ChannelUnknown { HID_CONSUMER_CHANNEL_UNKNOWN };

constexpr ConsumerKey SubChannel { HID_CONSUMER_SUB_CHANNEL };
constexpr ConsumerKey SubChannelIncrement { HID_CONSUMER_SUB_CHANNEL_INCREMENT };
constexpr ConsumerKey SubChannelDecrement { HID_CONSUMER_SUB_CHANNEL_DECREMENT };
constexpr ConsumerKey AlternateAudioIncrement { HID_CONSUMER_ALTERNATE_AUDIO_INCREMENT };
constexpr ConsumerKey AlternateAudioDecrement { HID_CONSUMER_ALTERNATE_AUDIO_DECREMENT };

constexpr ConsumerKey Application_Launch_Buttons { HID_CONSUMER_APPLICATION_LAUNCH_BUTTONS };
constexpr ConsumerKey AL_Launch_Button_Configuration_Tool { HID_CONSUMER_AL_LAUNCH_BUTTON_CONFIGURATION_TOOL };
constexpr ConsumerKey AL_Programmable_Button_Configuration { HID_CONSUMER_AL_PROGRAMMABLE_BUTTON_CONFIGURATION };
constexpr ConsumerKey AL_Consumer_Control_Configuration { HID_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION };
constexpr ConsumerKey AL_Word_Processor { HID_CONSUMER_AL_WORD_PROCESSOR };
constexpr ConsumerKey AL_Text_Editor { HID_CONSUMER_AL_TEXT_EDITOR };
constexpr ConsumerKey AL_Spreadsheet { HID_CONSUMER_AL_SPREADSHEET };
constexpr ConsumerKey AL_Graphics_Editor { HID_CONSUMER_AL_GRAPHICS_EDITOR };
constexpr ConsumerKey AL_Presentation_App { HID_CONSUMER_AL_PRESENTATION_APP };
constexpr ConsumerKey AL_Database_App { HID_CONSUMER_AL_DATABASE_APP };
constexpr ConsumerKey AL_Email_Reader { HID_CONSUMER_AL_EMAIL_READER };
constexpr ConsumerKey AL_Newsreader { HID_CONSUMER_AL_NEWSREADER };
constexpr ConsumerKey AL_Voicemail { HID_CONSUMER_AL_VOICEMAIL };
constexpr ConsumerKey AL_Contacts_Slash_Address_Book { HID_CONSUMER_AL_CONTACTS_SLASH_ADDRESS_BOOK };
constexpr ConsumerKey AL_Calendar_Slash_Schedule { HID_CONSUMER_AL_CALENDAR_SLASH_SCHEDULE };
constexpr ConsumerKey AL_Task_Slash_Project_Manager { HID_CONSUMER_AL_TASK_SLASH_PROJECT_MANAGER };
constexpr ConsumerKey AL_Log_Slash_Journal_Slash_Timecard { HID_CONSUMER_AL_LOG_SLASH_JOURNAL_SLASH_TIMECARD };
constexpr ConsumerKey AL_Checkbook_Slash_Finance { HID_CONSUMER_AL_CHECKBOOK_SLASH_FINANCE };
constexpr ConsumerKey AL_Calculator { HID_CONSUMER_AL_CALCULATOR };
constexpr ConsumerKey AL_AVCaptureSlashPlayback { HID_CONSUMER_AL_A_SLASH_V_CAPTURE_SLASH_PLAYBACK };
constexpr ConsumerKey AL_Local_MachineBrowser { HID_CONSUMER_AL_LOCAL_MACHINE_BROWSER };
constexpr ConsumerKey AL_Lan_SlashWanBrowser { HID_CONSUMER_AL_LAN_SLASH_WAN_BROWSER };
constexpr ConsumerKey AL_InternetBrowser { HID_CONSUMER_AL_INTERNET_BROWSER };
constexpr ConsumerKey AL_RemoteNetworkingSlashIspConnect { HID_CONSUMER_AL_REMOTE_NETWORKING_SLASH_ISP_CONNECT };
constexpr ConsumerKey AL_NetworkConference { HID_CONSUMER_AL_NETWORK_CONFERENCE };
constexpr ConsumerKey AL_NetworkChat { HID_CONSUMER_AL_NETWORK_CHAT };
constexpr ConsumerKey AL_TelephonySlashDialer { HID_CONSUMER_AL_TELEPHONY_SLASH_DIALER };
constexpr ConsumerKey AL_Logon { HID_CONSUMER_AL_LOGON };
constexpr ConsumerKey AL_Logoff { HID_CONSUMER_AL_LOGOFF };
constexpr ConsumerKey AL_LogonSlashLogoff { HID_CONSUMER_AL_LOGON_SLASH_LOGOFF };
constexpr ConsumerKey AL_TerminalLockSlashScreensaver { HID_CONSUMER_AL_TERMINAL_LOCK_SLASH_SCREENSAVER };
constexpr ConsumerKey AL_ControlPanel { HID_CONSUMER_AL_CONTROL_PANEL };
constexpr ConsumerKey AL_CommandLineProcessorSlashRun { HID_CONSUMER_AL_COMMAND_LINE_PROCESSOR_SLASH_RUN };
constexpr ConsumerKey AL_ProcessSlashTask_Manager { HID_CONSUMER_AL_PROCESS_SLASH_TASK_MANAGER };
constexpr ConsumerKey AL_SelectTaskSlashApplication { HID_CONSUMER_AL_SELECT_TASK_SLASH_APPLICATION };
constexpr ConsumerKey AL_NextTaskSlashApplication { HID_CONSUMER_AL_NEXT_TASK_SLASH_APPLICATION };
constexpr ConsumerKey AL_PreviousTaskSlashApplication { HID_CONSUMER_AL_PREVIOUS_TASK_SLASH_APPLICATION };
constexpr ConsumerKey AL_PreemptiveHaltTaskSlashApplication { HID_CONSUMER_AL_PREEMPTIVE_HALT_TASK_SLASH_APPLICATION };
constexpr ConsumerKey AL_IntegratedHelpCenter { HID_CONSUMER_AL_INTEGRATED_HELP_CENTER };
constexpr ConsumerKey AL_Documents { HID_CONSUMER_AL_DOCUMENTS };
constexpr ConsumerKey AL_Thesaurus { HID_CONSUMER_AL_THESAURUS };
constexpr ConsumerKey AL_Dictionary { HID_CONSUMER_AL_DICTIONARY };
constexpr ConsumerKey AL_Desktop { HID_CONSUMER_AL_DESKTOP };
constexpr ConsumerKey AL_SpellCheck { HID_CONSUMER_AL_SPELL_CHECK };
constexpr ConsumerKey AL_GrammarCheck { HID_CONSUMER_AL_GRAMMAR_CHECK };
constexpr ConsumerKey AL_WirelessStatus { HID_CONSUMER_AL_WIRELESS_STATUS };
constexpr ConsumerKey AL_KeyboardLayout { HID_CONSUMER_AL_KEYBOARD_LAYOUT };
constexpr ConsumerKey AL_VirusProtection { HID_CONSUMER_AL_VIRUS_PROTECTION };
constexpr ConsumerKey AL_Encryption { HID_CONSUMER_AL_ENCRYPTION };
constexpr ConsumerKey AL_ScreenSaver { HID_CONSUMER_AL_SCREEN_SAVER };
constexpr ConsumerKey AL_Alarms { HID_CONSUMER_AL_ALARMS };
constexpr ConsumerKey AL_Clock { HID_CONSUMER_AL_CLOCK };
constexpr ConsumerKey AL_FileBrowser { HID_CONSUMER_AL_FILE_BROWSER };
constexpr ConsumerKey AL_PowerStatus { HID_CONSUMER_AL_POWER_STATUS };
constexpr ConsumerKey AL_ImageBrowser { HID_CONSUMER_AL_IMAGE_BROWSER };
constexpr ConsumerKey AL_AudioBrowser { HID_CONSUMER_AL_AUDIO_BROWSER };
constexpr ConsumerKey AL_MovieBrowser { HID_CONSUMER_AL_MOVIE_BROWSER };
constexpr ConsumerKey AL_DigitalRightsManager { HID_CONSUMER_AL_DIGITAL_RIGHTS_MANAGER };
constexpr ConsumerKey AL_DigitalWallet { HID_CONSUMER_AL_DIGITAL_WALLET };

constexpr ConsumerKey AL_InstantMessaging { HID_CONSUMER_AL_INSTANT_MESSAGING };
constexpr ConsumerKey AL_OemFeaturesSlashTipsSlashTUTORIALBrowser { HID_CONSUMER_AL_OEM_FEATURES_SLASH__TIPS_SLASH_TUTORIAL_BROWSER };
constexpr ConsumerKey AL_OemHelp { HID_CONSUMER_AL_OEM_HELP };
constexpr ConsumerKey AL_OnlineCommunity { HID_CONSUMER_AL_ONLINE_COMMUNITY };
constexpr ConsumerKey AL_Entertainment_Content_Browser { HID_CONSUMER_AL_ENTERTAINMENT_CONTENT_BROWSER };
constexpr ConsumerKey AL_OnlineShoppingBrowser { HID_CONSUMER_AL_ONLINE_SHOPPING_BROWSER };
constexpr ConsumerKey AL_SmartcardInformationSlashHelp { HID_CONSUMER_AL_SMARTCARD_INFORMATION_SLASH_HELP };
constexpr ConsumerKey AL_MarketMonitorSlashFinanceBrowser { HID_CONSUMER_AL_MARKET_MONITOR_SLASH_FINANCE_BROWSER };
constexpr ConsumerKey AL_CustomizedCorporateNewsBrowser { HID_CONSUMER_AL_CUSTOMIZED_CORPORATE_NEWS_BROWSER };
constexpr ConsumerKey AL_OnlineActivityBrowser { HID_CONSUMER_AL_ONLINE_ACTIVITY_BROWSER };
constexpr ConsumerKey AL_ResearchSlashSearchBrowser { HID_CONSUMER_AL_RESEARCH_SLASH_SEARCH_BROWSER };
constexpr ConsumerKey AL_AudioPlayer { HID_CONSUMER_AL_AUDIO_PLAYER };

constexpr ConsumerKey GenericGuiApplicationControls { HID_CONSUMER_GENERIC_GUI_APPLICATION_CONTROLS };
constexpr ConsumerKey AC_New { HID_CONSUMER_AC_NEW };
constexpr ConsumerKey AC_Open { HID_CONSUMER_AC_OPEN };
constexpr ConsumerKey AC_Close { HID_CONSUMER_AC_CLOSE };
constexpr ConsumerKey AC_Exit { HID_CONSUMER_AC_EXIT };
constexpr ConsumerKey AC_Maximize { HID_CONSUMER_AC_MAXIMIZE };
constexpr ConsumerKey AC_Minimize { HID_CONSUMER_AC_MINIMIZE };
constexpr ConsumerKey AC_Save { HID_CONSUMER_AC_SAVE };
constexpr ConsumerKey AC_Print { HID_CONSUMER_AC_PRINT };
constexpr ConsumerKey AC_Properties { HID_CONSUMER_AC_PROPERTIES };
constexpr ConsumerKey AC_Undo { HID_CONSUMER_AC_UNDO };
constexpr ConsumerKey AC_Copy { HID_CONSUMER_AC_COPY };
constexpr ConsumerKey AC_Cut { HID_CONSUMER_AC_CUT };
constexpr ConsumerKey AC_Paste { HID_CONSUMER_AC_PASTE };
constexpr ConsumerKey AC_SelectAll { HID_CONSUMER_AC_SELECT_ALL };
constexpr ConsumerKey AC_Find { HID_CONSUMER_AC_FIND };
constexpr ConsumerKey AC_FindAndReplace { HID_CONSUMER_AC_FIND_AND_REPLACE };
constexpr ConsumerKey AC_Search { HID_CONSUMER_AC_SEARCH };
constexpr ConsumerKey AC_GoTo { HID_CONSUMER_AC_GO_TO };
constexpr ConsumerKey AC_Home { HID_CONSUMER_AC_HOME };
constexpr ConsumerKey AC_Back { HID_CONSUMER_AC_BACK };
constexpr ConsumerKey AC_Forward { HID_CONSUMER_AC_FORWARD };
constexpr ConsumerKey AC_Stop { HID_CONSUMER_AC_STOP };
constexpr ConsumerKey AC_Refresh { HID_CONSUMER_AC_REFRESH };
constexpr ConsumerKey AC_PreviousLink { HID_CONSUMER_AC_PREVIOUS_LINK };
constexpr ConsumerKey AC_NextLink { HID_CONSUMER_AC_NEXT_LINK };
constexpr ConsumerKey AC_Bookmarks { HID_CONSUMER_AC_BOOKMARKS };
constexpr ConsumerKey AC_History { HID_CONSUMER_AC_HISTORY };
constexpr ConsumerKey AC_Subscriptions { HID_CONSUMER_AC_SUBSCRIPTIONS };
constexpr ConsumerKey AC_ZoomIn { HID_CONSUMER_AC_ZOOM_IN };
constexpr ConsumerKey AC_ZoomOut { HID_CONSUMER_AC_ZOOM_OUT };
constexpr ConsumerKey AC_Zoom { HID_CONSUMER_AC_ZOOM };
constexpr ConsumerKey AC_FullSCreenView { HID_CONSUMER_AC_FULL_SCREEN_VIEW };
constexpr ConsumerKey AC_NormalView { HID_CONSUMER_AC_NORMAL_VIEW };
constexpr ConsumerKey AC_ViewToggle { HID_CONSUMER_AC_VIEW_TOGGLE };
constexpr ConsumerKey AC_ScrollUp { HID_CONSUMER_AC_SCROLL_UP };
constexpr ConsumerKey AC_ScrollDown { HID_CONSUMER_AC_SCROLL_DOWN };
constexpr ConsumerKey AC_Scroll { HID_CONSUMER_AC_SCROLL };
constexpr ConsumerKey AC_PanLeft { HID_CONSUMER_AC_PAN_LEFT };
constexpr ConsumerKey AC_PanRight { HID_CONSUMER_AC_PAN_RIGHT };
constexpr ConsumerKey AC_Pan { HID_CONSUMER_AC_PAN };
constexpr ConsumerKey AC_NewWindow { HID_CONSUMER_AC_NEW_WINDOW };
constexpr ConsumerKey AC_TileHorizontally { HID_CONSUMER_AC_TILE_HORIZONTALLY };
constexpr ConsumerKey AC_TileVertically { HID_CONSUMER_AC_TILE_VERTICALLY };
constexpr ConsumerKey AC_Format { HID_CONSUMER_AC_FORMAT };
constexpr ConsumerKey AC_Edit { HID_CONSUMER_AC_EDIT };
constexpr ConsumerKey AC_Bold { HID_CONSUMER_AC_BOLD };
constexpr ConsumerKey AC_Italics { HID_CONSUMER_AC_ITALICS };
constexpr ConsumerKey AC_Underline { HID_CONSUMER_AC_UNDERLINE };
constexpr ConsumerKey AC_Strikethrough { HID_CONSUMER_AC_STRIKETHROUGH };
constexpr ConsumerKey AC_Subscript { HID_CONSUMER_AC_SUBSCRIPT };
constexpr ConsumerKey AC_Superscript { HID_CONSUMER_AC_SUPERSCRIPT };
constexpr ConsumerKey AC_AllCaps { HID_CONSUMER_AC_ALL_CAPS };
constexpr ConsumerKey AC_Rotate { HID_CONSUMER_AC_ROTATE };
constexpr ConsumerKey AC_Resize { HID_CONSUMER_AC_RESIZE };
constexpr ConsumerKey AC_FlipHorizontal { HID_CONSUMER_AC_FLIP_HORIZONTAL };
constexpr ConsumerKey AC_FlipVertical { HID_CONSUMER_AC_FLIP_VERTICAL };
constexpr ConsumerKey AC_MirrorHorizontal { HID_CONSUMER_AC_MIRROR_HORIZONTAL };
constexpr ConsumerKey AC_MirrorVertical { HID_CONSUMER_AC_MIRROR_VERTICAL };
constexpr ConsumerKey AC_FontSelect { HID_CONSUMER_AC_FONT_SELECT };
constexpr ConsumerKey AC_FontColor { HID_CONSUMER_AC_FONT_COLOR };
constexpr ConsumerKey AC_FontSize { HID_CONSUMER_AC_FONT_SIZE };
constexpr ConsumerKey AC_JustifyLeft { HID_CONSUMER_AC_JUSTIFY_LEFT };
constexpr ConsumerKey AC_JustifyCenterH { HID_CONSUMER_AC_JUSTIFY_CENTER_H };
constexpr ConsumerKey AC_JustifyRight { HID_CONSUMER_AC_JUSTIFY_RIGHT };
constexpr ConsumerKey AC_JustifyBlockH { HID_CONSUMER_AC_JUSTIFY_BLOCK_H };
constexpr ConsumerKey AC_JustifyTop { HID_CONSUMER_AC_JUSTIFY_TOP };
constexpr ConsumerKey AC_JustifyCenterV { HID_CONSUMER_AC_JUSTIFY_CENTER_V };
constexpr ConsumerKey AC_JustifyBottom { HID_CONSUMER_AC_JUSTIFY_BOTTOM };
constexpr ConsumerKey AC_JustifyBlockV { HID_CONSUMER_AC_JUSTIFY_BLOCK_V };
constexpr ConsumerKey AC_IndentDecrease { HID_CONSUMER_AC_INDENT_DECREASE };
constexpr ConsumerKey AC_IndentIncrease { HID_CONSUMER_AC_INDENT_INCREASE };
constexpr ConsumerKey AC_NumberedList { HID_CONSUMER_AC_NUMBERED_LIST };
constexpr ConsumerKey AC_RestartNumbering { HID_CONSUMER_AC_RESTART_NUMBERING };
constexpr ConsumerKey AC_BulletedList { HID_CONSUMER_AC_BULLETED_LIST };
constexpr ConsumerKey AC_Promote { HID_CONSUMER_AC_PROMOTE };
constexpr ConsumerKey AC_Demote { HID_CONSUMER_AC_DEMOTE };
constexpr ConsumerKey AC_Yes { HID_CONSUMER_AC_YES };
constexpr ConsumerKey AC_No { HID_CONSUMER_AC_NO };
constexpr ConsumerKey AC_Cancel { HID_CONSUMER_AC_CANCEL };
constexpr ConsumerKey AC_Catalog { HID_CONSUMER_AC_CATALOG };
constexpr ConsumerKey AC_BuySlashCheckout { HID_CONSUMER_AC_BUY_SLASH_CHECKOUT };
constexpr ConsumerKey AC_AddToCart { HID_CONSUMER_AC_ADD_TO_CART };
constexpr ConsumerKey AC_Expand { HID_CONSUMER_AC_EXPAND };
constexpr ConsumerKey AC_ExpandAll { HID_CONSUMER_AC_EXPAND_ALL };
constexpr ConsumerKey AC_Collapse { HID_CONSUMER_AC_COLLAPSE };
constexpr ConsumerKey AC_CollapseAll { HID_CONSUMER_AC_COLLAPSE_ALL };
constexpr ConsumerKey AC_PrintPreview { HID_CONSUMER_AC_PRINT_PREVIEW };
constexpr ConsumerKey AC_PasteSpecial { HID_CONSUMER_AC_PASTE_SPECIAL };
constexpr ConsumerKey AC_InsertMode { HID_CONSUMER_AC_INSERT_MODE };
constexpr ConsumerKey AC_Delete { HID_CONSUMER_AC_DELETE };
constexpr ConsumerKey AC_Lock { HID_CONSUMER_AC_LOCK };
constexpr ConsumerKey AC_Unlock { HID_CONSUMER_AC_UNLOCK };
constexpr ConsumerKey AC_Protect { HID_CONSUMER_AC_PROTECT };
constexpr ConsumerKey AC_Unprotect { HID_CONSUMER_AC_UNPROTECT };
constexpr ConsumerKey AC_AttachComment { HID_CONSUMER_AC_ATTACH_COMMENT };
constexpr ConsumerKey AC_DeleteComment { HID_CONSUMER_AC_DELETE_COMMENT };
constexpr ConsumerKey AC_ViewComment { HID_CONSUMER_AC_VIEW_COMMENT };
constexpr ConsumerKey AC_SelectWord { HID_CONSUMER_AC_SELECT_WORD };
constexpr ConsumerKey AC_SelectSentence { HID_CONSUMER_AC_SELECT_SENTENCE };
constexpr ConsumerKey AC_SelectParagraph { HID_CONSUMER_AC_SELECT_PARAGRAPH };
constexpr ConsumerKey AC_SelectColumn { HID_CONSUMER_AC_SELECT_COLUMN };
constexpr ConsumerKey AC_SelectRow { HID_CONSUMER_AC_SELECT_ROW };
constexpr ConsumerKey AC_SelectTable { HID_CONSUMER_AC_SELECT_TABLE };
constexpr ConsumerKey AC_SelectObject { HID_CONSUMER_AC_SELECT_OBJECT };
constexpr ConsumerKey AC_RedoSlashRepeat { HID_CONSUMER_AC_REDO_SLASH_REPEAT };
constexpr ConsumerKey AC_Sort { HID_CONSUMER_AC_SORT };
constexpr ConsumerKey AC_Sort_Ascending { HID_CONSUMER_AC_SORT_ASCENDING };
constexpr ConsumerKey AC_Sort_Descending { HID_CONSUMER_AC_SORT_DESCENDING };
constexpr ConsumerKey AC_Filter { HID_CONSUMER_AC_FILTER };
constexpr ConsumerKey AC_SetClock { HID_CONSUMER_AC_SET_CLOCK };
constexpr ConsumerKey AC_ViewClock { HID_CONSUMER_AC_VIEW_CLOCK };
constexpr ConsumerKey AC_SelectTimeZone { HID_CONSUMER_AC_SELECT_TIME_ZONE };
constexpr ConsumerKey AC_EditTimeZones { HID_CONSUMER_AC_EDIT_TIME_ZONES };
constexpr ConsumerKey AC_SetAlarm { HID_CONSUMER_AC_SET_ALARM };
constexpr ConsumerKey AC_ClearAlarm { HID_CONSUMER_AC_CLEAR_ALARM };
constexpr ConsumerKey AC_SnoozeAlarm { HID_CONSUMER_AC_SNOOZE_ALARM };
constexpr ConsumerKey AC_ResetAlarm { HID_CONSUMER_AC_RESET_ALARM };
constexpr ConsumerKey AC_Synchronize { HID_CONSUMER_AC_SYNCHRONIZE };
constexpr ConsumerKey AC_SendSlashReceive { HID_CONSUMER_AC_SEND_SLASH_RECEIVE };
constexpr ConsumerKey AC_SendTo { HID_CONSUMER_AC_SEND_TO };
constexpr ConsumerKey AC_Reply { HID_CONSUMER_AC_REPLY };
constexpr ConsumerKey AC_ReplyAll { HID_CONSUMER_AC_REPLY_ALL };
constexpr ConsumerKey AC_ForwardMsg { HID_CONSUMER_AC_FORWARD_MSG };
constexpr ConsumerKey AC_Send { HID_CONSUMER_AC_SEND };
constexpr ConsumerKey AC_AttachFile { HID_CONSUMER_AC_ATTACH_FILE };
constexpr ConsumerKey AC_Upload { HID_CONSUMER_AC_UPLOAD };
constexpr ConsumerKey AC_Download { HID_CONSUMER_AC_DOWNLOAD };
constexpr ConsumerKey AC_SetBorders { HID_CONSUMER_AC_SET_BORDERS };
constexpr ConsumerKey AC_InsertRow { HID_CONSUMER_AC_INSERT_ROW };
constexpr ConsumerKey AC_InsertColumn { HID_CONSUMER_AC_INSERT_COLUMN };
constexpr ConsumerKey AC_InsertFile { HID_CONSUMER_AC_INSERT_FILE };
constexpr ConsumerKey AC_InsertPicture { HID_CONSUMER_AC_INSERT_PICTURE };
constexpr ConsumerKey AC_InsertObject { HID_CONSUMER_AC_INSERT_OBJECT };
constexpr ConsumerKey AC_InsertSymbol { HID_CONSUMER_AC_INSERT_SYMBOL };
constexpr ConsumerKey AC_SaveandClose { HID_CONSUMER_AC_SAVE_AND_CLOSE };
constexpr ConsumerKey AC_Rename { HID_CONSUMER_AC_RENAME };
constexpr ConsumerKey AC_Merge { HID_CONSUMER_AC_MERGE };
constexpr ConsumerKey AC_Split { HID_CONSUMER_AC_SPLIT };
constexpr ConsumerKey AC_Distribute_Horizontally { HID_CONSUMER_AC_DISTRIBUTE_HORIZONTALLY };
constexpr ConsumerKey AC_Distribute_Vertically { HID_CONSUMER_AC_DISTRIBUTE_VERTICALLY };

} // namespace consumer {

} // namespace cKey {

} // namespace kaleidoscope {
