#pragma once

//if code isnt working set ShowMessages to 1 and see exactly the order in which code is being executed
#define ShowMessages 0 //0 or 1


#if ShowMessages
#define MSG(x) cout << x << endl;
#else
#define MSG(x) ;
#endif
