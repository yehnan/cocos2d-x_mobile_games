package org.jasoet.chat.server;

import java.sql.SQLException;
import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;
import org.apache.mina.filter.logging.MdcInjectionFilter;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;
import org.jasoet.chat.dao.UserDAO;
import org.jasoet.chat.dao.impl.UserDAOImpl;
import org.jasoet.chat.db.DatabaseConnection;

public class ChatProtocolHandler extends IoHandlerAdapter {

    private ServerCallback callback;
    private final static Logger LOGGER = LoggerFactory.getLogger(ChatProtocolHandler.class);
    private final Set<IoSession> sessions = Collections.synchronizedSet(new HashSet<IoSession>());
    private final Set<String> users = Collections.synchronizedSet(new HashSet<String>());
    private UserDAO userDAO;

    public ChatProtocolHandler(ServerCallback callback) {
        this.callback = callback;
        try {
            userDAO = new UserDAOImpl(DatabaseConnection.getInstance().getConnection());
            callback.messageReceived("Database Connected");
        } catch (SQLException ex) {
            callback.error(ex.getMessage());
        }
    }

    @Override
    public void exceptionCaught(IoSession session, Throwable cause) {
        LOGGER.warn("Unexpected exception.", cause);
        callback.error("Unexpected exception." + cause.getMessage());
        session.close(true);
    }

    @Override
    public void messageReceived(IoSession session, Object message) {
        Logger log = LoggerFactory.getLogger(ChatProtocolHandler.class);
        log.info("received: " + message);
        String theMessage = (String) message;
        String[] result = theMessage.split(" ", 3);
        String theCommand = result[0];

        try {

            ChatCommand command = ChatCommand.valueOf(theCommand);
            String user = (String) session.getAttribute("user");
            String password = "";

            switch (command.toInt()) {

                case ChatCommand.QUIT:
                    session.write("QUIT OK");
                    session.close(true);
                    break;
                case ChatCommand.LOGIN:

                    if (user != null) {
                        session.write("LOGIN ERROR user " + user
                                + " already logged in.");
                        return;
                    }

                    if (result.length == 3) {
                        user = result[1];
                        password = result[2];
                    } else {
                        session.write("LOGIN ERROR invalid login command.");
                        return;
                    }
                    try {
                        if (!userDAO.isAuthenticate(user, password)) {
                            session.write("LOGIN ERROR for name " + user
                                    + " Wrong Username/Password Combination");
                            return;
                        }
                    } catch (SQLException ex) {
                        callback.messageReceived(ex.getMessage());
                    }

                    // check if the username is already used
                    if (users.contains(user)) {
                        session.write("LOGIN ERROR the name " + user
                                + " is already used.");
                        return;
                    }

                    sessions.add(session);
                    session.setAttribute("user", user);
                    MdcInjectionFilter.setProperty(session, "user", user);

                    // Allow all users
                    users.add(user);
                    session.write("LOGIN OK");
                    broadcast("The user " + user + " has joined the chat session.");

                    callback.setUsers(users);
                    break;

                case ChatCommand.BROADCAST:

                    if (result.length == 2) {
                        broadcast(user + ": " + result[1]);
                    }
                    break;

                case ChatCommand.USERS:
                    if (result.length == 1) {
                        sendUsersList(user);
                    }
                    break;
                case ChatCommand.PRIVATE:
                    if (result.length == 3) {
                        String userDestination = result[1];
                        String privateMessage = result[2];
                        sendPrivateMessage(userDestination, privateMessage);
                    }
                default:
                    LOGGER.info("Unhandled command: " + command);
                    break;
            }

        } catch (IllegalArgumentException e) {
            LOGGER.debug("Illegal argument", e);
        }
    }

    public void sendPrivateMessage(String userDestination, String message) {
         synchronized (sessions) {
            for (IoSession session : sessions) {
                if (session.isConnected() && userDestination.equals(session.getAttribute("user"))) {
                    session.write("PRIVATE OK " + message);
                }
            }
        }
    }

    public void sendUsersList(String userDestination) {
        String message = "";
        for (String str : users) {
            message = message + " " + str;
        }
        message = message.trim();
        synchronized (sessions) {
            for (IoSession session : sessions) {
                if (session.isConnected() && userDestination.equals(session.getAttribute("user"))) {
                    session.write("USERS OK " + message);
                }
            }
        }

        callback.messageReceived("User " + userDestination + " requests Users List");
    }

    public void broadcast(String message) {
        synchronized (sessions) {
            callback.messageReceived(message);
            for (IoSession session : sessions) {
                if (session.isConnected()) {
                    session.write("BROADCAST OK " + message);
                }
            }
        }
    }

    @Override
    public void sessionClosed(IoSession session) throws Exception {
        String user = (String) session.getAttribute("user");
        users.remove(user);
        sessions.remove(session);
        broadcast("The user " + user + " has left the chat session.");
        callback.setUsers(users);
    }

    public boolean isChatUser(String name) {
        return users.contains(name);
    }

    public int getNumberOfUsers() {
        return users.size();
    }

    public void kick(String name) {
        synchronized (sessions) {
            for (IoSession session : sessions) {
                if (name.equals(session.getAttribute("user"))) {
                    session.close(true);
                    break;
                }
            }
            callback.messageReceived("KICKED : " + name);
        }
    }
}
