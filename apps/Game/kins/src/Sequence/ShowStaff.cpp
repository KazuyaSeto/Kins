#include "ShowStaff.h"
#include "Parent.h"
#include "Title.h"
#include "Child.h"

#include <iostream>


using namespace Sequence;
using namespace std;

ShowStaff::ShowStaff(){

}

ShowStaff::~ShowStaff()
{
    //dtor
}

Child* ShowStaff::Update(Parent* parent){
  Child* next = this;
  if(false){
    next = new Title;
  }
  return next;
}

void ShowStaff::Draw(){
}

