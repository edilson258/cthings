#include "../include/MPSC.h"
#include "../include/Testlib.h"

TEST check_if_sent_msg_is_recvd() {
  Channel_t chan = Channel_new();
  Str_t msg = Str("Hello!");
  Channel_send(chan, msg);
  Str_t recvd = Channel_recv(chan);
  ASSERT_EQ_STR(msg, recvd);
}

int main() {
  TestSuite_t ts = TestSuite_new("MPSC tests");
  TestSuite_add(ts, check_if_sent_msg_is_recvd);
  return TestSuite_run(ts);
}
