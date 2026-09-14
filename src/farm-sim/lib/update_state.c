#include "update_state.h"
#include "globals.h"
#include "raylib.h"
#include "state.h"

static void handleInput(GameState *state, float dt) {
  if (IsKeyDown(KEY_H)) {
    state->avatar.x -= AVATAR_SPEED * dt;
    if (state->avatar.x < 0) {
      state->avatar.x = 0;
    }
  }
  if (IsKeyDown(KEY_J)) {
    state->avatar.y += AVATAR_SPEED * dt;
    if (state->avatar.y > WORLD_HEIGHT - state->avatar.height) {
      state->avatar.y = WORLD_HEIGHT - state->avatar.height;
    }
  }
  if (IsKeyDown(KEY_K)) {
    state->avatar.y -= AVATAR_SPEED * dt;
    if (state->avatar.y < 0) {
      state->avatar.y = 0;
    }
  }
  if (IsKeyDown(KEY_L)) {
    state->avatar.x += AVATAR_SPEED * dt;
    if (state->avatar.x > WORLD_WIDTH - state->avatar.width) {
      state->avatar.x = WORLD_WIDTH - state->avatar.width;
    }
  }
  state->camera.target.x = state->avatar.x;
  state->camera.target.y = state->avatar.y;
}

void updateState(GameState *state, float dt) {
  handleInput(state, dt);
}

