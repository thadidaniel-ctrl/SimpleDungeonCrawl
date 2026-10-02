# SimpleDungeonCrawler

A simple multiplayer dungeon crawler built with Unreal Engine 5, made by a few friends learning game dev.

## Getting started

1. Install [Git](https://git-scm.com/) and [Git LFS](https://git-lfs.com/), then run `git lfs install` once.
2. Clone the repo:
   ```
   git clone https://github.com/jpdupree/SimpleDungeonCrawl.git
   ```
3. Install **Unreal Engine 5.8** and **Visual Studio 2022** with the "Game development with C++" workload (or JetBrains Rider).
4. Open `SimpleDungeonCrawler/SimpleDungeonCrawler.uproject`. The first time, Unreal will ask to rebuild the C++ modules; say **Yes** (this takes a few minutes). If the rebuild fails, right-click the `.uproject` → **Generate Visual Studio project files**, open the `.sln`, and build the `Development Editor` configuration.

## Working together

- Pull before you start working, and commit and push often.
- `.uasset` and `.umap` files are binary and **can't be merged**. Before you edit a shared level or Blueprint, lock it:
  ```
  git lfs lock Content/Maps/MyLevel.umap
  ```
  Unlock it after you push: `git lfs unlock Content/Maps/MyLevel.umap`. Run `git lfs locks` to see who holds what.
- Do bigger features on a branch and open a pull request.
