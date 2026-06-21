# Repository Guidelines

## Project Structure & Module Organization

`retronomicon-conversation` is the visual-novel/conversation module for the base engine. Public headers live in `include/retronomicon/lib/conversation/`. Implementations are in `src/lib/conversation/`, with `data/` for nodes, choices, speakers, and actions, `input/` for input components, and loader/scene/textbox code at the module root. It is usually built by the workspace root after `retronomicon`.

## Build, Test, and Development Commands

- From the workspace root, run `./build-sandbox.sh` to build the module with the engine and sandbox.
- Use `cmake -S . -B build` and `cmake --build build` at the workspace root for manual builds.
- Run `./play.sh` at the workspace root to check dialogue behavior in the sandbox.

The module links against `retronomicon` and `nlohmann_json::nlohmann_json`; do not add duplicate dependency copies unless making a standalone build path.

## Coding Style & Naming Conventions

Use C++17 and existing naming. Files use lowercase snake case, for example `conversation_loader.cpp` and `vn_textbox_component.h`. Types use PascalCase (`ConversationNode`); functions and variables use lower camelCase (`loadFromJSON`, `nodeData`). Keep JSON parsing defensive and return `nullptr` or clear errors for invalid input.

## Testing Guidelines

No module-local tests are currently defined. Add Catch2 tests as `test_*.cpp` if introducing parser or state-machine changes. Focus on JSON loading from strings, missing fields, choice transitions, and action parsing. Always verify with the workspace build and, when assets change, sandbox playback.

## Commit & Pull Request Guidelines

Use short imperative commit messages such as `fix conversation loader` or `add speaker expressions`. PRs should include changed conversation JSON shape, affected asset paths, and the command used for verification.
