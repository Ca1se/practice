$(document).ready(function () {
    $('#btn_register').click(function () {
        var user_name = $('#username').val();
        var password = $('#password').val();
        var rpassword = $('#rpassword').val();
        if(user_name === '') {
            alert('用户名为空!');
            return;
        }else if(password === '') {
            alert('密码为空!');
            return;
        }else if(rpassword !== password) {
            alert('两次输入密码不一致');
            return;
        }
        
        var form_data = {
            id: 0,
            username: user_name,
            password: password.hashCode(),
        };

        $.ajax({
            type: "POST",
            url: "/register",
            data: JSON.stringify(form_data),
            success: function (response) {
                alert(response);
            },
            error: function (xhr) {
                var text = xhr.responseText;
                alert(text.substring(text.indexOf('message') + 8));
            }
        });
    });
});

String.prototype.hashCode = function() {
    var hash = 0;
    if (this.length == 0) {
        return hash;
    }
    for (var i = 0; i < this.length; i++) {
        char = this.charCodeAt(i);
        hash = ((hash<<5)-hash)+char;
        hash = hash & hash; // Convert to 32bit integer
    }
    return hash + '';
}