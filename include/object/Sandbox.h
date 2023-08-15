#pragma once

class Sandbox {
 public:
  enum ProfileTime {
    RENDER_TIME,
    SIMULATION_TIME,
    TOTAL_SIMULATION_TIME,

    PROFILE_TIME_COUNT
  };

 public:
  Sandbox(const unsigned int sandboxId, Ogre::SceneNode* const sandboxNode,
          Ogre::Camera* const camera){};

  void setup() {}
  void update(const int deltaMilliseconds) {}
  void shutdown() {}

  void setProfileTime(const ProfileTime profile, const uint64_t time) {
    m_profileTimes[profile] = time;
  }
  auto getProfileTime(const ProfileTime profile) const {
    return m_profileTimes[profile];
  }

  void loadScript(const char* const luaScript, const size_t bufferSize,
                  const char* const fileName){};

 private:
  uint64_t m_profileTimes[PROFILE_TIME_COUNT];
};