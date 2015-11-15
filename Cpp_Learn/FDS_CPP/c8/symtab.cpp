

template <class Name, Attribute>
class SymbolTable
// \fBobjects\fR: a set of name-attribute pairs, where the names are unique
{
public:
    SymbolTable(int size = defaultsize);
    // Create an empty symbol table with capacity @size@

    Boolean IsIn(Name name);
    // if @name@ is in symbol table, return TRUE (1); else return FALSE (0)

    Attribute *Find(Name name);
    // if @name@ is in symbol table, return a pointer to the corresponding
    // attribute; else return 0.

    void Insert(Name name, Attribute attr);
    // if @name@ is in symbol table, then replace its existing attribute with @attr@;
    // else, insert the pair (@name@, @attr@) into the symbol table

    void Delete(Name name);
    // if @name@ is in symbol table, delete (@name@, @attr@) from symbol table
};