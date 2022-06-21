package com.wu.db;


import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

public class DBUtil {
    public static String DRIVER_CLASS;
    public static String URL;
    public static String USERNAME;
    public static String PASSWORD;

    static {
        try {
            Properties properties = new Properties();
            InputStream input = DBUtil.class.getClassLoader().
                    getResourceAsStream("database.properties");
            properties.load(input);
            DRIVER_CLASS = properties.getProperty("driver");
            URL          = properties.getProperty("url");
            USERNAME     = properties.getProperty("user");
            PASSWORD     = properties.getProperty("password");
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() {
        try {
            Class.forName(DRIVER_CLASS);
            return DriverManager.getConnection(URL, USERNAME, PASSWORD);
        }catch (Exception e) {
            e.printStackTrace();
        }

        return null;
    }
}