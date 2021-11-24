package sut.edu.system;

import sut.edu.db.Database;
import sut.edu.log.Logger;

import java.sql.SQLException;
import java.util.List;

public class Manager {
    private static final String kTableName = "user_info";
    private static final String kPrimaryKey = "user_name";
    
    private Database database;

    public Manager(Database db) {
        this.database = db;
    }

    public boolean AddUser(String name, String identity, String password) {
        try {
            database.CreateStringValueRow(
                    kTableName,
                    new String[] {
                            "user_name", "user_identity", "user_password"
                    },
                    new String[] {
                            name, identity, password
                    }
            );
            return true;
        }catch(SQLException e) {
            return false;
        }
    }

    public boolean DeleteUser(String name) {
        try {
            database.DeleteStringValueRowByPrimaryKey(
                kTableName, kPrimaryKey, name);
            return true;
        }catch(SQLException e) {
            return false;
        }
    }

    public boolean ChangeUserIdentity(String name, String identity) {
        try {
            database.UpdateStringValueRowByPrimaryKey(
                kTableName, kPrimaryKey, name, "user_identity", identity);
            return true;
        }catch(SQLException e) {
            return false;
        }
    }

    public boolean ChangeUserPassword(String name, String password) {
        try {
            database.UpdateStringValueRowByPrimaryKey(
                kTableName, kPrimaryKey, name, "user_password", password);
            return true;
        }catch(SQLException e) {
            return false;
        }
    }

    public String GetUserPassword(String name) {
        try {
            return database.RetrieveStringValueByPrimaryKey(
                kTableName, kPrimaryKey, name, "user_password");
        }catch(SQLException e) {
            return null;
        }
    }

    public String GetUserIdentity(String name) {
        try {
            return database.RetrieveStringValueByPrimaryKey(
                    kTableName, kPrimaryKey, name, "user_identity");
        }catch(SQLException e) {
            return null;
        }
    }
}
