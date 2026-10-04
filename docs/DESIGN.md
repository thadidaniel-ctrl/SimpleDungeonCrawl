# SimpleDungeonCrawler — Design One-Pager

> Living document. If you want to change scope, open an issue labeled `design` and we'll decide together.

## Pitch

1–3 friends dive into a short, hand-built dungeon, fight their way through a few rooms of enemies, find the key, and beat the boss together. One run takes about 10 minutes.

## Goals

The real goal is **learning to build a game as a team**: git, branches, pull requests, splitting work, and actually finishing. The game is deliberately small so we can ship it in 8 weeks.

## Core loop

1. **Main menu** → Host or Join (by IP address).
2. **Spawn** in the dungeon entrance with up to 3 players.
3. **Explore** rooms, fight enemies with melee combos, grab health potions.
4. **Find the key** → open the locked boss door.
5. **Beat the boss** → Victory screen. **Everyone dies** → Defeat screen → back to menu.

## MVP scope (must ship)

| Area | What's in |
|---|---|
| Multiplayer | Listen server (one player hosts), join by IP, up to 3 players, everything that matters is synced. |
| Player | Third-person movement, melee combo + charged attack (from the template's Combat variant), health, death. |
| Enemies | One basic melee enemy type + one boss (bigger, more HP, one extra attack). |
| Dungeon | One hand-built level: entrance, ~4 combat rooms, key room, boss room. |
| Items | Health potion pickup, key pickup, locked door. |
| UI | Main menu, HUD (own health + teammates' health), victory/defeat screens. |
| Feel | Basic sounds (hits, pickups, music), simple VFX, free art from Fab/Quixel. |

## Stretch goals (only after MVP is done)

- Revive downed teammates
- A second enemy type (ranged)
- Online play through Steam sessions instead of direct IP
- Procedural room layout
- Loot / gold / simple upgrades between runs

## Explicitly out of scope

Character classes, inventory screens, skill trees, save systems, dedicated servers, mobile, and monetization of any kind.

## Tech notes

- **Engine:** Unreal Engine 5.8, C++ project with Blueprints on top.
- **Starting point:** the Third Person template's `Variant_Combat` code (combo attacks, damage interface, State Tree AI, spawner, life bars). It is single-player only, so making it **server-authoritative** is milestone 1.
- **Networking rule of thumb:** the server decides (damage, health, death, pickups, doors); clients request actions and play the visuals.
- **Levels** use World Partition with *One File Per Actor*, so two people can edit different actors in the same level without conflicts.
