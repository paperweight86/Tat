#pragma once

#define UTI_KEYBOARD_LBUTTON        0x01
#define UTI_KEYBOARD_RBUTTON        0x02
#define UTI_KEYBOARD_CANCEL         0x03
#define UTI_KEYBOARD_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define UTI_KEYBOARD_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define UTI_KEYBOARD_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

/*
* 0x07 : unassigned
*/

#define UTI_KEYBOARD_BACK           0x08
#define UTI_KEYBOARD_TAB            0x09

/*
* 0x0A - 0x0B : reserved
*/

#define UTI_KEYBOARD_CLEAR          0x0C
#define UTI_KEYBOARD_RETURN         0x0D

#define UTI_KEYBOARD_SHIFT          0x10
#define UTI_KEYBOARD_CONTROL        0x11
#define UTI_KEYBOARD_MENU           0x12
#define UTI_KEYBOARD_PAUSE          0x13
#define UTI_KEYBOARD_CAPITAL        0x14

#define UTI_KEYBOARD_KANA           0x15
#define UTI_KEYBOARD_HANGEUL        0x15  /* old name - should be here for compatibility */
#define UTI_KEYBOARD_HANGUL         0x15
#define UTI_KEYBOARD_JUNJA          0x17
#define UTI_KEYBOARD_FINAL          0x18
#define UTI_KEYBOARD_HANJA          0x19
#define UTI_KEYBOARD_KANJI          0x19

#define UTI_KEYBOARD_ESCAPE         0x1B

#define UTI_KEYBOARD_CONVERT        0x1C
#define UTI_KEYBOARD_NONCONVERT     0x1D
#define UTI_KEYBOARD_ACCEPT         0x1E
#define UTI_KEYBOARD_MODECHANGE     0x1F

#define UTI_KEYBOARD_SPACE          0x20
#define UTI_KEYBOARD_PRIOR          0x21
#define UTI_KEYBOARD_NEXT           0x22
#define UTI_KEYBOARD_END            0x23
#define UTI_KEYBOARD_HOME           0x24
#define UTI_KEYBOARD_LEFT           0x25
#define UTI_KEYBOARD_UP             0x26
#define UTI_KEYBOARD_RIGHT          0x27
#define UTI_KEYBOARD_DOWN           0x28
#define UTI_KEYBOARD_SELECT         0x29
#define UTI_KEYBOARD_PRINT          0x2A
#define UTI_KEYBOARD_EXECUTE        0x2B
#define UTI_KEYBOARD_SNAPSHOT       0x2C
#define UTI_KEYBOARD_INSERT         0x2D
#define UTI_KEYBOARD_DELETE         0x2E
#define UTI_KEYBOARD_HELP           0x2F

/*
* UTI_KEYBOARD_0 - UTI_KEYBOARD_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
* 0x40 : unassigned
* UTI_KEYBOARD_A - UTI_KEYBOARD_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
*/

#define UTI_KEYBOARD_LWIN           0x5B
#define UTI_KEYBOARD_RWIN           0x5C
#define UTI_KEYBOARD_APPS           0x5D

/*
* 0x5E : reserved
*/

#define UTI_KEYBOARD_SLEEP          0x5F

#define UTI_KEYBOARD_NUMPAD0        0x60
#define UTI_KEYBOARD_NUMPAD1        0x61
#define UTI_KEYBOARD_NUMPAD2        0x62
#define UTI_KEYBOARD_NUMPAD3        0x63
#define UTI_KEYBOARD_NUMPAD4        0x64
#define UTI_KEYBOARD_NUMPAD5        0x65
#define UTI_KEYBOARD_NUMPAD6        0x66
#define UTI_KEYBOARD_NUMPAD7        0x67
#define UTI_KEYBOARD_NUMPAD8        0x68
#define UTI_KEYBOARD_NUMPAD9        0x69
#define UTI_KEYBOARD_MULTIPLY       0x6A
#define UTI_KEYBOARD_ADD            0x6B
#define UTI_KEYBOARD_SEPARATOR      0x6C
#define UTI_KEYBOARD_SUBTRACT       0x6D
#define UTI_KEYBOARD_DECIMAL        0x6E
#define UTI_KEYBOARD_DIVIDE         0x6F
#define UTI_KEYBOARD_F1             0x70
#define UTI_KEYBOARD_F2             0x71
#define UTI_KEYBOARD_F3             0x72
#define UTI_KEYBOARD_F4             0x73
#define UTI_KEYBOARD_F5             0x74
#define UTI_KEYBOARD_F6             0x75
#define UTI_KEYBOARD_F7             0x76
#define UTI_KEYBOARD_F8             0x77
#define UTI_KEYBOARD_F9             0x78
#define UTI_KEYBOARD_F10            0x79
#define UTI_KEYBOARD_F11            0x7A
#define UTI_KEYBOARD_F12            0x7B
#define UTI_KEYBOARD_F13            0x7C
#define UTI_KEYBOARD_F14            0x7D
#define UTI_KEYBOARD_F15            0x7E
#define UTI_KEYBOARD_F16            0x7F
#define UTI_KEYBOARD_F17            0x80
#define UTI_KEYBOARD_F18            0x81
#define UTI_KEYBOARD_F19            0x82
#define UTI_KEYBOARD_F20            0x83
#define UTI_KEYBOARD_F21            0x84
#define UTI_KEYBOARD_F22            0x85
#define UTI_KEYBOARD_F23            0x86
#define UTI_KEYBOARD_F24            0x87

/*
* 0x88 - 0x8F : unassigned
*/

#define UTI_KEYBOARD_NUMLOCK        0x90
#define UTI_KEYBOARD_SCROLL         0x91

/*
* NEC PC-9800 kbd definitions
*/
#define UTI_KEYBOARD_OEM_NEC_EQUAL  0x92   // '=' key on numpad

/*
* Fujitsu/OASYS kbd definitions
*/
#define UTI_KEYBOARD_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define UTI_KEYBOARD_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define UTI_KEYBOARD_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define UTI_KEYBOARD_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define UTI_KEYBOARD_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

/*
* 0x97 - 0x9F : unassigned
*/

/*
* UTI_KEYBOARD_L* & UTI_KEYBOARD_R* - left and right Alt, Ctrl and Shift virtual keys.
* Used only as parameters to GetAsyncKeyState() and GetKeyState().
* No other API or message will distinguish left and right keys in this way.
*/
#define UTI_KEYBOARD_LSHIFT         0xA0
#define UTI_KEYBOARD_RSHIFT         0xA1
#define UTI_KEYBOARD_LCONTROL       0xA2
#define UTI_KEYBOARD_RCONTROL       0xA3
#define UTI_KEYBOARD_LMENU          0xA4
#define UTI_KEYBOARD_RMENU          0xA5

#if(_WIN32_WINNT >= 0x0500)
#define UTI_KEYBOARD_BROWSER_BACK        0xA6
#define UTI_KEYBOARD_BROWSER_FORWARD     0xA7
#define UTI_KEYBOARD_BROWSER_REFRESH     0xA8
#define UTI_KEYBOARD_BROWSER_STOP        0xA9
#define UTI_KEYBOARD_BROWSER_SEARCH      0xAA
#define UTI_KEYBOARD_BROWSER_FAVORITES   0xAB
#define UTI_KEYBOARD_BROWSER_HOME        0xAC

#define UTI_KEYBOARD_VOLUME_MUTE         0xAD
#define UTI_KEYBOARD_VOLUME_DOWN         0xAE
#define UTI_KEYBOARD_VOLUME_UP           0xAF
#define UTI_KEYBOARD_MEDIA_NEXT_TRACK    0xB0
#define UTI_KEYBOARD_MEDIA_PREV_TRACK    0xB1
#define UTI_KEYBOARD_MEDIA_STOP          0xB2
#define UTI_KEYBOARD_MEDIA_PLAY_PAUSE    0xB3
#define UTI_KEYBOARD_LAUNCH_MAIL         0xB4
#define UTI_KEYBOARD_LAUNCH_MEDIA_SELECT 0xB5
#define UTI_KEYBOARD_LAUNCH_APP1         0xB6
#define UTI_KEYBOARD_LAUNCH_APP2         0xB7

#endif /* _WIN32_WINNT >= 0x0500 */

/*
* 0xB8 - 0xB9 : reserved
*/

#define UTI_KEYBOARD_OEM_1          0xBA   // ';:' for US
#define UTI_KEYBOARD_OEM_PLUS       0xBB   // '+' any country
#define UTI_KEYBOARD_OEM_COMMA      0xBC   // ',' any country
#define UTI_KEYBOARD_OEM_MINUS      0xBD   // '-' any country
#define UTI_KEYBOARD_OEM_PERIOD     0xBE   // '.' any country
#define UTI_KEYBOARD_OEM_2          0xBF   // '/?' for US
#define UTI_KEYBOARD_OEM_3          0xC0   // '`~' for US

/*
* 0xC1 - 0xD7 : reserved
*/

/*
* 0xD8 - 0xDA : unassigned
*/

#define UTI_KEYBOARD_OEM_4          0xDB  //  '[{' for US
#define UTI_KEYBOARD_OEM_5          0xDC  //  '\|' for US
#define UTI_KEYBOARD_OEM_6          0xDD  //  ']}' for US
#define UTI_KEYBOARD_OEM_7          0xDE  //  ''"' for US
#define UTI_KEYBOARD_OEM_8          0xDF

/*
* 0xE0 : reserved
*/

/*
* Various extended or enhanced keyboards
*/
#define UTI_KEYBOARD_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
#define UTI_KEYBOARD_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define UTI_KEYBOARD_ICO_HELP       0xE3  //  Help key on ICO
#define UTI_KEYBOARD_ICO_00         0xE4  //  00 key on ICO

#if(WINVER >= 0x0400)
#define UTI_KEYBOARD_PROCESSKEY     0xE5
#endif /* WINVER >= 0x0400 */

#define UTI_KEYBOARD_ICO_CLEAR      0xE6


#if(_WIN32_WINNT >= 0x0500)
#define UTI_KEYBOARD_PACKET         0xE7
#endif /* _WIN32_WINNT >= 0x0500 */

/*
* 0xE8 : unassigned
*/

/*
* Nokia/Ericsson definitions
*/
#define UTI_KEYBOARD_OEM_RESET      0xE9
#define UTI_KEYBOARD_OEM_JUMP       0xEA
#define UTI_KEYBOARD_OEM_PA1        0xEB
#define UTI_KEYBOARD_OEM_PA2        0xEC
#define UTI_KEYBOARD_OEM_PA3        0xED
#define UTI_KEYBOARD_OEM_WSCTRL     0xEE
#define UTI_KEYBOARD_OEM_CUSEL      0xEF
#define UTI_KEYBOARD_OEM_ATTN       0xF0
#define UTI_KEYBOARD_OEM_FINISH     0xF1
#define UTI_KEYBOARD_OEM_COPY       0xF2
#define UTI_KEYBOARD_OEM_AUTO       0xF3
#define UTI_KEYBOARD_OEM_ENLW       0xF4
#define UTI_KEYBOARD_OEM_BACKTAB    0xF5

#define UTI_KEYBOARD_ATTN           0xF6
#define UTI_KEYBOARD_CRSEL          0xF7
#define UTI_KEYBOARD_EXSEL          0xF8
#define UTI_KEYBOARD_EREOF          0xF9
#define UTI_KEYBOARD_PLAY           0xFA
#define UTI_KEYBOARD_ZOOM           0xFB
#define UTI_KEYBOARD_NONAME         0xFC
#define UTI_KEYBOARD_PA1            0xFD
#define UTI_KEYBOARD_OEM_CLEAR      0xFE

/*
* 0xFF : reserved
*/

