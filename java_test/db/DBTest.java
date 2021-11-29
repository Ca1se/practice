package db;

import java.sql.Statement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DBTest {
    private static final String kUrl = "jdbc:mysql://localhost:3306/java_course";
    private static final String kUserName = "root";
    private static final String kPassword = "123456789";

    static {
        try {
            Class.forName("org.mariadb.jdbc.Driver");
        }catch(ClassNotFoundException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) throws SQLException {
        Connection connection = DriverManager
            .getConnection(kUrl, kUserName, kPassword);
        Statement statement = connection.createStatement();
        ResultSet res = statement.executeQuery(String.format("select * from user_info"));
        while(res.next()) {
            System.out.printf("%s %s %s", res.getString(1), res.getString(2));
        }
        statement.close();
        connection.close();
    }
}
