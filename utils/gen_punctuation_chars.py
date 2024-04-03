#!/usr/bin/env python3

"""
Script to generate a C header file with all the punctuation characters used in reStructuredText.

Usage:
    python gen_punctuation_chars.py > punctuation_chars.h

Or call it from the makefile (recommended):

    make gen-punctuation-chars
"""

from docutils.utils.punctuation_chars import (
    openers,
    closers,
    delimiters,
    closing_delimiters,
)


def is_ascii(ch) -> bool:
    return ord(ch) <= 127


def c_repr(ch) -> str:
    if is_ascii(ch):
        if ch == "'":
            return "'\\''"  # special case for single quote
        return repr(ch)
    else:
        return hex(ord(ch))


def generate_c_chars_define(name: str, chars: str, expects_range=False) -> list[str]:
    INDENT = " " * 2
    c_chars = [f"const int32_t {name}[] = {{"]
    c_char_ranges = [f"const int32_t {name}_range[][2] = {{"]
    range_start = None
    for i, ch in enumerate(chars):
        if range_start is not None:
            if ch == "-":
                continue  # skip range sign
            if is_ascii(ch):
                raise Exception(f"Expected unicode, found ascii: {ch}")
            c_char_ranges.append(f"{INDENT}{{{c_repr(range_start)}, {c_repr(ch)}}},")
            range_start = None

        if not is_ascii(ch) and i != len(chars) - 1 and chars[i + 1] == "-":
            range_start = ch
            continue

        c_chars.append(f"{INDENT}{c_repr(ch)},")

    c_chars.append("};")
    c_char_ranges.append("};")

    if len(c_char_ranges) > 2:
        if not expects_range:
            raise Exception(f"Expected no ranges, but a range was found for {name}")
        return c_chars + c_char_ranges
    if expects_range:
        raise Exception(f"Expected ranges, but none found for {name}")
    return c_chars


if __name__ == "__main__":
    lines = [
        "// This file is generated by utils/gen_punctuation_chars.py, DO NOT EDIT.",
        "",
        "#ifndef TREE_SITTER_RST_PUNCTUATION_CHARS_H_",
        "#define TREE_SITTER_RST_PUNCTUATION_CHARS_H_",
        "",
    ]

    lines.extend(generate_c_chars_define("start_chars", openers, expects_range=False))
    lines.append("")

    lines.extend(generate_c_chars_define("delim_chars", delimiters, expects_range=True))
    lines.append("")

    lines.extend(generate_c_chars_define("end_chars", closing_delimiters + closers, expects_range=False))
    lines.append("")

    lines.append("#endif /* ifndef TREE_SITTER_RST_PUNCTUATION_CHARS_H_ */")

    print("\n".join(lines))
