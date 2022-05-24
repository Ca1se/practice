<%@ page contentType="text/html; charset=UTF-8" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Nice Paint - Register</title>
        <link rel="stylesheet" href="styles/login.css" type="text/css">
        <link rel="stylesheet" href="styles/global.css" type="text/css">
        <script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.6.0.min.js" type="text/javascript"></script>
        <script src="scripts/jquery.md5.js" type="text/javascript"></script>
        <script src="scripts/register.js" type="text/javascript"></script>
    </head>
    <body>
        <section>
            <div class="register_frame">
                <div class="logo"><a href="index.html"></a></div>
                <form class="login_form">
                    <input type="text" id="username" required="required" placeholder="用户名">
                    <input type="password" id="password" required="required" placeholder="密码">
                    <input type="password" id="pwd-again" required="required" placeholder="再次输入密码">
                    <button class="login_btn" type="submit">注册</button>
                </form>
                <div class="hint"></div>
                <a class="button to_login" href="LoginPage">已有账号？点此登录</a>
            </div>
        </section>
        <footer>
            Web term project
        </footer>
    </body>
</html>