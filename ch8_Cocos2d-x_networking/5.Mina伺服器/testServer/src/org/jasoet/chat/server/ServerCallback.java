/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.jasoet.chat.server;

import java.util.Set;

/**
 *
 * @author jasoet
 */
public interface ServerCallback {

    public void setUsers(Set<String> users);

    public void connected();

    public void disconnected();

    public void messageReceived(String message);

    public void error(String message);
}
