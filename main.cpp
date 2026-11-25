// Explorers First Level
// A Geode mod that shows the online demon level "Explorers" as the
// first level in the main levels menu.
//
// How it works (two small hooks):
//   1) GameLevelManager::getMainLevel  -> hands the menu a fake level for slot 1
//      that is named "Explorers" and looks like a demon.
//   2) LevelPage::onPlay               -> when the player taps play on that page,
//      we open the real online level by its ID instead of starting a local level.

#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>
#include <Geode/modify/LevelPage.hpp>

using namespace geode::prelude;

// ---------- Settings you can change ----------
static constexpr int         EXPLORERS_ID   = 104138684;  // online level ID
static constexpr const char* EXPLORERS_NAME = "Explorers"; // name shown in the menu
static constexpr int         MAIN_SLOT      = 1;          // 1 = first level in the list
// ---------------------------------------------

// Keeps our fake level alive so we only build it once.
static Ref<GJGameLevel> s_explorersLevel = nullptr;

// Builds the fake level shown in the main menu.
static GJGameLevel* getExplorersLevel(GJGameLevel* original) {
	if (!s_explorersLevel) {
		auto level = GJGameLevel::create();
		level->m_levelName = EXPLORERS_NAME;
		level->m_levelID   = MAIN_SLOT;   // keep the slot number so the menu still works
		level->m_levelType = GJLevelType::Main;

		// Make the level look like a demon
		level->m_difficulty      = GJDifficulty::Demon;
		level->m_demon           = 1;
		level->m_demonDifficulty = 0;     // 0 = hard demon
		level->m_stars           = 10;    // demons are 10 stars
		level->m_ratings         = 1;
		level->m_ratingsSum      = 10;

		// Borrow the song and length from the level we are replacing
		if (original) {
			level->m_audioTrack = original->m_audioTrack;
			level->m_songID     = original->m_songID;
			level->m_levelLength = original->m_levelLength;
		}
		s_explorersLevel = level;
	}
	return s_explorersLevel;
}

// True if this level is our fake Explorers level.
static bool isExplorers(GJGameLevel* level) {
	return level && level == s_explorersLevel.data();
}

// Hook 1: swap the main level in slot 1 for Explorers.
class $modify(ExplorersLevelManager, GameLevelManager) {
	GJGameLevel* getMainLevel(int levelID, bool dontGetLevelString) {
		auto original = GameLevelManager::getMainLevel(levelID, dontGetLevelString);
		if (levelID == MAIN_SLOT) {
			return getExplorersLevel(original);
		}
		return original;
	}
};

// Hook 2: when Explorers is played, open the real online level.
class $modify(ExplorersLevelPage, LevelPage) {
	void onPlay(CCObject* sender) {
		if (isExplorers(m_level)) {
			// Same thing the "search by ID" box does in the game
			auto search = GJSearchObject::create(SearchType::Search, std::to_string(EXPLORERS_ID));
			auto scene  = LevelBrowserLayer::scene(search);
			CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
			return;
		}
		// Every other level plays normally
		LevelPage::onPlay(sender);
	}
};
