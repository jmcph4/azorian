# Contributing #
---

The project aims to implement the multiformat specifications in memory-safe ISO C11 and is open to assistance from the entire OSS community.

## Workflow ##
1. **Pick or create an issue**. Regardless of whether it's a bug report, an enhancement, or a feature request - if you're proposing new work, open an issue first. IF you're using an existing issue, skip to Step 2.
2. **Discuss**. Use this issue to discuss whatever the task at hand is. Wait to be assigned the issue directly.
3. **Fork**. Fork this repository.
4. **Create a new branch on your local**. Create a branch on your local called `fix[n]` where `n` is the issue number.
5. **Work on your issue**. Push your changes to your local on your newly-created branch.
6. **Submit pull request**. Submit a PR to this repository and await a code review. You should add as much information as you can about your changes and design choices. Also ensure you ditectly reference the associated issue (e.g. "See #[n]").

## Getting your PR accepted ##
As the project only has one maintainer right now, and this maintainer does not work anywhere near full-time on this project, do not expect instant code reviews.

While your help is encouraged and appreciated, to keep things simple (and *stable*), if your branch is not passing CI, it **will not be merged**. The good news is that we try to place as much work on CI as possible, so if your changes pass CI, they're already halfway to being merged.

## Picking an existing issue ##
Issues are labeled accordingly, so issues labeled with `help wanted` want help! Issues that are deemed ideal for first time contributors to either the project or OSS in general are labeled with `good first issue`.

Bugs are labeled `bug` and enhancements are labeled `enhancement`.

## Commit message style ##
This project uses [this standard](https://chris.beams.io/posts/git-commit/#seven-rules) for commit messages. Please adhere to it in all of your commits. While no particular workflow is required, a good one to use is:

    $ git add [files_to_commit]     # add required changes
    $ $EDITOR msg.tmp               # use your favourite editor to write the commit message
    $ git status                    # double check your staged changes
    $ cat msg.tmp                   # double check your commit message
    $ git commit -F msg.tmp         # commit your changes

