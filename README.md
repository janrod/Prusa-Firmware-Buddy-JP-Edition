# Prusa Firmware Buddy - JP Edition (日本語・漢字対応ファームウェア)

> [!CAUTION]
> ## ⚠️ Unofficial firmware - read before installing
>
> **This is unofficial community firmware. It is not made, tested, endorsed or supported by Prusa Research.**
> It is an independent fork of the open-source
> [prusa3d/Prusa-Firmware-Buddy](https://github.com/prusa3d/Prusa-Firmware-Buddy) (6.10.1).
> "Prusa", "Original Prusa" and "CORE One" are trademarks of Prusa Research a.s., used here only to say
> which printers the firmware is for.
>
> - **You have to break the appendix seal on the printer's main board to install it.** From the factory the
>   printer only accepts firmware signed by Prusa. Breaking the seal is permanent - it cannot be undone - and
>   lets the printer accept any firmware.
> - **What Prusa says:** "Breaking the appendix seal won't void your warranty", but Prusa "disclaim[s]
>   liability for any kind of damage or harm a printer with a broken seal may cause (e.g. in case of a fire)."
>   Read Prusa's article for your printer before you start:
>   - CORE One L, CORE One, MK4/S, MK3.9/S, MK3.5/S:
>     [Flashing custom firmware](https://help.prusa3d.com/article/flashing-custom-firmware-core-one-l-core-one-mk4-s-mk3-9-s-mk3-5-s_814967) (seal on the xBuddy board, inside the electronics box)
>   - XL: [Imposter! Fake signature #17606 (XL)](https://help.prusa3d.com/article/imposter-fake-signature-17606-xl_399880) (seal on the XLBuddy board)
> - **No warranty from this project** (GPL v3.0). It has only been tested in a simulator on the MK4, never on
>   real hardware. Use it entirely at your own risk.
> - **Do not contact Prusa Research support about this firmware.** Report problems in this repository's
>   [Issues](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/issues), and flash official firmware
>   again before asking Prusa for help.
> - **MINI / MINI+ is not supported** - see [below](#original-prusa-mini--mini-is-not-supported--minimini-は非対応).
>
> ## ⚠️ 非公式ファームウェアです - インストール前に必ずお読みください
>
> **非公式のコミュニティ版です。Prusa Research による作成・テスト・承認・サポートは一切ありません。**
> オープンソースの Prusa Firmware Buddy (6.10.1) をもとにした独立したフォークです。
> 「Prusa」「Original Prusa」「CORE One」は Prusa Research a.s. の商標で、対応機種を示すためにのみ使用しています。
>
> - **インストールにはメイン基板の「アペンディクス」(シール)を折る必要があります。** 出荷時のプリンタは Prusa が
>   署名したファームウェアしか受け付けません。折ると元に戻せず、以後どのファームウェアでも書き込めるようになります。
> - **Prusa の説明:** アペンディクスを折っても保証は無効になりません。ただし、アペンディクスを折ったプリンタが
>   引き起こす損害 (火災など) について Prusa は一切責任を負いません。作業前に機種ごとの Prusa の記事を確認してください:
>   - CORE One L、CORE One、MK4/S、MK3.9/S、MK3.5/S: [Flashing custom firmware](https://help.prusa3d.com/article/flashing-custom-firmware-core-one-l-core-one-mk4-s-mk3-9-s-mk3-5-s_814967)
>   - XL: [Imposter! Fake signature #17606 (XL)](https://help.prusa3d.com/article/imposter-fake-signature-17606-xl_399880)
> - **本プロジェクトは無保証です** (GPL v3.0)。MK4 のシミュレータでのみ動作確認しており、実機ではまだテストしていません。
>   すべて自己責任でご利用ください。
> - **このファームウェアについて Prusa Research のサポートに問い合わせないでください。** 不具合は
>   [Issues](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/issues) にご報告ください。
>   Prusa にサポートを依頼する際は、公式ファームウェアに戻してから問い合わせてください。
> - **MINI / MINI+ には対応していません。**

The original upstream README follows [below](#original-readme-prusa-firmware-buddy).

The stock firmware can only show Japanese as half-width katakana, written word by word with spaces
(セッティング ノ ロード シュウリョウ). This fork draws kanji and hiragana, and the whole Japanese
translation is rewritten in modern Japanese (設定の読み込みが完了しました).

## 概要

Prusa純正ファームウェア 6.10.1 をベースに、漢字・ひらがなで表示できるようにした非公式のコミュニティ版です。
従来のカタカナのみの日本語訳を、すべて漢字かな交じりの日本語に翻訳し直しました。

アペンディクスの折り方は、上記の機種ごとの Prusa の記事を参照してください。
翻訳は機械支援によるもので、まだネイティブスピーカーによる全文チェックは済んでいません。
誤訳や表示崩れを見つけたら [Issues](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/issues) で教えてください。

## Downloads / ダウンロード

Firmware files are attached to the [releases](https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition/releases) of this
repository, for example `COREONE_6.10.1-jp.1.bbf`. Pick the file for your printer; `SHA256SUMS.txt`
lists the checksums.

| Printer / プリンタ | File / ファイル |
|---|---|
| Original Prusa MK4, MK4S, MK3.9, MK3.9S | `MK4_<version>.bbf` |
| Original Prusa MK3.5, MK3.5S | `MK3.5_<version>.bbf` |
| Original Prusa XL | `XL_<version>.bbf` |
| Prusa CORE One | `COREONE_<version>.bbf` |
| Prusa CORE One L | `COREONEL_<version>.bbf` |
| Prusa CORE One with INDX | `COREONE_INDX_<version>.bbf` |
| Prusa CORE One L with INDX | `COREONEL_INDX_<version>.bbf` |

## Original Prusa MINI / MINI+ is not supported / MINI・MINI+ は非対応

**There is no JP Edition firmware for the MINI or MINI+, and there will not be one from this project.**
Do not flash any of the files above onto a MINI, and do not build this repository for a MINI either: all
printers share one Japanese translation, so a MINI build would show `?` in place of every kanji. MINI owners
should keep using [Prusa's official firmware](https://www.prusa3d.com/drivers/), which shows Japanese in katakana.

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
このリポジトリを MINI 向けにビルドしないでください。翻訳ファイルは全機種共通のため、漢字がすべて「?」で表示されます。
MINI では Prusa の公式ファームウェア (カタカナ表示) をそのままご利用ください。

**Installing / インストール:**
1. Break the appendix seal on the printer's main board, following Prusa's article for your printer:
   [CORE One L, CORE One, MK4/S, MK3.9/S, MK3.5/S](https://help.prusa3d.com/article/flashing-custom-firmware-core-one-l-core-one-mk4-s-mk3-9-s-mk3-5-s_814967) or [XL](https://help.prusa3d.com/article/imposter-fake-signature-17606-xl_399880). This is permanent.
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

1. **Measured the flash budget.** Read the font pipeline and measured the stock MK4 build: about 750 KB of
   the 1919 KB firmware flash is free, and a 16x16 1-bit kanji costs 34 B, so even every kanji in JIS X 0208
   fits (table above).
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

The changes are commits on top of upstream 6.10.1:
- `gui: Draw full-width Japanese characters` - font generation (`src/module/gui/font_data`), text layout
  (`src/common/str_utils.cpp`) and rendering (`src/guiapi`).
- `lang: Translate Japanese with kanji` - `src/lang/po/ja/Prusa-Firmware-Buddy_ja.po`.

**Building it yourself:**

```bash
git clone https://github.com/janrod/Prusa-Firmware-Buddy-JP-Edition.git
cd Prusa-Firmware-Buddy-JP-Edition
python utils/build.py --preset coreone --build-type release --bootloader yes
```

The `.bbf` ends up in `build/products`. See [Building](#building-on-all-platforms-without-an-ide) below
for details.

## License

Same as upstream: the source code is GPL v3.0, provided without any warranty, graphics CC BY-NC-SA 4.0 (see [LICENSE](LICENSE.md)).
The Shinonome font is public domain.

---

# Original README (Prusa Firmware Buddy)

> This is the upstream README of [prusa3d/Prusa-Firmware-Buddy](https://github.com/prusa3d/Prusa-Firmware-Buddy),
> kept for reference. Strikethrough marks what does not apply to the JP Edition.

## Buddy
This repository includes source code and firmware releases for the Original Prusa 3D printers based on the 32-bit ARM microcontrollers.

The currently supported models are:
- ~~Original Prusa MINI/MINI+~~ (not supported by the JP Edition)
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
