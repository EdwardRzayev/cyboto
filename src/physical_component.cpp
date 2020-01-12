#include "physical_component.h"

#include "geom.h"

bool PhysicalComponent::CallFunctiuon(FunctionSignature signature) {
  try {
    available_functions_.at(signature.FuncName())(signature.Args());
  } catch(...){
    return false;
  }
  return true;
}

ServoMotor::ServoMotor(std::string_view name, RotationLimits rotation_limits)
  : component_name_(name), rotation_limits_(rotation_limits) {
  assert(rotation_limits.first < rotation_limits.second
         && "second value must be bigger or equal to the first one");
  // to check default position with bounds
  Rotate(UnificatedArguments(("0@" /*@ is arg separator*/)));
  type_ = ComponentType::ServoMotor;
  available_functions_.emplace("Rotate", [=](UnificatedArguments args){this->Rotate(args);});
}

// FIXME test version
void ServoMotor::Rotate(UnificatedArguments rotation_speed) {
  double rotation_speed_d;
  rotation_speed.NextArgument(rotation_speed_d);
  double new_angle = current_angle_ + rotation_speed_d;
  if (geom::IsInRange(new_angle, rotation_limits_)) {
    current_angle_ = new_angle;
  } else {
    new_angle > rotation_limits_.second ?
        current_angle_ = rotation_limits_.second :
        current_angle_ = rotation_limits_.first;
  }
}

void ServoMotor::PrintAllInfo() {
  std::cout << "ServoMotor name: " << component_name_ <<std::endl;
  std::cout << "Current angle: " << current_angle_ <<std::endl;
}