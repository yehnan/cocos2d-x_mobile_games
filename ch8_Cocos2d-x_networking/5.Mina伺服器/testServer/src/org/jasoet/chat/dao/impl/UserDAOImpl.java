package org.jasoet.chat.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import org.jasoet.chat.dao.UserDAO;
import org.jasoet.chat.model.User;
import org.jasoet.chat.util.EncriptionUtil;

public class UserDAOImpl implements UserDAO {

    private Connection connection;

    public UserDAOImpl(Connection connection) {
        this.connection = connection;
    }

    public List<User> getAll() throws SQLException {
        String sql = "SELECT o.id,o.username,o.password FROM users o;";
        PreparedStatement ps = connection.prepareStatement(sql);

        ResultSet rs = ps.executeQuery();
        List<User> data = new ArrayList<User>();

        while (rs.next()) {
            User d = new User();
            d.setId(rs.getInt("id"));
            d.setUsername(rs.getString("username"));
            d.setPassword(rs.getString("password"));
            data.add(d);
        }

        return data;

    }

    public User getByUsername(String username) throws SQLException {
        String sql = "SELECT o.id,o.username,o.password FROM users o WHERE o.username = ?";
        PreparedStatement ps = connection.prepareStatement(sql);
        ps.setString(1, username);

        ResultSet rs = ps.executeQuery();
        User data = null;

        if (rs.next()) {
            data = new User();
            data.setId(rs.getInt("id"));
            data.setUsername(rs.getString("username"));
            data.setPassword(rs.getString("password"));
        }

        return data;
    }

    public int insert(User d) throws SQLException {
        String sql = "INSERT INTO users (username,password) VALUES (?, ?);";
        PreparedStatement ps = connection.prepareStatement(sql);
        ps.setString(1, d.getUsername());
        ps.setString(2, EncriptionUtil.MD5MySQL(d.getPassword()));
        return ps.executeUpdate();
    }

    public int delete(int id) throws SQLException {
        String sql = "DELETE FROM user WHERE id=?";
        PreparedStatement ps = connection.prepareStatement(sql);
        ps.setInt(1, id);
        return ps.executeUpdate();
    }

    public int update(int id, User newUser) throws SQLException {
        String sql = "UPDATE users SET username=?,password=? WHERE id=?";
        PreparedStatement ps = connection.prepareStatement(sql);
        ps.setString(1, newUser.getUsername());
        ps.setString(2, EncriptionUtil.MD5MySQL(newUser.getPassword()));
        ps.setInt(3, id);
        return ps.executeUpdate();
    }

    public boolean isAuthenticate(String username, String password) throws SQLException {
        User u = this.getByUsername(username);

        if (u == null) {
            return false;
        }

        if (password.equals(u.getPassword())) {
            return true;
        } else {
            return false;
        }

    }
}
