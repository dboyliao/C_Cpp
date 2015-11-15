#include <iostream.h>

enum Boolean { FALSE, TRUE};

class ThreeLetterList {
private:
    class ThreeLetterNode {
    public:
       char data[3];
       ThreeLetterNode *link;
    };
    ThreeLetterNode *first;
public:
   void test();
};

void ThreeLetterList::test()
{
ThreeLetterNode *f = new ThreeLetterNode;
f->data[0] = 'a';
f->data[1] = 'b';
f->data[2] = 'c';
f->link = 0;
}

main()
{
   ThreeLetterList l;
   l.test();
}
