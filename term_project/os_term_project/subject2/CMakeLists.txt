cmake_minimum_required(VERSION 3.0)
project(subject2)

set(CMAKE_C_STANDARD 11)

add_definitions(
    -DTEXT_FILE_PATH="${CMAKE_SOURCE_DIR}/test.in"
)

add_executable(signal_test src/signal_test.c)
add_executable(pipe_test src/pipe_test.c)
add_executable(mq_sender src/mq_sender.c)
add_executable(mq_reciver src/mq_reciver.c)

