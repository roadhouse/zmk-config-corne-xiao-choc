# Backlog

## BLE TX power (deferred)
- Context: the repo currently uses `CONFIG_BT_CTLR_TX_PWR_PLUS_8=y` in `config/chippy.conf`.
- Why deferred: this is not critical right now because battery life is already good.
- Open question: what is the best balance between battery life and connection stability in your real environment.
- Next step: test lower TX levels (`+4` and `0`) for a few days and compare split-link stability, host-link stability, and perceived battery life.

## `xiaoReset.uf2` handling
- Context: `xiaoReset.uf2` is kept in the repository as a prebuilt reset/recovery UF2 for XIAO.
- Decision pending: keep it in the repo or remove it and document how to obtain/use it when needed.
- Next step: choose one policy and update docs accordingly.

## Ergonomic layout ideas (ZMK-only, QWERTY unchanged)
- Sticky modifiers for pinky relief:
  - `&sk LSHIFT` for one-shot shift.
  - Evaluate `&sk LCTRL` as an optional one-shot ctrl.
- Hold-tap tuning on thumbs:
  - Keep dual-role thumbs and tune timing/behavior only if needed.
- Mod-morph opportunities:
  - Test `BSPC` -> `DEL` when shift is held.
- Macro opportunities:
  - Add tmux-focused macros for repeated workflows.
- Sticky layer opportunities:
  - Test `&sl` for temporary access to symbols/navigation without long holds.
- Strategy note for frequent ctrl use:
  - Keep thumb hold-ctrl as primary path for high-frequency chords.
  - Optionally add sticky-ctrl as a secondary path for reduced pinky strain.

## HRM pilot (deferred): F/J only
- Scope: test home-row mod behavior on `F` and `J` only (do not change QWERTY letters).
- Goal: evaluate whether this reduces pinky load without introducing typing friction.
- Guardrails:
  - Keep thumb hold-ctrl as the primary ctrl path.
  - Keep current dedicated tmux activation key (`Ctrl+A`) during the pilot.
- Evaluation criteria:
  - misfire rate (tap interpreted as hold, hold interpreted as tap);
  - perceived finger fatigue after long terminal sessions;
  - impact on speed/confidence in tmux/zsh usage.
