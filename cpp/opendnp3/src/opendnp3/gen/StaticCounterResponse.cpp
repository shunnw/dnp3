//
//  _   _         ______    _ _ _   _             _ _ _
// | \ | |       |  ____|  | (_) | (_)           | | | |
// |  \| | ___   | |__   __| |_| |_ _ _ __   __ _| | | |
// | . ` |/ _ \  |  __| / _` | | __| | '_ \ / _` | | | |
// | |\  | (_) | | |___| (_| | | |_| | | | | (_| |_|_|_|
// |_| \_|\___/  |______\__,_|_|\__|_|_| |_|\__, (_|_|_)
//                                           __/ |
//                                          |___/
// Copyright 2013 Automatak LLC
// 
// Automatak LLC (www.automatak.com) licenses this file
// to you under the the Apache License Version 2.0 (the "License"):
// 
// http://www.apache.org/licenses/LICENSE-2.0.html
//

#include <opendnp3/gen/StaticCounterResponse.h>

namespace opendnp3 {

std::string StaticCounterResponseToString(StaticCounterResponse arg)
{
  switch(arg)
  {
    case(StaticCounterResponse::Group20Var1):
      return "Group20Var1";
    case(StaticCounterResponse::Group20Var2):
      return "Group20Var2";
    case(StaticCounterResponse::Group20Var5):
      return "Group20Var5";
    case(StaticCounterResponse::Group20Var6):
      return "Group20Var6";
  }
  return "Group20Var6";
}
int StaticCounterResponseToType(StaticCounterResponse arg)
{
  return static_cast<int>(arg);
}
StaticCounterResponse StaticCounterResponseFromType(int arg)
{
  switch(arg)
  {
    case(0):
      return StaticCounterResponse::Group20Var1;
    case(1):
      return StaticCounterResponse::Group20Var2;
    case(2):
      return StaticCounterResponse::Group20Var5;
    case(3):
      return StaticCounterResponse::Group20Var6;
  }
  return StaticCounterResponse::Group20Var6;
}

}
