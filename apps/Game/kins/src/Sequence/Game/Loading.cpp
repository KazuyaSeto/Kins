#include "Loading.h"
#include "Play.h"
#include "../GameParent.h"
#include "../../materials.h"
#include <iostream>
using namespace Sequence::GameSeq;
using namespace std;

Loading::Loading(){
  time = 0;
  DB = materials::Instance();
}

Loading::~Loading(){

}

Child* Loading::update(GameParent* gameParent){
  if(time<120){
    time++;
    return this;
  }else{
    return new Play(Play::DIFF_EASY);
  }
}

void Loading::draw(){
  ofPushMatrix();
  ofPushStyle();
  ofSetColor(0,0,0);
  ofRect(100, 300, time*4, 50);
  ofPopStyle();
  ofPopMatrix();
}

