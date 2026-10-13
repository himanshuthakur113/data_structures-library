#include <iostream>
#include "redis_lite.h"

// Demo: starts the RedisLite command-line store.
// Commands: SET key value | GET key | DEL key | EXISTS key | COUNT | CLEAR | EXIT
int main()
{
    RedisLite redis;
    redis.run();
    return 0;
}
