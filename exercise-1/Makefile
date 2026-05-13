BUILD_DIR  = build
CLIENT_SRC = src/tcp_echo_client.cc
CLIENT_EXE = $(BUILD_DIR)/client
SERVER_SRC = src/tcp_echo_server.cc
SERVER_EXE = $(BUILD_DIR)/server

.PHONY: all clean

all: $(CLIENT_EXE) $(SERVER_EXE)

# the | signals a prerequisite but does not trigger a rebuild if it changes.
$(CLIENT_EXE): $(CLIENT_SRC) | $(BUILD_DIR)
	g++ -o $@ $<

$(SERVER_EXE): $(SERVER_SRC) | $(BUILD_DIR)
	g++ -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)