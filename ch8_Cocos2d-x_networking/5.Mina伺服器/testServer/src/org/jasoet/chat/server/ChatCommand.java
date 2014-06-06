package org.jasoet.chat.server;

public class ChatCommand {

    public static final int LOGIN = 0;
    public static final int QUIT = 1;
    public static final int BROADCAST = 2;
    public static final int USERS = 3;
    public static final int PRIVATE = 4;
    private final int num;

    private ChatCommand(int num) {
        this.num = num;
    }

    public int toInt() {
        return num;
    }

    public static ChatCommand valueOf(String s) {
        s = s.toUpperCase();
        if ("LOGIN".equals(s)) {
            return new ChatCommand(LOGIN);
        }
        if ("QUIT".equals(s)) {
            return new ChatCommand(QUIT);
        }
        if ("BROADCAST".equals(s)) {
            return new ChatCommand(BROADCAST);
        }

        if ("USERS".equals(s)) {
            return new ChatCommand(USERS);
        }

        if ("PRIVATE".equals(s)) {
            return new ChatCommand(PRIVATE);
        }

        throw new IllegalArgumentException("Unrecognized command: " + s);
    }
}
