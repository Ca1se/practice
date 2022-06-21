package com.wu.dao;

import com.wu.domain.UserBean;

import java.sql.ResultSet;
import java.sql.SQLException;

public interface UserDao {
    public UserBean login(UserBean user) throws SQLException;
    public boolean register(UserBean user) throws  SQLException;
}
