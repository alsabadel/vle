#install(FILES toto.vpz DESTINATION exp)
install(DIRECTORY . DESTINATION exp FILES_MATCHING PATTERN "*.vpz")
