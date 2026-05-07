#pragma once

class ParticuleNeige;

class Agent {
public:
  virtual void opere_sur(ParticuleNeige &) const = 0;

  virtual ~Agent() = default;
};
