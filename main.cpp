#include <cstdio>
#include <cassert>
#include "stack.h"
#include "stack_err.h"

#define forever for(;;)

int main () {

    //float c = 0;
    char state = 0;
    int ch = 0;

    /*Stack<float> Stakkur(10) ;

    state = Stakkur.Push(3.6);
    assert(ok(state));

    state = Stakkur.Push(567.89);
    assert(ok(state));

    state = Stakkur.Top(&c);
    assert(ok(state));
    printf("%g\n", c);
    state = Stakkur.Pop();
    assert(ok(state));

    state = Stakkur.Top(&c);
    assert(ok(state));
    printf("%g\n", c);
    state = Stakkur.Pop();
    assert(ok(state));*/

    Stack<int> Sc;

    forever
    {
        while ((ch = getchar()) != '\n') {
            state = Sc.Push(ch);
            assert(ok(state));
        }

        while (Sc.Size() > 0) {
            state = Sc.Top(&ch);
            assert(ok(state));
            putchar(ch);
            state = Sc.Pop();
            assert(ok(state));
        }

        putchar('\n');
    }

    return 0;
}
