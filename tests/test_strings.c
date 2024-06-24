#include "../include/Strings.h"
#include "../include/Testlib.h"

TEST(ensureInnerValueIsNotModified) {
  String_t string = String_new("Hello Mom!");
  ASSERT_EQ_STR("Hello Mom!", String_val(string));
}

TEST(stringsLeftTrimFunction) {
  String_t string = String_new(" Hello");
  string = String_ltrim(string);
  ASSERT_EQ_STR("Hello", String_val(string));
  String_drop(string);

  string = String_new("Hi");
  string = String_ltrim(string);
  ASSERT_EQ_STR("Hi", String_val(string));
}

TEST(stringsRightTrimFunction) {
  String_t string = String_new("Some text ");
  string = String_rtrim(string);
  ASSERT_EQ_STR("Some text", String_val(string));
  String_drop(string);

  string = String_new("Hi");
  string = String_ltrim(string);
  ASSERT_EQ_STR("Hi", String_val(string));
  String_drop(string);
}

TEST(stringsTrimFunction) {
  String_t string = String_new(" Hello Friend ");
  string = String_trim(string);
  ASSERT_EQ_STR("Hello Friend", String_val(string));
}

TEST(joinFunction) {
  String_t hello = String_new("Hello");
  String_t mom = String_new("Mom");
  String_t hello_mon = String_join(hello, mom);
  ASSERT_EQ_STR("HelloMom", String_val(hello_mon));
}

TEST(joinByFunction) {
  String_t hello = String_new("Hello");
  String_t mom = String_new("Mom");
  String_t hello_mon = String_join_by(hello, mom, "-");
  ASSERT_EQ_STR("Hello-Mom", String_val(hello_mon));
}

int main(void) { return RUN_ALL_TESTS(); }
