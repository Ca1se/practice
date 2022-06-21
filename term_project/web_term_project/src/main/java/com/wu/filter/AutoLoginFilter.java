package com.wu.filter;

import com.wu.dao.UserDao;
import com.wu.dao.UserDaoImpl;
import com.wu.domain.UserBean;
import com.wu.util.CookieUtil;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

@WebFilter(filterName = "AutoLoginFilter", urlPatterns = "/*")
public class AutoLoginFilter extends HttpFilter {
    @Override
    protected void doFilter(HttpServletRequest req, HttpServletResponse res, FilterChain chain) throws IOException, ServletException {
        UserBean user_bean = (UserBean) req.getSession().getAttribute("user");
        if(user_bean != null) {
            chain.doFilter(req, res);
        }else {
            Cookie[] cookies = req.getCookies();
            Cookie auto_login = CookieUtil.findCookie(cookies, "auto_login");
            if(auto_login == null) {
                chain.doFilter(req, res);
            }else {
                String[] info = auto_login.getValue().split("#");
                String username = info[0];
                String password = info[1];
                UserBean user = new UserBean();
                user.setUsername(username);
                user.setPassword(password);
                UserDao dao = new UserDaoImpl();
                try {
                    UserBean login = dao.login(user);
                    req.getSession().setAttribute("user", login);
                }catch (SQLException e) {
                    e.printStackTrace();
                }
                chain.doFilter(req, res);
            }
        }
    }
}
