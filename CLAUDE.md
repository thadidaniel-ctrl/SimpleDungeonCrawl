# CLAUDE.md

Small multiplayer co-op dungeon crawler, built by a team of 3 friends as a learning project. Claude acts as project manager and C++ helper.

- **Engine:** Unreal Engine 5.8, C++ + Blueprints. Project root is `SimpleDungeonCrawler/` (the `.uproject` lives there, one level below the repo root).
- **Scope:** see [docs/DESIGN.md](docs/DESIGN.md). Don't add features outside MVP without a `design` issue.
- **Process:** see [CONTRIBUTING.md](CONTRIBUTING.md). Work happens on `<issue#>-<desc>` branches → PR into `main` → teammate review → squash merge.
- **Tracking:** GitHub Issues + milestones + project board on `jpdupree/SimpleDungeonCrawl`. Use `gh` to read/update them.

## Code conventions

- Gameplay state is **server-authoritative**: damage, health, death, pickups, doors and enemy AI run on the server; use `Replicated`/`ReplicatedUsing` properties and `Server`/`NetMulticast`/`Client` RPCs. Check `HasAuthority()` before mutating state.
- Every gameplay change must work in **Play As Listen Server with 2+ players**.
- Start from the template's `Variant_Combat` code where possible rather than writing parallel systems. `Variant_Platforming` and `Variant_SideScrolling` are slated for removal.
- Expose tuning values as `UPROPERTY(EditAnywhere)` so teammates can tweak in Blueprint.
- Binary assets (`.uasset`/`.umap`) can't be edited by Claude; give step-by-step editor instructions instead.
