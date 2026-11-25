# Explorers First Level (Geode mod)

Shows the demon level Explorers (ID 104138684) as the first level in the main levels menu.
Tapping play opens the real online level, so you need to be online.

## Build
1. Install the Geode SDK and the Geode CLI: https://docs.geode-sdk.org/getting-started/
2. In this folder run:
   geode build
3. The .geode file shows up in the build folder. Drop it in your Geode mods folder.

## Notes
- This REPLACES the Stereo Madness slot. The rest of the main levels stay the same.
- Change EXPLORERS_ID, EXPLORERS_NAME, or MAIN_SLOT at the top of src/main.cpp.

## Easiest way: let GitHub build it
1. Make a new GitHub repo and upload everything in this folder (keep the .github folder).
2. Open the Actions tab, pick "Build Mod", and press Run workflow.
3. When it turns green, open the run and download "Build Output" under Artifacts.
4. Unzip it and put the .geode file in your Geode mods folder.
