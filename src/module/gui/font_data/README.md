# `font_data` module

Fonts are stored as source PNGs inside the repository. This module is
responsible for transforming font data to a form usable by the renderer.

This module provides all the font data. If you don't need some of them,
just don't reference them and linker will happily drop the unused data.

## Character sets
To save FLASH, module provides multiple copies of the same font.
The copies differ in characters included:
 * `digits` - digits + punctuation
 * `full` - printable ASCII + accents + cyrillic + punctuation, and the full-width
   characters drawn from the font below
 * `latin_and_accents` - printable ASCII + accents + punctuation
 * `latin_and_cyrillic` - printable ASCII + cyrillic + punctuation
 * `latin_and_katakana` - printable ASCII + katakana + punctuation

## Full-width characters
Kana, kanji and Japanese punctuation are wider than a character cell. The `full`
fonts at least 16 pixels tall draw them 16x16 pixels, 1 bit per pixel, and advance
by 16 pixels.
The `latin_and_katakana` fonts of the MINI keep their own katakana instead.

They all come from a single source PNG, `16x16px_shinonome-gothic_jis.png`, laid
out as the JIS X 0208 code chart: row *n* of the chart is the *n*-th row of
16-pixel glyphs, cell *m* the *m*-th column, 94 cells per row. It holds the rows
up to the end of the level 1 kanji - symbols, full-width alphanumerics, kana and
2965 kanji. Black is ink; an empty cell is a code the chart leaves unassigned.

Only the characters the translations use end up in the firmware, so a bigger PNG
costs no FLASH. A character the PNG does not hold, such as a level 2 kanji, stops
the build with an error naming it.

The glyphs are from the Shinonome 16 dot gothic font (`shnmk16.bdf`) by Yasuyuki
Furukawa and /efont/, which is in the public domain.
