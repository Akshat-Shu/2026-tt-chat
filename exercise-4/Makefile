BUILD_DIR  = build
LIB_DIR = lib
LIB = $(LIB_DIR)/lib_tcp_echo.a

CLIENT_SRC = src/tcp_echo_client.cpp
CLIENT_EXE = $(BUILD_DIR)/client
SERVER_SRC = src/tcp_echo_server.cpp
SERVER_EXE = $(BUILD_DIR)/server
UTIL_SRC = src/tcp_echo_utils.cpp
UTIL_OBJ = src/tcp_echo_utils.o
UTIL_H = include/tcp_echo_utils.h

CXX_FLAGS = -g -Wall -Wextra -O3 -fsanitize=address -Iinclude
LD_FLAGS = -L$(LIB_DIR) -l:lib_tcp_echo.a


.PHONY: all clean

all: $(CLIENT_EXE) $(SERVER_EXE)

# the | signals a prerequisite but does not trigger a rebuild if it changes.
$(CLIENT_EXE): $(CLIENT_SRC) $(LIB) | $(BUILD_DIR)
	g++ $(CXX_FLAGS) -o $@ $< $(LD_FLAGS)

$(SERVER_EXE): $(SERVER_SRC) $(LIB) | $(BUILD_DIR)
	g++ $(CXX_FLAGS) -o $@ $< $(LD_FLAGS)

$(LIB): $(UTIL_OBJ) | $(LIB_DIR)
	ar rcs $@ $^

$(UTIL_OBJ): $(UTIL_SRC) $(UTIL_H) | $(BUILD_DIR)
	g++ $(CXX_FLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@



clean:
	rm -rf $(BUILD_DIR)