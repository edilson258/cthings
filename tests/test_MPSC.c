#include "../include/MPSC.h"
#include "../include/Testlib.h"

TEST(ensureSentMessageIsEqualToReceived) {
  Channel_t chan = Channel_new();
  Str_t msg = Str("Hello!");
  Channel_send(chan, msg);
  Str_t recvd = Channel_recv(chan);
  ASSERT_EQ_STR(msg, recvd);
}

int main() { return RUN_ALL_TESTS(); }
