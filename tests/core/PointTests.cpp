#include <gtest/gtest.h>
#include <string.h>

#include <cstdio>
#include <exception>
#include <stdexcept>

extern "C" {
#include "../include/point.h"
}

class ReadPoint : public ::testing::Test {
 protected:
  FILE *stream_correct_input1_;
  FILE *stream_correct_input2_;
  FILE *stream_incorrect_input1_erepr_;
  FILE *stream_incorrect_input2_efmti_;
  FILE *stream_incorrect_input3_efmti_;
  FILE *stream_incorrect_input4_efmti_;
  char correct_input1_[MAX_CONSOLE_INPUT] = "{2.2; 3.1}";
  char correct_input2_[MAX_CONSOLE_INPUT] = "{2.2; 3.1}asd";
  char incorrect_input1_erepr_[MAX_CONSOLE_INPUT] = "{2.2; --1e--12}\n";
  char incorrect_input2_efmti_[MAX_CONSOLE_INPUT] = "2.1; 32.12";
  char incorrect_input3_efmti_[MAX_CONSOLE_INPUT] = {EOF};
  char incorrect_input4_efmti_[MAX_CONSOLE_INPUT] = "{2.1; 32.12";

  void SetUp() {
    stream_correct_input1_ = fmemopen(correct_input1_, MAX_CONSOLE_INPUT, "r");
    stream_correct_input2_ = fmemopen(correct_input2_, MAX_CONSOLE_INPUT, "r");
    stream_incorrect_input1_erepr_ =
        fmemopen(incorrect_input1_erepr_, MAX_CONSOLE_INPUT, "r");
    stream_incorrect_input2_efmti_ =
        fmemopen(incorrect_input2_efmti_, MAX_CONSOLE_INPUT, "r");
    stream_incorrect_input3_efmti_ =
        fmemopen(incorrect_input3_efmti_, MAX_CONSOLE_INPUT, "r");
    stream_incorrect_input4_efmti_ =
        fmemopen(incorrect_input4_efmti_, MAX_CONSOLE_INPUT, "r");

    if (stream_correct_input1_ == nullptr ||
        stream_correct_input2_ == nullptr ||
        stream_incorrect_input1_erepr_ == nullptr ||
        stream_incorrect_input2_efmti_ == nullptr ||
        stream_incorrect_input3_efmti_ == nullptr ||
        stream_incorrect_input4_efmti_ == nullptr) {
      throw std::runtime_error("One of streams was not opened");
    }
  }

  void TearDown() {
    fclose(stream_correct_input1_);
    fclose(stream_correct_input2_);
    fclose(stream_incorrect_input1_erepr_);
    fclose(stream_incorrect_input2_efmti_);
    fclose(stream_incorrect_input3_efmti_);
    fclose(stream_incorrect_input4_efmti_);
  }
};

TEST(CreatePointTests, BasicTest) {
  point_t *p = create_point(0.0, 0.0, nullptr);
  ASSERT_NE(p, nullptr);
  delete_point(p);
}

TEST(DeletePoint, CorrectArguments) {
  point_t *p = create_point(0.0, 0.0, nullptr);
  EXPECT_NE(p, nullptr);
  int status = delete_point(p);
  ASSERT_EQ(status, 0);
}

TEST(DeletePoint, InorrectArguments) {
  int status = delete_point(nullptr);
  ASSERT_EQ(status, -1);
}

TEST_F(ReadPoint, CorrectArguments) {
  point_t *p = read_point(stream_correct_input1_, nullptr);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(delete_point(p), 0);
}

TEST_F(ReadPoint, CorrectArgumentsBraketsTest) {
  point_t *p = read_point(stream_correct_input2_, nullptr);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(delete_point(p), 0);
}

TEST_F(ReadPoint, IncorrectArgumentsRepr) {
  int status = 0;
  point_t *p = read_point(stream_incorrect_input1_erepr_, &status);
  ASSERT_EQ(p, nullptr);
  ASSERT_EQ(status, EREPR);
}

TEST_F(ReadPoint, IncorrectArgumentsEFMTI) {
  int status = 0;
  point_t *p = read_point(stream_incorrect_input2_efmti_, &status);
  ASSERT_EQ(p, nullptr);
  ASSERT_EQ(status, EFMTI);
}

TEST_F(ReadPoint, IncorrectArgumentsEOF) {
  int status = 0;
  point_t *p = read_point(stream_incorrect_input3_efmti_, &status);
  ASSERT_EQ(p, nullptr);
  ASSERT_EQ(status, EFMTI);
}

TEST_F(ReadPoint, IncorrectArgumentsBraketsEMFTI) {
  int status = 0;
  point_t *p = read_point(stream_incorrect_input4_efmti_, &status);
  ASSERT_EQ(p, nullptr);
  ASSERT_EQ(status, EFMTI);
}

TEST_F(ReadPoint, IncorrectArgumentsStream) {
  int status = 0;
  point_t *p = read_point(nullptr, &status);
  ASSERT_EQ(p, nullptr);
  ASSERT_EQ(status, ESTREAM);
}

TEST(CreatePointFromString, CorrectArguments1) {
  char point_string[] = "{1.2; 3.2}";
  size_t p_size = strlen(point_string);

  point_t *p = create_point_from_string(point_string, p_size, nullptr);
  ASSERT_NE(p, nullptr);
  delete_point(p);
}

TEST(CreatePointFromString, CorrectArguments2) {
  char point_string[] = "{1e2; 1e-22}";
  size_t p_size = strlen(point_string);

  point_t *p = create_point_from_string(point_string, p_size, nullptr);
  ASSERT_NE(p, nullptr);
  delete_point(p);
}

TEST(CreatePointFromString, CorrectArguments3) {
  char point_string[] = "{5; 3e-23}";
  size_t p_size = strlen(point_string);

  point_t *p = create_point_from_string(point_string, p_size, nullptr);
  ASSERT_NE(p, nullptr);
  delete_point(p);
}

TEST(CreatePointFromString, InorrectArguments1) {
  char point_string1[] = "{5eeee; 3e-23}";
  size_t p_size = strlen(point_string1);

  int err = 0;
  point_t *p = create_point_from_string(point_string1, p_size, &err);
  EXPECT_EQ(p, nullptr);
  ASSERT_EQ(err, EREPR);
  delete_point(p);
}

TEST(CreatePointFromString, InorrectArguments2) {
  char point_string1[] = "{5; 13e.-1123-23}";
  size_t p_size = strlen(point_string1);

  int err = 0;
  point_t *p = create_point_from_string(point_string1, p_size, &err);
  EXPECT_EQ(p, nullptr);
  ASSERT_EQ(err, EREPR);
  delete_point(p);
}

TEST(CreatePointFromString, InorrectArguments3) {
  char point_string1[] = "{53.213, 5.21}";
  size_t p_size = strlen(point_string1);

  int err = 0;
  point_t *p = create_point_from_string(point_string1, p_size, &err);
  EXPECT_EQ(p, nullptr);
  ASSERT_EQ(err, EFMTI);
  delete_point(p);
}

TEST(CreatePointFromString, InorrectArguments4) {
  char point_string1[] = "53.213 5.21";
  size_t p_size = strlen(point_string1);

  int err = 0;
  point_t *p = create_point_from_string(point_string1, p_size, &err);
  EXPECT_EQ(p, nullptr);
  ASSERT_EQ(err, EFMTI);
  delete_point(p);
}

TEST(CreatePointFromString, EmptyString1) {
  int err = 0;
  point_t *p = create_point_from_string(nullptr, 0, &err);
  EXPECT_EQ(p, nullptr);
  ASSERT_EQ(err, EEMTYSTR);
  delete_point(p);
}

TEST(CreatePointFromString, EmptyString2) {
  char c;
  int err = 0;
  point_t *p = create_point_from_string(&c, 0, &err);
  EXPECT_EQ(p, nullptr);
  ASSERT_EQ(err, EEMTYSTR);
  delete_point(p);
}
