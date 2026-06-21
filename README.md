# retronomicon-conversation

Retronomicon module for visual-novel style conversation scenes.

## Responsibilities

This module owns backend-neutral conversation data loading, validation, and node
traversal. Textbox rendering, input binding, audio cues, and character sprite
presentation should be implemented as adapters on top of this module.

## Data Format

Conversation files use JSON with a `background` map and keyed `nodes`:

```json
{
  "background": {
    "office-door": "asset/image/office_door.png"
  },
  "nodes": {
    "start": {
      "speaker": "jenna",
      "background": "office-door",
      "expression": "neutral",
      "text": "Hello.",
      "next": null
    }
  }
}
```

Node fields handled by `ConversationLoader` are `speaker`, `background`,
`expression`, `text`, `next`, `choices`, and `actions`.

## Public API

Use the current namespace and headers:

- `retronomicon/conversation/conversation_loader.h`
- `retronomicon/conversation/conversation_document.h`
- `retronomicon/conversation/conversation_state.h`

`ConversationLoader` parses JSON into a `ConversationDocument`.
`ConversationDocument::validate()` reports missing start nodes, broken `next`
links, broken choice links, and unknown background references.
`ConversationState` tracks the active node and supports `advance()`, `choose()`,
and `jumpTo()`.

## Runtime Requirements

Build from the workspace root:

```sh
cmake -S . -B build
cmake --build build --target retronomicon-conversation-tests
cmake --build build --target conversation-console
./build/bin/conversation-console
```

Link gameplay or examples against `retronomicon-conversation`; do not include
the old `retronomicon/lib/conversation/...` headers in new code.

## Reference Project

Use `~/Desktop/project-yuzu` as the reference for current behavior:

- `asset/conversation/conversation.json`: example conversation schema.
- `asset/conversation/characters.json`: character database entry point.
- `asset/conversation/characters/*.json`: conversation character module data.
- `sandbox-opengl/main_conv.cpp`: minimal console traversal example.
- workspace `sandbox/main.cpp`: older graphical setup flow.
- workspace `examples/conversation-console`: active backend-neutral data
  traversal example.

## Current Graphical State

The stale graphical scene, textbox component, and character module loader files
under `include/retronomicon/lib/conversation/` and `src/lib/conversation/` are
kept for reference but are not part of the current CMake target. Do not add them
back to the build without migrating them to the current core interfaces.

Use the workspace `examples/conversation-console` target as the active data
contract example. It parses the same conversation JSON, validates links, and
traverses the story from the start node through `ConversationState`.

## Migration Checklist

1. Add a graphical `conversation-example` target that consumes
   `ConversationDocument` and `ConversationState`.
2. Replace old `retronomicon/lib/core/*` includes with current `entity`,
   `component`, `scene`, `system`, and `engine` headers before reusing legacy
   scene files.
3. Remove SDL scancodes from conversation input and bind engine `Key` values.
4. Inject renderer, texture manager, raw input, and audio through current core
   interfaces instead of accessing SDL-specific objects.
5. Keep parser/traversal behavior covered by `retronomicon-conversation-tests`.
