#pragma once

class ParticuleNeige;
class ParticuleRoche;

class Agent {
public:
  virtual void opere_sur(ParticuleNeige &) const = 0;
  virtual void opere_sur(ParticuleRoche &) const = 0;

  virtual ~Agent() = default;
};
