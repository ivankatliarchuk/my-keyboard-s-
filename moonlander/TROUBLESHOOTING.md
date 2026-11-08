# Moonlander Troubleshooting

## Idle-hang: keyboard stops responding after ~1 minute, requires USB replug

### Symptom

- Mac is awake and in active use.
- Keyboard works fine while typing.
- After roughly 1 minute of not pressing any keys, the keyboard goes silent.
- No key presses register. Only physically unplugging and replugging the USB-C cable restores it.
- Different cables and different ports (direct, through monitor) make no difference.

### Confirmed diagnosis

macOS is **not** dropping the device. The keyboard stays attached in `ioreg` and no USB disconnect events are logged in the system log. The firmware inside the keyboard is going silent on its own while USB stays "connected" from the host side. That is why only USB re-enumeration (physical replug) recovers it, not any OS-level reset.

### Diagnostic commands (read-only, safe to re-run)

Check power management settings (look for `displaysleep`, `sleep`, `standby`):

```
pmset -g
```

Confirm the keyboard is currently attached and its power state:

```
ioreg -p IOUSB -l -w 0 | grep -A 20 -i moonlander
```

List all USB devices with vendor/product strings:

```
ioreg -p IOUSB -l -w 0 | grep -iE "idProduct|idVendor|USB Product Name|USB Vendor Name" | head -n 60
```

Search macOS logs for Moonlander-related events over the last 2 hours:

```
/usr/bin/log show --last 2h --info --predicate 'eventMessage CONTAINS "Moonlander"' | tail -n 40
```

Search USB subsystem logs for disconnect, suspend, or Moonlander events:

```
/usr/bin/log show --last 2h --info --predicate 'subsystem == "com.apple.iokit.IOUSBHostFamily"' 2>&1 | grep -iE "disconnect|reset|suspend|resume|detach|attach|moonlander"
```

Pull printable strings out of a firmware binary:

```
strings -n 6 <path-to-firmware>.bin | grep -iE "qmk|rgb|idle|version"
```

### Firmware findings (from the Oryx source bundle `zsa_moonlander_*_source`)

Files examined inside `zsa_moonlander_ivka-moonlander-2026-fork_source/`:

- `config.h`
- `rules.mk`
- `keymap.c`
- `keymap.json`
- `build.log`

Key facts about the current build:

1. `RGB_MATRIX_TIMEOUT` is **not** defined in `config.h`. "Disable RGB after inactivity" is OFF. The RGB idle code path is never triggered, so RGB idle is not the cause.
2. `rules.mk` has `ORYX_ENABLE = yes`. The ZSA Oryx live-view module is compiled in. This opens a raw HID channel for the Oryx webpage to show live keypresses.
3. `config.h` sets `USB_POLLING_INTERVAL_MS 10` (100 Hz polling). The QMK default is 1 ms (1000 Hz). Slower than typical; see note below.
4. `keymap.c` references `rawhid_state.rgb_control` in 9 places. Every custom keycode bails out if the Oryx RGB control flag is set.
5. The build log shows modern QMK with `wear_leveling` EEPROM and ARM GCC 12.2. Compiles clean, no warnings or errors.
6. The compiled `.bin` contains the embedded strings `wear_leveling`, `idle`, and the layout tag `RyYle/v6Bd9r` (matches keyboard serial). First bytes are a standard STM32F303 vector table.

### USB polling interval, firmware vs OS

The polling interval is set by the **keyboard**, not the OS. QMK writes `USB_POLLING_INTERVAL_MS` into the `PollingIntervalMS` (`bInterval`) field of every HID endpoint descriptor. The OS polls no faster than the keyboard advertises; it can throttle slower under power management but cannot override upward. Relevant source: `tmk_core/protocol/usb_descriptor.c` lines 729-730 (default is 1 ms) and the five endpoint definitions that use it.

### Current working theory

The idle-hang is most likely in the raw HID path used by the ZSA Oryx module. When an Oryx-enabled browser tab is open, the module stays paired and sends a packet on every keypress. If the host stops reading that endpoint (tab backgrounded, browser throttling, extension misbehaving), the IN buffer fills up. The next keypress calls `send_report` on a full endpoint, which blocks on a ChibiOS USB driver mutex. On some ChibiOS versions that lock can be held across a USB suspend, and the main loop never gets past it, which matches the "only replug recovers" symptom.

### Things to try, cheapest first

1. Close every browser tab on `configure.zsa.io`, disable any ZSA browser extensions, and quit Keymapp. Use the keyboard for a day. If hangs stop, the raw HID path is confirmed as the trigger.
2. Set USB polling interval back to 1 ms in Oryx Layout Settings (Advanced section). This is a cheap test rather than a strong hypothesis.
3. Build locally with `ORYX_ENABLE = no` in `rules.mk` to remove the Oryx module entirely and flash that firmware.
4. If none of the above resolves it, email `contact@zsa.io` with the keyboard serial `RyYle/v6Bd9r`, firmware build date, and a note that macOS `ioreg` shows the keyboard attached when it hangs.

### Relevant repositories and source locations

ZSA QMK fork (what Oryx compiles against):

- URL: `https://github.com/zsa/qmk_firmware`
- Branch naming: `firmware25`, `firmware24`, etc, matching the version shown on the Oryx layout badge
- Clone:

```
git clone https://github.com/zsa/qmk_firmware.git
cd qmk_firmware
git submodule update --init --recursive
```

ZSA community modules (contains the Oryx raw HID module):

- URL: `https://github.com/zsa/qmk_modules`
- Mounted as submodule at `modules/zsa/` inside the qmk_firmware clone

User's local fork of the ZSA QMK tree (already cloned):

- Path: `/Users/ik/source/self/keyboard/qmk_firmware-fork`
- Remote: `https://github.com/ivankatliarchuk/qmk_firmware-fork.git`
- Current branch: `firmware25`

Specific files of interest in the user's local fork:

- `modules/zsa/oryx/oryx.c` (Oryx raw HID module, 10.7 KB)
- `modules/zsa/oryx/oryx.h` (protocol definitions, `rawhid_state_t`)
- `modules/zsa/oryx/config.h` (defines `ORYX_ENABLE`, `ORYX_CONFIGURATOR`)
- `quantum/raw_hid.c` (QMK raw HID endpoint handler)
- `tmk_core/protocol/usb_descriptor.c` (USB descriptors including `PollingIntervalMS`)
- `keyboards/zsa/moonlander/moonlander.c` (board-specific code, not yet reviewed)
- `keyboards/zsa/moonlander/matrix.c` (matrix scan over I2C to MCP23018, not yet reviewed)
- `keyboards/zsa/moonlander/reva/keyboard.json` and `revb/keyboard.json`

Oryx layout (Ivan's current):

- URL: `https://configure.zsa.io/moonlander/layouts/RyYle/v6Bd9r/0`
- Serial embedded in firmware: `RyYle/v6Bd9r`

Source bundle downloaded from Oryx for current build:

- Path: `/Users/ik/Downloads/zsa_moonlander_reva_RyYle_v6Bd9r_ivka-moonlander-2026-fork_source/`
- Contains both `reva` and `revb` compiled binaries; Keymapp auto-selects which to flash.

### Building locally against the ZSA fork

Drop the layout source files into the fork's keymaps directory:

```
cp -r /Users/ik/Downloads/zsa_moonlander_reva_RyYle_v6Bd9r_ivka-moonlander-2026-fork_source/zsa_moonlander_ivka-moonlander-2026-fork_source \
      /Users/ik/source/self/keyboard/qmk_firmware-fork/keyboards/zsa/moonlander/keymaps/ivka-2026
```

Compile for revb (modern hardware, most Moonlanders bought 2022+):

```
cd /Users/ik/source/self/keyboard/qmk_firmware-fork
qmk compile -kb zsa/moonlander/revb -km ivka-2026
```

Or for reva:

```
qmk compile -kb zsa/moonlander/reva -km ivka-2026
```

Output `.bin` lands at the repo root. Flash with Keymapp (drag the file in) or `qmk flash` after pressing the reset button under the top-left thumb cluster.
