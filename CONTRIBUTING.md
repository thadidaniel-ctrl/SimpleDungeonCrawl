# How we work

Short version: **pick an issue → branch → small commits → pull request → review → merge.**

## 1. Pick up work

- All work lives in [GitHub Issues](https://github.com/jpdupree/SimpleDungeonCrawl/issues) and on the [project board](https://github.com/users/jpdupree/projects).
- Take an issue from the **Todo** column of the current milestone. Assign yourself and move it to **In Progress**.
- Only hold **1–2 issues at a time**. If life gets busy, unassign yourself and leave a comment — no guilt, that's how the board stays honest.
- Issues labeled `good first issue` are a gentle starting point for anyone new to Unreal or git.

## 2. Branch

```
git checkout main
git pull
git checkout -b 12-health-pickup
```

Name branches `<issue number>-<short-description>`.

## 3. Binary files: lock before you edit

`.uasset` and `.umap` files can't be merged. Before editing a Blueprint, material, widget, etc.:

```
git lfs lock "SimpleDungeonCrawler/Content/Path/To/Asset.uasset"
```

- `git lfs locks` shows who holds what. If someone has it, ask them in chat.
- Your locks are released when you `git lfs unlock <file>` after merging (or `git lfs unlock --id=<id>`).
- Levels use *One File Per Actor*, so editing an actor in a level only touches that actor's file under `__ExternalActors__`. You usually don't need to lock the whole `.umap`.

## 4. Commit and push

- Commit small and often, with a message that says what changed: `Add health potion pickup actor`.
- Push your branch: `git push -u origin 12-health-pickup`.
- **Before pushing, make sure the project compiles and opens.** A broken `main` blocks everyone.

## 5. Pull request

- Open a PR into `main`. Put `Closes #12` in the description so the issue closes on merge.
- Describe **how to test it** (e.g. "Play as Listen Server, 2 players, pick up the potion on client 2").
- At least **one teammate reviews** before merging. Reviewing is how we all learn the codebase — ask questions freely.
- Merge with **Squash and merge**, then delete the branch.

## 6. Definition of done

An issue is done when:

- [ ] It works in **Play As Listen Server with 2+ players** (anything gameplay-related must work on clients, not just the host)
- [ ] It compiles with no new warnings
- [ ] It's merged to `main`
- [ ] Any locks are released

## Weekly rhythm

- **Weekly check-in (~30 min, or async in chat):** what I finished, what I'm doing next, what's blocking me.
- **End of each milestone:** play the game together for 20 minutes, file bugs as issues, then plan the next milestone.

## Where things go

| Thing | Location |
|---|---|
| C++ code | `SimpleDungeonCrawler/Source/SimpleDungeonCrawler/` |
| Our own game assets | `SimpleDungeonCrawler/Content/Dungeon/` (subfolders: `Blueprints`, `Maps`, `UI`, `Art`, `Audio`) |
| Your personal test stuff | `SimpleDungeonCrawler/Content/Developers/<YourName>/` — never referenced by real content |
| Design decisions | [docs/DESIGN.md](docs/DESIGN.md) |
