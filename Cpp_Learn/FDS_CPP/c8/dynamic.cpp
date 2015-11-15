
const int WordSize = 5;  // maximum number of directory bits
const int PageSize = 10; // maximum size of a page
const int MaxDir = 32; // maximum size of a directory
struct TwoChars { char str[2];};
struct page {
    int LocalDepth; // number of bits to distinguish ids
    TwoChars names[PageSize]; // the actual identifiers
    int NumIdents; // number of identifiers in this page
};
typedef page* paddr;
struct record {  // a sample record
    TwoChars KeyField;
    int IntData;
    char CharData;
};
paddr rdirectory[MaxDir]; // will contain pointers to pages
int gdepth; // not to exceed @WordSize@

paddr hash(TwoChars key, int precision);
/* @key@ is hashed using  a uniform hash function, and the low order
@precision@ bits are returned as the page address. */

paddr buddy(paddr index);
/* Take an address of a page and return the page's buddy; i.e., the
leading bit is complemented. */

int size(paddr ptr);
// Return the number of identifiers in the page

paddr coalesce(paddr ptr, paddr buddy);
// Combine page @ptr@ and its buddy, @buddy@ into a single page.

Boolean PageSearch(TwoChars key, paddr index);
// Search page @index@ for key @key@. If found, return TRUE; otherwise return FALSE

int convert(paddr p);
// Convert a pointer to a page to an equivalent integer.

void enter(record r, paddr p);
// Insert the new record @r@ into the page pointed at by @p@

void PageDelete(TwoChar key);
// Remove the record with key @key@ from the page pointed at by @p@

paddr find(TwoChars key)
/* Search for a record with key @key@ in the file.
If found, return the address of the page in which it was found. If
not found, return 0; */
{
    paddr index = hash(key, gdepth);
    int IntIndex = convert(index);
    paddr ptr = rdirectory[IntIndex];
    if (PageSearch(key, ptr) return ptr;
    else return 0;
}

void insert(record r, TwoChars key)
// Insert a new record into the file pointed at by the directory
{
    paddr p = find(key); // check if key is present
    if (p) return; // key already in
    if (p->NumIdents != PageSize) { // page not full
	enter(r,p); p->NumIdents++;
    }
    else {
	Split the page into two, insert the new key, and
	update @gdepth@ if necessary; if this causes @gdepth@
	to exceed @WordSize@, print an error and terminate.
    }
}

void Delete(TwoChars key)
// Find and delete the record with key @key@
{
    paddr p = find(key);
    if (p) {
	PageDelete(key, p);
	if (size(p) + size(buddy(p)) <= PageSize) coalesce(p, buddy(p);
    }
}

void main() {}  // main program
