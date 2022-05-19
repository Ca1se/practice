package com.wu.dao;

import com.wu.domain.UserBean;

import java.sql.SQLException;

public interface UserDao {
    public UserBean login(UserBean user) throws SQLException;
}
