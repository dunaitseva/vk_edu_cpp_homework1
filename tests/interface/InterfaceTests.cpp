#include <gtest/gtest.h>

#include <exception>
#include <stdexcept>
#include <string_view>

extern "C" {
#include "../include/dispatcher.h"
#include "../include/point.h"
}

class CommandLineModeTests : public ::testing::Test {
 protected:
  // Necessary for  every test fflush because all interface
  // functions have the buffer I/O under in their code.
  FILE *output_stream_;
  FILE *error_stream_;

  char correct_p1_[MAX_CONSOLE_INPUT] = "{12.2; -2.1}";
  char correct_p2_[MAX_CONSOLE_INPUT] = "{1; 2}";
  char correct_p3_[MAX_CONSOLE_INPUT] = "{1.2e-5; 2.1e3}";
  char *correct_input_[REQ_POINTS_AMOUNT] = {correct_p1_, correct_p2_,
                                             correct_p3_};

  char incorrect_p_efmti_[MAX_CONSOLE_INPUT] = "asd{12.2; -2.1}";
  char *incorrect_input_efmti1_[REQ_POINTS_AMOUNT] = {incorrect_p_efmti_,
                                                      correct_p2_, correct_p3_};
  char *incorrect_input_efmti2_[REQ_POINTS_AMOUNT] = {
      correct_p1_, incorrect_p_efmti_, correct_p3_};
  char *incorrect_input_efmti3_[REQ_POINTS_AMOUNT] = {correct_p1_, correct_p2_,
                                                      incorrect_p_efmti_};

  char incorrect_p_erepr_[MAX_CONSOLE_INPUT] = "{12.2; -eee2.eee.12eee1}";
  char *incorrect_input_erepr1_[REQ_POINTS_AMOUNT] = {incorrect_p_erepr_,
                                                      correct_p2_, correct_p3_};
  char *incorrect_input_erepr2_[REQ_POINTS_AMOUNT] = {
      correct_p1_, incorrect_p_erepr_, correct_p3_};
  char *incorrect_input_erepr3_[REQ_POINTS_AMOUNT] = {correct_p1_, correct_p2_,
                                                      incorrect_p_erepr_};

  constexpr static size_t CONSOLE_BUFF_SIZE = 256;
  char output_buffer_[CONSOLE_BUFF_SIZE];
  char error_buffer_[CONSOLE_BUFF_SIZE];

  void SetUp() {
    memset(output_buffer_, 0, CONSOLE_BUFF_SIZE);
    memset(error_buffer_, 0, CONSOLE_BUFF_SIZE);
    output_stream_ = fmemopen(output_buffer_, CONSOLE_BUFF_SIZE, "w");
    error_stream_ = fmemopen(error_buffer_, CONSOLE_BUFF_SIZE, "w");
    if (output_stream_ == nullptr || error_stream_ == nullptr) {
      throw std::runtime_error("One of streams was not opened");
    }
  }

  void TearDown() {
    fclose(output_stream_);
    fclose(error_stream_);
  }
};

class ConsoleAppModeTests : public ::testing::Test {
 protected:
  // Also necessary for  every test fflush because all interface
  // functions have the buffer I/O under in their code.
  FILE *output_stream_;
  FILE *error_stream_;

  FILE *input_correct_stream_;
  FILE *input_incorrect_efmti_stream_;
  FILE *input_correct_non_ind_sys_stream_;
  FILE *input_incorrect_unexp_cmd_stream_;

  constexpr static size_t MAX_INPUT = 2048;
  constexpr static size_t MAX_OUTPUT = 4096;
  char output_buffer_[MAX_OUTPUT];
  char error_buffer_[MAX_OUTPUT];

  char input_correct_[MAX_INPUT] =
      "solve\n"
      "{12.3; 44.3}\n"
      "{2.1; 32.1}\n"
      "{23.1; 33.2}\n"
      "exit\n";
  char input_incorrect_efmti_[MAX_INPUT] =
      "solve\n"
      "{12.3; 44.3}\n"
      "{2.1; 32.1}asdd\n";
  char input_correct_non_ind_sys_[MAX_INPUT] =
      "solve\n"
      "{1; 1}\n"
      "{1; 1}\n"
      "{1; 1}\n"
      "exit\n";
  char input_incorrect_unexp_cmd_[MAX_INPUT] =
      "delete smth\n"
      "exit\n";

  void SetUp() {
    memset(output_buffer_, 0, MAX_OUTPUT);
    memset(error_buffer_, 0, MAX_OUTPUT);

    output_stream_ = fmemopen(output_buffer_, MAX_OUTPUT, "w");
    error_stream_ = fmemopen(error_buffer_, MAX_OUTPUT, "w");

    input_correct_stream_ = fmemopen(input_correct_, MAX_INPUT, "r");
    input_incorrect_efmti_stream_ =
        fmemopen(input_incorrect_efmti_, MAX_INPUT, "r");
    input_correct_non_ind_sys_stream_ =
        fmemopen(input_correct_non_ind_sys_, MAX_INPUT, "r");
    input_incorrect_unexp_cmd_stream_ =
        fmemopen(input_incorrect_unexp_cmd_, MAX_INPUT, "r");

    if (output_stream_ == nullptr || error_stream_ == nullptr ||
        input_correct_stream_ == nullptr ||
        input_incorrect_efmti_stream_ == nullptr ||
        input_correct_non_ind_sys_stream_ == nullptr ||
        input_incorrect_unexp_cmd_stream_ == nullptr) {
      throw std::runtime_error("One of streams was not opened");
    }
  }

  void TearDown() {
    fclose(output_stream_);
    fclose(error_stream_);
    fclose(input_correct_stream_);
    fclose(input_incorrect_efmti_stream_);
    fclose(input_correct_non_ind_sys_stream_);
    fclose(input_incorrect_unexp_cmd_stream_);
  }
};

TEST_F(CommandLineModeTests, CorrectArguments) {
  char expected_output[] =
      "coefficient a: 171.939440\n"
      "coefficient b: -2269.966680\n"
      "coefficient c: 2100.027240\n";
  int status = command_line_mode(correct_input_, output_stream_, error_stream_);

  fflush(output_stream_);
  fflush(error_stream_);
  EXPECT_EQ(error_buffer_[0], '\0');
  ASSERT_EQ(status, 1);
  ASSERT_STREQ(output_buffer_, expected_output);
}

TEST_F(CommandLineModeTests, IncorrectArgumentsEFMTI1) {
  int status =
      command_line_mode(incorrect_input_efmti1_, output_stream_, error_stream_);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_EQ(status, 1);
  ASSERT_STREQ(error_buffer_, EFMTI_MSG);
}

TEST_F(CommandLineModeTests, IncorrectArgumentsEFMTI2) {
  int status =
      command_line_mode(incorrect_input_efmti2_, output_stream_, error_stream_);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_EQ(status, 1);
  ASSERT_STREQ(error_buffer_, EFMTI_MSG);
}

TEST_F(CommandLineModeTests, IncorrectArgumentsEFMTI3) {
  int status =
      command_line_mode(incorrect_input_efmti3_, output_stream_, error_stream_);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_EQ(status, 1);
  ASSERT_STREQ(error_buffer_, EFMTI_MSG);
}

TEST_F(CommandLineModeTests, IncorrectArgumentsEREPR1) {
  int status =
      command_line_mode(incorrect_input_erepr1_, output_stream_, error_stream_);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_EQ(status, 1);
  ASSERT_STREQ(error_buffer_, EREPR_MSG);
}

TEST_F(CommandLineModeTests, IncorrectArgumentsEREPR2) {
  int status =
      command_line_mode(incorrect_input_erepr2_, output_stream_, error_stream_);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_EQ(status, 1);
  ASSERT_STREQ(error_buffer_, EREPR_MSG);
}

TEST_F(CommandLineModeTests, IncorrectArgumentsEREPR3) {
  int status =
      command_line_mode(incorrect_input_erepr3_, output_stream_, error_stream_);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_EQ(status, 1);
  ASSERT_STREQ(error_buffer_, EREPR_MSG);
}

TEST_F(CommandLineModeTests, EmtyArguments) {
  int status = command_line_mode(nullptr, output_stream_, error_stream_);
  ASSERT_EQ(status, 0);
}

TEST(GetCmdTest, SolveCommand) {
  char input_buff[MAX_COMMAND_LENGTH + 1] = "solve\n";
  FILE *input_stream = fmemopen(input_buff, MAX_COMMAND_LENGTH + 1, "r");
  ASSERT_NE(input_stream, nullptr);
  int cmd = get_cmd(input_stream);
  fclose(input_stream);
  ASSERT_EQ(cmd, CSOL);
}

TEST(GetCmdTest, ExitCommand) {
  char input_buff[MAX_COMMAND_LENGTH + 1] = "exit\n";
  FILE *input_stream = fmemopen(input_buff, MAX_COMMAND_LENGTH + 1, "r");
  ASSERT_NE(input_stream, nullptr);
  int cmd = get_cmd(input_stream);
  fclose(input_stream);
  ASSERT_EQ(cmd, CEXT);
}

TEST(GetCmdTest, UnexpectedCommand) {
  char input_buff[MAX_COMMAND_LENGTH + 1] = "copy\n";
  FILE *input_stream = fmemopen(input_buff, MAX_COMMAND_LENGTH + 1, "r");
  ASSERT_NE(input_stream, nullptr);
  int cmd = get_cmd(input_stream);
  fclose(input_stream);
  ASSERT_EQ(cmd, ECMD);
}

TEST_F(ConsoleAppModeTests, CorrectInput) {
  char expected_output[MAX_OUTPUT] =
      "Choose the command: Enter point: Enter point: Enter point: "
      "coefficient a: -0.105898\n"
      "coefficient b: 2.721008\n"
      "coefficient c: 26.852892\n"
      "Choose the command: ";

  int status = dispatcher(input_correct_stream_, output_stream_, error_stream_);
  ASSERT_EQ(status, 1);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_STREQ(output_buffer_, expected_output);
}

TEST_F(ConsoleAppModeTests, IncorrectInputUnexpectedCommand) {
  char expected_output[MAX_OUTPUT] =
      "Commands available: solve, exit.\n"
      "Commands available: solve, exit.\n";

  int status = dispatcher(input_incorrect_unexp_cmd_stream_, output_stream_,
                          error_stream_);
  ASSERT_EQ(status, 1);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_STREQ(error_buffer_, expected_output);
}

TEST_F(ConsoleAppModeTests, IncorrectInputUnexpectedEfmti) {
  int status =
      dispatcher(input_incorrect_efmti_stream_, output_stream_, error_stream_);
  ASSERT_EQ(status, 0);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_STREQ(error_buffer_, EFMTI_MSG);
}

TEST_F(ConsoleAppModeTests, CorectArgumetnsNonIndependernSystem) {
  int status = dispatcher(input_correct_non_ind_sys_stream_, output_stream_,
                          error_stream_);
  ASSERT_EQ(status, 1);
  fflush(output_stream_);
  fflush(error_stream_);
  ASSERT_STREQ(error_buffer_, NON_IND_MSG);
}
