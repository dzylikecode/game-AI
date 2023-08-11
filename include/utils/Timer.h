#pragma once

class Timer {
 public:
  Timer();
  virtual ~Timer();
  void reset();
  double getSeconds();

 private:
  double m_startTime;
};
