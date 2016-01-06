#ifndef INCLUDE_SEQUENCE_MENU_H

#define INCLUDE_SEQUENCE_MENU_H


#include "Child.h"


namespace Sequence{

  class GameParent;

  namespace GameSeq{

    class Menu : public Child{

    public:

      Menu();

      ~Menu();

      Child* update(GameParent*);

      void draw();

    };

  };

};


#endif
