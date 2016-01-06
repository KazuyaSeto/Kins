#ifndef INCLUDE_SEQUENCE_GAME_LOADING_H

#define INCLUDE_SEQUENCE_GAME_LOADING_H


#include "Child.h"

#include "ofMain.h"

#include <vector>

#include <string>


class materials;

namespace Sequence{

  class GameParent;

  namespace GameSeq{

    class Loading : public Child{

    public:

      Loading();

      ~Loading();

      Child* update(GameParent*);

      void draw();

    private:

      materials* DB;

      int time;

    };

  };

};


#endif
