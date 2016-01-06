#ifndef SHOWSTAFF_H
#define SHOWSTAFF_H

#include "Child.h"
#include "ofMain.h"
#include <vector>
#include <string>

using namespace std;

namespace Sequence{
  class Parent;
  class ShowStaff:public Child
  {
    public:
    ShowStaff();
    ~ShowStaff();
    Child* Update( Parent* parent );
    void Draw();
  };
};

#endif // SHOWSTAFF_H
