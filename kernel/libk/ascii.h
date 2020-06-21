#ifndef ASOS_LIBK_ASCII_H
#define ASOS_LIBK_ASCII_H

typedef enum {
    ASCII_NULL,
    ASCII_HEADER_START,
    ASCII_TEXT_START,
    ASCII_TEXT_END,
    ASCII_TX_END,
    ASCII_ENQUIRY,
    ASCII_ACK,
    ASCII_BELL,
    ASCII_BACKSPACE,
    ASCII_H_TAB,
    ASCII_LINE_FEED, // \n or LF 
    ASCII_V_TAB,
    ASCII_FORM_FEED,
    ASCII_CR,
    ASCII_SHIFT_OUT,
    ASCII_SHIFT_IN,
    ASCII_DL_ESC,
    ASCII_DEV_CTRL_1,
    ASCII_DEV_CTRL_2,
    ASCII_DEV_CTRL_3,
    ASCII_DEV_CTRL_4,
    ASCII_NACK,
    ASCII_SYNC,
    ASCII_TX_BLK_END,
    ASCII_CANCEL,
    ASCII_MEDIUM_END,
    ASCII_SUBSTITUTE,
    ASCII_ESCAPE,
    ASCII_FILE_SEP,
    ASCII_GROUP_SEP,
    ASCII_RECORD_SEP,
    ASCII_UNIT_SET,
    ASCII_SPACE,
    ASCII_EXCLAMATION_MARK,
    ASCII_DOUBLE_QOUTE,
    ASCII_NUMBER_SIGN,
    ASCII_DOLLAR_SIGN,
    ASCII_PERCENT,
    ASCII_AMPERSAND,
    ASCII_SINGLE_QUOTE,
    ASCII_LEFT_PAREN,
    ASCII_RIGHT_PAREN,
    ASCII_ASTERISK,
    ASCII_PLUS,
    ASCII_COMMA,
    ASCII_MINUS,
    ASCII_PERIOD,
    ASCII_SLASH,
    ASCII_ZERO,
    ASCII_ONE,
    ASCII_TWO,
    ASCII_THREE,
    ASCII_FOUR,
    ASCII_FIVE,
    ASCII_SIX,
    ASCII_SEVEN,
    ASCII_EIGHT,
    ASCII_NINE,
    ASCII_COLON,
    ASCII_SEMICOLON,
    ASCII_LESS_THAN,
    ASCII_EQUAL,
    ASCII_GREATER_THAN,
    ASCII_QUESTION_MARK,
    ASCII_AT_SIGN,
    ASCII_UPPER_A,
    ASCII_UPPER_B,
    ASCII_UPPER_C,
    ASCII_UPPER_D,
    ASCII_UPPER_E,
    ASCII_UPPER_F,
    ASCII_UPPER_G,
    ASCII_UPPER_H,
    ASCII_UPPER_I,
    ASCII_UPPER_J,
    ASCII_UPPER_K,
    ASCII_UPPER_L,
    ASCII_UPPER_M,
    ASCII_UPPER_N,
    ASCII_UPPER_O,
    ASCII_UPPER_P,
    ASCII_UPPER_Q,
    ASCII_UPPER_R,
    ASCII_UPPER_S,
    ASCII_UPPER_T,
    ASCII_UPPER_U,
    ASCII_UPPER_V,
    ASCII_UPPER_W,
    ASCII_UPPER_X,
    ASCII_UPPER_Y,
    ASCII_UPPER_Z,
    ASCII_L_SQR_BRKT,
    ASCII_BACKSLASH,
    ASCII_R_SQR_BRKT,
    ASCII_CARET,
    ASCII_UNDERSCORE,
    ASCII_ACCENT,
    ASCII_LOWER_A,
    ASCII_LOWER_B,
    ASCII_LOWER_C,
    ASCII_LOWER_D,
    ASCII_LOWER_E,
    ASCII_LOWER_F,
    ASCII_LOWER_G,
    ASCII_LOWER_H,
    ASCII_LOWER_I,
    ASCII_LOWER_J,
    ASCII_LOWER_K,
    ASCII_LOWER_L,
    ASCII_LOWER_M,
    ASCII_LOWER_N,
    ASCII_LOWER_O,
    ASCII_LOWER_P,
    ASCII_LOWER_Q,
    ASCII_LOWER_R,
    ASCII_LOWER_S,
    ASCII_LOWER_T,
    ASCII_LOWER_U,
    ASCII_LOWER_V,
    ASCII_LOWER_W,
    ASCII_LOWER_X,
    ASCII_LOWER_Y,
    ASCII_LOWER_Z,
    ASCII_L_CURLY_BRKT,
    ASCII_VERT_BAR,
    ASCII_R_CURLY_BRKT,
    ASCII_TILDE,
    ASCII_DELETE,
} ascii_char;


#endif