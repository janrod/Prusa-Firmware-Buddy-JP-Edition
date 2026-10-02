# Prusa Firmware Buddy - JP Edition (日本語・漢字対応ファームウェア)

> [!WARNING]
> **Unofficial community firmware.** This project is not made, endorsed or supported by Prusa Research.
> It is an independent fork of the open-source
> [prusa3d/Prusa-Firmware-Buddy](https://github.com/prusa3d/Prusa-Firmware-Buddy) (6.10.1).
> "Prusa", "Original Prusa" and "CORE One" are trademarks of Prusa Research a.s. and are used here
> only to say which printers the firmware is for.
>
> - Installing it requires breaking the appendix on the printer's main board, which is permanent and
>   affects the electronics warranty.
> - It comes with **no warranty** (GPL v3.0). Use it at your own risk.
> - Please do not contact Prusa Research support about problems with this firmware - report them in this
>   repository's [Issues](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/issues).
>   Flash official firmware before asking Prusa for help.
>
> **非公式のコミュニティ版ファームウェアです。** Prusa Research が作成・承認・サポートしているものではありません。
> オープンソースの Prusa Firmware Buddy (6.10.1) をもとにした独立したフォークです。
> 「Prusa」「Original Prusa」「CORE One」は Prusa Research a.s. の商標で、対応機種を示すためにのみ使用しています。
>
> - インストールにはメイン基板の「アペンディクス」を折る必要があります。元に戻せず、電子部品の保証に影響します。
> - **無保証**です (GPL v3.0)。自己責任でご利用ください。
> - このファームウェアに関する問題を Prusa Research のサポートに問い合わせないでください。
>   [Issues](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/issues) にご報告ください。
>   Prusa にサポートを依頼する際は、公式ファームウェアに戻してから問い合わせてください。

The original upstream README follows [below](#buddy).

The stock firmware can only show Japanese as half-width katakana, written word by word with spaces
(セッティング ノ ロード シュウリョウ). This fork draws kanji and hiragana, and the whole Japanese
translation is rewritten in modern Japanese (設定の読み込みが完了しました).

## 概要

Prusa純正ファームウェア 6.10.1 をベースに、漢字・ひらがなで表示できるようにした非公式のコミュニティ版です。
従来のカタカナのみの日本語訳を、すべて漢字かな交じりの日本語に翻訳し直しました。

アペンディクスの折り方は Prusa の
[公式ガイド](https://help.prusa3d.com/article/zoiw36imrs-flashing-custom-firmware) を参照してください。
翻訳は機械支援によるもので、まだネイティブスピーカーによる全文チェックは済んでいません。
誤訳や表示崩れを見つけたら [Issues](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/issues) で教えてください。

## Downloads / ダウンロード

Firmware files are attached to the [releases](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/releases) of this
repository. Pick the file for your printer:

| Printer / プリンタ | File / ファイル |
|---|---|
| Original Prusa MK4, MK4S, MK3.9, MK3.9S | `mk4_*.bbf` |
| Original Prusa MK3.5, MK3.5S | `mk3.5_*.bbf` |
| Original Prusa XL | `xl_*.bbf` |
| Prusa CORE One | `coreone_*.bbf` |
| Prusa CORE One L | `coreonel_*.bbf` |
| Prusa CORE One with INDX | `coreone_indx_*.bbf` |
| Prusa CORE One L with INDX | `coreonel_indx_*.bbf` |

## Original Prusa MINI / MINI+ is not supported / MINI・MINI+ は非対応

**There is no JP Edition firmware for the MINI or MINI+, and there will not be one from this project.**
Do not flash any of the files above onto a MINI. The MINI source in this repository is left as it is
upstream, still with katakana only.

Why:
- **Its screen fonts are too small.** The MINI's smallest font is 13 px tall, smaller than the 16 px kanji.
  Kanji legible at that size would need a second, smaller kanji font.
- **Its flash is already full.** The MINI has 895 KB for the firmware, less than half of the 1919 KB the other
  printers have. It is so tight that Prusa ships a separate MINI firmware for each language. There is no
  room for a kanji font on top of that.

We have not built or measured a MINI image with kanji; these limits are what rules it out.

**MINI / MINI+ 用の JP Edition はありません。** 上記のファイルを MINI に書き込まないでください。
MINI は画面フォントが小さく（最小 13 px で、16 px の漢字が収まりません）、ファームウェア用のフラッシュも
895 KB しかなく、すでに言語ごとに別のファームウェアになるほど容量に余裕がないためです。
MINI は従来どおりカタカナ表示のままです。

**Installing / インストール:**
1. Break the appendix on the printer's main board, see Prusa's
   [guide to flashing custom firmware](https://help.prusa3d.com/article/zoiw36imrs-flashing-custom-firmware).
   This is permanent and affects the electronics warranty.
2. Copy the `.bbf` file for your printer to the root of a USB drive, insert it and restart the printer.
   Confirm the installation.
3. Select 日本語 in *Settings → Language* (設定 → 言語).

To go back, flash an official firmware from [prusa3d.com](https://www.prusa3d.com/drivers/) the same way.
The version shown on the printer ends with `-jp.N`, for example `6.10.1-jp.1`.

## Status / 状況

- Tested in the MINI404 simulator on the MK4 only. The other builds compile, but have not run on real
  hardware yet - reports welcome.
- The translation was drafted with AI assistance against a shared glossary and checked automatically
  (format strings, line structure, character set, width). A review by native speakers is still needed.
- About 125 strings are still wider than their English original and may scroll or be cut off.

## How it works

**Font.** Kana, kanji and Japanese punctuation come from
[Shinonome 16](http://openlab.ring.gr.jp/efont/shinonome/) (東雲フォント, public domain), a 16x16 bitmap font
designed for Japanese. The build embeds only the characters the translation actually uses, stored as
1 bit per pixel: 32 B of bitmap plus a 2 B index, 34 B per character. The full translation uses
498 kanji and 673 full-width characters in total, about 23 KB.

**Flash.** Everything fits in the printer's internal flash. The MK4 build is slightly *smaller* than stock,
because the fonts no longer need the half-width katakana:

| MK4 build | Flash used |
|---|---|
| Stock 6.10.1 (katakana) | 1,211,396 B |
| This fork (full translation) | 1,204,692 B |
| This fork with *every* JIS X 0208 character (6,879, all 6,355 kanji) | 1,415,124 B (72 % of 1919 KB) |

So "kanji does not fit into the printer" is not true for the 32-bit Prusa printers.

**Layout.** Full-width characters advance by 16 px, Latin characters by the width of the font (9-13 px).
Text layout, line buffers and scrolling labels measure in pixels instead of character cells.
Japanese wraps between any two full-width characters, except before characters that must not start a
line (、。ー and small kana; 禁則処理).

**Translation.** Terms prefer established kanji compounds over long katakana loanwords (校正 rather than
キャリブレーション, 自己診断 rather than セルフテスト) and drop the trailing long vowel of technical loanwords
(センサ, モータ, JIS Z 8301 style). In the menu font the Japanese UI ends up about 29 % narrower than English.

## How we did it

This was done with the help of an AI coding assistant (Claude, by Anthropic), directed and reviewed by the
maintainer. In order:

1. **Checked the claim that kanji does not fit.** Read the font pipeline and measured the stock MK4 build:
   about 750 KB of the 1919 KB firmware flash is free, and a 16x16 1-bit kanji costs 34 B. Even every kanji
   in JIS X 0208 fits (table above).
2. **Built a prototype.** Added the Shinonome font to the font generator, made text layout and rendering
   handle full-width characters, and hand-translated a few screens.
3. **Tested in the simulator.** Ran the firmware in [MINI404](https://github.com/vintagepc/MINI404),
   the QEMU-based Prusa simulator, and compared screenshots before and after. The stock simulator release
   could not boot current firmware, so we used a locally patched build (board revision, two I2C bugs and
   one display mode).
4. **Translated all 1,795 strings.** AI agents translated in batches against a shared glossary. A
   validation script checked every string: printf format codes kept in the same order, line structure,
   only characters the font contains, and width compared with English. The maintainer spot-checked
   terminology and fixed strings whose meaning depended on the code.
5. **Made it compact.** The first translation leaned on long katakana loanwords and drew each kanji in two
   Latin cells, so it came out 3 % wider than English. A second pass with a kanji-first glossary, plus drawing
   kanji at their own 16 px width, made it 29 % narrower than English.
6. **Built the release** for every 32-bit printer except the MINI, from the commits below.

What this means for you: the code has been tested only in the simulator on the MK4, and the translation is
machine-made with human spot checks, not a professional or native-speaker translation. Please report anything
wrong or unnatural in [Issues](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/issues).

The changes are in two commits on top of upstream 6.10.1:
- `gui: Draw full-width Japanese characters` - font generation (`src/module/gui/font_data`), text layout
  (`src/common/str_utils.cpp`) and rendering (`src/guiapi`).
- `lang: Translate Japanese with kanji` - `src/lang/po/ja/Prusa-Firmware-Buddy_ja.po`.

**Building it yourself:**

```bash
python utils/build.py --preset coreone --build-type release --bootloader yes
```

The `.bbf` ends up in `build/products`. See [Building](#building-on-all-platforms-without-an-ide) below
for details.

## License

Same as upstream: the source code is GPL v3.0, provided without any warranty, graphics CC BY-NC-SA 4.0 (see [LICENSE](LICENSE.md)).
The Shinonome font is public domain.

---

# Buddy
This repository includes source code and firmware releases for the Original Prusa 3D printers based on the 32-bit ARM microcontrollers.

The currently supported models are:
- Original Prusa MINI/MINI+
- Original Prusa MK3.5
- Original Prusa MK3.9
- Original Prusa MK4
- Original Prusa XL
- Prusa CORE One

## Getting Started

### Requirements

- Python 3.8 or newer
- system installation of Python's `requests` package (use either pip or your system package manager)

### Cloning this repository

Run `git clone https://github.com/prusa3d/Prusa-Firmware-Buddy.git`.

### Building (on all platforms, without an IDE)

Run `python utils/build.py`. The binaries are then going to be stored under `./build/products`.

- Without any arguments, it will build a release version of the firmware for all supported printers and bootloader settings.
- Use `--build-type` to select build configurations to be built (`debug`, `release`).
- Use `--preset` to select for which printers the firmware should be built.
- By default, it will build the firmware in "prerelease mode" set to `beta`. You can change the prerelease using `--prerelease alpha`, or use `--final` to build a final version of the firmware.
- Use `--host-tools` to include host tools in the build
- Find more options using the `--help` flag!

#### Examples:

Build the firmware for MINI and XL in `debug` mode:

```bash
python utils/build.py --preset mini,xl --build-type debug
```

Build the firmware for MINI using a custom version of gcc-arm-none-eabi (available in `$PATH`) and use `Make` instead of `Ninja` (not recommended):

```bash
python utils/build.py --preset mini --toolchain cmake/AnyGccArmNoneEabi.cmake --generator 'Unix Makefiles'
```

#### Windows 10 troubleshooting

If you have python installed and in your PATH but still getting cmake error `Python3 not found.` Try running python and python3 from cmd. If one of it opens Microsoft Store instead of either opening python interpreter or complaining `'python3' is not recognized as an internal or external command,
operable program or batch file.` Open `manage app execution aliases` and disable `App Installer` association with `python.exe` and `python3.exe`.

### Development

The build process of this project is driven by CMake and `build.py` is just a high-level wrapper around it. As most modern IDEs support some kind of CMake integration, it should be possible to use almost any editor for development. Below are some documents describing how to setup some popular text editors.

- [Visual Studio Code](doc/editor/vscode.md)
- [Vim](doc/editor/vim.md)
- [Eclipse, STM32CubeIDE](doc/editor/stm32cubeide.md)
- [Other LSP-based IDEs (Atom, Sublime Text, ...)](doc/editor/lsp-based-ides.md)

#### Contributing

If you want to contribute to the codebase, please read the [Contribution Guidelines](doc/contributing.md).

#### XL and Puppies

With the XL, the situation gets a bit more complex. The firmware of XLBuddy contains firmwares for the puppies (Dwarf and Modularbed) to flash them when necessary. We support several ways of dealing with those firmwares when developing:

1. Build Dwarf/Modularbed firmware automatically and flash it on startup by XLBuddy (the default)
    - The Dwarf & ModularBed firmware will be built from this repo.
    - The puppies are going to be flashed on startup by the XLBuddy. The puppies have to be running the [Puppy Bootloader](http://github.com/prusa3d/Prusa-Bootloader-Puppy).

2. Use pre-built Dwarf/Modularbed firmware and flash it on startup by xlBuddy
    - Specify the location of the .bin file with `DWARF_BINARY_PATH`/`MODULARBED_BINARY_PATH`.
    - For example
    ```
    cmake .. --preset xl_release_boot -DDWARF_BINARY_PATH=/Downloads/dwarf-4.4.0-boot.bin
    ```

3. Do not include any puppy firmware, and do not flash the puppies by XLBuddy.
    ```
    -DENABLE_PUPPY_BOOTLOAD=NO
    ```
    - With the `ENABLE_PUPPY_BOOTLOAD` set to false, the project will disable Puppy flashing & interaction with Puppy bootloaders.
    - It is up to you to flash the correct firmware to the puppies (noboot variant).

5. Keep bootloaders but do not write firmware on boot.
    ```
    -DPUPPY_SKIP_FLASH_FW=YES
    ```
    - With the `PUPPY_SKIP_FLASH_FW` set to true, the project will disable Puppy flashing on boot.
    - You can keep other puppies that are not debugged in the same state as before.
    - Use puppy build config with bootloaders (e.g. `xl-dwarf_debug_boot`) on one or more puppies.
    - Recommend breakpoint at the end of `puppy_task_body()` to prevent buddy from resetting the puppy immediately when puppy stops on breakpoint.

See /ProjectOptions.cmake for more information about those cache variables.

#### Running tests
See the detailed testing guide in our [comprehensive testing guide].

[comprehensive testing guide]: tests/unit/README.md

## Flashing Custom Firmware

To install custom firmware, you have to break the appendix on the board. Learn how to in the following article https://help.prusa3d.com/article/zoiw36imrs-flashing-custom-firmware.

## Feedback

- [Feature Requests from Community](https://github.com/prusa3d/Prusa-Firmware-Buddy/labels/feature%20request)

## Credits

- [Marlin](https://marlinfw.org/) - 3D printing core driver
- [Klipper](https://www.klipper3d.org/) - input shaper code based on Klipper

## License

The firmware source code is licensed under the GNU General Public License v3.0 and the graphics and design are licensed under Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0). Fonts are licensed under different license (see [LICENSE](LICENSE.md)).
