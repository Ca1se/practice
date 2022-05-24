<%@ page contentType="text/html; charset=UTF-8" %>
<!DOCTYPE html>
<html lang="zh">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Nice Paint - Login</title>
        <link rel="stylesheet" href="styles/login.css" type="text/css">
        <link rel="stylesheet" href="styles/global.css" type="text/css">
        <script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.6.0.min.js" type="text/javascript"></script>
        <script src="scripts/jquery.md5.js" type="text/javascript"></script>
        <script src="scripts/login.js" type="text/javascript"></script>
        <script type="text/javascript">
            function checkLogin() {
                location.href="index.html";
            }
            $(function () {
                autoLogin(checkLogin);
            });
        </script>
    </head>
    <body>
        <section>
            <div class="login_frame">
                <div class="logo"><a href="index.html"></a></div>
                <form class="login_form">
                    <input type="text" id="username" required="required" placeholder="用户名">
                    <input type="password" id="password" required="required" placeholder="密码">
                    <button class="login_btn" type="submit">登录</button>
                </form>
                <div class="hint"></div>
                <a class="button to_login" href="RegisterPage">还没有账号？点此注册</a>
            </div>
        </section>
        <footer>
            Web term project
        </footer>
    </body>
</html>