#ifndef INCLUDE_SEQUENCE_TITLE_H
#define INCLUDE_SEQUENCE_TITLE_H



#include "Child.h"
#include "../Child.h"
#include "ofMain.h"
#include <vector>
#include <string>

namespace Sequence{
  namespace Game{
    class Parent;
    class Title : public Child {

    public:

      Title();

      ~Title();

      void update( Parent* parent );

      void draw();


      // 入力バトン

      void keyPressed(int key);

      void keyReleased(int key);

      void mouseMoved(int x, int y );

      void mouseDragged(int x, int y, int button);

      void mousePressed(int x, int y, int button);

      void mouseReleased(int x, int y, int button);

      void windowResized(int w, int h);

      void exit();


    private:

      string str_Title;

      vector<string> menu;

      int curser;

      int lineHeight;

      ofTrueTypeFont franklinBook;

    };

  };

};


#endif
