#include<memory>
template <typename T>
class TD;

const int theAnswer = 42;
auto x = theAnswer;
const auto y =  &theAnswer;
auto rValue=std::move(theAnswer);

TD<decltype(rValue)> xType;
TD<decltype(y)> yType;
make_unique<>