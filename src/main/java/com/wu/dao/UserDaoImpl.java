package com.wu.dao;


import com.wu.db.DBUtil;
import com.wu.domain.UserBean;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDaoImpl implements UserDao {
    @Override
    public UserBean login(UserBean user) throws SQLException {
        Connection conn = DBUtil.getConnection();
        UserBean ret = null;

        String sql = "select * from user_info where username=?";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, user.getUsername());
        ResultSet result = statement.executeQuery();
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
}
