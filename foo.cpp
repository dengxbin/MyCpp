#include <iostream>
class base{
  public:
    base(){std::cout<<"construct "<<std::endl;}
   void foo(){
     std::cout<<"base foo"<<std::endl;
   }
  virtual void vfoo(){
   std::cout<<"base foo"<<std::endl;}
  private:
  int member1;
  void pfoo(){std::cout<<"pfoo"<<std::endl;}
};
class drive: public base{
    public:
  void vfoo()
  {std::cout<<"drive foo"<<std::endl;}
};
template<typename T,typename U>
auto add(T c,U i){
  return c+i;
}

int main()
{
  // drive d1;
  // drive *pd=new drive;
  // d1.foo();
  // d1.vfoo();
  // pd->foo();
  // pd->vfoo();

  // delete pd;
  std::cout<<add(1,1)<<std::endl;
  //std::cout<<add("hello","world")<<std::endl;
  return 0;

}