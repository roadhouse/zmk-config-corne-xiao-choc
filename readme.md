Chippy (Corne Choc + XIAO BLE) ZMK config and shield.

Current hardware target:
- Split Corne 3x6 + 3 thumb keys
- No display
- No RGB

Source of truth:
- Keymap: `config/chippy.keymap`
- Runtime config: `config/chippy.conf`

Build with Docker (local):
- `make build` (builds both halves)
- `make build-left`
- `make build-right`
- `make keymap-image` (generate SVG layout image from keymap)
- `make update` (force dependency update)
- `make rebuild` (clean + build)

Output files:
- ZMK default outputs:
  - `build/chippy_left/zephyr/zmk.uf2`
  - `build/chippy_right/zephyr/zmk.uf2`
- Renamed copies (for clarity):
  - `build/artifacts/chippy_left-xiao_ble-zmk.uf2`
  - `build/artifacts/chippy_right-xiao_ble-zmk.uf2`
- Keymap image:
  - `build/artifacts/keymap.svg`

Notes:
- `make keymap-image` checks if `keymap-drawer` is installed before generating files.
