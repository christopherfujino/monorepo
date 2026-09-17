#include <stdlib.h> // abort()

#include "globals.h"
#include "raylib.h"
#include "state.h"
#include "update_state.h"

static inline void _handleInput(GameState *state, float dt) {
  if (IsKeyDown(KEY_H)) {
    state->avatar.destRect.x -= AVATAR_SPEED * dt;
    if (state->avatar.destRect.x < 0) {
      state->avatar.destRect.x = 0;
    }
  }
  if (IsKeyDown(KEY_J)) {
    state->avatar.destRect.y += AVATAR_SPEED * dt;
    if (state->avatar.destRect.y >
        WORLD_HEIGHT - state->avatar.destRect.height) {
      state->avatar.destRect.y = WORLD_HEIGHT - state->avatar.destRect.height;
    }
  }
  if (IsKeyDown(KEY_K)) {
    state->avatar.destRect.y -= AVATAR_SPEED * dt;
    if (state->avatar.destRect.y < 0) {
      state->avatar.destRect.y = 0;
    }
  }
  if (IsKeyDown(KEY_L)) {
    state->avatar.destRect.x += AVATAR_SPEED * dt;
    if (state->avatar.destRect.x > WORLD_WIDTH - state->avatar.destRect.width) {
      state->avatar.destRect.x = WORLD_WIDTH - state->avatar.destRect.width;
    }
  }
  state->camera.target.x = state->avatar.destRect.x;
  state->camera.target.y = state->avatar.destRect.y;
}

static inline void _updateAnimations(GameState *state, float dt) {
  switch (state->avatar.animationType) {
  case avatarAnimationIdle:
    auto animation = &state->avatar.idleAnimation;
    animation->dt += dt;
    if (animation->dt > animation->frameLength) {
      animation->dt = 0;
      state->avatar.idleAnimation.frameIndex += 1;
      if (state->avatar.idleAnimation.frameIndex ==
          state->avatar.idleAnimation.frameCount) {
        state->avatar.idleAnimation.frameIndex = 0;
      }
    }
    break;
  default:
    abort();
  }
}

void updateState(GameState *state, float dt) {
  _handleInput(state, dt);
  _updateAnimations(state, dt);
}
