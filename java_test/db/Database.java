package db;

import java.lang.ClassNotFoundException;
import java.lang.IllegalArgumentException;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

import javax.xml.crypto.Data;

import java.sql.Connection;
import java.sql.ResultSet;


public class Database {
    private static Statement statement;
    private static Connection connection;

    static {
        try {
            Class.forName("org.mariadb.jdbc.Driver");
        }catch(ClassNotFoundException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public Database(DBConnectionInfo info)
            throws SQLException {
        connection = DriverManager.getConnection(
                info.getUrl(), info.getUserName(), info.getPassword());
        statement = connection.createStatement();
    }

    public synchronized String
    RetrieveStringValueByPrimaryKey(
            String tableName, String keyName,
            String keyValue, String queryName
            )throws SQLException {
        ResultSet res = statement.executeQuery(
                String.format("select %s from %s where %s='%s'",
                queryName, tableName, keyName, keyValue));
        
        if(res.next()) {
            return res.getString(queryName);
        }else {
            return null;
        }
    }

    public synchronized void
    CreateStringValueRow(
            String tableName, String[] names,
            String[] values)
            throws SQLException {

        if(names.length <= 0 || values.length <= 0
                || names.length != values.length) {
            throw new IllegalArgumentException();
        }

        StringBuilder nameSeq = new StringBuilder();
        StringBuilder valueSeq = new StringBuilder();

        for(int i = 0; i < names.length - 1; i++) {
            nameSeq.append(names[i]).append(',');
        }
        nameSeq.append(names[names.length - 1]);

        for(int i = 0; i < values.length - 1; i++) {
            valueSeq.append(String.format("'%s',", values[i]));
        }
        valueSeq.append(String.format("'%s'", values[values.length - 1]));

        statement.executeQuery(
                String.format("insert into %s (%s) values (%s)",
                tableName, nameSeq.toString(), valueSeq.toString()));
    }

    public synchronized void
    DeleteStringValueRowByPrimaryKey(
            String tableName, String keyName,
            String keyValue)
            throws SQLException {
        statement.executeQuery(
                String.format("delete from %s where %s='%s'",
                tableName, keyName, keyValue));
    }

    public synchronized void
    UpdateStringValueRowByPrimaryKey(
            String tableName, String keyName,
            String keyValue, String queryName,
            String queryValue)
            throws SQLException {
        statement.executeQuery(
                String.format("update %s set %s='%s' where %s='%s'",
                tableName, queryName, queryValue, keyName, keyValue));
    }

    public synchronized void Close() throws SQLException {
        statement.close();
        connection.close();
    }

    public static void main(String[] args) {
        Database database = new Database(new DBConnectionInfo());
    }
}
