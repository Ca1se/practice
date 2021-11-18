package sut.edu.db;

import java.sql.*;
import java.util.ArrayList;
import java.util.Map;

public class Database {
    private static Connection connection;
    private static Statement statement;

    public static void connect(String url, String name, String passwd) {
        try {
            Class.forName("org.mariadb.jdbc.Driver");
            connection = DriverManager.getConnection(url, name, passwd);
            statement = connection.createStatement();
        }catch(Exception e) {
            System.out.println("Database::connect: Failed to connect database");
            e.printStackTrace();
        }
    }

    public static ArrayList<String> getStringValue(String table, Map<String, String> judge, String fieldName) {
        ArrayList<String> list = new ArrayList<>();
        String query = String.format("select %s from %s where %s", fieldName, table, getCondition(judge));

        try {
            ResultSet res = statement.executeQuery(query);
            while(res.next()) {
                list.add(res.getString(fieldName));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    public static boolean deleteValue(String table, Map<String, String> judge) {
        String query = String.format("delete from %s where %s", table, getCondition(judge));

        try {
            statement.executeQuery(query);
        }catch(SQLException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean insertStringValue(String table, Map<String, String> value) {
        StringBuffer names = new StringBuffer();
        StringBuffer values = new StringBuffer();

        int cnt = 0;
        for(var it: value.entrySet()) {
            if(cnt != 0) {
                names.append(",").append(it.getKey());
                values.append(String.format(",'%s'", it.getValue()));
            }else {
                names.append(it.getKey());
                values.append(String.format("'%s'", it.getValue()));
                cnt++;
            }
        }
        String query = String.format("insert into %s (%s) values (%s)", table, names, values);

        try {
            statement.executeQuery(query);
        }catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean updateStringValue(String table, Map<String, String> judge, String field, String value) {
        String query = String.format("update %s set %s='%s' where %s", table, field, value, getCondition(judge));

        try {
            statement.executeQuery(query);
        }catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static void disconnect() {
        try {
            statement.close();
            connection.close();
        }catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static String getCondition(Map<String, String> judge) {
        StringBuffer stringBuffer = new StringBuffer();
        var set = judge.entrySet();
        int cnt = 0;
        for(var it: set) {
            if(cnt != 0) {
                stringBuffer.append(String.format(" and %s='%s'", it.getKey(), it.getValue()));
            }else {
                stringBuffer.append(String.format("%s='%s'", it.getKey(), it.getValue()));
                cnt++;
            }
        }
        return stringBuffer.toString();
    }

}
