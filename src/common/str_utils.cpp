#include "str_utils.hpp"

#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <cinttypes>
#include <string_view_utf8.hpp>

namespace {
/// Has to match is_wide() of the font generator (font.py), which decides what the fonts draw full-width
bool is_full_width(unichar c) {
    return (c >= 0x3000 && c <= 0x9FFF) || (c >= 0xFF01 && c <= 0xFF60);
}

/// Japanese wraps between any two full-width characters, except before the ones that
/// must not start a line - punctuation, small kana and the prolonged sound mark (kinsoku).
/// Only the line start is checked; a line may still end with an opening bracket.
bool can_start_line(unichar c) {
    switch (c) {
    case 0x3001: // 、
    case 0x3002: // 。
    case 0x30FB: // ・
    case 0x30FC: // ー
    case 0x300D: // 」
    case 0x300F: // 』
    case 0xFF09: // ）
    case 0x3005: // 々
    case 0x3041: // ぁ
    case 0x3043: // ぃ
    case 0x3045: // ぅ
    case 0x3047: // ぇ
    case 0x3049: // ぉ
    case 0x3063: // っ
    case 0x3083: // ゃ
    case 0x3085: // ゅ
    case 0x3087: // ょ
    case 0x308E: // ゎ
    case 0x30A1: // ァ
    case 0x30A3: // ィ
    case 0x30A5: // ゥ
    case 0x30A7: // ェ
    case 0x30A9: // ォ
    case 0x30C3: // ッ
    case 0x30E3: // ャ
    case 0x30E5: // ュ
    case 0x30E7: // ョ
    case 0x30EE: // ヮ
    case 0x30F5: // ヵ
    case 0x30F6: // ヶ
        return false;
    default:
        return true;
    }
}
} // namespace

RectTextLayout::RectTextLayout(StringReaderUtf8 &reader, uint16_t max_width, uint16_t max_rows, is_multiline multiline, CharWidth char_width) {
    if (max_width == 0 || max_rows == 0) {
        overflow = (reader.getUtf8Char() != 0);
        return;
    }

    if (multiline == is_multiline::no) {
        max_rows = 1;
    }

    std::optional<Position> split = std::nullopt;
    unichar c = 0;
    Position line;

    while ((c = reader.getUtf8Char()) != 0) {
        const int c_width = char_width(c);

        switch (c) {
        case '\n': // new line

            set_current_line(line);
            skip_char[current_line] = true;
            if (!new_line(max_rows)) {
                return;
            }

            line = {};
            split = std::nullopt;
            break;

        case ' ': // remember space position

            // erasing start space is not handled here
            // Whenever we enter new line (except the first one), we always skip 1 char ('\n' || ' ') from the stream
            // If there are more whitespace characters, its clearly a choice

            split = Position { line.chars + 1, line.width + c_width };
            skip_char[current_line] = true;
            [[fallthrough]];

        default:
            // A wrap at a space right before this character is kept, so that the space is skipped
            if (is_full_width(c) && line.chars > 0 && can_start_line(c) && !(split && split->chars == line.chars)) {
                split = line;
                skip_char[current_line] = false;
            }

            line.chars++;
            line.width += c_width;

            if (line.width > max_width) {
                if (line.chars == 1) {
                    // A single character wider than the whole line: wrapping would only produce
                    // empty lines, so stop - the text does not fit
                    overflow = true;
                    set_current_line({});
                    return;
                }

                if (!split || current_line == max_rows - 1) { // Do not wrap singleline texts
                    split = Position { line.chars - 1, line.width - c_width };
                    overflow = true;
                    skip_char[current_line] = false;
                }

                // It does not count newline char and space before wrapped word
                // Wrapping cuts overflown word and put it on the next line
                // If word is too long for a line, it will split the word before the overflowing character

                // count chars in next line
                line.chars -= split->chars;
                line.width -= split->width;
                const int skipped_chars = skip_char[current_line] ? 1 : 0;
                const int skipped_width = skip_char[current_line] ? char_width(' ') : 0;
                set_current_line({ split->chars - skipped_chars, split->width - skipped_width });
                split = std::nullopt;

                if (!new_line(max_rows)) {
                    return;
                }
            }

            // Japanese comma and full stop allow a wrap after them. Only once they have a place
            // on a line - if they overflow, they take the character before them to the next line.
            if (c == 0x3001 || c == 0x3002) {
                split = line;
                skip_char[current_line] = false;
            }
        }
    }

    skip_char[current_line] = false;
    set_current_line(line);
    return;
}

void RectTextLayout::set_current_line(Position line) {
    data[current_line] = line.chars;
    widths[current_line] = line.width;
    longest_width = std::max<uint16_t>(longest_width, line.width);
}

uint8_t RectTextLayout::get_current_line_characters() const {
    return get_line_characters(current_line);
}

uint8_t RectTextLayout::get_line_count() const {
    return current_line == 0 && get_current_line_characters() == 0 ? 0 : current_line + 1;
}

bool RectTextLayout::new_line(uint8_t max_rows) {
    if (current_line >= MaxLines || current_line + 1 >= max_rows) {
        overflow = true;
        return false;
    }
    current_line++;
    return true;
}

template <typename T, auto strtox_func>
from_chars_light_result from_chars_light_common(const char *first, const char *last, T &value, int base) {
    std::array<char, sizeof(value) * 8 + 2> buffer; // buffer where we'll copy the number with ending zero, size reserved is to fit base 2 number + sign, plus ending zero.

    size_t len = std::distance(first, last);
    if (len > buffer.size() - 1) {
        // buffer is too small, or won't fit ending zero
        return { first, std::errc::value_too_large };
    }
    std::copy(first, last, buffer.begin());
    buffer[len] = '\0'; // make sure there is ending zero, to avoid strtoi reading beyond the buffer
    char *out_end = nullptr;
    errno = 0;
    auto value_res = strtox_func(buffer.data(), &out_end, base);
    if (errno != 0) {
        return { out_end, std::errc::result_out_of_range };
    }
    if (out_end == buffer.data()) {
        return { out_end, std::errc::invalid_argument };
    }
    if (value_res < std::numeric_limits<T>::min() || value_res > std::numeric_limits<T>::max()) {
        return { out_end, std::errc::result_out_of_range };
    }
    value = value_res;

    return { out_end, std::errc {} };
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, unsigned long long &value, int base) {
    static_assert(sizeof(unsigned long long) >= sizeof(value));
    return from_chars_light_common<unsigned long long, std::strtoull>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, unsigned long &value, int base) {
    static_assert(sizeof(unsigned long) >= sizeof(value));
    return from_chars_light_common<unsigned long, std::strtoul>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, unsigned int &value, int base) {
    static_assert(sizeof(unsigned long) >= sizeof(value));
    return from_chars_light_common<unsigned int, std::strtoul>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, unsigned short &value, int base) {
    static_assert(sizeof(unsigned long) >= sizeof(value));
    return from_chars_light_common<unsigned short, std::strtoul>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, unsigned char &value, int base) {
    static_assert(sizeof(unsigned long) >= sizeof(value));
    return from_chars_light_common<unsigned char, std::strtoul>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, long long &value, int base) {
    static_assert(sizeof(long long) >= sizeof(value));
    return from_chars_light_common<long long, std::strtoll>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, long &value, int base) {
    static_assert(sizeof(long) >= sizeof(value));
    return from_chars_light_common<long, std::strtol>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, int &value, int base) {
    static_assert(sizeof(long) >= sizeof(value));
    return from_chars_light_common<int, std::strtol>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, short &value, int base) {
    static_assert(sizeof(long) >= sizeof(value));
    return from_chars_light_common<short, std::strtol>(first, last, value, base);
}

template <>
from_chars_light_result from_chars_light(const char *first, const char *last, signed char &value, int base) {
    static_assert(sizeof(long) >= sizeof(value));
    return from_chars_light_common<signed char, std::strtol>(first, last, value, base);
}

from_chars_light_result from_chars_light(const char *first, const char *last, float &value) {
    std::array<char, 32> buffer; // buffer where we'll copy the number with ending zero

    size_t len = std::distance(first, last);
    if (len >= buffer.size() - 1) {
        return { first, std::errc::value_too_large };
    }
    std::copy(first, last, buffer.begin());
    buffer[len] = '\0'; // make sure there is ending zero, to avoid strtoi reading beyond the buffer
    char *out_end = nullptr;
    value = std::strtof(buffer.data(), &out_end);
    if (out_end == buffer.data()) {
        return { first, std::errc::invalid_argument };
    }
    return { out_end, std::errc {} };
}
