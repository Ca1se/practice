package sut.edu.system;

import sut.edu.db.DBConnectionInfo;
import sut.edu.db.Database;
import sut.edu.log.Logger;

import java.sql.SQLException;
import java.util.HashMap;
import java.util.Objects;

public class Manager {
    private static final String HELP_INFO =
            "user and admin:\n" +
                    "   help -- display this info\n" +
                    "   getlog -- display all system log\n" +
                    "   exit -- quit this system\n" +
                    "admin:\n" +
                    "   adduser [user_name] [user_identity] [user_password] -- add a new user\n" +
                    "   deleteuser [user_name] -- delete a user\n" +
                    "   changepassword [user_name] [new_password] -- change the password of a user\n" +
                    "   changeidentity [user_name] [new_identity] -- change the level of a user, the level can be admin or user\n";
    private Database database;

    public Manager(Database db) {
        this.database = db;
    }

    public enum Identity {
        user("user"),
        admin("admin");

        private final String stringValue;

        public String getValue() {
            return stringValue;
        }

        Identity(String s) {
            stringValue = s;
        }
    }

    public void AddUser(String name, String identity, String password) {
        try {
            database.CreateStringValueRow(
                    "user_info",
                    new String[] {
                            "user_name", "user_identity", "user_password"
                    },
                    new String[] {
                            name, identity, password
                    }
            );
        }catch(SQLException e) {
            e.printStackTrace();
        }
    }
}
