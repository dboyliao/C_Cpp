enum Triple {var, ptr, no};
class PolyNode
{
    PolyNode *link;
    int exp;
    Triple trio;
    union {
	char vble;
	PolyNode *dlink;
	int coef;
    };
};

main ()
{}