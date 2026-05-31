#!/usr/bin/env python3

import json
import sys
from pathlib import Path


def load_fragment(path: Path):
    text = path.read_text(encoding="utf-8").strip()

    if not text:
        return None

    if text.endswith(","):
        text = text[:-1]

    return json.loads(text)


def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <fragment-dir> <output-json>")
        return 1

    fragment_dir = Path(sys.argv[1])
    output_json = Path(sys.argv[2])

    entries = []

    if fragment_dir.exists():
        for frag in sorted(fragment_dir.rglob("*.json")):
            try:
                entry = load_fragment(frag)
                if entry is not None:
                    entries.append(entry)
            except Exception as e:
                print(f"warning: failed to parse {frag}: {e}", file=sys.stderr)

    output_json.write_text(
        json.dumps(entries, indent=2, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )

    print(f"generated {output_json} with {len(entries)} entries")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
