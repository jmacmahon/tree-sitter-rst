#include <ctype.h>

#include "tree_sitter_rst/utils.h"
#include "tree_sitter_rst/chars.h"


bool is_newline(int32_t c) {
  for (int i = 0; i < NEWLINE_CHARS_LENGTH; i++) {
    if (c == NEWLINE_CHARS[i]) {
      return true;
    }
  }
  return false;
}


bool is_space(int32_t c) {
  return isspace(c) || is_newline(c);
}


bool is_start_char(int32_t c) {
  for (int i = 0; i < START_CHARS_LENGTH; i++) {
    if (c == START_CHARS[i]) {
      return true;
    }
  }
  return false;
}


bool is_end_char(int32_t c) {
  for (int i = 0; i < END_CHARS_LENGTH; i++) {
    if (c == END_CHARS[i]) {
      return true;
    }
  }
  return false;
}


bool is_inline_markup_start_char(int32_t c) {
  const int32_t inline_markup_chars[] = {
    '*',  // *emphasis*, and **strong**.
    '`',  // `interpreted text`, ``literals``, `hyperlink references`_, and `anonymous references`__.
    '|',  // |substitution references|.
    '_',  // _`inline internal target`.
    '[',  // [foot-note]_.
  };
  const int length = 5;
  for (int i = 0; i < length; i++) {
    if (c == inline_markup_chars[i]) {
      return true;
    }
  }
  return false;
}


bool is_inline_markup_end_char(int32_t c) {
  const int32_t inline_markup_chars[] = {
    '*',  // *emphasis*, and **strong**.
    '`',  // `interpreted text`, ``literals``, _`inline internal target`,
          // `hyperlink references`_, and `anonymous references`__.
    '|',  // |substitution references|.
    ']',  // [foot-note]_.
  };
  const int length = 4;
  for (int i = 0; i < length; i++) {
    if (c == inline_markup_chars[i]) {
      return true;
    }
  }
  return false;
}


bool is_char_bullet(int32_t c) {
  for (int i = 0; i < CHAR_BULLETS_LENGTH; i++) {
    if (c == CHAR_BULLETS[i]) {
      return true;
    }
  }
  return false;
}


bool is_numeric_bullet(int32_t c) {
  return (
    is_numeric_bullet_simple(c)
    || is_numeric_bullet_roman_lower(c)
    || is_numeric_bullet_roman_upper(c)
    || is_numeric_bullet_abc_lower(c)
    || is_numeric_bullet_abc_upper(c)
  );
}


bool is_numeric_bullet_simple(int32_t c) {
  for (int i = 0; i < NUMERIC_BULLETS_SIMPLE_LENGTH; i++) {
    if (c == NUMERIC_BULLETS_SIMPLE[i]) {
      return true;
    }
  }
  return false;
}


bool is_numeric_bullet_roman_lower(int32_t c) {
  for (int i = 0; i < ROMAN_NUMERS_LENGTH; i++) {
    if (c == ROMAN_NUMERS_LOWERCASE[i]) {
      return true;
    }
  }
  return false;
}


bool is_numeric_bullet_roman_upper(int32_t c) {
  for (int i = 0; i < ROMAN_NUMERS_LENGTH; i++) {
    if (c == ROMAN_NUMERS_UPPPERCASE[i]) {
      return true;
    }
  }
  return false;
}


bool is_numeric_bullet_abc_lower(int32_t c) {
  for (int i = 0; i < ABC_LENGTH; i++) {
    if (c == ABC_LOWERCASE[i]) {
      return true;
    }
  }
  return false;
}


bool is_numeric_bullet_abc_upper(int32_t c) {
  for (int i = 0; i < ABC_LENGTH; i++) {
    if (c == ABC_UPPERCASE[i]) {
      return true;
    }
  }
  return false;
}


bool is_internal_reference_char(int32_t c) {
  const int32_t internal_chars[] = {'-', '_', '.', ':', '+'};
  const int length = 5;
  for (int i = 0; i < length; i++) {
    if (c == internal_chars[i]) {
      return true;
    }
  }
  return false;
}