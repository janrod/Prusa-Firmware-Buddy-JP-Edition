/**
 * @file display_helper.cpp
 */

#include <algorithm>

#include "display_helper.h"
#include "display.hpp"
#include "window.hpp"
#include "gui.hpp"
#include "../lang/string_view_utf8.hpp"
#include "ScreenHandler.hpp"
#include <math.h>
#include "guitypes.hpp"
#include "cmath_ext.h"
#include <bsod/bsod.h>

namespace {
/// Gap between lines of full-width characters, in pixels
constexpr uint16_t WIDE_LINE_GAP = 4;
} // namespace

/// Fill space from [@top, @left] corner to the end of @rc with height @h
/// If @h is too high, it will be cropped so nothing is drawn outside of the @rc but
/// @top and @left are not checked whether they are in @rc
void fill_till_end_of_line(const int left, const int top, const int h, Rect16 rc, Color clr) {
    display::fill_rect(Rect16(left, top, std::max(0, rc.EndPoint().x - left), CLAMP(rc.EndPoint().y - top, 0, h)), clr);
}

/// Fills space between two rectangles with a color
/// @r_in must be completely in @r_out
void fill_between_rectangles(const Rect16 *r_out, const Rect16 *r_in, Color color) {
    if (!r_out->Contain(*r_in)) {
        return;
    }
    /// top
    const Rect16 rc_t = { r_out->Left(), r_out->Top(), r_out->Width(), uint16_t(r_in->Top() - r_out->Top()) };
    display::fill_rect(rc_t, color);
    /// bottom
    const Rect16 rc_b = { r_out->Left(), int16_t(r_in->Top() + r_in->Height()), r_out->Width(), uint16_t((r_out->Top() + r_out->Height()) - (r_in->Top() + r_in->Height())) };
    display::fill_rect(rc_b, color);
    /// left
    const Rect16 rc_l = { r_out->Left(), r_in->Top(), uint16_t(r_in->Left() - r_out->Left()), r_in->Height() };
    display::fill_rect(rc_l, color);
    /// right
    const Rect16 rc_r = { int16_t(r_in->Left() + r_in->Width()), r_in->Top(), uint16_t((r_out->Left() + r_out->Width()) - (r_in->Left() + r_in->Width())), r_in->Height() };
    display::fill_rect(rc_r, color);
}

size_ui16_t calculate_text_size(const string_view_utf8 &str, const Font font, is_multiline multiline) {
    const auto *pf = resource_font(font);
    StringReaderUtf8 reader(str);
    const auto layout = RectTextLayout(reader, UINT16_MAX, 255, multiline, char_width(pf));
    debug_assert(!layout.has_text_overflown());
    return size_ui16_t(layout.get_width(), layout.get_height_in_chars() * pf->h);
}

void render_line(StringReaderUtf8 &reader, uint8_t chars_to_print, Rect16 rc, const font_t *pf, Color clr_bg, Color clr_fg) {
    const uint16_t buff_width_capacity = display::buffer_pixel_size() / pf->h;
    debug_assert(buff_width_capacity >= std::max<uint16_t>(pf->w, font_data::WIDE_GLYPH_SIZE) && "Buffer needs to take at least one character");
    point_ui16_t pt = point_ui16(rc.Left(), rc.Top());

    uint8_t chars_left = chars_to_print;
    while (chars_left > 0) {
        // The buffer has to know the width of what will be stored to correctly compute display buffer offsets
        auto peek = reader.copy();
        uint8_t char_cnt = 0;
        uint16_t width = 0;
        while (char_cnt < chars_left) {
            const uint8_t char_w = pf->char_width(peek.getUtf8Char());
            if (width + char_w > buff_width_capacity) {
                break;
            }
            char_cnt++;
            width += char_w;
        }

        if (char_cnt == 0) {
            // A character wider than the whole buffer cannot be drawn - leave its space empty
            // rather than loop forever or write past the buffer
            pt.x += pf->char_width(reader.getUtf8Char());
            chars_left--;
            continue;
        }

        // Storing text in the display buffer
        uint16_t x = 0;
        for (uint8_t j = 0; j < char_cnt; j++) {
            const unichar c = reader.getUtf8Char();
            if (c == '\n' || c == '\0') {
                bsod("Bad RectTextLayout");
            }
            display::store_char_in_buffer(width, x, c, pf, clr_bg, clr_fg);
            x += pf->char_width(c);
        }
        // Drawing from the buffer
        chars_left -= char_cnt;
        display::draw_from_buffer(pt, width, pf->h);
        pt.x += width;
    }
}

void render_text_align(Rect16 rc, const string_view_utf8 &text, const Font f, Color clr_bg, Color clr_fg, padding_ui8_t padding, text_flags flags, bool fill_rect) {
    StringReaderUtf8 reader(text);
    render_text_align(rc, reader, f, clr_bg, clr_fg, padding, flags, fill_rect);
}

void render_text_align(Rect16 rc, StringReaderUtf8 &reader, const Font f, Color clr_bg, Color clr_fg, padding_ui8_t padding, text_flags flags, bool fill_rect) {
    const font_t *font = resource_font(f);
    Rect16 rc_pad = rc;
    rc_pad.CutPadding(padding);

    auto reader_copy = reader.copy();
    const RectTextLayout layout = RectTextLayout(reader_copy, rc_pad.Width(), rc_pad.Height() / font->h, flags.multiline, char_width(font));

    debug_assert(flags.overflow == check_overflow::no || !layout.has_text_overflown());

    if (layout.get_width() == 0 || layout.get_height_in_chars() == 0) {
        if (fill_rect) {
            display::fill_rect(rc, clr_bg);
        }
        return;
    }

    // Full-width glyphs fill the whole height of the smaller fonts, so their lines would touch.
    // Space them out where the rectangle has room for it.
    const uint16_t line_count = layout.get_height_in_chars();
    uint16_t line_pitch = font->h;
    if (layout.has_full_width() && line_count > 1) {
        const uint16_t spaced_pitch = std::max<uint16_t>(font->h, font_data::WIDE_GLYPH_SIZE + WIDE_LINE_GAP);
        if ((line_count - 1) * spaced_pitch + font->h <= rc_pad.Height()) {
            line_pitch = spaced_pitch;
        }
    }

    Rect16 rc_txt = Rect16(0, 0, layout.get_width(), (line_count - 1) * line_pitch + font->h);
    rc_txt.Align(rc_pad, flags.align);
    rc_pad = rc_txt.Intersection(rc_pad); ///  set padding rect to new value, crop the rectangle if the text is too long

    for (size_t i = 0; i < layout.get_height_in_chars(); ++i) {
        Rect16 rect_to_align(rc_pad.Left(), rc_pad.Top() + i * line_pitch, rc_pad.Width(), font->h);
        const size_t line_char_cnt = layout.get_line_characters(i);
        Rect16 line_rect(0, 0, layout.get_line_width(i), font->h);
        line_rect.Align(rect_to_align, flags.align);

        // in front of line
        const Rect16 front = rect_to_align.LeftSubrect(line_rect);
        if (front.Width()) {
            display::fill_rect(front, clr_bg);
        }
        // behind line
        const Rect16 behind = rect_to_align.RightSubrect(line_rect);
        if (behind.Width()) {
            display::fill_rect(behind, clr_bg);
        }

        render_line(reader, line_char_cnt, line_rect, font, clr_bg, clr_fg);

        if (line_pitch > font->h && i + 1 < line_count) {
            display::fill_rect(Rect16(rc_pad.Left(), rect_to_align.Top() + font->h, rc_pad.Width(), line_pitch - font->h), clr_bg);
        }

        // skip character, that splits the lines (usually '\n' || ' ')
        if (layout.get_skip_char_on_line(i)) {
            reader.skip(1);
        }
    }

    /// fill borders (padding)
    if (fill_rect) {
        fill_between_rectangles(&rc, &rc_pad, clr_bg);
    }
}

void render_icon_align(Rect16 rc, const img::Resource *res, Color clr_back, icon_flags flags) {

    if (res) {
        point_ui16_t wh_ico = { res->w, res->h };
        Rect16 rc_ico = Rect16(0, 0, wh_ico.x, wh_ico.y);
        rc_ico.Align(rc, flags.align);
        rc_ico = rc_ico.Intersection(rc);
        display::draw_img(point_ui16(rc_ico.Left(), rc_ico.Top()), *res, clr_back, flags.raster_flags);
    } else {
        display::fill_rect(rc, clr_back);
    }
}

void render_rect(Rect16 rc, Color clr) {
    display::fill_rect(rc, clr);
}

void render_rounded_rect(Rect16 rc, Color bg_clr, Color fg_clr, uint8_t rad, uint8_t flag) {
    display::draw_rounded_rect(rc, bg_clr, fg_clr, rad, flag);
}
