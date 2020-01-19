#ifndef FUNCTIONBASEMENT_H
#define FUNCTIONBASEMENT_H

#include <string>

#include "parsers.h"

enum class FunctionType{
  Base,
  Physical,
  Standart,
  Trigger
};

class FunctionBasement
{
 public:
  using Events = std::vector<EventSignature>;
  FunctionBasement(FunctionType type);
  virtual void FunctionCalled();
  Events ReceiveEvents();
  bool need_to_delete() const { return need_to_delete_; }
  FunctionType type() const { return type_; }
 protected:
  static int id_setter_;
  int id_;
  FunctionType type_;
  Events event_pool_;
  bool need_to_delete_ = false;
};

class PhysicalFunction : public FunctionBasement {
 public:
  PhysicalFunction(const std::string& target_component,
                   FunctionSignature function_signature,
                   int left_lifetime = consts::atomic_time_value)
    : FunctionBasement(FunctionType::Physical),
      target_component_(target_component),
      function_signature_(function_signature),
      left_lifetime_(left_lifetime) {}
  virtual void FunctionCalled() override;
  const std::string& target_component() const { return target_component_; }
  FunctionSignature& function_signature() { return function_signature_; }
 private:
  const std::string target_component_;
  FunctionSignature function_signature_;
  int left_lifetime_;
};

class StandartFunction : public FunctionBasement {
 public:
  StandartFunction() : FunctionBasement(FunctionType::Standart) {}
};

class TriggerFunction : public FunctionBasement {
 public:
  TriggerFunction() : FunctionBasement(FunctionType::Trigger) {}
};

#endif // FUNCTIONBASEMENT_H
