/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.jasoet.chat.db;

import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

/**
 *
 * @author jasoet
 */
public class DatabaseConnection {

    private Connection connection = null;
    private static DatabaseConnection staticObject = null;
    private Properties properties;

    public DatabaseConnection() {
        try {
            properties = new Properties();
            InputStream konfigurasi = getClass().getResourceAsStream("config.properties");
            properties.load(konfigurasi);

            Class.forName(properties.getProperty("jdbc.driver")).newInstance();
        } catch (IOException ex) {
            ex.printStackTrace();
        } catch (InstantiationException ex) {
            ex.printStackTrace();
        } catch (IllegalAccessException ex) {
            ex.printStackTrace();
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
    }

    public static DatabaseConnection getInstance() {
        DatabaseConnection conn = null;
        try {
            if (staticObject == null) {
                staticObject = new DatabaseConnection();
                conn = staticObject;
            } else if (staticObject.getConnection().isClosed()) {
                staticObject = new DatabaseConnection();
                conn = staticObject;
            } else {
                conn = staticObject;
            }
            return conn;
        } catch (SQLException ex) {
            ex.printStackTrace();
            return null;
        }
    }

    public void closeConnection() throws SQLException {
        this.connection.close();
    }

    public Connection getConnection() throws SQLException {
        if (this.connection == null) {
            this.connection = DriverManager.getConnection(properties.getProperty("jdbc.url"),
                    properties.getProperty("jdbc.username"), properties.getProperty("jdbc.password"));
        }
        return this.connection;
    }
}
