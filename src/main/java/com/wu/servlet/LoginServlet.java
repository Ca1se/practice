package com.wu.servlet;

import com.wu.dao.UserDao;
import com.wu.dao.UserDaoImpl;
import com.wu.domain.UserBean;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

@WebServlet(name = "LoginServlet", urlPatterns = "/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            String username = req.getParameter("username");
            String password = req.getParameter("password");

            UserBean user = new UserBean();
            user.setUsername(username);
            user.setPassword(password);
            UserDao dao = new UserDaoImpl();
            UserBean login = dao.login(user);
            if(login != null) {
                Cookie cookie = new Cookie("auto_login", username + "#" + password);
                cookie.setMaxAge(60 * 60 * 24 * 7);
                cookie.setPath(req.getContextPath());
                resp.addCookie(cookie);
                req.getSession().setAttribute("user", login);
                resp.sendRedirect("pages/myfile.html");
            }else {
                req.setAttribute("errorInfo", "用户名或密码不正确");
                req.getRequestDispatcher("WEB-INF/pages/login.jsp").forward(req, resp);
            }

        }catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
