#pragma once

class Sandbox {
 public:
  enum ProfileTime {
    RENDER_TIME,
    SIMULATION_TIME,
    TOTAL_SIMULATION_TIME,

    PROFILE_TIME_COUNT
  };

  Sandbox();
  ~Sandbox();
  void init();
  void update(double deltaSeconds){};
  void shutdown();
  void setProfileTime(const ProfileTime profile, double time){};

 private:
};