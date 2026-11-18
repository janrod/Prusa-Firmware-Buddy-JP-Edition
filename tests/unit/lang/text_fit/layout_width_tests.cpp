#include <catch2/catch_test_macros.hpp>
#include <fonts.hpp>
#include <str_utils.hpp>

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

/// The originals and the translations of a .mo file
std::vector<std::string> mo_strings(const char *path) {
    std::ifstream file(path, std::ios::binary);
    const std::vector<char> data { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    const auto word = [&](size_t offset) {
        uint32_t value;
        memcpy(&value, data.data() + offset, sizeof(value));
        return value;
    };
    REQUIRE(data.size() >= 20);
    REQUIRE(word(0) == 0x950412de);

    std::vector<std::string> strings;
    const uint32_t count = word(8);
    for (const uint32_t table : { word(12), word(16) }) {
        for (uint32_t i = 0; i < count; ++i) {
            strings.emplace_back(data.data() + word(table + i * 8 + 4), word(table + i * 8));
        }
    }
    return strings;
}

/// Everything about a layout, or nothing when laying it out failed an assert
std::optional<std::string> describe(const char *text, uint16_t max_width, uint16_t max_rows, is_multiline multiline, CharWidth char_width, uint16_t unit) {
    try {
        auto view = string_view_utf8::MakeCPUFLASH(text);
        StringReaderUtf8 reader(view);
        const RectTextLayout layout(reader, max_width, max_rows, multiline, char_width);
        std::string result = std::to_string(layout.get_width() / unit) + (layout.has_text_overflown() ? " overflown:" : ":");
        for (uint8_t line = 0; line < layout.get_line_count(); ++line) {
            result += " " + std::to_string(layout.get_line_characters(line)) + (layout.get_skip_char_on_line(line) ? "+skip" : "");
        }
        return result;
    } catch (const std::exception &) {
        return std::nullopt;
    }
}

} // namespace

// The languages written in character cells must wrap exactly as when the layout counted
// characters - measuring in pixels is only meant to change full-width text
TEST_CASE("Layout in pixels matches the layout in characters") {
    const font_t *font = &font_data::bold_11x19_full;
    for (const char *lang : { "cs", "de", "es", "fr", "it", "pl", "uk" }) {
        const auto strings = mo_strings((std::string("MO/") + lang + ".mo").c_str());
        CHECK(strings.size() > 1000);
        for (const auto &text : strings) {
            for (const uint16_t columns : { 9, 16, 26, 40 }) {
                for (const uint16_t rows : { 1, 8 }) {
                    for (const is_multiline multiline : { is_multiline::no, is_multiline::yes }) {
                        INFO("Lang = " << lang << ", text = \"" << text << "\", " << columns << " columns, " << rows << " rows");
                        CHECK(describe(text.c_str(), columns * font->w, rows, multiline, char_width(font), font->w)
                            == describe(text.c_str(), columns, rows, multiline, {}, 1));
                    }
                }
            }
        }
    }
}
