# retronomicon-conversation

Retronomicon module for visual-novel style conversation scenes.

## Responsibilities

This module owns conversation data loading, node traversal, textbox rendering,
conversation input, and conversation-specific character module setup. It should
stay independent from concrete graphics and audio backends.

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

Node fields currently handled by `ConversationLoader` are `speaker`,
`background`, `expression`, `text`, `next`, `choices`, and `actions`.

## Runtime Requirements

`ConversationScene` expects to run inside a configured `GameEngine`. Before
initializing a graphical conversation scene, set the engine, register character
module loaders, load the character database, configure the font, and configure
the textbox background image.

The scene uses:

- `AssetManager` for backgrounds, fonts, and textbox art.
- `CharacterDatabase` for speaker sprites and expressions.
- render and input systems from the engine.
- `ConversationCharacterModuleLoader` for character JSON sections named
  `retronomicon-conversation`.

## Reference Project

Use `~/Desktop/project-yuzu` as the reference for current behavior:

- `asset/conversation/conversation.json`: example conversation schema.
- `asset/conversation/characters.json`: character database entry point.
- `asset/conversation/characters/*.json`: conversation character module data.
- `sandbox-opengl/main_conv.cpp`: minimal console traversal example.
- workspace `sandbox/main.cpp`: older graphical setup flow.
- workspace `examples/conversation-console`: active backend-neutral data
  traversal example.

## Current Migration State

The graphical module still includes the old `retronomicon/lib/...` API and does
not compile against the current `retronomicon` core branch. Keep
`RETRONOMICON_BUILD_CONVERSATION` off until the includes and runtime dependencies
are migrated to the current core interfaces.

Use the workspace `examples/conversation-console` target as the active,
backend-neutral data contract example. It parses the same conversation JSON,
validates node links, and traverses the story from the `start` node.

## Migration Checklist

1. Replace old `retronomicon/lib/core/*` includes with current `entity`,
   `component`, `scene`, `system`, and `engine` headers.
2. Remove SDL scancodes from conversation input and bind engine `Key` values.
3. Inject renderer, texture manager, raw input, and audio through current core
   interfaces instead of accessing SDL-specific objects.
4. Add tests for `ConversationLoader` parsing before restoring the graphical
   scene target.
5. Add a graphical `conversation-example` after `retronomicon-conversation`
   builds cleanly with the selected backend.
