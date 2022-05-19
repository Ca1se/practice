// check username is valid
function checkUsername(username) {
    const usernameRegex = /^[a-zA-Z][a-zA-Z0-9]{4,14}$/;
    return usernameRegex.test(username);
}

function checkPassword(password) {
    const passwordRegex = /^[a-zA-Z0-9_.]{8,20}$/;
    return passwordRegex.test(password);
}

$(function () {
    $('.login_form').submit(function (e) {
        e.preventDefault();
        let $username = $('#username').val();
        let $password = $('#password').val();
        if(!checkUsername($username)) {
            alert('用户名格式不正确。\n' +
                  '用户名长度为5-15位，由英文字母与数字构成，且首字母必须为字母。');
            return;
        }

        if(!checkPassword($password)) {
            alert('密码格式不正确。\n' +
                  "密码长度为8-20位，由英文字母、数字、英文句号与下划线构成。");
            return;
        }

        $.ajax({
            type: 'POST',
            url: '/demo_war_exploded/login',
            data: {
                username: null,
                password: $.md5($.md5($.md5($password, 'what'), 'the'), 'hell')
            },
            success: function (data) {
                alert(data);
            },
            error: function () {
                alert('error');
            }
        });

    });
});
