package com.wu.dao;


import com.wu.db.DBUtil;
import com.wu.domain.UserBean;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDaoImpl implements UserDao {

    public ResultSet checkUsername(String username) throws SQLException {
        Connection conn = DBUtil.getConnection();

        String sql = "select * from user_info where username=?";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, username);
        return statement.executeQuery();
    }
    @Override
    public UserBean login(UserBean user) throws SQLException {
        UserBean ret = null;
        ResultSet result = checkUsername(user.getUsername());
        if(result.next()) {
            String password = result.getString("password");
            if(password.equals(user.getPassword())) {
                ret = new UserBean();
                ret.setId(result.getInt("id"));
                ret.setUsername(user.getUsername());
                ret.setPassword(password);
            }
        }

        return ret;
    }

    @Override
    public boolean register(UserBean user) throws SQLException {
        ResultSet result = checkUsername(user.getUsername());
        if(!result.next()) {
            Connection conn = DBUtil.getConnection();
            String sql = "insert into user_info (username, password) values (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassword());
            statement.executeUpdate();
            return true;
        }

        return false;
    }
}
