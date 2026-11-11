#ifndef MONOREPO_SRC_DICEWARE_INCLUDE_CLIPBOARD_H
#define MONOREPO_SRC_DICEWARE_INCLUDE_CLIPBOARD_H

[[nodiscard]]
bool which(const char *name);

[[nodiscard]]
bool clipboard(const char *password);

bool zenity(const char *msg);

#endif // MONOREPO_SRC_DICEWARE_INCLUDE_CLIPBOARD_H
