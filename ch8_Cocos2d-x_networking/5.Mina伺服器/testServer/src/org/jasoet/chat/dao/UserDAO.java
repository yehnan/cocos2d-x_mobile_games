/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.jasoet.chat.dao;

import java.sql.SQLException;
import java.util.List;
import org.jasoet.chat.model.User;

/**
 *
 * @author jasoet
 */
public interface UserDAO {

    public List<User> getAll() throws SQLException;

    public User getByUsername(String username) throws SQLException;

    public int insert(User d) throws SQLException;

    public int delete(int id) throws SQLException;

    public int update(int id, User newUser) throws SQLException;

    public boolean isAuthenticate(String username, String password) throws SQLException;
}
