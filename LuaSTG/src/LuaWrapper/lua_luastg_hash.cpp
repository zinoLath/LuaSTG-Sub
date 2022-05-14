// Write by Kuanlan (Kuanlan@outlook.com)
// Minimum perfect hash function for Lua language binding.
// This source file is generated by code generator.
// Don't modify this file directly, please modify the generator configuration.

#include "lua_luastg_hash.hpp"

LuaSTG::GameObjectMember LuaSTG::MapGameObjectMember(const char* key) {
  switch(key[0]) {
    case '_':
      switch(key[1]) {
        case 'a':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::_A;
            case 'n':
              switch(key[3]) {
                case 'g':
                  switch(key[4]) {
                    case 'l':
                      switch(key[5]) {
                        case 'e':
                          switch(key[6]) {
                            case '\0':
                              return LuaSTG::GameObjectMember::VANGLE;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 'b':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::_B;
            case 'l':
              switch(key[3]) {
                case 'e':
                  switch(key[4]) {
                    case 'n':
                      switch(key[5]) {
                        case 'd':
                          switch(key[6]) {
                            case '\0':
                              return LuaSTG::GameObjectMember::_BLEND;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 'c':
          switch(key[2]) {
            case 'o':
              switch(key[3]) {
                case 'l':
                  switch(key[4]) {
                    case 'o':
                      switch(key[5]) {
                        case 'r':
                          switch(key[6]) {
                            case '\0':
                              return LuaSTG::GameObjectMember::_COLOR;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 'g':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::_G;
          }
          break;
        case 'r':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::_R;
          }
          break;
        case 's':
          switch(key[2]) {
            case 'p':
              switch(key[3]) {
                case 'e':
                  switch(key[4]) {
                    case 'e':
                      switch(key[5]) {
                        case 'd':
                          switch(key[6]) {
                            case '\0':
                              return LuaSTG::GameObjectMember::VSPEED;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'a':
      switch(key[1]) {
        case '\0':
          return LuaSTG::GameObjectMember::A;
        case 'g':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::AG;
          }
          break;
        case 'n':
          switch(key[2]) {
            case 'i':
              switch(key[3]) {
                case '\0':
                  return LuaSTG::GameObjectMember::ANI;
              }
              break;
          }
          break;
        case 'x':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::AX;
          }
          break;
        case 'y':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::AY;
          }
          break;
      }
      break;
    case 'b':
      switch(key[1]) {
        case '\0':
          return LuaSTG::GameObjectMember::B;
        case 'o':
          switch(key[2]) {
            case 'u':
              switch(key[3]) {
                case 'n':
                  switch(key[4]) {
                    case 'd':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::BOUND;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'c':
      switch(key[1]) {
        case 'l':
          switch(key[2]) {
            case 'a':
              switch(key[3]) {
                case 's':
                  switch(key[4]) {
                    case 's':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::CLASS;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 'o':
          switch(key[2]) {
            case 'l':
              switch(key[3]) {
                case 'l':
                  switch(key[4]) {
                    case 'i':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::COLLI;
                        case 'd':
                          switch(key[6]) {
                            case 'e':
                              switch(key[7]) {
                                case 'r':
                                  switch(key[8]) {
                                    case '\0':
                                      return LuaSTG::GameObjectMember::COLLIDER;
                                  }
                                  break;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'd':
      switch(key[1]) {
        case 'x':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::DX;
          }
          break;
        case 'y':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::DY;
          }
          break;
      }
      break;
    case 'g':
      switch(key[1]) {
        case 'r':
          switch(key[2]) {
            case 'o':
              switch(key[3]) {
                case 'u':
                  switch(key[4]) {
                    case 'p':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::GROUP;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'h':
      switch(key[1]) {
        case 'i':
          switch(key[2]) {
            case 'd':
              switch(key[3]) {
                case 'e':
                  switch(key[4]) {
                    case '\0':
                      return LuaSTG::GameObjectMember::HIDE;
                  }
                  break;
              }
              break;
          }
          break;
        case 's':
          switch(key[2]) {
            case 'c':
              switch(key[3]) {
                case 'a':
                  switch(key[4]) {
                    case 'l':
                      switch(key[5]) {
                        case 'e':
                          switch(key[6]) {
                            case '\0':
                              return LuaSTG::GameObjectMember::HSCALE;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'i':
      switch(key[1]) {
        case 'm':
          switch(key[2]) {
            case 'g':
              switch(key[3]) {
                case '\0':
                  return LuaSTG::GameObjectMember::IMG;
              }
              break;
          }
          break;
      }
      break;
    case 'l':
      switch(key[1]) {
        case 'a':
          switch(key[2]) {
            case 'y':
              switch(key[3]) {
                case 'e':
                  switch(key[4]) {
                    case 'r':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::LAYER;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'm':
      switch(key[1]) {
        case 'a':
          switch(key[2]) {
            case 'x':
              switch(key[3]) {
                case 'v':
                  switch(key[4]) {
                    case '\0':
                      return LuaSTG::GameObjectMember::MAXV;
                    case 'x':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::MAXVX;
                      }
                      break;
                    case 'y':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::MAXVY;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'n':
      switch(key[1]) {
        case 'a':
          switch(key[2]) {
            case 'v':
              switch(key[3]) {
                case 'i':
                  switch(key[4]) {
                    case '\0':
                      return LuaSTG::GameObjectMember::NAVI;
                  }
                  break;
              }
              break;
          }
          break;
        case 'o':
          switch(key[2]) {
            case 'p':
              switch(key[3]) {
                case 'a':
                  switch(key[4]) {
                    case 'u':
                      switch(key[5]) {
                        case 's':
                          switch(key[6]) {
                            case 'e':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::GameObjectMember::IGNORESUPERPAUSE;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'o':
      switch(key[1]) {
        case 'm':
          switch(key[2]) {
            case 'i':
              switch(key[3]) {
                case 'g':
                  switch(key[4]) {
                    case 'a':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::OMEGA;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'p':
      switch(key[1]) {
        case 'a':
          switch(key[2]) {
            case 'u':
              switch(key[3]) {
                case 's':
                  switch(key[4]) {
                    case 'e':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::PAUSE;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'r':
      switch(key[1]) {
        case 'c':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::RES_RC;
          }
          break;
        case 'e':
          switch(key[2]) {
            case 'c':
              switch(key[3]) {
                case 't':
                  switch(key[4]) {
                    case '\0':
                      return LuaSTG::GameObjectMember::RECT;
                  }
                  break;
              }
              break;
          }
          break;
        case 'm':
          switch(key[2]) {
            case 'o':
              switch(key[3]) {
                case 'v':
                  switch(key[4]) {
                    case 'e':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::RESOLVEMOVE;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 'o':
          switch(key[2]) {
            case 't':
              switch(key[3]) {
                case '\0':
                  return LuaSTG::GameObjectMember::ROT;
              }
              break;
          }
          break;
      }
      break;
    case 's':
      switch(key[1]) {
        case 't':
          switch(key[2]) {
            case 'a':
              switch(key[3]) {
                case 't':
                  switch(key[4]) {
                    case 'u':
                      switch(key[5]) {
                        case 's':
                          switch(key[6]) {
                            case '\0':
                              return LuaSTG::GameObjectMember::STATUS;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 't':
      switch(key[1]) {
        case 'i':
          switch(key[2]) {
            case 'm':
              switch(key[3]) {
                case 'e':
                  switch(key[4]) {
                    case 'r':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::TIMER;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'v':
      switch(key[1]) {
        case 's':
          switch(key[2]) {
            case 'c':
              switch(key[3]) {
                case 'a':
                  switch(key[4]) {
                    case 'l':
                      switch(key[5]) {
                        case 'e':
                          switch(key[6]) {
                            case '\0':
                              return LuaSTG::GameObjectMember::VSCALE;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 'x':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::VX;
          }
          break;
        case 'y':
          switch(key[2]) {
            case '\0':
              return LuaSTG::GameObjectMember::VY;
          }
          break;
      }
      break;
    case 'w':
      switch(key[1]) {
        case 'o':
          switch(key[2]) {
            case 'r':
              switch(key[3]) {
                case 'l':
                  switch(key[4]) {
                    case 'd':
                      switch(key[5]) {
                        case '\0':
                          return LuaSTG::GameObjectMember::WORLD;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'x':
      switch(key[1]) {
        case '\0':
          return LuaSTG::GameObjectMember::X;
      }
      break;
    case 'y':
      switch(key[1]) {
        case '\0':
          return LuaSTG::GameObjectMember::Y;
      }
      break;
  }
  return LuaSTG::GameObjectMember::__NOT_FOUND;
}

LuaSTG::BlendModeX LuaSTG::MapBlendModeX(const char* key) {
  switch(key[0]) {
    case 'a':
      switch(key[1]) {
        case 'd':
          switch(key[2]) {
            case 'd':
              switch(key[3]) {
                case '+':
                  switch(key[4]) {
                    case 'a':
                      switch(key[5]) {
                        case 'd':
                          switch(key[6]) {
                            case 'd':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::AddAdd;
                              }
                              break;
                          }
                          break;
                        case 'l':
                          switch(key[6]) {
                            case 'p':
                              switch(key[7]) {
                                case 'h':
                                  switch(key[8]) {
                                    case 'a':
                                      switch(key[9]) {
                                        case '\0':
                                          return LuaSTG::BlendModeX::AddAlpha;
                                      }
                                      break;
                                  }
                                  break;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                    case 'm':
                      switch(key[5]) {
                        case 'a':
                          switch(key[6]) {
                            case 'x':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::AddMax;
                              }
                              break;
                          }
                          break;
                        case 'i':
                          switch(key[6]) {
                            case 'n':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::AddMin;
                              }
                              break;
                          }
                          break;
                        case 'u':
                          switch(key[6]) {
                            case 'l':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::AddMutiply;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                    case 'r':
                      switch(key[5]) {
                        case 'e':
                          switch(key[6]) {
                            case 'v':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::AddRev;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                    case 's':
                      switch(key[5]) {
                        case 'c':
                          switch(key[6]) {
                            case 'r':
                              switch(key[7]) {
                                case 'e':
                                  switch(key[8]) {
                                    case 'e':
                                      switch(key[9]) {
                                        case 'n':
                                          switch(key[10]) {
                                            case '\0':
                                              return LuaSTG::BlendModeX::AddScreen;
                                          }
                                          break;
                                      }
                                      break;
                                  }
                                  break;
                              }
                              break;
                          }
                          break;
                        case 'u':
                          switch(key[6]) {
                            case 'b':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::AddSub;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 'l':
          switch(key[2]) {
            case 'p':
              switch(key[3]) {
                case 'h':
                  switch(key[4]) {
                    case 'a':
                      switch(key[5]) {
                        case '+':
                          switch(key[6]) {
                            case 'b':
                              switch(key[7]) {
                                case 'a':
                                  switch(key[8]) {
                                    case 'l':
                                      switch(key[9]) {
                                        case '\0':
                                          return LuaSTG::BlendModeX::AlphaBal;
                                      }
                                      break;
                                  }
                                  break;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'm':
      switch(key[1]) {
        case 'u':
          switch(key[2]) {
            case 'l':
              switch(key[3]) {
                case '+':
                  switch(key[4]) {
                    case 'a':
                      switch(key[5]) {
                        case 'd':
                          switch(key[6]) {
                            case 'd':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::MulAdd;
                              }
                              break;
                          }
                          break;
                        case 'l':
                          switch(key[6]) {
                            case 'p':
                              switch(key[7]) {
                                case 'h':
                                  switch(key[8]) {
                                    case 'a':
                                      switch(key[9]) {
                                        case '\0':
                                          return LuaSTG::BlendModeX::MulAlpha;
                                      }
                                      break;
                                  }
                                  break;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                    case 'm':
                      switch(key[5]) {
                        case 'a':
                          switch(key[6]) {
                            case 'x':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::MulMax;
                              }
                              break;
                          }
                          break;
                        case 'i':
                          switch(key[6]) {
                            case 'n':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::MulMin;
                              }
                              break;
                          }
                          break;
                        case 'u':
                          switch(key[6]) {
                            case 'l':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::MulMutiply;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                    case 'r':
                      switch(key[5]) {
                        case 'e':
                          switch(key[6]) {
                            case 'v':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::MulRev;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                    case 's':
                      switch(key[5]) {
                        case 'c':
                          switch(key[6]) {
                            case 'r':
                              switch(key[7]) {
                                case 'e':
                                  switch(key[8]) {
                                    case 'e':
                                      switch(key[9]) {
                                        case 'n':
                                          switch(key[10]) {
                                            case '\0':
                                              return LuaSTG::BlendModeX::MulScreen;
                                          }
                                          break;
                                      }
                                      break;
                                  }
                                  break;
                              }
                              break;
                          }
                          break;
                        case 'u':
                          switch(key[6]) {
                            case 'b':
                              switch(key[7]) {
                                case '\0':
                                  return LuaSTG::BlendModeX::MulSub;
                              }
                              break;
                          }
                          break;
                      }
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'o':
      switch(key[1]) {
        case 'n':
          switch(key[2]) {
            case 'e':
              switch(key[3]) {
                case '\0':
                  return LuaSTG::BlendModeX::One;
              }
              break;
          }
          break;
      }
      break;
  }
  return LuaSTG::BlendModeX::__NOT_FOUND;
}

LuaSTG::ColorMember LuaSTG::MapColorMember(const char* key) {
  switch(key[0]) {
    case 'A':
      switch(key[1]) {
        case 'H':
          switch(key[2]) {
            case 'S':
              switch(key[3]) {
                case 'V':
                  switch(key[4]) {
                    case '\0':
                      return LuaSTG::ColorMember::f_AHSV;
                  }
                  break;
              }
              break;
          }
          break;
        case 'R':
          switch(key[2]) {
            case 'G':
              switch(key[3]) {
                case 'B':
                  switch(key[4]) {
                    case '\0':
                      return LuaSTG::ColorMember::f_ARGB;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'a':
      switch(key[1]) {
        case '\0':
          return LuaSTG::ColorMember::m_a;
        case 'r':
          switch(key[2]) {
            case 'g':
              switch(key[3]) {
                case 'b':
                  switch(key[4]) {
                    case '\0':
                      return LuaSTG::ColorMember::m_argb;
                  }
                  break;
              }
              break;
          }
          break;
      }
      break;
    case 'b':
      switch(key[1]) {
        case '\0':
          return LuaSTG::ColorMember::m_b;
      }
      break;
    case 'g':
      switch(key[1]) {
        case '\0':
          return LuaSTG::ColorMember::m_g;
      }
      break;
    case 'h':
      switch(key[1]) {
        case '\0':
          return LuaSTG::ColorMember::m_h;
      }
      break;
    case 'r':
      switch(key[1]) {
        case '\0':
          return LuaSTG::ColorMember::m_r;
      }
      break;
    case 's':
      switch(key[1]) {
        case '\0':
          return LuaSTG::ColorMember::m_s;
      }
      break;
    case 'v':
      switch(key[1]) {
        case '\0':
          return LuaSTG::ColorMember::m_v;
      }
      break;
  }
  return LuaSTG::ColorMember::__NOT_FOUND;
}

